# Allegro 5 wrapper for Amiga 68k

A static library, `liballegro5.a`, that provides the part of the Allegro 5
API the Amiga build of Dune Dynasty 1.5.7 links against: 150 functions, plus
`al_uninstall_system`. They are being implemented on SDL2 (SDL2-NovaMesa) for
AmigaOS 3.x with RTG one module at a time; the rest are still stubs, so the
game always compiles and links.

This directory is self-contained so it can be moved into the
[NovaCoderX/Allegro5](https://github.com/NovaCoderX/Allegro5) repository.

## Layout

```
include/allegro5/          public headers, Allegro 5.2.11.3, unmodified
  allegro_audio.h, allegro_image.h, allegro_memfile.h, allegro_primitives.h
                           the four addon headers Dune Dynasty includes
  internal/, inline/, platform/
                           only the internal headers the public ones include
  platform/alplatf.h       hand-written Amiga configuration (see below)
src/                       one file per Allegro module
  a5_internal.h            event sources, the shared lock, timer internals
  a5_stub.h                A5_STUB() for functions not implemented yet
makefile                   builds lib/liballegro5.a
```

The headers are from the same release as the `internal/` and `platform/`
headers already in the Allegro5 repository: those files are byte-identical
to Allegro 5.2.11.3. Left out because nothing on the Amiga uses them:
`allegro_opengl.h`, `allegro_direct3d.h`, and the Windows, X11, macOS, iOS
and Android headers.

## Building

```
make                           # lib/liballegro5.a
make install PREFIX=/opt/amiga # copies include/allegro5 and the library
```

Compiler flags match the Dune Dynasty build: `-O2 -m68060 -noixemul`
(libnix), GCC 13.3 from AmigaPorts/m68k-amigaos-gcc.

The sources include `<SDL.h>`, so the compiler needs SDL2's header
directory: the makefile uses `SDL2_CFLAGS`, `-I/opt/amiga/include/SDL2` by
default. Anything linking the library also needs `-lSDL2`, after
`-lallegro5`.

## Implemented on SDL2

### System and time (`system.c`)

`al_install_system()` calls `SDL_Init(0)`, which starts SDL's clock
(timer.device and the EClock on AmigaOS). It deliberately does not use
`SDL_INIT_TIMER`, which would start SDL's timer thread, a separate Amiga
process the wrapper does not need. It registers `al_uninstall_system()`
with the `atexit` function it is given, as Allegro does, so `SDL_Quit()`
also runs when the game calls `exit()`.

`al_get_time()` is seconds since `al_install_system()`, from SDL's
performance counter (the EClock). `al_set_app_name()` does nothing:
Allegro only uses the name for standard paths and default window titles,
and the Amiga build needs neither.

### Event queues (`events.c`) and timers (`timer.c`)

Queues are growable ring buffers. One SDL mutex guards every queue, event
source and timer, since the game's main thread and its music thread both
use them; `al_wait_for_event()` sleeps on a per-queue SDL condition
variable.

Timers have no thread. A timer's ticks are worked out from `al_get_time()`
whenever something looks at it: a queue it feeds being checked or waited
on, or its count being read. Ticks that fell due in the meantime are
generated together, oldest first across all of a queue's timers, the same
way Allegro's timer thread catches up when it runs late. Counts and events
come out as in Allegro, without a task waking up for every tick: a thread
waiting on a queue sleeps until the next tick with a timed condition wait,
which SDL2-NovaMesa implements with timer.device (UNIT_MICROHZ below
100 ms).

Behaviour matches Allegro 5.2 where Dune Dynasty depends on it:

- `al_start_timer()` keeps the count and schedules the first tick one
  period ahead; `al_stop_timer()` freezes the count.
- `al_set_timer_speed()` lengthens or shortens the tick in progress by the
  change in speed.
- One timer can feed several queues (the GUI timer feeds the input queue
  and, during `Timer_Sleep()`, the timer queue).
- `al_unregister_event_source()` and `al_destroy_timer()` drop the
  source's events that are still queued.
- `al_wait_for_event(queue, NULL)` waits without removing the event.

### Keyboard (`keyboard.c`) and mouse (`mouse.c`)

SDL's input has to be pumped by the task that owns the window, so, as in
Allegro's own SDL backend, checking, reading, flushing or waiting on a
queue pumps SDL's events first, but only on the thread that called
`al_install_system()`; the music thread's queue never touches SDL. A wait
on the main thread wakes at least every 10 ms to pump again, which is how
input reaches a queue with no timer running. `SDL_PumpEvents()` runs once
per call, followed by `SDL_PeepEvents()`, since `SDL_PollEvent()` would
pump again for every event.

- Keys map from SDL scancodes as in Allegro's SDL backend: left Alt is
  `ALLEGRO_KEY_ALT`, right Alt `ALLEGRO_KEY_ALTGR`, the Amiga keys
  `ALLEGRO_KEY_LWIN`/`RWIN`; keys Allegro has no code for (such as Help)
  come through as keycode 0.
- `KEY_DOWN` on the first press, `KEY_UP` on release, and `KEY_CHAR` on
  every press and auto-repeat (with `repeat` set), which is where Dune
  Dynasty reads Enter, Alt+Enter and F10 to F12 from. `unichar` is the
  character the key types unshifted; `SDL_TEXTINPUT` is not used, since
  the game never reads `unichar`.
- Mouse buttons are 1 left, 2 right, 3 middle. Motion and the wheel are
  `ALLEGRO_EVENT_MOUSE_AXES` with `x`/`y`, `dx`/`dy`, and `z`/`dz` for the
  wheel.
- `display` in keyboard and mouse events is NULL until the display module
  exists.

`al_set_mouse_xy()` and the cursor functions need the display and bitmaps,
so they are still stubs. Input only arrives once there is a window: SDL2's
video driver reads it from the window's IDCMP port.

### Configuration files (`config.c`)

Plain C on stdio, reading and writing Allegro's format: `[section]`
headers, `key=value` lines (trimmed), and a global section before the
first header. Comments and blank lines are kept where they are, so the
game saving `dunedynasty.cfg` changes only the values it sets. A key the
program adds goes after the last key of its section, and a new section
goes at the end after a blank line. Line endings are read either way and
written as LF.

## How the stubs behave

Each stub does nothing and returns a failure value: `false`, `NULL`, `0` or
`-1`, or an empty string for path queries. With system, timers, event
queues, keyboard and mouse working, and the game data in place, Dune
Dynasty now gets as far as creating its display in `VideoA5_Init()`: the
stubbed `al_create_display()` returns NULL, the game prints "Could not
create display!" and exits with status 1. Nothing on that path
dereferences a stub's NULL.

`ALLEGRO_STUB_TRACE` (on by default in the makefile) reports the first
call to each stub through Allegro's trace output (`debug.c`): to the
handler the program registered with `al_register_trace_handler()`, or to
stderr if there is none. Dune Dynasty registers one that sends the trace
to its log:

```
allegro5 stub: al_set_new_display_flags()
allegro5 stub: al_set_new_display_option()
allegro5 stub: al_create_display()
```

As modules get implemented, this trace shows which call is next on the path.
Remove `-DALLEGRO_STUB_TRACE` from `CPPFLAGS` to silence it.

Some functions in stubbed modules are already real, because they are
plain C that needs no SDL2 and a fake value would silently corrupt the
caller's state:

| Function | Source |
| --- | --- |
| `al_malloc_with_context` (`al_malloc`) | `malloc()`, as Allegro's default |
| `al_map_rgb`, `al_map_rgba` | Allegro `pixels.c` |
| `al_identity_transform`, `al_build_transform` | Allegro `transformations.c` |
| `al_get_audio_depth_size` | Allegro `audio.c` |

## Function list by module

| File | Header(s) | Functions | Status |
| --- | --- | --- | --- |
| `system.c` | system.h, altime.h, memory.h | 5 | SDL2 |
| `events.c` | events.h | 8 | SDL2 |
| `timer.c` | timer.h | 7 | SDL2 |
| `display.c` | display.h, drawing.h, blender.h | 18 | stubs |
| `bitmap.c` | bitmap.h, bitmap_lock.h, bitmap_io.h | 15 | stubs |
| `bitmap_draw.c` | bitmap_draw.h | 8 | stubs |
| `color.c` | color.h | 2 | plain C |
| `transformations.c` | transformations.h | 3 | 2 plain C, 1 stub |
| `keyboard.c` | keyboard.h | 2 | SDL2 |
| `mouse.c` | mouse.h, mouse_cursor.h | 8 | 2 SDL2, 6 stubs (warp, cursors) |
| `threads.c` | threads.h | 5 | stubs |
| `path.c` | path.h | 9 | stubs |
| `config.c` | config.h | 7 | plain C |
| `file.c` | file.h | 9 | stubs |
| `fshook.c` | fshook.h | 8 | stubs |
| `primitives.c` | allegro_primitives.h | 5 | stubs |
| `image.c` | allegro_image.h | 1 | stubs |
| `memfile.c` | allegro_memfile.h | 1 | stubs |
| `audio.c` | allegro_audio.h | 29 | 1 plain C, 28 stubs |
| `debug.c` | debug.h | 1 | plain C |

`al_is_sub_bitmap` is only called inside `assert()`, so a release build
(`-DNDEBUG`) does not need it; it is stubbed anyway so debug builds link.
`al_get_standard_path` is not needed at all: on the Amiga the game takes
its directory from `g_amiga_path` (see `src/os/amiga_main.c`).

If Dune Dynasty starts calling a new Allegro function, the link fails with
`undefined reference to 'al_...'`. Add the function to the matching
`src/` file, copying the prototype from the header.

## platform/alplatf.h

Upstream generates this from `alplatf.h.cmake`. The Amiga version is
written by hand and differs from the earlier draft (a Linux CMake output)
as follows:

- `ALLEGRO_CFG_OPENGL`, `_OPENGLES`, `_OPENGLES2`,
  `_OPENGL_PROGRAMMABLE_PIPELINE` and `ALLEGRO_CFG_SHADER_GLSL` are off,
  because SDL2-NovaMesa is built without `SDL_VIDEO_OPENGL`. Dune Dynasty's
  `video_a5.c` tests `ALLEGRO_CFG_OPENGL` to decide whether to build its GL
  stencil effects.
- `ALLEGRO_CFG_PTHREADS_TLS` is off: the wrapper does not use Allegro's
  thread-local state code (`tls.c`).
- `ALLEGRO_HAVE_*` entries were checked against the libnix headers and
  libraries in the GCC 13.3 toolchain. Off: `OSAtomic.h` (macOS only),
  `mmap` and `mprotect` (no `sys/mman.h`), and `sched_yield`, which is
  declared but has no implementation. libnix does provide `mkstemp`,
  `fseeko`/`ftello`, `strerror_r`, `sysconf` and `uname`, so those stay on.
  These settings only matter when compiling Allegro's own sources.
- Unchanged: `ALLEGRO_SDL` and `ALLEGRO_BIG_ENDIAN`.

## Next steps

The display is what the game needs next, and what makes keyboard and
mouse input arrive. When it exists, `a5_pump_sdl_events()` needs cases for
SDL's window events (close becomes `ALLEGRO_EVENT_DISPLAY_CLOSE`), and the
input events' `display` field should point at it.

`threads.c` is small and is what Dune Dynasty's MIDI music runs on.
Several Allegro modules are plain C and could be compiled from the
5.2.11.3 sources instead of rewritten: `path.c`, `utf8.c`
with `misc/bstrlib.c`, `file.c`, `file_stdio.c`, `fshook_stdio.c`,
`transformations.c` and the memfile addon. They need the `internal/`
headers, which are already in the Allegro5 repository. The display,
bitmap and audio modules are the ones that need SDL2.

Allegro 5 is distributed under the zlib licence; see `LICENSE.txt`.
