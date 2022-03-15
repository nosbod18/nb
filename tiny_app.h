#ifndef __tiny_app_h__
#define __tiny_app_h__

typedef enum tapp_key {
        TAPP_KEY_INVALID                = 0x00,
        TAPP_KEY_BACKSPACE              = 0x08,
        TAPP_KEY_TAB                    = 0x09,
        TAPP_KEY_ESCAPE                 = 0x1b,
        TAPP_KEY_SPACE                  = ' ',
        TAPP_KEY_BANG                   = '!',
        TAPP_KEY_QUOTE                  = '\"',
        TAPP_KEY_POUND                  = '#',
        TAPP_KEY_DOLLAR                 = '$',
        TAPP_KEY_PERCENT                = '%',
        TAPP_KEY_AMPERSAN               = '&',
        TAPP_KEY_APOSTROPHE             = '\'',
        TAPP_KEY_LEFT_PARENTHESES       = '(',
        TAPP_KEY_RIGHT_PARENTHESES      = ')',
        TAPP_KEY_ASTERISK               = '*',
        TAPP_KEY_PLUS                   = '+',
        TAPP_KEY_COMMA                  = ',',
        TAPP_KEY_MINUS                  = '-',
        TAPP_KEY_PERIOD                 = '.',
        TAPP_KEY_FORWARD_SLASH          = '/',
        TAPP_KEY_0                      = '0',
        TAPP_KEY_1                      = '1',
        TAPP_KEY_2                      = '2',
        TAPP_KEY_3                      = '3',
        TAPP_KEY_4                      = '4',
        TAPP_KEY_5                      = '5',
        TAPP_KEY_6                      = '6',
        TAPP_KEY_7                      = '7',
        TAPP_KEY_8                      = '8',
        TAPP_KEY_9                      = '9',
        TAPP_KEY_COLON                  = ':',
        TAPP_KEY_SEMICOLON              = ';',
        TAPP_KEY_LEFT_ANGLE_BRACKET     = '<',
        TAPP_KEY_EQUALS                 = '=',
        TAPP_KEY_RIGHT_ANGLE_BRACKET    = '>',
        TAPP_KEY_QUESTION_MARK          = '?',
        TAPP_KEY_AT                     = '@',
        TAPP_KEY_A                      = 'A',
        TAPP_KEY_B                      = 'B',
        TAPP_KEY_C                      = 'C',
        TAPP_KEY_D                      = 'D',
        TAPP_KEY_E                      = 'E',
        TAPP_KEY_F                      = 'F',
        TAPP_KEY_G                      = 'G',
        TAPP_KEY_H                      = 'H',
        TAPP_KEY_I                      = 'I',
        TAPP_KEY_J                      = 'J',
        TAPP_KEY_K                      = 'K',
        TAPP_KEY_L                      = 'L',
        TAPP_KEY_M                      = 'M',
        TAPP_KEY_N                      = 'N',
        TAPP_KEY_O                      = 'O',
        TAPP_KEY_P                      = 'P',
        TAPP_KEY_Q                      = 'Q',
        TAPP_KEY_R                      = 'R',
        TAPP_KEY_S                      = 'S',
        TAPP_KEY_T                      = 'T',
        TAPP_KEY_U                      = 'U',
        TAPP_KEY_V                      = 'V',
        TAPP_KEY_W                      = 'W',
        TAPP_KEY_X                      = 'X',
        TAPP_KEY_Y                      = 'Y',
        TAPP_KEY_Z                      = 'Z',
        TAPP_KEY_LEFT_BRACKET           = '[',
        TAPP_KEY_BACKSLASH              = '\\',
        TAPP_KEY_RIGHT_BRACKET          = ']',
        TAPP_KEY_CARROT                 = '^',
        TAPP_KEY_UNDERSCORE             = '_',
        TAPP_KEY_GRAVE_ACCENT           = '`',
        TAPP_KEY_LEFT_CURLY_BRACE       = '{',
        TAPP_KEY_VERTICALbAR            = '|',
        TAPP_KEY_RIGHT_CURLY_BRACE      = '}',
        TAPP_KEY_TILDA                  = '~',
        TAPP_KEY_DELETE                 = 0x7f,
        TAPP_KEY_KEYPAD_0               = 0x80,
        TAPP_KEY_KEYPAD_1               = 0x81,
        TAPP_KEY_KEYPAD_2               = 0x82,
        TAPP_KEY_KEYPAD_3               = 0x83,
        TAPP_KEY_KEYPAD_4               = 0x84,
        TAPP_KEY_KEYPAD_5               = 0x85,
        TAPP_KEY_KEYPAD_6               = 0x86,
        TAPP_KEY_KEYPAD_7               = 0x87,
        TAPP_KEY_KEYPAD_8               = 0x88,
        TAPP_KEY_KEYPAD_9               = 0x89,
        TAPP_KEY_KEYPAD_SEPARATOR       = 0x8a,
        TAPP_KEY_KEYPAD_FORWARD_SLASH   = 0x8b,
        TAPP_KEY_KEYPAD_ASTERISK        = 0x8c,
        TAPP_KEY_KEYPAD_PLUS            = 0x8d,
        TAPP_KEY_KEYPAD_MINUS           = 0x8e,
        TAPP_KEY_KEYPAD_ENTER           = 0x8f,
        TAPP_KEY_UP                     = 0x90,
        TAPP_KEY_DOWN                   = 0x91,
        TAPP_KEY_LEFT                   = 0x92,
        TAPP_KEY_RIGHT                  = 0x93,
        TAPP_KEY_PAGE_UP                = 0x94,
        TAPP_KEY_PAGE_DOWN              = 0x95,
        TAPP_KEY_HOME                   = 0x96,
        TAPP_KEY_END                    = 0x97,
        TAPP_KEY_INSERT                 = 0x98,
        TAPP_KEY_F1                     = 0xa0,
        TAPP_KEY_F2                     = 0xa2,
        TAPP_KEY_F3                     = 0xa3,
        TAPP_KEY_F4                     = 0xa4,
        TAPP_KEY_F5                     = 0xa5,
        TAPP_KEY_F6                     = 0xa6,
        TAPP_KEY_F7                     = 0xa7,
        TAPP_KEY_F8                     = 0xa8,
        TAPP_KEY_F9                     = 0xa9,
        TAPP_KEY_F10                    = 0xaa,
        TAPP_KEY_F11                    = 0xab,
        TAPP_KEY_F12                    = 0xac,
        TAPP_KEY_LEFT_SHIFT             = 0xb0,
        TAPP_KEY_RIGHT_SHIFT            = 0xb1,
        TAPP_KEY_LEFT_CONTROL           = 0xb2,
        TAPP_KEY_RIGHT_CONTROL          = 0xb3,
        TAPP_KEY_LEFT_ALT               = 0xb4,
        TAPP_KEY_RIGHT_ALT              = 0xb5,
        TAPP_KEY_LEFT_SUPER             = 0xb6,
        TAPP_KEY_RIGHT_SUPER            = 0xb7,
        TAPP_KEY_MENU                   = 0xb8,
        TAPP_KEY_ALTGR                  = 0xb9,
        TAPP_KEY_NUM_LOCK               = 0xba,
        TAPP_KEY_CAPS_LOCK              = 0xbb,
        TAPP_KEY_SCROLL_LOCK            = 0xbc,
        TAPP_KEY_LAST                   = 0x100 // 256
} tapp_key;

typedef enum tapp_button {
        TAPP_MOUSE_BUTTON_1             = 0x01,
        TAPP_MOUSE_BUTTON_2             = 0x02,
        TAPP_MOUSE_BUTTON_3             = 0x03,
        TAPP_MOUSE_BUTTON_4             = 0x04,
        TAPP_MOUSE_BUTTON_5             = 0x05,
        TAPP_MOUSE_BUTTON_6             = 0x05,
        TAPP_MOUSE_BUTTON_7             = 0x07,
        TAPP_MOUSE_BUTTON_LAST          = 0x08,
        TAPP_MOUSE_BUTTON_LEFT          = TAPP_MOUSE_BUTTON_1,
        TAPP_MOUSE_BUTTON_MIDDLE        = TAPP_MOUSE_BUTTON_2,
        TAPP_MOUSE_BUTTON_RIGHT         = TAPP_MOUSE_BUTTON_3,
} tapp_button;

typedef enum tapp_mod {
        TAPP_MOD_SHIFT                  = 1 << 0,
        TAPP_MOD_CONTROL                = 1 << 1,
        TAPP_MOD_ALT                    = 1 << 2,
        TAPP_MOD_SUPER                  = 1 << 3,
        TAPP_MOD_NUM_LOCK               = 1 << 4,
        TAPP_MOD_CAPS_LOCK              = 1 << 5,
        TAPP_MOD_LAST
} tapp_mod;

typedef enum tapp_event_type {
        TAPP_EVENT_TYPE_NONE            = 0, // No event
        TAPP_EVENT_TYPE_WINDOWCLOSE,         // A window was closed. Note that this does not necessarily mean TAPP_EVENT_TYPE_QUIT if there is multiple windows
        TAPP_EVENT_TYPE_WINDOWEXPOSE,        // A window was exposed and needs to be redrawn
        TAPP_EVENT_TYPE_WINDOWRESIZE,        // A window's size was changed
        TAPP_EVENT_TYPE_WINDOWFOCUS,         // A window's focus was changed
        TAPP_EVENT_TYPE_MOUSEBUTTON,         // A mouse button was pressed or released
        TAPP_EVENT_TYPE_MOUSEENTER,          // The mouse entered the window space
        TAPP_EVENT_TYPE_MOUSELEAVE,          // The mouse left the window space
        TAPP_EVENT_TYPE_MOUSEMOTION,         // The mouse changed position
        TAPP_EVENT_TYPE_MOUSESCROLL,         // The scroll wheel was moved
        TAPP_EVENT_TYPE_KEY,                 // A key was pressed or released
} tapp_event_type;

typedef struct tapp_window tapp_window;

typedef struct tapp_window_desc {
        char const *title;
        int x;
        int y;
        int width;
        int height;
        int fullscreen;
        int vsync;
} tapp_window_desc;

typedef struct tapp_close_event {
        tapp_event_type type;
        tapp_window *window;
} tapp_close_event;

typedef struct tapp_expose_event {
        tapp_event_type type;
        tapp_window *window;
        int visible;
} tapp_expose_event;

typedef struct tapp_focus_event {
        tapp_event_type type;
        tapp_window *window;
        int focused;
} tapp_focus_event;

typedef struct tapp_resize_event {
        tapp_event_type type;
        tapp_window *window;
        int width;
        int height;
} tapp_resize_event;

typedef struct tapp_key_event {
        tapp_event_type type;
        tapp_key sym;
        unsigned mods;
        int pressed;
} tapp_key_event;

typedef struct tapp_button_event {
        tapp_event_type type;
        tapp_button sym;
        unsigned mods;
        int pressed;
        int x;
        int y;
} tapp_button_event;

typedef struct tapp_motion_event {
        tapp_event_type type;
        double dx;
        double dy;
} tapp_motion_event;

typedef struct tapp_scroll_event {
        tapp_event_type type;
        double dx;
        double dy;
} tapp_scroll_event;

typedef union tapp_event {
        int                     type;
        tapp_close_event        close;
        tapp_expose_event       expose;
        tapp_focus_event        focus;
        tapp_resize_event       resize;
        tapp_key_event          key;
        tapp_button_event       button;
        tapp_motion_event       motion;
        tapp_scroll_event       scroll;
} tapp_event;

typedef void (*tapp_init_callback)(void);
typedef void (*tapp_event_callback)(tapp_event const *event);
typedef void (*tapp_update_callback)(double dt);
typedef void (*tapp_quit_callback)(void);

typedef struct tapp_desc {
        tapp_window_desc        window;
        tapp_init_callback      on_init;
        tapp_event_callback     on_event;
        tapp_update_callback    on_update;
        tapp_quit_callback      on_quit;
} tapp_desc;


tapp_desc       tapp_main               (int argc, char **argv);

void            tapp_process_events     (void);
int             tapp_get_should_quit    (void);
void            tapp_set_should_quit    (int quit);

tapp_window    *tapp_window_create      (tapp_window_desc const *desc);
void            tapp_window_delete      (tapp_window *window);
void            tapp_window_show        (tapp_window const *window, int show);
void            tapp_window_get_pos     (tapp_window const *window, int *x, int *y);
void            tapp_window_get_size    (tapp_window const *window, int *w, int *h);
void            tapp_window_set_pos     (tapp_window *window, int x, int y);
void            tapp_window_set_size    (tapp_window *window, int w, int h);
void            tapp_window_set_title   (tapp_window *window, char const *title);


/***********************************************************************************************************************************************************
************************************************************************************************************************************************************
****                                                                                                                                                    ****
****                                                                                                                                                    ****
****                                                                   Implementation                                                                   ****
****                                                                                                                                                    ****
****                                                                                                                                                    ****
************************************************************************************************************************************************************
***********************************************************************************************************************************************************/


#if defined(TAPP_IMPL) || defined(TINY_IMPL)
#ifndef __tiny_app_c__
#define __tiny_app_c__

#if defined(__linux__)
        #include <X11/Xlib.h>
#endif // __linux__

#include <stdio.h> // fprintf
#include <stdlib.h>


struct tapp_window {
#if defined(__linux__)
        struct {
                Display *dpy;
                Window wnd;
                Atom wm_del_win;
        } x11;
#endif

        tapp_window_desc desc;
};

static struct {
        tapp_desc desc;
        int should_quit;
} _tapp = 0;

// Internal function prototypes

void _tapp_post_quit_event      (void);
void _tapp_post_close_event     (tapp_window *window);
void _tapp_post_resize_event    (tapp_window *window, int w, int h);
void _tapp_post_expose_event    (tapp_window *window, int exposed);
void _tapp_post_focus_event     (tapp_window *window, int focused);
void _tapp_post_key_event       (tapp_key sym, unsigned mods, int pressed);
void _tapp_post_button_event    (tapp_button sym, unsigned mods, int pressed);
void _tapp_post_enter_event     (tapp_window *window, int x, int y);
void _tapp_post_leave_event     (tapp_window *window, int x, int y);
void _tapp_post_motion_event    (double dx, double dy);
void _tapp_post_scroll_event    (double dx, double dy);

inline void _tapp_noop          (void) {}


//==============================================================
// Linux

#if defined(__linux__)

tapp_window *tapp_window_create(tapp_window_desc const *desc) {
        tapp_window *window = calloc(1, sizeof *window);
        if (!window) {
                return NULL;
        }

        /* Open X11 display */
        window->dpy = XOpenDisplay(NULL);
        if (!dpy) {
                TAPP_LOG("Failed to connect to X server");
                tapp_window_delete(window);
                return NULL;
        }

        /* Setup common parameters for window creation */
        Window  root_wnd = DefaultRootWindow(dpy);
        int     screen   = DefaultScreen(dpy);
        Visual *visual   = DefaultVisual(dpy, screen);
        int     depth    = DefaultDepth(dpy, screen);

        /* Setup window attributes */
        XSetWindowAttributes swa = {
                .background_pixel = WhitePixel(dpy, screen),
                .event_mask       = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
        };

        unsigned long swa_mask = CWEventMask | CWBorderPixel | CWBackPixel;

        Window wnd = XCreateWindow(dpy, root_wnd, x, y, w, h, 0, depth, InputOutput, visual, swa_mask, &swa);

        tapp_window_set_title(window, desc->title);
        tapp_window_show(window, 1);

        /* Enable WM_DELETE_WINDOW protocol */
        Atom wm_del_win = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(dpy, wnd, &wm_del_win, 1);
}

void tapp_window_delete(tapp_window *window) {
        XDestroyWindow(dpy, wnd);

        if (!(--g_win_count)) {
                XCloseDisplay(dpy);
        }
}

void tapp_window_show(tapp_window *window, int show) {
        if (show) {
                XMapWindow(_tapp.x11.dpy, window->x11.wnd);
                XMoveWindow(_tapp.x11.dpy, window->x11.wnd, window->desc.x, window->desc.y);
        } else {
                XUnmapWindow(_tapp.x11.dpy, window->x11.wnd);
        }
}

void tapp_window_set_title(tapp_window *window, char const *title) {
        XStoreName(_tapp.x11.dpy, window->x11.wnd, title);
}

int _tapp_translate_key(int key) {
        (void)key;
        return 0;
}

#endif // __linux__

//==============================================================
// Entry point

#ifndef TAPP_CUSTOM_ENTRY

int main(int argc, char **argv) {
        tapp_desc desc = tapp_main(argc, argv);

        if (!desc.on_init)   desc.on_init   = _tapp_noop;
        if (!desc.on_event)  desc.on_event  = _tapp_noop;
        if (!desc.on_update) desc.on_update = _tapp_noop;
        if (!desc.on_quit)   desc.on_quit   = _tapp_noop;

        tapp_window *main_window = tapp_window_create(&desc.window);
        if (!main_window) {
                TAPP_LOG("Failed to create main window");
                return -1;
        }

        desc.on_init();

        double dt = 0.0;
        while (tapp_process_events(main_window, desc.on_event)) {
                desc.on_update();
        }

        if (desc.on_quit)
                desc.on_quit();

        tapp_window_delete(main_window);
        return 0;
}

#endif // !TAPP_CUSTOM_ENTRY


//==============================================================
// Internal function implementation

void _tapp_post_quit_event(tapp_event_callback on_event) {
        on_event(&(tapp_event){
                .type = TAPP_EVENT_TYPE_QUIT
        });
}

void _tapp_post_resize_event(tapp_event_callback on_event, tapp_window *window, int w, int h) {
        on_event(&(tapp_event){
                .resize = {
                        .type = TAPP_EVENT_TYPE_RESIZE,
                        .window = window,
                        .width = w,
                        .height = h
                },
        });

        window->desc.width  = w;
        window->desc.height = h;
}

void _tapp_post_button_event(tapp_event_callback on_event, int sym, int x, int y, int pressed) {
        on_event(&(tapp_event){
                .button = {
                        .type = TAPP_EVENT_TYPE_MOUSEBUTTON,
                        .x = x,
                        .y = y,
                        .sym = sym,
                        .pressed = pressed,
                }
        });
}

void _tapp_post_key_event(tapp_event_callback on_event, int sym, int pressed) {
        on_event(&(tapp_event){
                .key = {
                        .type = TAPP_EVENT_TYPE_KEY,
                        .sym = sym,
                        .pressed = pressed,
                }
        });
}


#endif // !__tiny_app_c__
#endif // TINY_APP_IMPL || TINY_IMPL
#endif // !__tiny_app_h__


/// ## License
/// This software is available under 2 licenses -- choose whichever you prefer.
///
/// #### ALTERNATIVE A - MIT License
/// Copyright (c) 2022 Evan Dobson
/// Permission is hereby granted, free of charge, to any person obtaining a copy of
/// this software and associated documentation files (the "Software"), to deal in
/// the Software without restriction, including without limitation the rights to
/// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
/// of the Software, and to permit persons to whom the Software is furnished to do
/// so, subject to the following conditions:
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.
///
/// #### ALTERNATIVE B - Public Domain (www.unlicense.org)
/// This is free and unencumbered software released into the public domain.
/// Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
/// software, either in source code form or as a compiled binary, for any purpose,
/// commercial or non-commercial, and by any means.
/// In jurisdictions that recognize copyright laws, the author or authors of this
/// software dedicate any and all copyright interest in the software to the public
/// domain. We make this dedication for the benefit of the public at large and to
/// the detriment of our heirs and successors. We intend this dedication to be an
/// overt act of relinquishment in perpetuity of all present and future rights to
/// this software under copyright law.
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
/// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
/// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
