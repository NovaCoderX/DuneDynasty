/** @file src/os/readdir.c Directory traversal for POSIX systems */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <proto/dos.h>
//#include <proto/exec.h>
//#include <stdbool.h>
//#include <string.h>
//#include <stdio.h>

#include "types.h"
#include "file.h"
#include "error.h"
#include "strings.h"
#include "readdir.h"

/**
 * Process all files in the directory.
 *
 * @param dirpath path to directory to traverse.
 * @param callback function called back for each file found.
 * @return True if and only if everything was ok.
 */
bool ReadDir_ProcessAllFiles(const char *dirpath, bool (*callback)(const char *name, const char *path, uint32 size))
{
    BPTR lock;
    struct FileInfoBlock *fib;

    lock = Lock((STRPTR)dirpath, ACCESS_READ);
    if (!lock)
        return false;

    fib = (struct FileInfoBlock *)AllocDosObject(DOS_FIB, NULL);
    if (!fib) {
        UnLock(lock);
        return false;
    }

    if (Examine(lock, fib)) {
        while (ExNext(lock, fib)) {
            if (fib->fib_DirEntryType < 0) {  // It's a file (directories are positive)
                char path[1024];
                snprintf(path, sizeof(path), "%s%s", dirpath, fib->fib_FileName);
                if (!callback((const char*)fib->fib_FileName, path, fib->fib_Size)) {
                    FreeDosObject(DOS_FIB, fib);
                    UnLock(lock);
                    return false;
                }
            }
        }
    }

    FreeDosObject(DOS_FIB, fib);
    UnLock(lock);
    return true;
}

