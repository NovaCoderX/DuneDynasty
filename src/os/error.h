/** @file src/os/error.h Platform dependant error messages. */

#ifndef OS_ERROR_H
#define OS_ERROR_H

#if __cplusplus
extern "C" {
#endif

/* Log_Error, Log_Warning and Log_Debug print to stderr, Log_Info to
 * stdout; on Amiga they also go to the log (see error.c).  Not Info() and
 * Debug(): AmigaOS has functions of those names in dos.library and
 * exec.library.
 */
extern void Log_Error(const char *format, ...) __attribute__((format(printf, 1, 2)));
extern void Log_Warning(const char *format, ...) __attribute__((format(printf, 1, 2)));
extern void Log_Info(const char *format, ...) __attribute__((format(printf, 1, 2)));
extern void Log_Debug(const char *format, ...) __attribute__((format(printf, 1, 2)));

#if __cplusplus
}
#endif

#endif /* OS_ERROR_H */
