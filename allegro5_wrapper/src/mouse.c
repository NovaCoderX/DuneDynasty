/* Mouse and mouse cursors: mouse.h, mouse_cursor.h.
 *
 * Mouse events come from SDL's mouse events, as in Allegro's SDL backend.
 * Warping and cursors need the display, so they are still stubs.
 */

#include <string.h>
#include <SDL.h>
#include "allegro5/allegro.h"
#include "a5_internal.h"
#include "a5_stub.h"

static bool s_installed = false;
static A5_EVENT_SOURCE_ALIGN ALLEGRO_EVENT_SOURCE s_source;

/* Where the mouse is, the wheel totals, and the buttons held. */
static int s_x, s_y, s_z, s_w;
static unsigned int s_buttons;

/* SDL numbers the middle button 2 and the right 3; Allegro the other way. */
static unsigned int get_button(Uint8 sdl_button)
{
   switch (sdl_button) {
      case SDL_BUTTON_LEFT:   return 1;
      case SDL_BUTTON_RIGHT:  return 2;
      case SDL_BUTTON_MIDDLE: return 3;
      case SDL_BUTTON_X1:     return 4;
      case SDL_BUTTON_X2:     return 5;
      default:                return 0;
   }
}

void a5_mouse_handle_event(const SDL_Event *e)
{
   ALLEGRO_EVENT event;

   if (!s_installed)
      return;

   memset(&event, 0, sizeof(event));
   event.mouse.type = ALLEGRO_EVENT_MOUSE_AXES;

   switch (e->type) {
      case SDL_MOUSEMOTION:
         s_x = e->motion.x;
         s_y = e->motion.y;
         event.mouse.dx = e->motion.xrel;
         event.mouse.dy = e->motion.yrel;
         break;

      case SDL_MOUSEWHEEL:
         s_z += e->wheel.y;
         s_w += e->wheel.x;
         event.mouse.dz = e->wheel.y;
         event.mouse.dw = e->wheel.x;
         break;

      default:
         event.mouse.button = get_button(e->button.button);
         if (event.mouse.button == 0)
            return;

         s_x = e->button.x;
         s_y = e->button.y;

         if (e->type == SDL_MOUSEBUTTONDOWN) {
            event.mouse.type = ALLEGRO_EVENT_MOUSE_BUTTON_DOWN;
            s_buttons |= 1 << (event.mouse.button - 1);
         }
         else {
            event.mouse.type = ALLEGRO_EVENT_MOUSE_BUTTON_UP;
            s_buttons &= ~(1 << (event.mouse.button - 1));
         }
         break;
   }

   event.mouse.timestamp = al_get_time();
   event.mouse.display = NULL;
   event.mouse.x = s_x;
   event.mouse.y = s_y;
   event.mouse.z = s_z;
   event.mouse.w = s_w;
   event.mouse.pressure = s_buttons ? 1.0f : 0.0f;

   a5_lock();
   a5_emit_event_locked(&s_source, &event);
   a5_unlock();
}

bool al_install_mouse(void)
{
   if (s_installed)
      return true;

   if (SDL_InitSubSystem(SDL_INIT_EVENTS) != 0)
      return false;

   a5_event_source_init(&s_source);
   s_installed = true;
   return true;
}

ALLEGRO_EVENT_SOURCE *al_get_mouse_event_source(void)
{
   return s_installed ? &s_source : NULL;
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
