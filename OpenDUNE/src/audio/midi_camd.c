/** @file src/audio/midi_none.c In case no MIDI is selected, create an empty
 *  one, which ignores all input */


#include <string.h>

#include "types.h"
#include "midi.h"
#include "../os/error.h"

// Amiga includes.
#include <proto/exec.h>

#include <midi/camd.h>
#include <inline/camd.h>

#include "../inifile.h"

struct Library *CamdBase = NULL;

static struct MidiNode *s_midi_node = NULL;
static struct MidiLink *s_midi_link = NULL;



static char *getDeviceName() {
	char *retname = NULL;

	APTR key = LockCAMD(CD_Linkages);
	if (key != NULL) {
		struct MidiCluster *cluster = NextCluster(NULL);

		while (cluster && !retname) {
			// Get the current cluster name
			char *dev = cluster->mcl_Node.ln_Name;

			if (strstr(dev, "out") != NULL) {
				// This is an output device, return this
				retname = dev;
			} else {
				// Search the next one
				cluster = NextCluster(cluster);
			}
		}

		UnlockCAMD(key);
	}
 
	return retname;
}

static inline uint32 READ_LE_UINT32(const void *ptr) {
	const uint8 *b = (const uint8 *)ptr;
	return (b[3] << 24) | (b[2] << 16) | (b[1] << 8) | (b[0]);
} 

bool midi_init(void)
{
    if (IniFile_GetInteger("camdmidi", 0) != 0) {
        CamdBase = OpenLibrary("camd.library", 0L);
    	if (!CamdBase) {
    		Error("Could not open 'camd.library'\n");
    		return false;
    	}
    
    	s_midi_node = CreateMidi(MIDI_MsgQueue, 0L, MIDI_SysExSize, 4096L, MIDI_Name, (ULONG)"Dune2 CAMD", TAG_END);
    	if (!s_midi_node) {
    		midi_uninit();
    		Error("Could not create CAMD MIDI node\n");
    		return false;
    	}
    
    	char *devicename = getDeviceName();
    	if (!devicename) {
    		midi_uninit();
    		Error("Could not find a CAMD output device\n");
    		return false;
    	}
    
        s_midi_link = AddMidiLink(s_midi_node, MLTYPE_Sender,
                                 MLINK_Priority,  21,
                                 MLINK_Private,  TRUE,
                                 MLINK_Location, (ULONG)devicename,
                                 TAG_END);
    
    	if (!s_midi_link) {
    		midi_uninit();
    		Error("Could not create CAMD MIDI link to %s\n", devicename);
    		return false;
    	}
    
        // All good to go...
    	return true;
    } else {
        return false;
    }
}

void midi_uninit(void)
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

void midi_send(uint32 data)
{
	if (s_midi_link) {
        ULONG convertedData = READ_LE_UINT32(&data);
        	
        PutMidi(s_midi_link, convertedData);
    }	
}
 
uint16 midi_send_string(uint8 * data, uint16 len)
{
	if (s_midi_link) {
        PutSysEx(s_midi_link, data);
    }
    
	return len;
}

void midi_reset(void)
{
    // Not used.
}
