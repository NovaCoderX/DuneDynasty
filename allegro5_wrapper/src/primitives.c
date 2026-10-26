/* Primitives addon: allegro_primitives.h. */

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "a5_stub.h"

bool al_init_primitives_addon(void)
{
   A5_STUB();
   return false;
}

void al_draw_line(float x1, float y1, float x2, float y2,
   ALLEGRO_COLOR color, float thickness)
{
   A5_STUB();
}

void al_draw_rectangle(float x1, float y1, float x2, float y2,
   ALLEGRO_COLOR color, float thickness)
{
   A5_STUB();
}

void al_draw_filled_rectangle(float x1, float y1, float x2, float y2,
   ALLEGRO_COLOR color)
{
   A5_STUB();
}

int al_draw_indexed_prim(const void *vtxs, const ALLEGRO_VERTEX_DECL *decl,
   ALLEGRO_BITMAP *texture, const int *indices, int num_vtx, int type)
{
   A5_STUB();
   return 0;
}
