/*
 *  Minimal CAMD MIDI output backend for Dune Legacy on AmigaOS 3
 *
 *  Adapted from the OpenDUNE AmigaOS CAMD driver (midi_camd.c).
 *
 *  Differences from the OpenDUNE version:
 *   - No IniFile dependency; caller decides whether to init.
 *   - Direct CAMD message packing: PutMidi() expects the message as
 *       (status << 24) | (data1 << 16) | (data2 << 8)
 *     (This is exactly what the OpenDUNE READ_LE_UINT32() conversion
 *      produced from the DOS little-endian dword convention.)
 *   - Added CAMD_AllNotesOff() for clean playback stop.
 */

#include <FileClasses/music/CAMDMidi.h>
#include <string.h>

#include <proto/exec.h>
#include <midi/camd.h>
#include <inline/camd.h>


struct Library *CamdBase = NULL;

static struct MidiNode *s_midi_node = NULL;
static struct MidiLink *s_midi_link = NULL;

static char *getDeviceName(void)
{
    char *retname = NULL;

    APTR key = LockCAMD(CD_Linkages);
    if (key != NULL) {
        struct MidiCluster *cluster = NextCluster(NULL);

        while (cluster && !retname) {
            char *dev = cluster->mcl_Node.ln_Name;

            if (strstr(dev, "out") != NULL) {
                /* This is an output device, use it */
                retname = dev;
            } else {
                cluster = NextCluster(cluster);
            }
        }

        UnlockCAMD(key);
    }

    return retname;
}

int CAMD_Init(void)
{
    char *devicename;

    if (s_midi_link) {
        return 1;   /* already initialised */
    }

    CamdBase = OpenLibrary("camd.library", 0L);
    if (!CamdBase) {
        return 0;
    }

    s_midi_node = CreateMidi(MIDI_MsgQueue, 0L,
                             MIDI_SysExSize, 4096L,
                             MIDI_Name, (ULONG)"DuneLegacy CAMD",
                             TAG_END);
    if (!s_midi_node) {
        CAMD_Uninit();
        return 0;
    }

    devicename = getDeviceName();
    if (!devicename) {
        CAMD_Uninit();
        return 0;
    }

    s_midi_link = AddMidiLink(s_midi_node, MLTYPE_Sender,
                              MLINK_Priority, 21,
                              MLINK_Private,  TRUE,
                              MLINK_Location, (ULONG)devicename,
                              TAG_END);
    if (!s_midi_link) {
        CAMD_Uninit();
        return 0;
    }

    return 1;
}

void CAMD_Uninit(void)
{
    if (s_midi_link) {
        RemoveMidiLink(s_midi_link);
        s_midi_link = NULL;
    }

    if (s_midi_node) {
        DeleteMidi(s_midi_node);
        s_midi_node = NULL;
    }

    if (CamdBase) {
        CloseLibrary(CamdBase);
        CamdBase = NULL;
    }
}

int CAMD_IsReady(void)
{
    return (s_midi_link != NULL) ? 1 : 0;
}

void CAMD_SendMidi(unsigned char status, unsigned char data1, unsigned char data2)
{
    if (s_midi_link) {
        ULONG msg = ((ULONG)status << 24) |
                    ((ULONG)data1  << 16) |
                    ((ULONG)data2  <<  8);

        PutMidi(s_midi_link, msg);
    }
}

void CAMD_SendSysEx(unsigned char *data)
{
    if (s_midi_link) {
        PutSysEx(s_midi_link, data);
    }
}

void CAMD_AllNotesOff(void)
{
    int ch;

    if (!s_midi_link) {
        return;
    }

    for (ch = 0; ch < 16; ch++) {
        unsigned char status = (unsigned char)(0xB0 | ch);  /* Controller */

        CAMD_SendMidi(status, 120, 0);   /* All Sound Off        */
        CAMD_SendMidi(status, 123, 0);   /* All Notes Off        */
        CAMD_SendMidi(status,  64, 0);   /* Sustain Pedal Off    */
        CAMD_SendMidi(status, 121, 0);   /* Reset All Controllers */
    }
}
