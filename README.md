# DuneDynasty
Dune Dynasty is a continuation of the classic real-time strategy game Dune II by Westwood Studios.

This is a port of Dune Dynasty 1.5.7 to the Amiga 68k (RTG, PiStorm 4), using
SDL2 through a small Allegro 5 wrapper library.

## Building for Amiga 68k

Needs m68k-amigaos-gcc 13.3 from
[AmigaPorts/m68k-amigaos-gcc](https://github.com/AmigaPorts/m68k-amigaos-gcc)
(libnix runtime).

```
cd allegro5_wrapper && make     # lib/liballegro5.a (stubbed Allegro 5)
cd ../amiga_build && make       # amiga_build/DuneDynasty
```

The Allegro 5 library is currently all stubs: the executable links and
starts, then exits in `al_install_system()`. See
[allegro5_wrapper/README.md](allegro5_wrapper/README.md).

### Build configuration

`src/os/amiga_main.c` provides `main()`. It refuses to start with less than
300,000 bytes of stack, stores the game's directory in `g_amiga_path`
(the current directory from the Shell, the icon's directory from
Workbench), then calls the game's own entry point, renamed `dune_main()`
on Amiga. The game data, `dunedynasty.cfg` and saves are all read from and
written to that directory.

`include/buildcfg.h` replaces the CMake-generated header: AUD music on;
FluidSynth, MP3 (libmad) and FLAC/Ogg off. MIDI goes through the
`src/audio/midi.h` interface (`midi_init`, `midi_send`, ...); `midi_none.c`
fills it for now, and a CAMD driver would replace that file.

The OpenGL stencil effects in `src/video/video_a5.c` (the dissolve fade-in
and the sandworm/sonic blur) are only compiled when Allegro has OpenGL
(`ALLEGRO_CFG_OPENGL`). The Amiga wrapper has no OpenGL, so those effects
are skipped.

These sources from 1.5.7 are not part of the Amiga build and were removed:
the ALSA, Core MIDI and Win32 MIDI drivers, `os/error_win32.c`, the libmad
and FluidSynth decoders (`allegro_mad.c`, `allegro_midi.cpp`,
`xmi/xmidi.cpp`), the `allegro_adl.cpp` test player, audlib's Allegro 4
version and examples, and OpenDUNE's unused `gui/security.c`.

### Eclipse CDT

`amiga_build/` is an Eclipse CDT managed build, so CDT regenerates its
makefiles from the project settings. To get the same build:

- The project needs the C++ nature: `src/audio/audio_a5.cpp` and
  `src/audio/adl/*.cpp` are part of the game. Link with Cross G++ Linker.
- C and C++ compiler, same settings for both:
  - Include paths: `include` and `allegro5_wrapper/include` (or
    `/opt/amiga/include` after `make install` in `allegro5_wrapper`).
    **Do not add `src`**: it contains `string.h`, which then hides the C
    library's `<string.h>`.
  - Defines: `NDEBUG`
  - Flags: `-O2 -fno-optimize-sibling-calls -Wall -m68060 -noixemul`
- Linker: flags `-s -noixemul`, libraries `allegro5` and `m`, library path
  `allegro5_wrapper/lib`.
