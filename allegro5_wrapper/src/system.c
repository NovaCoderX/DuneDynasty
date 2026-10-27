/* System, time and memory: system.h, altime.h, memory.h. */

#include <stdlib.h>
#include <SDL.h>
#include "allegro5/allegro.h"
#include "a5_internal.h"

static bool s_installed = false;
static Uint64 s_time_start;
static double s_time_scale;

bool al_install_system(int version, int (*atexit_ptr)(void (*)(void)))
{
   if (s_installed)
      return true;

   /* SDL_Init(0) only starts SDL's clock (timer.device and the EClock on
    * AmigaOS).  SDL_INIT_TIMER would also start SDL's timer thread, which
    * the wrapper's timers do not use: see timer.c.
    */
   if (SDL_Init(0) != 0)
      return false;

   if (!a5_events_init()) {
      SDL_Quit();
      return false;
   }

   s_time_start = SDL_GetPerformanceCounter();
   s_time_scale = 1.0 / (double)SDL_GetPerformanceFrequency();
   s_installed = true;

   if (atexit_ptr)
      atexit_ptr(al_uninstall_system);

   return true;
}

void al_uninstall_system(void)
{
   if (!s_installed)
      return;

   s_installed = false;
   a5_events_shutdown();
   SDL_Quit();
}

/* Allegro uses the name for standard paths and default window titles; the
 * Amiga build needs neither (paths come from g_amiga_path, and the game
 * sets its own window title).
 */
void al_set_app_name(const char *app_name)
{
}

/* Seconds since al_install_system(), from SDL's performance counter (the
 * EClock on AmigaOS).
 */
double al_get_time(void)
{
   if (!s_installed)
      return 0.0;

   return (double)(SDL_GetPerformanceCounter() - s_time_start) * s_time_scale;
}

/* Real implementation: Allegro's default allocator is plain malloc(). */
void *al_malloc_with_context(size_t n, int line, const char *file,
   const char *func)
{
   return malloc(n);
}
