/* Shared helpers for the stubbed Allegro 5 wrapper.
 *
 * Every function that has no real implementation yet starts with
 * A5_STUB().  Stubs do nothing and return a failure value (false, NULL,
 * 0), so a caller that checks for errors stops cleanly instead of
 * dereferencing a fake object.
 *
 * Build with -DALLEGRO_STUB_TRACE to print the first call to each stub
 * on stderr; the output shows how far a program gets and which functions
 * to implement next.
 */
#ifndef A5_STUB_H
#define A5_STUB_H

#ifdef ALLEGRO_STUB_TRACE
#include <stdio.h>

#define A5_STUB()                                                    \
   do {                                                              \
      static int reported;                                           \
      if (!reported) {                                               \
         reported = 1;                                               \
         fprintf(stderr, "allegro5 stub: %s()\n", __func__);          \
      }                                                              \
   } while (0)
#else
#define A5_STUB()    ((void)0)
#endif

#endif
