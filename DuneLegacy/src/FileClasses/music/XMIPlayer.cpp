/*
 *  This file is part of Dune Legacy.
 *
 *  Dune Legacy is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Dune Legacy is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Dune Legacy.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <FileClasses/music/XMIPlayer.h>

#include <globals.h>

#include <FileClasses/FileManager.h>
#include <FileClasses/xmidi/xmidi.h>
#include <FileClasses/xmidi/databuf.h>
#include <FileClasses/music/CAMDMidi.h>

#include <misc/exceptions.h>
#include <mmath.h>

#include <SDL_rwops.h>





/* Default MIDI tempo: 500000 microseconds per quarter note (120 BPM) */
#define DEFAULT_TEMPO_US    500000

XMIPlayer::XMIPlayer(bool useMT32)
 : MusicPlayer(settings.audio.playMusic, settings.audio.musicVolume), useMT32(useMT32) {
    eventList = nullptr;
    ppqn = 60;
    loopCurrentSong = true;
    playbackThread = nullptr;

    SDL_Log("XMIPlayer: %s mode", useMT32 ? "MT-32" : "General MIDI");

    SDL_AtomicSet(&threadRunning, 0);
    SDL_AtomicSet(&stopRequested, 0);
    SDL_AtomicSet(&atomicVolume, musicVolume);

    for (int i = 0; i < 16; i++) {
        channelVolume[i] = 127;     /* MIDI default full channel volume */
    }

    camdReady = (CAMD_Init() != 0);
    if (!camdReady) {
        SDL_Log("XMIPlayer: CAMD initialisation failed - no MIDI output device");
        return;
    }

    if (useMT32) {
        playMT32InitSequence();
    }
}

XMIPlayer::~XMIPlayer() {
    stopPlayback();
    CAMD_Uninit();
}

const char* XMIPlayer::musicFileExtension() const {
    return useMT32 ? "XMI" : "C55";
}

void XMIPlayer::playMT32InitSequence() {
    /* DUNEINIT.XMI is the MT-32 setup song: a timed XMIDI sequence of
       SysEx timbre/patch uploads. The inter-event timing is intentional
       (the MT-32 needs processing gaps between SysEx bursts), so it is
       played through the normal playback path - once, not looped - and
       we block until it completes so the instruments are configured
       before any music starts. Mirrors OpenDUNE's Music_InitMT32(). */

    SDL_Log("XMIPlayer: Uploading MT-32 instrument setup (DUNEINIT.XMI)...");

    if (startPlayback("DUNEINIT.XMI", 0, false)) {
        /* Wait for the init song to finish. stopPlayback() joins the
           thread (already exited or about to) and frees the list. */
        while (SDL_AtomicGet(&threadRunning) != 0) {
            SDL_Delay(50);
        }
        stopPlayback();
        SDL_Log("XMIPlayer: MT-32 setup complete");
    } else {
        SDL_Log("XMIPlayer: MT-32 setup skipped (DUNEINIT.XMI not available)");
    }
}

Uint8 XMIPlayer::scaleVolume(Uint8 midiVolume) const {
    int vol = SDL_AtomicGet(const_cast<SDL_atomic_t*>(&atomicVolume));
    int scaled = ((int)midiVolume * vol) / MIX_MAX_VOLUME;
    if (scaled > 127) scaled = 127;
    if (scaled < 0)   scaled = 0;
    return (Uint8)scaled;
}

int XMIPlayer::playbackThreadEntry(void *data) {
    static_cast<XMIPlayer*>(data)->playbackLoop();
    return 0;
}

void XMIPlayer::playbackLoop() {
    Uint32 tempo_us = DEFAULT_TEMPO_US;

    midi_event *event = eventList;
    int lastTime = 0;

    while (SDL_AtomicGet(&stopRequested) == 0) {

        if (event == nullptr) {
            /* End of track reached */
            if (!loopCurrentSong) {
                /* One-shot playback (MT-32 init sequence) - done */
                break;
            }

            /* Looping music: silence hanging notes, restart from the top */
            CAMD_AllNotesOff();
            event = eventList;
            lastTime = 0;
            tempo_us = DEFAULT_TEMPO_US;
            continue;
        }

        /* Wait for this event's timestamp. midi_event.time is in ticks
           at ppqn resolution; tempo gives microseconds per quarter. */
        int deltaTicks = event->time - lastTime;
        if (deltaTicks > 0) {
            Uint32 waitMs = (Uint32)(((Uint64)deltaTicks * tempo_us) / ((Uint64)ppqn * 1000));

            /* Sleep in small slices so a stop request is honoured quickly */
            while (waitMs > 0 && SDL_AtomicGet(&stopRequested) == 0) {
                Uint32 slice = (waitMs > 20) ? 20 : waitMs;
                SDL_Delay(slice);
                waitMs -= slice;
            }

            if (SDL_AtomicGet(&stopRequested) != 0) {
                break;
            }
        }
        lastTime = event->time;

        const Uint8 status = event->status;
        const Uint8 type   = status & 0xF0;

        if (status == 0xFF) {
            /* Meta event. data[0] = meta type, buffer = content */
            if (event->data[0] == 0x51 && event->buffer != nullptr && event->len >= 3) {
                /* Set Tempo: 3 bytes, microseconds per quarter note */
                tempo_us = ((Uint32)event->buffer[0] << 16) |
                           ((Uint32)event->buffer[1] <<  8) |
                            (Uint32)event->buffer[2];
            }
            else if (event->data[0] == 0x2F) {
                /* End of Track - advance to nullptr, handled above */
                event = event->next;
                continue;
            }
            /* All other meta events (track name etc.) are ignored */
        }
        else if (status == 0xF0 || status == 0xF7) {
            /* SysEx. The xmidi converter stores the payload in buffer.
               CAMD's PutSysEx expects a full 0xF0 ... 0xF7 stream.
               (In MT-32 mode this path carries the DUNEINIT timbre
               uploads and any in-song patch changes.) */
            if (event->buffer != nullptr && event->len > 0 && event->buffer[0] == 0xF0) {
                CAMD_SendSysEx(event->buffer);
            }
        }
        else if (type == 0xB0 && event->data[0] == 7) {
            /* Channel Volume (CC7): remember the track's intended level
               and send the version scaled by the game music volume. */
            int channel = status & 0x0F;
            channelVolume[channel] = event->data[1];
            CAMD_SendMidi(status, 7, scaleVolume(event->data[1]));
        }
        else if (type == 0xC0 || type == 0xD0) {
            /* Two-byte messages: Program Change / Channel Pressure */
            CAMD_SendMidi(status, event->data[0], 0);
        }
        else {
            /* All other three-byte channel messages:
               Note Off/On, Aftertouch, Controller, Pitch Wheel */
            CAMD_SendMidi(status, event->data[0], event->data[1]);
        }

        event = event->next;
    }

    /* Thread exiting: make sure nothing keeps sounding */
    CAMD_AllNotesOff();
    SDL_AtomicSet(&threadRunning, 0);
}

void XMIPlayer::stopPlayback() {
    if (playbackThread != nullptr) {
        SDL_AtomicSet(&stopRequested, 1);
        SDL_WaitThread(playbackThread, nullptr);
        playbackThread = nullptr;
    }
    SDL_AtomicSet(&stopRequested, 0);

    if (eventList != nullptr) {
        XMIDI::DeleteEventList(eventList);
        eventList = nullptr;
    }
}

bool XMIPlayer::startPlayback(const std::string& filename, int track, bool loop) {
    if (!camdReady) {
        return false;
    }

    stopPlayback();

    /* Load the file completely into memory from the PAK */
    SDL_RWops* rwop = pFileManager->openFile(filename);
    if (rwop == nullptr) {
        SDL_Log("XMIPlayer: Cannot open %s!", filename.c_str());
        return false;
    }

    Sint64 fileSize = SDL_RWsize(rwop);
    if (fileSize <= 0) {
        SDL_RWclose(rwop);
        SDL_Log("XMIPlayer: Invalid size for %s!", filename.c_str());
        return false;
    }

    char* fileData = new char[(size_t)fileSize];
    if (SDL_RWread(rwop, fileData, 1, (size_t)fileSize) != (size_t)fileSize) {
        delete [] fileData;
        SDL_RWclose(rwop);
        SDL_Log("XMIPlayer: Read error on %s!", filename.c_str());
        return false;
    }
    SDL_RWclose(rwop);

    /* Convert XMIDI -> MIDI event list using Ryan Nunn's converter.
       Both .XMI (MT-32) and .C55 (GM) variants are the same XMIDI
       container format - only the instrument targeting differs. */
    {
        BufferDataSource source(fileData, (unsigned int)fileSize);
        XMIDI xmidi(&source, XMIDI_CONVERT_NOCONVERSION);

        if (track < 0 || track >= xmidi.number_of_tracks()) {
            SDL_Log("XMIPlayer: Track %d out of range for %s!", track, filename.c_str());
            delete [] fileData;
            return false;
        }

        if (xmidi.retrieve((unsigned int)track, &eventList, ppqn) == 0 || eventList == nullptr) {
            SDL_Log("XMIPlayer: Conversion of %s track %d failed!", filename.c_str(), track);
            delete [] fileData;
            eventList = nullptr;
            return false;
        }
    }

    delete [] fileData;     /* converter copied what it needs */

    /* Reset per-channel volume tracking for the new song */
    for (int i = 0; i < 16; i++) {
        channelVolume[i] = 127;
    }

    loopCurrentSong = loop;

    /* Start the playback thread */
    SDL_AtomicSet(&stopRequested, 0);
    SDL_AtomicSet(&threadRunning, 1);

    playbackThread = SDL_CreateThread(playbackThreadEntry, "XMIPlayer", this);
    if (playbackThread == nullptr) {
        SDL_AtomicSet(&threadRunning, 0);
        XMIDI::DeleteEventList(eventList);
        eventList = nullptr;
        SDL_Log("XMIPlayer: Could not create playback thread!");
        return false;
    }

    return true;
}

void XMIPlayer::changeMusic(MUSICTYPE musicType) {
    int fileNum = -1;
    int musicNum = -1;

    if ((currentMusicType == musicType) && isMusicPlaying()) {
        return;
    }

    /* Same file/track mapping as ADLPlayer - the XMI and C55 files
       parallel the ADL files with identical numbering and tracks. */
    switch (musicType) {
        case MUSIC_ATTACK: {
            switch (getRandomInt(0, 5)) {
                case 0:     fileNum = 10;   musicNum = 7;   break;
                case 1:     fileNum = 11;   musicNum = 7;   break;
                case 2:     fileNum = 12;   musicNum = 7;   break;
                case 3:     fileNum = 13;   musicNum = 7;   break;
                case 4:     fileNum = 14;   musicNum = 7;   break;
                case 5:     fileNum = 15;   musicNum = 7;   break;
            }
        } break;

        case MUSIC_PEACE: {
            switch (getRandomInt(0, 8)) {
                case 0:     fileNum = 1;    musicNum = 6;   break;
                case 1:     fileNum = 2;    musicNum = 6;   break;
                case 2:     fileNum = 3;    musicNum = 6;   break;
                case 3:     fileNum = 4;    musicNum = 6;   break;
                case 4:     fileNum = 5;    musicNum = 6;   break;
                case 5:     fileNum = 6;    musicNum = 6;   break;
                case 6:     fileNum = 9;    musicNum = 4;   break;
                case 7:     fileNum = 9;    musicNum = 5;   break;
                case 8:     fileNum = 18;   musicNum = 6;   break;
            }
        } break;

        case MUSIC_INTRO:       fileNum = 0;    musicNum = 2;   break;
        case MUSIC_MENU:        fileNum = 7;    musicNum = 6;   break;
        case MUSIC_BRIEFING_H:  fileNum = 7;    musicNum = 2;   break;
        case MUSIC_BRIEFING_A:  fileNum = 7;    musicNum = 3;   break;
        case MUSIC_BRIEFING_O:  fileNum = 7;    musicNum = 4;   break;
        case MUSIC_WIN_H:       fileNum = 8;    musicNum = 3;   break;
        case MUSIC_WIN_A:       fileNum = 8;    musicNum = 2;   break;
        case MUSIC_WIN_O:       fileNum = 17;   musicNum = 4;   break;
        case MUSIC_LOSE_H:      fileNum = 1;    musicNum = 4;   break;
        case MUSIC_LOSE_A:      fileNum = 1;    musicNum = 5;   break;
        case MUSIC_LOSE_O:      fileNum = 1;    musicNum = 3;   break;
        case MUSIC_GAMESTAT:    fileNum = 20;   musicNum = 2;   break;
        case MUSIC_MAPCHOICE:   fileNum = 16;   musicNum = 7;   break;
        case MUSIC_MEANWHILE:   fileNum = 16;   musicNum = 8;   break;
        case MUSIC_FINALE_H:    fileNum = 19;   musicNum = 4;   break;
        case MUSIC_FINALE_A:    fileNum = 19;   musicNum = 2;   break;
        case MUSIC_FINALE_O:    fileNum = 19;   musicNum = 3;   break;

        case MUSIC_RANDOM:
        default: {
            switch (getRandomInt(0, 14)) {
                /* attack */
                case 0:     fileNum = 10;   musicNum = 7;   break;
                case 1:     fileNum = 11;   musicNum = 7;   break;
                case 2:     fileNum = 12;   musicNum = 7;   break;
                case 3:     fileNum = 13;   musicNum = 7;   break;
                case 4:     fileNum = 14;   musicNum = 7;   break;
                case 5:     fileNum = 15;   musicNum = 7;   break;
                /* peace */
                case 6:     fileNum = 1;    musicNum = 6;   break;
                case 7:     fileNum = 2;    musicNum = 6;   break;
                case 8:     fileNum = 3;    musicNum = 6;   break;
                case 9:     fileNum = 4;    musicNum = 6;   break;
                case 10:    fileNum = 5;    musicNum = 6;   break;
                case 11:    fileNum = 6;    musicNum = 6;   break;
                case 12:    fileNum = 9;    musicNum = 4;   break;
                case 13:    fileNum = 9;    musicNum = 5;   break;
                case 14:    fileNum = 18;   musicNum = 6;   break;
            }
        } break;
    }

    currentMusicType = musicType;

    if (musicOn && fileNum >= 0 && musicNum >= 0) {
        std::string filename = "DUNE" + std::to_string(fileNum) + "." + musicFileExtension();

        if (startPlayback(filename, musicNum, true)) {
            SDL_Log("Now playing %s (track %d)!", filename.c_str(), musicNum);
        } else {
            SDL_Log("Unable to play %s (track %d)!", filename.c_str(), musicNum);
        }
    }
}

void XMIPlayer::toggleSound() {
    if (!musicOn) {
        musicOn = true;
        currentMusicType = MUSIC_RANDOM;    /* force restart */
        changeMusic(MUSIC_PEACE);
    } else {
        musicOn = false;
        stopPlayback();
    }
}

bool XMIPlayer::isMusicPlaying() {
    return (SDL_AtomicGet(&threadRunning) != 0);
}

void XMIPlayer::setMusic(bool value) {
    musicOn = value;

    if (musicOn) {
        changeMusic(MUSIC_RANDOM);
    } else {
        stopPlayback();
    }
}

void XMIPlayer::setMusicVolume(int newVolume) {
    MusicPlayer::setMusicVolume(newVolume);
    SDL_AtomicSet(&atomicVolume, musicVolume);

    /* Re-apply the scaled channel volumes immediately so a volume
       change is audible without waiting for the next CC7 in the song */
    if (isMusicPlaying()) {
        for (int ch = 0; ch < 16; ch++) {
            CAMD_SendMidi((Uint8)(0xB0 | ch), 7, scaleVolume(channelVolume[ch]));
        }
    }
}
