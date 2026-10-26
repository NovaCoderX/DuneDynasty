#ifndef BUILDCFG_H
#define BUILDCFG_H

/* Hand-maintained equivalent of buildcfg.h.in for the Amiga 68k build,
 * which has no CMake configure step.
 */

#define DUNE_DYNASTY_VERSION "dd1.5.7"

#define DUNE_DATA_DIR "PROGDIR:"

/* #undef WITH_ACODEC */     /* FLAC/Ogg Vorbis music: too heavy for 68k. */
#define WITH_AUD             /* Dune 2000 AUD music. */
/* #undef WITH_FLUIDSYNTH */ /* MIDI goes to CAMD via src/audio/midi.h instead. */
/* #undef WITH_MAD */        /* MP3 music: no libmad. */

#endif
