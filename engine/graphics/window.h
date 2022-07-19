#pragma once
#include <stdbool.h>

typedef enum NbEventType {
    NbEventType_WindowClose,
    NbEventType_WindowResize,
    NbEventType_WindowFocus,
    NbEventType_WindowUnfocus,
    NbEventType_MouseMotion,
    NbEventType_MouseScroll,
    NbEventType_MouseUp,
    NbEventType_MouseDown,
    NbEventType_KeyUp,
    NbEventType_KeyDown,
} NbEventType;

typedef union NbEventData {
    struct { int width, height;     } resize;
    struct { int key, mods;         } key;
    struct { int button, mods, x, y;} mouse;
    struct { int dx, dy;            } scroll;
} NbEventData;

typedef struct NbWindow NbWindow;

typedef void NbEventHandler(NbWindow *window, NbEventType type, NbEventData const *data);

typedef struct NbWindowDescriptor {
    NbEventHandler *eventHandler;
    char const *title;
    int width;
    int height;
    bool fullscreen;
    bool hidden;
} NbWindowDescriptor;

bool        nbInit                  (void);
void        nbQuit                  (void);

NbWindow   *nbWindowCreate          (NbWindowDescriptor const *desc);
void        nbWindowDelete          (NbWindow *window);
void        nbWindowPollEvents      (void);
void        nbWindowSwapBuffers     (NbWindow const *window);

void        nbWindowGetSize         (NbWindow const *window, int *width, int *height);
void        nbWindowGetPosition     (NbWindow const *window, int *x, int *y);

bool        nbWindowIsClosed        (NbWindow const *window);
bool        nbWindowIsVisible       (NbWindow const *window);
bool        nbWindowIsFullscreen    (NbWindow const *window);

void        nbWindowSetSize         (NbWindow *window, int width, int height);
void        nbWindowSetPosition     (NbWindow *window, int x, int y);
void        nbWindowSetFullscreen   (NbWindow *window, bool fullscreen);
void        nbWindowSetVisibile     (NbWindow *window, bool visible);
void        nbWindowSetClosed       (NbWindow *window, bool closed);

