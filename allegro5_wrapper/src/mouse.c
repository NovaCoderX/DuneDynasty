/* Mouse and mouse cursors: mouse.h, mouse_cursor.h. */

#include "allegro5/allegro.h"
#include "a5_stub.h"

bool al_install_mouse(void)
{
   A5_STUB();
   return false;
}

ALLEGRO_EVENT_SOURCE *al_get_mouse_event_source(void)
{
   A5_STUB();
   return NULL;
}

bool al_set_mouse_xy(ALLEGRO_DISPLAY *display, int x, int y)
{
   A5_STUB();
   return false;
}

ALLEGRO_MOUSE_CURSOR *al_create_mouse_cursor(ALLEGRO_BITMAP *sprite,
   int xfocus, int yfocus)
{
   A5_STUB();
   return NULL;
}

void al_destroy_mouse_cursor(ALLEGRO_MOUSE_CURSOR *cursor)
{
   A5_STUB();
}

bool al_set_mouse_cursor(ALLEGRO_DISPLAY *display, ALLEGRO_MOUSE_CURSOR *cursor)
{
   A5_STUB();
   return false;
}

bool al_show_mouse_cursor(ALLEGRO_DISPLAY *display)
{
   A5_STUB();
   return false;
}

bool al_hide_mouse_cursor(ALLEGRO_DISPLAY *display)
{
   A5_STUB();
   return false;
}
