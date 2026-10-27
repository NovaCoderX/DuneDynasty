/** @file src/os/error.c System dependant error messages. */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "types.h"
#include "strings.h"

#include "error.h"

#if defined(__AMIGA__)
#include <time.h>
#include "../file.h"

/* On the Amiga, errors and warnings are also written to dunedynasty.log in
 * the game directory, where they survive the game exiting or crashing.  The
 * log is created by a run's first message, so a run without any leaves the
 * previous log in place; the date at the top tells them apart.
 */
static FILE *s_log = NULL;
static bool s_logFailed = false;

static void Log_Write(const char *format, va_list ap)
{
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

	vfprintf(s_log, format, ap);

	/* Not every message ends its line. */
	if (format[0] != '\0' && format[strlen(format) - 1] != '\n')
		fputc('\n', s_log);

	/* So the log is complete up to a crash. */
	fflush(s_log);
}
#endif

void Error(const char *format, ...) {
	va_list ap;

	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);

#if defined(__AMIGA__)
	va_start(ap, format);
	Log_Write(format, ap);
	va_end(ap);
#endif
}

void Warning(const char *format, ...) {
	va_list ap;

	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);

#if defined(__AMIGA__)
	va_start(ap, format);
	Log_Write(format, ap);
	va_end(ap);
#endif
}
