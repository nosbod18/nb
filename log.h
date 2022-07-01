#pragma once
#include <stdlib.h> // abort
#include <stdio.h>  // printf, strftime
#include <time.h>   // time_t, time, localtime

#ifndef LOG_LEVEL
    #define LOG_LEVEL LOG_LEVEL_INFO
#endif

enum {
    LOG_LEVEL_SILENT,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL,
};

#define log_stdout(COLOR, LEVEL, ...) do {\
    time_t _raw__ = time(NULL);\
    char _now__[16];\
    _now__[strftime(_now__, sizeof _now__, "%T", localtime(&_raw__))] = 0;\
    printf("%s%s [%7s] (%s:%d) - ", COLOR, _now__, LEVEL, __FILE__, __LINE__);\
    printf(__VA_ARGS__);\
    printf("\x1b[0m\n");\
} while (0)

#define log_debug(...) do {\
    if (LOG_LEVEL <= LOG_LEVEL_DEBUG)\
        log_stdout("", "DEBUG", __VA_ARGS__);\
} while (0)

#define log_info(...) do {\
    if (LOG_LEVEL <= LOG_LEVEL_INFO)\
        log_stdout("\x1b[36m", "INFO", __VA_ARGS__);\
} while (0)

#define log_warn(...) do {\
    if (LOG_LEVEL <= LOG_LEVEL_WARNING)\
        log_stdout("\x1b[33m", "WARNING", __VA_ARGS__);\
} while (0)

#define log_error(...) do {\
    if (LOG_LEVEL <= LOG_LEVEL_ERROR)\
        log_stdout("\x1b[31m", "ERROR", __VA_ARGS__);\
} while (0)

#define log_fatal(...) do {\
    if (LOG_LEVEL <= LOG_LEVEL_FATAL) {\
        log_stdout("\x1b[35m", "FATAL", __VA_ARGS__);\
        abort();\
    }\
} while (0)

#ifndef NDEBUG
    #define log_assert(X) do {\
       if (!(X))\
           log_fatal("Assertion failed - " #X);\
    } while (0)
#else
    #define log_assert(X)
#endif

