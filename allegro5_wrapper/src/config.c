/* Configuration files: config.h. */

#include "allegro5/allegro.h"
#include "a5_stub.h"

ALLEGRO_CONFIG *al_create_config(void)
{
   A5_STUB();
   return NULL;
}

void al_destroy_config(ALLEGRO_CONFIG *config)
{
   A5_STUB();
}

ALLEGRO_CONFIG *al_load_config_file(const char *filename)
{
   A5_STUB();
   return NULL;
}

bool al_save_config_file(const char *filename, const ALLEGRO_CONFIG *config)
{
   A5_STUB();
   return false;
}

const char *al_get_config_value(const ALLEGRO_CONFIG *config,
   const char *section, const char *key)
{
   A5_STUB();
   return NULL;
}

void al_set_config_value(ALLEGRO_CONFIG *config,
   const char *section, const char *key, const char *value)
{
   A5_STUB();
}

void al_add_config_comment(ALLEGRO_CONFIG *config,
   const char *section, const char *comment)
{
   A5_STUB();
}
