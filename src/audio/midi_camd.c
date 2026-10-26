/** @file src/audio/midi_camd.c MIDI output through CAMD on AmigaOS.
 *
 * Sends to the first CAMD cluster with "out" in its name: a MIDI
 * interface (e.g. camdusbmidi.out.0, mmp.out.0) or a software synth.
 * Adapted from the OpenDUNE and Dune Legacy 68k ports.
 */

#include <stdlib.h>
#include <string.h>

#include <proto/exec.h>
#include <midi/camd.h>
#include <inline/camd.h>

#include "types.h"
#include "midi.h"
#include "../os/error.h"

struct Library *CamdBase = NULL;

static struct MidiNode *s_midi_node = NULL;
static struct MidiLink *s_midi_link = NULL;

static bool midi_find_output(char *name, size_t len)
{
	struct MidiCluster *cluster;
	bool found = false;
	APTR key = LockCAMD(CD_Linkages);

	if (key == NULL) return false;

	for (cluster = NextCluster(NULL); cluster != NULL; cluster = NextCluster(cluster)) {
		const char *dev = cluster->mcl_Node.ln_Name;

		if (strstr(dev, "out") != NULL) {
			/* Copy it: the cluster can go away once CAMD is unlocked. */
			strncpy(name, dev, len - 1);
			name[len - 1] = '\0';
			found = true;
			break;
		}
	}

	UnlockCAMD(key);
	return found;
}

/* CAMD takes a short message as status << 24 | data1 << 16 | data2 << 8. */
static void midi_put(uint8 status, uint8 data1, uint8 data2)
{
	PutMidi(s_midi_link, ((ULONG)status << 24) | ((ULONG)data1 << 16) | ((ULONG)data2 << 8));
}

bool midi_init(void)
{
	char device[128];

	CamdBase = OpenLibrary("camd.library", 0L);
	if (CamdBase == NULL) {
		Error("Could not open camd.library\n");
		return false;
	}

	s_midi_node = CreateMidi(MIDI_MsgQueue, 0L, MIDI_SysExSize, 4096L, MIDI_Name, (ULONG)"Dune Dynasty", TAG_END);
	if (s_midi_node == NULL) {
		midi_uninit();
		Error("Could not create CAMD MIDI node\n");
		return false;
	}

	if (!midi_find_output(device, sizeof(device))) {
		midi_uninit();
		Error("Could not find a CAMD output device\n");
		return false;
	}

	s_midi_link = AddMidiLink(s_midi_node, MLTYPE_Sender,
	                          MLINK_Priority, 21,
	                          MLINK_Private, TRUE,
	                          MLINK_Location, (ULONG)device,
	                          TAG_END);
	if (s_midi_link == NULL) {
		midi_uninit();
		Error("Could not create CAMD MIDI link to %s\n", device);
		return false;
	}

	/* CAMD nodes and links outlive the process, and several error paths
	 * call exit() without shutting audio down. */
	atexit(midi_uninit);
	return true;
}

void midi_uninit(void)
{
	if (s_midi_link != NULL) {
		midi_reset();
		RemoveMidiLink(s_midi_link);
		s_midi_link = NULL;
	}

	if (s_midi_node != NULL) {
		DeleteMidi(s_midi_node);
		s_midi_node = NULL;
	}

	if (CamdBase != NULL) {
		CloseLibrary(CamdBase);
		CamdBase = NULL;
	}
}

void midi_send(uint32 data)
{
	if (s_midi_link == NULL) return;

	/* mt32mpu.c packs status | data1 << 8 | data2 << 16. */
	midi_put(data & 0xFF, (data >> 8) & 0xFF, (data >> 16) & 0xFF);
}

/* Called whenever a song starts or stops: silence every channel so no
 * notes hang on the synth. */
void midi_reset(void)
{
	uint8 chan;

	if (s_midi_link == NULL) return;

	for (chan = 0; chan < 16; chan++) {
		midi_put(0xB0 | chan, 120, 0);  /* All Sound Off. */
		midi_put(0xB0 | chan, 123, 0);  /* All Notes Off. */
		midi_put(0xB0 | chan,  64, 0);  /* Sustain off. */
		midi_put(0xB0 | chan, 121, 0);  /* Reset All Controllers. */
	}
}
