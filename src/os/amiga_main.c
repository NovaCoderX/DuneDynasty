/** @file src/os/amiga_main.c Amiga entry point: checks the stack, records
 *  the program's directory in g_amiga_path, then runs dune_main(). */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Amiga includes.
#include <proto/dos.h>
#include <proto/exec.h>
#include <workbench/startup.h>

const char *ID = "$VER: DuneDynasty 1.5.7\r\n";

extern int dune_main(int argc, char **argv);

// the startup message from workbench or 0 if started via cli
extern struct WBStartup *_WBenchMsg;

#define MAX_SYSTEM_PATH 255
#define MAX_ARGVS 100

// Skirmish_GenerateMap() alone keeps about 72 KB of map data on the stack.
#define MIN_STACK_BYTES 300000

static int myargc = 0;
static char *myargv[MAX_ARGVS];

char g_amiga_path[MAX_SYSTEM_PATH];

int main(int argc, char **argv)
{
    struct Process* thisProcess;
    ULONG stackSize = 0;
    int rc;

    thisProcess = (struct Process*)FindTask(NULL);

    if (thisProcess) {
        stackSize = (ULONG)thisProcess->pr_Task.tc_SPUpper - (ULONG)thisProcess->pr_Task.tc_SPLower;
    }

    if (stackSize < MIN_STACK_BYTES) {
        printf("Stack size (%lu bytes) is too small...\n", stackSize);
        return EXIT_FAILURE;
    }

    if (!_WBenchMsg) {
        // Started from the shell.
        GetCurrentDirName((STRPTR)g_amiga_path, MAX_SYSTEM_PATH);

        rc = dune_main(argc, argv);
    } else {
        BPTR oldDir;

        // Get path
        if (!NameFromLock(_WBenchMsg->sm_ArgList[0].wa_Lock, (STRPTR)g_amiga_path, MAX_SYSTEM_PATH)) {
            printf("Could not determine the program directory.\n");
            return EXIT_FAILURE;
        }

        // Set working directory.
        oldDir = CurrentDir(_WBenchMsg->sm_ArgList[0].wa_Lock);

        // Setup command line arguments.
        myargv[myargc] = (char*)malloc(strlen("DuneDynasty")+1);
        strcpy(myargv[myargc++], "DuneDynasty");

        rc = dune_main(myargc, myargv);
        free(myargv[0]);
        CurrentDir(oldDir);
    }

    return rc;
}
