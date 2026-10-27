/* Internals shared between the wrapper's modules. */
#ifndef A5_INTERNAL_H
#define A5_INTERNAL_H

#include "allegro5/allegro.h"

/* What the wrapper keeps inside an ALLEGRO_EVENT_SOURCE's padding: the
 * queues it feeds and, for a timer's source, the timer.  may_alias, since
 * it is accessed through that int padding, which strict aliasing would
 * otherwise let GCC reorder.
 */
#define A5_MAX_SOURCE_QUEUES  8

typedef struct __attribute__((may_alias)) A5_EVENT_SOURCE {
   ALLEGRO_EVENT_QUEUE *queues[A5_MAX_SOURCE_QUEUES];
   int num_queues;
   ALLEGRO_TIMER *timer;
} A5_EVENT_SOURCE;

#define A5_SOURCE(source)  ((A5_EVENT_SOURCE *)(source))

/* events.c.  One lock guards every queue, event source and timer, since
 * the game and its music thread both use them.
 */
bool a5_events_init(void);
void a5_events_shutdown(void);
void a5_lock(void);
void a5_unlock(void);
void a5_event_source_init(ALLEGRO_EVENT_SOURCE *source);

/* Call these with the lock held. */
void a5_event_source_free_locked(ALLEGRO_EVENT_SOURCE *source);
void a5_emit_event_locked(ALLEGRO_EVENT_SOURCE *source, ALLEGRO_EVENT *event);

/* timer.c.  Call these with the lock held. */
bool a5_timer_next_tick_locked(const ALLEGRO_TIMER *timer, double *when);
void a5_timer_tick_locked(ALLEGRO_TIMER *timer, double now);

#endif
