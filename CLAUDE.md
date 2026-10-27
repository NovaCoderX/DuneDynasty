### CLAUDE.md — Dune Dynasty Port (Amiga 68K RTG / PiStorm/ SDL2)

### Project Overview

Dune Dynasty is a continuation of the classic real-time strategy game Dune II by Westwood Studios.. 

* **Target Hardware:** Amiga 68k with RTG (32-bit color space) PiStorm 4.

### Build

* Toolchain: m68k-amigaos-gcc 13.3 (AmigaPorts/m68k-amigaos-gcc), libnix (`-noixemul`), `-m68060`.
* Base source: Dune Dynasty 1.5.7 (SourceForge release), no network code.
* `allegro5_wrapper/` builds `liballegro5.a`: the Allegro 5.2.11.3 API that Dune Dynasty uses, currently stubs, to be implemented on SDL2.
* `amiga_build/` is the Eclipse CDT managed build of the game (`make` from that directory).
* `src/os/amiga_main.c` owns `main()` (stack check, `g_amiga_path`); the game's entry point is `dune_main()` on Amiga. Data paths are joined as `"%s/name"` on `g_amiga_path`, so never build them with a trailing or doubled `/` (AmigaDOS reads `//` as the parent directory).
* Logging: `Error()`/`Warning()` in `src/os/error.c` also write to `dunedynasty.log` in `g_amiga_path` on Amiga; route anything that should reach the log through them.
* MIDI music: `src/audio/midi_camd.c` implements `src/audio/midi.h` on camd.library (headers from `make camd` in the toolchain build tree).
* `DuneLegacy/` and `OpenDUNE/` are the author's earlier 68k ports, kept for reference only; they are not part of the build.
* Never put `src/` on the include path: `src/string.h` shadows the C library's `<string.h>`.
* `AMIGA` is predefined and `int32_t` is `long` on this target; use the `uint32`/`int32` typedefs from `include/types.h`.
