#pragma once

typedef enum NbLogLevel {
    NbLogLevel_Silent   = 0x0,
    NbLogLevel_Debug    = 0x1,
    NbLogLevel_Info     = 0x2,
    NbLogLevel_Warning  = 0x4,
    NbLogLevel_Error    = 0x8,
    NbLogLevel_Fatal    = 0x10,
    NbLogLevel_All      = 0xFF,
} NbLogLevel;

#define nbLogDebug(...)     nbLogStdout(NbLogLevel_Debug,   __FILE__, __LINE__, __VA_ARGS__)
#define nbLogInfo(...)      nbLogStdout(NbLogLevel_Info,    __FILE__, __LINE__, __VA_ARGS__)
#define nbLogWarning(...)   nbLogStdout(NbLogLevel_Warning, __FILE__, __LINE__, __VA_ARGS__)
#define nbLogError(...)     nbLogStdout(NbLogLevel_Error,   __FILE__, __LINE__, __VA_ARGS__)
#define nbLogFatal(...)     nbLogStdout(NbLogLevel_Fatal,   __FILE__, __LINE__, __VA_ARGS__)

#ifndef NDEBUG
    #define nbLogAssert(x)  do { if (!(x)) nbFatal("Assertion failed - " #x); } while (0)
#else
    #define nbLogAssert(x)
#endif

void    nbLogStdout         (NbLogLevel level, char const *file, int line, char const *fmt, ...);
