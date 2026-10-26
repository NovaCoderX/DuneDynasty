/* Threads: threads.h. */

#include "allegro5/allegro.h"
#include "a5_stub.h"

ALLEGRO_THREAD *al_create_thread(
   void *(*proc)(ALLEGRO_THREAD *thread, void *arg), void *arg)
{
   A5_STUB();
   return NULL;
}

void al_start_thread(ALLEGRO_THREAD *thread)
{
   A5_STUB();
}

void al_set_thread_should_stop(ALLEGRO_THREAD *thread)
{
   A5_STUB();
}

bool al_get_thread_should_stop(ALLEGRO_THREAD *thread)
{
   A5_STUB();
   return true;
}

void al_destroy_thread(ALLEGRO_THREAD *thread)
{
   A5_STUB();
}
