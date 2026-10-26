/* Paths: path.h. */

#include "allegro5/allegro.h"
#include "a5_stub.h"

ALLEGRO_PATH *al_create_path(const char *str)
{
   A5_STUB();
   return NULL;
}

ALLEGRO_PATH *al_create_path_for_directory(const char *str)
{
   A5_STUB();
   return NULL;
}

void al_destroy_path(ALLEGRO_PATH *path)
{
   A5_STUB();
}

const char *al_path_cstr(const ALLEGRO_PATH *path, char delim)
{
   A5_STUB();
   return "";
}

void al_replace_path_component(ALLEGRO_PATH *path, int i, const char *s)
{
   A5_STUB();
}

void al_set_path_filename(ALLEGRO_PATH *path, const char *filename)
{
   A5_STUB();
}

const char *al_get_path_filename(const ALLEGRO_PATH *path)
{
   A5_STUB();
   return "";
}

const char *al_get_path_basename(const ALLEGRO_PATH *path)
{
   A5_STUB();
   return "";
}

const char *al_get_path_extension(const ALLEGRO_PATH *path)
{
   A5_STUB();
   return "";
}

const char *al_get_path_tail(const ALLEGRO_PATH *path)
{
   A5_STUB();
   return NULL;
}
