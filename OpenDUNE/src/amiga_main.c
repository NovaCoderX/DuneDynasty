
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SDL.h>


// Amiga includes.
#include <proto/dos.h>
#include <proto/exec.h>
#include <clib/icon_protos.h>
#include <workbench/startup.h>

extern int dune_main(int argc, char **argv, char *homeDir);

const char *ID = "$VER: Dune2 0.9.042\r\n";

// the startup message from workbench or 0 if started via cli
extern struct WBStartup *_WBenchMsg;
 

#define MAX_SYSTEM_PATH 255
#define MAX_ARGVS   100
#define MIN_STACK_BYTES 300000


int main(int argc, char **argv)
{
    char path[MAX_SYSTEM_PATH];
    struct Process* thisProcess;
    ULONG stackSize = 0;
    
   	thisProcess = (struct Process*) FindTask(NULL);
    
	if (thisProcess) {
        stackSize = thisProcess->pr_Task.tc_SPUpper - thisProcess->pr_Task.tc_SPLower;
    }
    
	if (stackSize < MIN_STACK_BYTES) {
        printf("Stack size (%d bytes) is too small...\n", stackSize);
        return EXIT_FAILURE;
    }
    
    if (!_WBenchMsg) {
        // Started from the shell.
        GetCurrentDirName((STRPTR)path, MAX_SYSTEM_PATH);
        
        return dune_main(argc, argv, path);
    } else {
        static char *myargv[MAX_ARGVS];
        static int myargc = 0;
  
        // Get path
        NameFromLock(_WBenchMsg->sm_ArgList[0].wa_Lock, (STRPTR)path, MAX_SYSTEM_PATH);
        CurrentDir(_WBenchMsg->sm_ArgList[0].wa_Lock);
        
        // Setup command line arguments.
        myargv[myargc] = (char *)malloc(strlen("Dune2")+1);
        strcpy(myargv[myargc++], "Dune2");
        
        return dune_main(myargc, myargv, path);
    }
}
