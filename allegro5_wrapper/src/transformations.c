/* Transformations: transformations.h.
 *
 * al_identity_transform() and al_build_transform() are the real code from
 * Allegro's transformations.c; only applying a transform needs a target.
 */

#include <math.h>
#include "allegro5/allegro.h"
#include "a5_stub.h"

void al_identity_transform(ALLEGRO_TRANSFORM *trans)
{
   trans->m[0][0] = 1;
   trans->m[0][1] = 0;
   trans->m[0][2] = 0;
   trans->m[0][3] = 0;

   trans->m[1][0] = 0;
   trans->m[1][1] = 1;
   trans->m[1][2] = 0;
   trans->m[1][3] = 0;

   trans->m[2][0] = 0;
   trans->m[2][1] = 0;
   trans->m[2][2] = 1;
   trans->m[2][3] = 0;

   trans->m[3][0] = 0;
   trans->m[3][1] = 0;
   trans->m[3][2] = 0;
   trans->m[3][3] = 1;
}

void al_build_transform(ALLEGRO_TRANSFORM *trans, float x, float y,
   float sx, float sy, float theta)
{
   float c, s;

   c = cosf(theta);
   s = sinf(theta);

   trans->m[0][0] = sx * c;
   trans->m[0][1] = sy * s;
   trans->m[0][2] = 0;
   trans->m[0][3] = 0;

   trans->m[1][0] = -sx * s;
   trans->m[1][1] = sy * c;
   trans->m[1][2] = 0;
   trans->m[1][3] = 0;

   trans->m[2][0] = 0;
   trans->m[2][1] = 0;
   trans->m[2][2] = 1;
   trans->m[2][3] = 0;

   trans->m[3][0] = x;
   trans->m[3][1] = y;
   trans->m[3][2] = 0;
   trans->m[3][3] = 1;
}

void al_use_transform(const ALLEGRO_TRANSFORM *trans)
{
   A5_STUB();
}
