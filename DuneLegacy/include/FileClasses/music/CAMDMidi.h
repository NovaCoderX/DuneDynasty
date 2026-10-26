/*
 *  camd_midi.h - Minimal CAMD MIDI output backend for Dune Legacy on AmigaOS 3
 *
 *  Adapted from the OpenDUNE AmigaOS CAMD driver.
 *  Provides raw MIDI message output to the first CAMD "out" cluster
 *  (e.g. camdusbmidi.out.0, mmp.out.0, or a software synth link).
 */

#ifndef CAMD_MIDI_H
#define CAMD_MIDI_H

/* Open camd.library, create the MIDI node and link to the first
   available output cluster. Returns 1 on success, 0 on failure. */
int  CAMD_Init(void);

/* Tear down link/node/library. Safe to call if not initialised. */
void CAMD_Uninit(void);

/* Send a 1-3 byte channel voice/mode message.
   status = full status byte (e.g. 0x90 | channel),
   data1/data2 = data bytes (pass 0 when unused). */
void CAMD_SendMidi(unsigned char status, unsigned char data1, unsigned char data2);

/* Send a SysEx message. data must begin with 0xF0 and end with 0xF7. */
void CAMD_SendSysEx(unsigned char *data);

/* Convenience: send All Sound Off + All Notes Off + Sustain Off +
   Reset All Controllers on all 16 MIDI channels. Call when stopping
   playback so no notes hang on the synth. */
void CAMD_AllNotesOff(void);

/* Returns 1 if the CAMD link is up and messages can be sent. */
int  CAMD_IsReady(void);

#endif /* CAMD_MIDI_H */
