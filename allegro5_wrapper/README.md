# Allegro 5 wrapper for Amiga 68k (stubbed)

A static library, `liballegro5.a`, that provides the part of the Allegro 5
API the Amiga build of Dune Dynasty 1.5.7 links against: 149 functions. The plan is for these to call
through to SDL2 (SDL2-NovaMesa) on AmigaOS 3.x with RTG. For now every
function is a stub, so the game compiles and links while the real
implementation is written one module at a time.

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

## How the stubs behave

Each stub does nothing and returns a failure value: `false`, `NULL`, `0` or
`-1`, or an empty string for path queries. Dune Dynasty checks the result of
`al_init()`, so a stubbed build starts, fails in `al_install_system()`, and
exits with status 1 rather than crashing.

`ALLEGRO_STUB_TRACE` (on by default in the makefile) prints the first call
to each stub on stderr:

```
allegro5 stub: al_install_system()
```

As modules get implemented, this trace shows which call is next on the path.
Remove `-DALLEGRO_STUB_TRACE` from `CPPFLAGS` to silence it.

Six functions are already real, because they are plain C that needs no
SDL2 and a fake value would silently corrupt the caller's state:

| Function | Source |
| --- | --- |
| `al_malloc_with_context` (`al_malloc`) | `malloc()`, as Allegro's default |
| `al_map_rgb`, `al_map_rgba` | Allegro `pixels.c` |
| `al_identity_transform`, `al_build_transform` | Allegro `transformations.c` |
| `al_get_audio_depth_size` | Allegro `audio.c` |

## Function list by module

| File | Header(s) | Functions |
| --- | --- | --- |
| `system.c` | system.h, altime.h, memory.h | 4 |
| `display.c` | display.h, drawing.h, blender.h | 18 |
| `bitmap.c` | bitmap.h, bitmap_lock.h, bitmap_io.h | 15 |
| `bitmap_draw.c` | bitmap_draw.h | 8 |
| `color.c` | color.h | 2 |
| `transformations.c` | transformations.h | 3 |
| `events.c` | events.h | 8 |
| `keyboard.c` | keyboard.h | 2 |
| `mouse.c` | mouse.h, mouse_cursor.h | 8 |
| `timer.c` | timer.h | 7 |
| `threads.c` | threads.h | 5 |
| `path.c` | path.h | 9 |
| `config.c` | config.h | 7 |
| `file.c` | file.h | 9 |
| `fshook.c` | fshook.h | 8 |
| `primitives.c` | allegro_primitives.h | 5 |
| `image.c` | allegro_image.h | 1 |
| `memfile.c` | allegro_memfile.h | 1 |
| `audio.c` | allegro_audio.h | 29 |

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

Several Allegro modules are plain C and could be compiled from the
5.2.11.3 sources instead of rewritten: `path.c`, `config.c`, `utf8.c`
with `misc/bstrlib.c`, `file.c`, `file_stdio.c`, `fshook_stdio.c`,
`transformations.c` and the memfile addon. They need the `internal/`
headers, which are already in the Allegro5 repository. The display,
bitmap, event, input, timer and audio modules are the ones that need
SDL2.

Allegro 5 is distributed under the zlib licence; see `LICENSE.txt`.
