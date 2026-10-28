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
* Logging: all output goes through `Log_Error()`/`Log_Warning()`/`Log_Info()`/`Log_Debug()` (`src/os/error.h`), which also write to `dunedynasty.log` in `g_amiga_path` on Amiga; never print with `printf`/`fprintf` directly. Don't name game functions `Info()` or `Debug()`: AmigaOS has both (dos.library, exec.library).
* MIDI music: `src/audio/midi_camd.c` implements `src/audio/midi.h` on camd.library (headers from `make camd` in the toolchain build tree).
* `DuneLegacy/` and `OpenDUNE/` are the author's earlier 68k ports, kept for reference only; they are not part of the build.
* Never put `src/` on the include path: `src/string.h` shadows the C library's `<string.h>`.
* `AMIGA` is predefined and `int32_t` is `long` on this target; use the `uint32`/`int32` typedefs from `include/types.h`.

### Future plans

#### Convert the game to pure C

The only C++ is the audio code (about 5,200 lines; the rest of the game is C99):

* Dune II's AdLib sound is two layers, and both are needed:
  * `src/audio/adl/sound_adlib.cpp` is the player: ScummVM's port of Westwood's AdLib driver. It runs the `.ADL` files (`DUNE0.ADL`..., music and AdLib sound effects) and turns them into OPL register writes.
  * `src/audio/adl/opl_mame.cpp` is the chip: MAME's YM3812 (OPL2) emulator, which turns the register writes into PCM.
* The MIDI music is separate: `mt32mpu.c` plays the `.XMI` files and `midi_camd.c` sends them to camd.library.
* Plan:
  * Drop the DOSBox OPL emulator (`opl_dosbox.cpp`, `opl_impl.h`, `opl_inc.h`) and the chip switch (`fmopl.cpp`/`fmopl.h`, the `opl_mame` config option). MAME is already the default and is the lighter emulator.
  * `opl_mame.cpp` → `opl_mame.c`: it is MAME's `fmopl.c` wrapped in a namespace and one template (`CLIP`).
  * `sound_adlib.cpp` → `sound_adlib.c`, the main work:
    * `AdLibDriver` and `SoundAdLibPC` become structs passed by pointer.
    * The member function pointer tables (opcodes, update callbacks, parser opcodes) become plain function pointer tables.
    * `Channel &` and `uint8 *&` become pointers, and `std::min` a macro.
    * Remove `getSubsongs()`: Dune Legacy's SDL_mixer path, unused.
  * `audio_a5.cpp` → `audio_a5.c`: `new`/`delete` become `malloc`/`free`.
  * Then drop the C++ nature and libstdc++ from the Eclipse project and link with the C linker.
* Verify the AdLib conversion byte for byte. Before converting, a host program renders every `.ADL` track and sound effect to raw PCM; after converting, the output must be identical.
* Best done before or with the wrapper's SDL2 audio module, since `audio_a5` gets reworked then anyway.

#### Audio mixing rate

Mix at 22 kHz, 16-bit integer. `audio_a5.cpp` sets up Allegro's voice and mixer at 44.1 kHz with a float mixer, which is too heavy for a 68060 on top of OPL emulation. Change that when the wrapper's audio module goes onto SDL2 and AHI. Neither music set plays until that module works: the AdLib PCM goes through the voice and mixer, and MIDI only starts after `al_install_audio()`, `al_create_voice()` and `al_create_mixer()` succeed.
