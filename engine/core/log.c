#include "log.h"
#include <time.h>   // time_t, time, localtime
#include <stdio.h>  // printf, strftime
#include <stdarg.h> // va_list, va_start
#include <stdlib.h> // abort

static char const *levels[] = {
    "", "DEBUG", "INFO", "WARNING", "ERROR", "FATAL"
};

static char const *colors[] = {
    "", "", "\x1b[36m", "\x1b[33m", "\x1b[31m", "\x1b[35m"
};

void nbLogStdout(NbLogLevel level, char const *file, int line, char const *fmt, ...) {
    time_t raw = time(NULL);
    char now[16];
    now[strftime(now, 16, "%T", localtime(&raw))] = 0;

    va_list va;
    va_start(va, fmt);

    printf("%s%s %10s (%s:%d) - ", colors[level], now, levels[level], file, line);
    vprintf(fmt, va);
    printf("\x1b[0m\n");

    va_end(va);

    if (level == NbLogLevel_Fatal)
        abort();
}
