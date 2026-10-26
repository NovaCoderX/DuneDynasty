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

#ifndef XMIPLAYER_H
#define XMIPLAYER_H

#include <FileClasses/music/MusicPlayer.h>

#include <SDL.h>
#include <string>

// Forward declaration - Ryan Nunn's XMIDI converter event type
struct midi_event;

/*
    XMI music player that routes converted MIDI events to CAMD
    (camd.library) on AmigaOS, playing on real or virtual MIDI
    hardware instead of synthesising via FluidSynth.

    Supports both Dune 2 MIDI variants:
      - General MIDI  : DUNEx.C55 files (authored for the Roland SC-55)
      - MT-32         : DUNEx.XMI files (authored for the Roland MT-32)

    In MT-32 mode the DUNEINIT.XMI setup song (a timed sequence of
    MT-32 SysEx timbre/patch uploads) is played once, synchronously,
    before any music - mirroring OpenDUNE's Music_InitMT32().
*/
class XMIPlayer : public MusicPlayer {
public:
    /**
        Constructor.
        \param useMT32  true  = MT-32 mode: play DUNEx.XMI files and run
                                the DUNEINIT.XMI setup sequence first.
                        false = General MIDI mode: play DUNEx.C55 files
                                (default; correct for SC-55/GM devices).
    */
    explicit XMIPlayer(bool useMT32 = false);
    virtual ~XMIPlayer();

    /*!
        change type of current music
        @param musicType type of music to be played
    */
    void changeMusic(MUSICTYPE musicType);

    /*!
        Toggle the music on and off
    */
    void toggleSound();

    /**
        Returns whether music is currently being played
        \return true = currently playing, false = not playing
    */
    bool isMusicPlaying();

    /*!
        turns music playing on or off
        @param value when true the function turns music on
    */
    void setMusic(bool value);

    /**
        Sets the volume of the music channel
        \param  newVolume   the new volume [0;MIX_MAX_VOLUME]
    */
    virtual void setMusicVolume(int newVolume);

private:
    /* File extension for the active MIDI format ("XMI" or "C55"). */
    const char* musicFileExtension() const;

    /* Play the MT-32 setup song DUNEINIT.XMI once and wait for it
       to complete. Called from the constructor in MT-32 mode. */
    void playMT32InitSequence();

    /* Stop the playback thread (if running), silence the synth,
       and free the current event list. */
    void stopPlayback();

    /* Load the given XMI/C55 file/track, convert to a MIDI event
       list and start the playback thread.
       loop = true  -> restart the song at End of Track (music)
       loop = false -> thread exits at End of Track (init sequence) */
    bool startPlayback(const std::string& filename, int track, bool loop);

    /* Playback thread entry point (SDL thread). */
    static int playbackThreadEntry(void *data);
    void playbackLoop();

    /* Scale a MIDI channel volume (CC7) value by musicVolume. */
    Uint8 scaleVolume(Uint8 midiVolume) const;

    bool             useMT32;           /* MT-32 (.XMI) vs GM (.C55)  */

    midi_event      *eventList;         /* converted MIDI event list  */
    int              ppqn;              /* pulses per quarter note    */
    bool             loopCurrentSong;   /* set before thread starts   */

    SDL_Thread      *playbackThread;
    SDL_atomic_t     threadRunning;     /* 1 while thread active      */
    SDL_atomic_t     stopRequested;     /* 1 = thread should exit     */
    SDL_atomic_t     atomicVolume;      /* current music volume, read
                                           by the playback thread     */

    bool             camdReady;         /* CAMD link established      */

    /* Last CC7 (channel volume) value seen per MIDI channel, before
       scaling - used to re-apply volume when setMusicVolume changes. */
    Uint8            channelVolume[16];
};

#endif // XMIPLAYER_H
