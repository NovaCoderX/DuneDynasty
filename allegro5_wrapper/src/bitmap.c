/* Bitmaps: bitmap.h, bitmap_lock.h, bitmap_io.h. */

#include "allegro5/allegro.h"
#include "a5_stub.h"

void al_set_new_bitmap_flags(int flags)
{
   A5_STUB();
}

int al_get_new_bitmap_flags(void)
{
   A5_STUB();
   return 0;
}

ALLEGRO_BITMAP *al_create_bitmap(int w, int h)
{
   A5_STUB();
   return NULL;
}

ALLEGRO_BITMAP *al_create_sub_bitmap(ALLEGRO_BITMAP *parent,
   int x, int y, int w, int h)
{
   A5_STUB();
   return NULL;
}

ALLEGRO_BITMAP *al_clone_bitmap(ALLEGRO_BITMAP *bitmap)
{
   A5_STUB();
   return NULL;
}

void al_destroy_bitmap(ALLEGRO_BITMAP *bitmap)
{
   A5_STUB();
}

int al_get_bitmap_width(ALLEGRO_BITMAP *bitmap)
{
   A5_STUB();
   return 0;
}

int al_get_bitmap_height(ALLEGRO_BITMAP *bitmap)
{
   A5_STUB();
   return 0;
}

bool al_is_sub_bitmap(ALLEGRO_BITMAP *bitmap)
{
   A5_STUB();
   return false;
}

void al_set_clipping_rectangle(int x, int y, int width, int height)
{
   A5_STUB();
}

ALLEGRO_LOCKED_REGION *al_lock_bitmap(ALLEGRO_BITMAP *bitmap,
   int format, int flags)
{
   A5_STUB();
   return NULL;
}

ALLEGRO_LOCKED_REGION *al_lock_bitmap_region(ALLEGRO_BITMAP *bitmap,
   int x, int y, int width, int height, int format, int flags)
{
   A5_STUB();
   return NULL;
}

void al_unlock_bitmap(ALLEGRO_BITMAP *bitmap)
{
   A5_STUB();
}

ALLEGRO_BITMAP *al_load_bitmap(const char *filename)
{
   A5_STUB();
   return NULL;
}

bool al_save_bitmap(const char *filename, ALLEGRO_BITMAP *bitmap)
{
   A5_STUB();
   return false;
}
