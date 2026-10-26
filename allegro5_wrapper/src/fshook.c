/* File system entries and directories: fshook.h. */

#include "allegro5/allegro.h"
#include "a5_stub.h"

ALLEGRO_FS_ENTRY *al_create_fs_entry(const char *path)
{
   A5_STUB();
   return NULL;
}

void al_destroy_fs_entry(ALLEGRO_FS_ENTRY *e)
{
   A5_STUB();
}

const char *al_get_fs_entry_name(ALLEGRO_FS_ENTRY *e)
{
   A5_STUB();
   return NULL;
}

uint32_t al_get_fs_entry_mode(ALLEGRO_FS_ENTRY *e)
{
   A5_STUB();
   return 0;
}

bool al_open_directory(ALLEGRO_FS_ENTRY *e)
{
   A5_STUB();
   return false;
}

ALLEGRO_FS_ENTRY *al_read_directory(ALLEGRO_FS_ENTRY *e)
{
   A5_STUB();
   return NULL;
}

bool al_close_directory(ALLEGRO_FS_ENTRY *e)
{
   A5_STUB();
   return false;
}

bool al_make_directory(const char *path)
{
   A5_STUB();
   return false;
}
