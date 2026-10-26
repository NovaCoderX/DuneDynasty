/* Colours: color.h.  Real implementation, as in Allegro's pixels.c. */

#include "allegro5/allegro.h"

ALLEGRO_COLOR al_map_rgba(
   unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
   ALLEGRO_COLOR color;
   color.r = r * (1.0f / 255.0f);
   color.g = g * (1.0f / 255.0f);
   color.b = b * (1.0f / 255.0f);
   color.a = a * (1.0f / 255.0f);
   return color;
}

ALLEGRO_COLOR al_map_rgb(
   unsigned char r, unsigned char g, unsigned char b)
{
   return al_map_rgba(r, g, b, 255);
}
