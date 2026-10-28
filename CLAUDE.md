### CLAUDE.md — Dune Dynasty Port (Amiga 68K RTG / PiStorm/ SDL2)

### Project Overview

Dune Dynasty is a continuation of the classic real-time strategy game Dune II by Westwood Studios.. 

* **Target Hardware:** Amiga 68k with RTG (32-bit color space) PiStorm 4.

### Build

* Toolchain: m68k-amigaos-gcc 13.3 (AmigaPorts/m68k-amigaos-gcc), libnix (`-noixemul`), `-m68060`.
* Base source: Dune Dynasty 1.5.7 (SourceForge release), no network code.
* `allegro5_wrapper/` builds `liballegro5.a`: the Allegro 5.2.11.3 API that Dune Dynasty uses, implemented module by module on SDL2 or plain C (system, events, timers, keyboard, mouse input, config so far); the rest are stubs.
* `amiga_build/` is the Eclipse CDT managed build of the game (`make` from that directory).
* `src/os/amiga_main.c` owns `main()` (stack check, `g_amiga_path`); the game's entry point is `dune_main()` on Amiga. Data paths are joined as `"%s/name"` on `g_amiga_path`, so never build them with a trailing or doubled `/` (AmigaDOS reads `//` as the parent directory).
* Logging: all output goes through `Log_Error()`/`Log_Warning()`/`Log_Info()`/`Log_Debug()` (`src/os/error.h`), which also write to `dunedynasty.log` in `g_amiga_path` on Amiga; never print with `printf`/`fprintf` directly. Don't name game functions `Info()` or `Debug()`: AmigaOS has both (dos.library, exec.library).
* MIDI music: `src/audio/midi_camd.c` implements `src/audio/midi.h` on camd.library (headers from `make camd` in the toolchain build tree).
* `DuneLegacy/` and `OpenDUNE/` are the author's earlier 68k ports, kept for reference only; they are not part of the build.
* Never put `src/` on the include path: `src/string.h` shadows the C library's `<string.h>`.
* `AMIGA` is predefined and `int32_t` is `long` on this target; use the `uint32`/`int32` typedefs from `include/types.h`.
* m68k is big-endian and Dune II's files are little-endian: read multi-byte values with `READ_LE_UINT16`/`READ_LE_UINT32` (`src/os/endian.h`), `File_Read_LE16`/`File_Read_LE32` or `fread_le_uint16`/`fread_le_uint32` (`src/file.h`), and write saves with `fwrite_le_*`. Never `fread` into a `uint16`/`uint32` or cast file data to `uint16 *`. Chunk IDs and lengths in IFF-style files (`FORM`, saves, `.EMC`, `.XMI`) are big-endian (`BETOH32`).

### Future plans

#### Display (next), in phases

Agreed decisions: own software renderer in the wrapper (not SDL_Renderer); fullscreen is always `SDL_WINDOW_FULLSCREEN`, never `SDL_WINDOW_FULLSCREEN_DESKTOP` (SDL2-NovaMesa then scales internally, which is slow); always the game's software cursor on Amiga (SDL2-NovaMesa ignores custom cursor images); PNG loading through the user's 68k SDL2_image.

How Dune Dynasty draws: at start-up `video_a5.c` builds 1024x1024 32-bit atlases (shapes, icons, regions, interface, mentats); every frame it clears and redraws the whole screen from them, mostly `al_draw_bitmap_region`/`al_draw_scaled_bitmap` through per-area transforms that are only scale + offset (2x by default at 640x480). Blenders: copy (ONE, ZERO), alpha (ALPHA, INVERSE_ALPHA), additive highlight (ALPHA, ONE), shadows as a black tint with alpha. Rotation only for air units with smooth rotation. Primitives: rectangles, lines, flat-colour triangle lists (window borders). Locks ask for `ABGR_8888_LE` (R,G,B,A bytes) and are nearly all at load time (per frame: the 64x64 minimap and the dissolve fade-in).

* Phase 1, a picture on screen:
  * `display.c`: the window or `SDL_WINDOW_FULLSCREEN` screen for both `ALLEGRO_FULLSCREEN` and `ALLEGRO_FULLSCREEN_WINDOW` (`ALLEGRO_OPENGL` ignored); the backbuffer is a bitmap over `SDL_GetWindowSurface()` (ARGB8888 in fast RAM, which SDL2-NovaMesa copies to RTG with `p96WritePixelArray`); `al_flip_display()` is `SDL_UpdateWindowSurface()`; window close/expose/focus become display events in `a5_pump_sdl_events()`, and input events get their `display`; title through SDL, icons a no-op, `al_set_display_flag()` false.
  * `bitmap.c`: ARGB8888 bitmaps; sub-bitmaps are views into the parent; locks convert to and from `ABGR_8888_LE` (skipping the read for write-only and the write-back for read-only); clipping.
  * Target bitmap, blender, `al_clear_to_color()`, `al_use_transform()` (scale + translate).
  * `bitmap_draw.c`: one general blit (region, flips, nearest-neighbour scaling, tint, the blenders, clip), and a rotated blit by inverse mapping.
  * `primitives.c`: filled/outlined rectangles, lines, flat-colour triangles for `al_draw_indexed_prim()`/`al_draw_filled_triangle()`.
  * Mouse: `al_create_mouse_cursor()` returns NULL and the system pointer is hidden (`SDL_ShowCursor(SDL_DISABLE)`); `al_set_mouse_xy()` is `SDL_WarpMouseInWindow()`. `config_a5.c` defaults to fullscreen and forces the software cursor on Amiga, as it does for Pandora.
  * `al_load_bitmap()` returns NULL and `al_save_bitmap()` false for now; the game copes (no hi-res overlays or rubble masks from `gfx/`).
* Phase 2, speed: measure with the game's FPS display on the PiStorm, then fast paths: opaque rows as `memcpy`, on/off-alpha sprites without blending maths, a dedicated 2x scaler, a longword fill for the per-frame clear; a frame limiter if needed (the game asks for vsync, which there isn't).
* Phase 3: `al_load_bitmap()` on SDL2_image for `gfx/*.png`; screenshots; optionally a software version of the sandworm/sonic blur, which the game only draws with OpenGL or Direct3D.
* Testing: the rasterizer under vamos (big-endian lock conversions); where possible, compare against upstream Allegro 5.2.11.3's memory-bitmap (software) drawing on the host; real game runs on FS-UAE and the PiStorm with the user's data.


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
