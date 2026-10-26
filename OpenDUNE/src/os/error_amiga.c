/** @file src/os/error_win32.c System dependant error messages for win32. */

#include <string.h>

#include "types.h"
#include "strings.h"
#include "error.h"

#ifdef _DEBUG
FILE * g_outlog = NULL;
#endif





void Error(const char *message, ...) {
    va_list		argptr;
    char		text[1024];
    FILE        *errorLogFile = NULL;

    va_start (argptr, message);
    vsprintf (text, message, argptr);
    va_end (argptr);

    // Always append for warnings.
    errorLogFile = fopen("DUNE_ERROR.TXT", "a");
    if (errorLogFile) {
        setbuf(errorLogFile, NULL);
        fwrite(text, 1, strlen(text), errorLogFile);
        fclose(errorLogFile);
        errorLogFile = NULL;
    }	
}
 
void Warning(const char *message, ...) {
    va_list		argptr;
    char		text[1024];
    FILE        *warningLogFile = NULL;

    va_start (argptr, message);
    vsprintf (text, message, argptr);
    va_end (argptr);    
    
    // Always append for warnings.
    if (!warningLogFile) {
        warningLogFile = fopen("DUNE_WARNING.TXT", "a");
        if (warningLogFile) {
            setbuf(warningLogFile, NULL);
            fwrite(text, 1, strlen(text), warningLogFile);
            fclose(warningLogFile);
            warningLogFile = NULL;
        }
    }
}

#ifdef _DEBUG
void Debug(const char *message, ...) {
    va_list		argptr;
    char		text[1024];
       
    va_start (argptr, message);
    vsprintf (text, message, argptr);
    va_end (argptr);
    
    if (g_outlog) {
        fwrite(text, 1, strlen(text), g_outlog);
    } 
}
#endif
