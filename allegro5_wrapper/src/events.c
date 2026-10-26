/* Event queues: events.h. */

#include "allegro5/allegro.h"
#include "a5_stub.h"

ALLEGRO_EVENT_QUEUE *al_create_event_queue(void)
{
   A5_STUB();
   return NULL;
}

void al_destroy_event_queue(ALLEGRO_EVENT_QUEUE *queue)
{
   A5_STUB();
}

void al_register_event_source(ALLEGRO_EVENT_QUEUE *queue,
   ALLEGRO_EVENT_SOURCE *source)
{
   A5_STUB();
}

void al_unregister_event_source(ALLEGRO_EVENT_QUEUE *queue,
   ALLEGRO_EVENT_SOURCE *source)
{
   A5_STUB();
}

bool al_is_event_queue_empty(ALLEGRO_EVENT_QUEUE *queue)
{
   A5_STUB();
   return true;
}

bool al_get_next_event(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_EVENT *ret_event)
{
   A5_STUB();
   return false;
}

void al_flush_event_queue(ALLEGRO_EVENT_QUEUE *queue)
{
   A5_STUB();
}

void al_wait_for_event(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_EVENT *ret_event)
{
   A5_STUB();
}
