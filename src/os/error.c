/** @file src/os/error.c System dependant error messages. */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "types.h"
#include "strings.h"

#include "error.h"

enum LogLevel {
	LOGLEVEL_ERROR,
	LOGLEVEL_WARNING,
	LOGLEVEL_INFO,
	LOGLEVEL_DEBUG
};

#if defined(__AMIGA__)
#include <time.h>
#include "../file.h"

/* On the Amiga, every message is also written to dunedynasty.log in the
 * game directory, where it survives the game exiting or crashing.  The log
 * is created by a run's first message, so a run without any leaves the
 * previous log in place; the date at the top tells them apart.
 */
static FILE *s_log = NULL;
static bool s_logFailed = false;

static void LogFile_Write(enum LogLevel level, const char *format, va_list ap)
{
	static const char * const levelNames[] = { "ERROR:", "WARNING:", "INFO:", "DEBUG:" };
	char message[1024];
	size_t length;

	if (s_log == NULL) {
		char path[1024];
		char date[32];
		const time_t now = time(NULL);

		if (s_logFailed) return;

		snprintf(path, sizeof(path), "%s/dunedynasty.log", g_amiga_path);
		s_log = fopen(path, "w");
		if (s_log == NULL) {
			s_logFailed = true;
			fprintf(stderr, "Could not create %s\n", path);
			return;
		}

		strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", localtime(&now));
		fprintf(s_log, "Dune Dynasty log, %s\n", date);
	}

	/* Not every message ends its line; the log puts each on its own. */
	vsnprintf(message, sizeof(message), format, ap);
	length = strlen(message);
	fprintf(s_log, "%-9s%s%s", levelNames[level], message,
		(length > 0 && message[length - 1] == '\n') ? "" : "\n");

	/* So the log is complete up to a crash. */
	fflush(s_log);
}
#endif

static void Message(enum LogLevel level, FILE *console, const char *format, va_list ap)
{
#if defined(__AMIGA__)
	va_list log_ap;

	va_copy(log_ap, ap);
#else
	VARIABLE_NOT_USED(level);
#endif

	vfprintf(console, format, ap);

#if defined(__AMIGA__)
	LogFile_Write(level, format, log_ap);
	va_end(log_ap);
#endif
}

void Log_Error(const char *format, ...) {
	va_list ap;

	va_start(ap, format);
	Message(LOGLEVEL_ERROR, stderr, format, ap);
	va_end(ap);
}

void Log_Warning(const char *format, ...) {
	va_list ap;

	va_start(ap, format);
	Message(LOGLEVEL_WARNING, stderr, format, ap);
	va_end(ap);
}

void Log_Info(const char *format, ...) {
	va_list ap;

	va_start(ap, format);
	Message(LOGLEVEL_INFO, stdout, format, ap);
	va_end(ap);
}

void Log_Debug(const char *format, ...) {
	va_list ap;

	va_start(ap, format);
	Message(LOGLEVEL_DEBUG, stderr, format, ap);
	va_end(ap);
}
