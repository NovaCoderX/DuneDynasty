/* Display, render target and blending: display.h, drawing.h, blender.h. */

#include "allegro5/allegro.h"
#include "a5_stub.h"

void al_set_new_display_flags(int flags)
{
   A5_STUB();
}

void al_set_new_display_option(int option, int value, int importance)
{
   A5_STUB();
}

ALLEGRO_DISPLAY *al_create_display(int w, int h)
{
   A5_STUB();
   return NULL;
}

void al_flip_display(void)
{
   A5_STUB();
}

ALLEGRO_BITMAP *al_get_backbuffer(ALLEGRO_DISPLAY *display)
{
   A5_STUB();
   return NULL;
}

ALLEGRO_EVENT_SOURCE *al_get_display_event_source(ALLEGRO_DISPLAY *display)
{
   A5_STUB();
   return NULL;
}

int al_get_display_flags(ALLEGRO_DISPLAY *display)
{
   A5_STUB();
   return 0;
}

int al_get_display_width(ALLEGRO_DISPLAY *display)
{
   A5_STUB();
   return 0;
}

int al_get_display_height(ALLEGRO_DISPLAY *display)
{
   A5_STUB();
   return 0;
}

bool al_set_display_flag(ALLEGRO_DISPLAY *display, int flag, bool onoff)
{
   A5_STUB();
   return false;
}

void al_set_display_icon(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *icon)
{
   A5_STUB();
}

void al_set_window_title(ALLEGRO_DISPLAY *display, const char *title)
{
   A5_STUB();
}

void al_set_target_bitmap(ALLEGRO_BITMAP *bitmap)
{
   A5_STUB();
}

void al_set_target_backbuffer(ALLEGRO_DISPLAY *display)
{
   A5_STUB();
}

ALLEGRO_BITMAP *al_get_target_bitmap(void)
{
   A5_STUB();
   return NULL;
}

void al_hold_bitmap_drawing(bool hold)
{
   A5_STUB();
}

void al_clear_to_color(ALLEGRO_COLOR color)
{
   A5_STUB();
}

void al_set_blender(int op, int source, int dest)
{
   A5_STUB();
}
