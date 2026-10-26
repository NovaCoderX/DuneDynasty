/* System, time and memory: system.h, altime.h, memory.h. */

#include <stdlib.h>
#include "allegro5/allegro.h"
#include "a5_stub.h"

bool al_install_system(int version, int (*atexit_ptr)(void (*)(void)))
{
   A5_STUB();
   return false;
}

void al_set_app_name(const char *app_name)
{
   A5_STUB();
}

double al_get_time(void)
{
   A5_STUB();
   return 0.0;
}

/* Real implementation: Allegro's default allocator is plain malloc(). */
void *al_malloc_with_context(size_t n, int line, const char *file,
   const char *func)
{
   return malloc(n);
}
