/* Timers: timer.h. */

#include "allegro5/allegro.h"
#include "a5_stub.h"

ALLEGRO_TIMER *al_create_timer(double speed_secs)
{
   A5_STUB();
   return NULL;
}

void al_destroy_timer(ALLEGRO_TIMER *timer)
{
   A5_STUB();
}

void al_start_timer(ALLEGRO_TIMER *timer)
{
   A5_STUB();
}

void al_stop_timer(ALLEGRO_TIMER *timer)
{
   A5_STUB();
}

int64_t al_get_timer_count(const ALLEGRO_TIMER *timer)
{
   A5_STUB();
   return 0;
}

void al_set_timer_speed(ALLEGRO_TIMER *timer, double speed_secs)
{
   A5_STUB();
}

ALLEGRO_EVENT_SOURCE *al_get_timer_event_source(ALLEGRO_TIMER *timer)
{
   A5_STUB();
   return NULL;
}
