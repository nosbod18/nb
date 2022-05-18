/* nb_platform.h - v0.06 - public domain
    Platform abstraction for C/C++

    Table of Contents
    -----------------
    Table of Contents
    Summary
    Usage
    Example
    Documentation
    Version History
    Licence

    Summary
    -------
    TODO

    Usage
    -----
    To use this library, do this in *one* C or C++ file:

        #define NB_PLATFORM_IMPLEMENTATION
        #include "nb_platform.h"

    Then include it as normal in all other files.

    Example
    -------
    #define NB_PLATFORM_IMPLEMENTATION
    #include "nb_platform.h"

    int main(void) {
        if (nbp_init() != 0) {
            return -1;
        }

        nbp_window *wnd = nbp_wnd_create(&(nbp_wnd_desc){0});
        if (wnd == NULL) {
            return -1;
        }

        while (nbp_wnd_should_close(wnd) == 0) {
            nbp_poll_events(NULL);
            nbp_swap_buffers();
        }

        nbp_wnd_destroy(wnd);

        nbp_exit();
        return 0;
    }

    Documentation
    -------------
    TODO

    Version History
    ---------------
    0.06  - Project name change
    0.05b - Cocoa window works now
    0.05a - Separated platform code into distinct sections
    0.05  - Added window and event API
    0.04  - Basic cocoa window
    0.03  - Changed naming style
    0.02a - Fix X11 stuff
    0.02  - X11 basics
    0.01  - Initial version

    License
    -------
    This is free and unencumbered software released into the public domain.
    Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
    software, either in source code form or as a compiled binary, for any purpose,
    commercial or non-commercial, and by any means.

    In jurisdictions that recognize copyright laws, the author or authors of this
    software dedicate any and all copyright interest in the software to the public
    domain. We make this dedication for the benefit of the public at large and to
    the detriment of our heirs and successors. We intend this dedication to be an
    overt act of relinquishment in perpetuity of all present and future rights to
    this software under copyright law.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
    ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

    For more information, please refer to <http://unlicense.org/>
*/

#ifndef _nb_platform_h_
#define _nb_platform_h_

#include <stdint.h> // int

typedef enum nbp_key {
    NBP_KEY_INVALID                 = 0x00,
    NBP_KEY_BACKSPACE               = 0x08,
    NBP_KEY_TAB                     = 0x09,
    NBP_KEY_ESCAPE                  = 0x1b,
    NBP_KEY_SPACE                   = ' ',
    NBP_KEY_BANG                    = '!',
    NBP_KEY_QUOTE                   = '\"',
    NBP_KEY_POUND                   = '#',
    NBP_KEY_DOLLAR                  = '$',
    NBP_KEY_PERCENT                 = '%',
    NBP_KEY_AMPERSAN                = '&',
    NBP_KEY_APOSTROPHE              = '\'',
    NBP_KEY_LEFT_PARENTHESES        = '(',
    NBP_KEY_RIGHT_PARENTHESES       = ')',
    NBP_KEY_ASTERISK                = '*',
    NBP_KEY_PLUS                    = '+',
    NBP_KEY_COMMA                   = ',',
    NBP_KEY_MINUS                   = '-',
    NBP_KEY_PERIOD                  = '.',
    NBP_KEY_FORWARD_SLASH           = '/',
    NBP_KEY_0                       = '0',
    NBP_KEY_1                       = '1',
    NBP_KEY_2                       = '2',
    NBP_KEY_3                       = '3',
    NBP_KEY_4                       = '4',
    NBP_KEY_5                       = '5',
    NBP_KEY_6                       = '6',
    NBP_KEY_7                       = '7',
    NBP_KEY_8                       = '8',
    NBP_KEY_9                       = '9',
    NBP_KEY_COLON                   = ':',
    NBP_KEY_SEMICOLON               = ';',
    NBP_KEY_LEFT_ANGLE_BRACKET      = '<',
    NBP_KEY_EQUALS                  = '=',
    NBP_KEY_RIGHT_ANGLE_BRACKET     = '>',
    NBP_KEY_QUESTION_MARK           = '?',
    NBP_KEY_AT                      = '@',
    NBP_KEY_A                       = 'A',
    NBP_KEY_B                       = 'B',
    NBP_KEY_C                       = 'C',
    NBP_KEY_D                       = 'D',
    NBP_KEY_E                       = 'E',
    NBP_KEY_F                       = 'F',
    NBP_KEY_G                       = 'G',
    NBP_KEY_H                       = 'H',
    NBP_KEY_I                       = 'I',
    NBP_KEY_J                       = 'J',
    NBP_KEY_K                       = 'K',
    NBP_KEY_L                       = 'L',
    NBP_KEY_M                       = 'M',
    NBP_KEY_N                       = 'N',
    NBP_KEY_O                       = 'O',
    NBP_KEY_P                       = 'P',
    NBP_KEY_Q                       = 'Q',
    NBP_KEY_R                       = 'R',
    NBP_KEY_S                       = 'S',
    NBP_KEY_T                       = 'T',
    NBP_KEY_U                       = 'U',
    NBP_KEY_V                       = 'V',
    NBP_KEY_W                       = 'W',
    NBP_KEY_X                       = 'X',
    NBP_KEY_Y                       = 'Y',
    NBP_KEY_Z                       = 'Z',
    NBP_KEY_LEFT_BRACKET            = '[',
    NBP_KEY_BACKSLASH               = '\\',
    NBP_KEY_RIGHT_BRACKET           = ']',
    NBP_KEY_CARROT                  = '^',
    NBP_KEY_UNDERSCORE              = '_',
    NBP_KEY_GRAVE_ACCENT            = '`',
    NBP_KEY_LEFT_CURLY_BRACE        = '{',
    NBP_KEY_VERTICALBAR             = '|',
    NBP_KEY_RIGHT_CURLY_BRACE       = '}',
    NBP_KEY_TILDA                   = '~',
    NBP_KEY_DELETE                  = 0x7f,
    NBP_KEY_KEYPAD_0                = 0x80,
    NBP_KEY_KEYPAD_1                = 0x81,
    NBP_KEY_KEYPAD_2                = 0x82,
    NBP_KEY_KEYPAD_3                = 0x83,
    NBP_KEY_KEYPAD_4                = 0x84,
    NBP_KEY_KEYPAD_5                = 0x85,
    NBP_KEY_KEYPAD_6                = 0x86,
    NBP_KEY_KEYPAD_7                = 0x87,
    NBP_KEY_KEYPAD_8                = 0x88,
    NBP_KEY_KEYPAD_9                = 0x89,
    NBP_KEY_KEYPAD_SEPARATOR        = 0x8a,
    NBP_KEY_KEYPAD_FORWARD_SLASH    = 0x8b,
    NBP_KEY_KEYPAD_ASTERISK         = 0x8c,
    NBP_KEY_KEYPAD_PLUS             = 0x8d,
    NBP_KEY_KEYPAD_MINUS            = 0x8e,
    NBP_KEY_KEYPAD_ENTER            = 0x8f,
    NBP_KEY_UP                      = 0x90,
    NBP_KEY_DOWN                    = 0x91,
    NBP_KEY_LEFT                    = 0x92,
    NBP_KEY_RIGHT                   = 0x93,
    NBP_KEY_PAGE_UP                 = 0x94,
    NBP_KEY_PAGE_DOWN               = 0x95,
    NBP_KEY_HOME                    = 0x96,
    NBP_KEY_END                     = 0x97,
    NBP_KEY_INSERT                  = 0x98,
    NBP_KEY_F1                      = 0xa0,
    NBP_KEY_F2                      = 0xa2,
    NBP_KEY_F3                      = 0xa3,
    NBP_KEY_F4                      = 0xa4,
    NBP_KEY_F5                      = 0xa5,
    NBP_KEY_F6                      = 0xa6,
    NBP_KEY_F7                      = 0xa7,
    NBP_KEY_F8                      = 0xa8,
    NBP_KEY_F9                      = 0xa9,
    NBP_KEY_F10                     = 0xaa,
    NBP_KEY_F11                     = 0xab,
    NBP_KEY_F12                     = 0xac,
    NBP_KEY_LEFT_SHIFT              = 0xb0,
    NBP_KEY_RIGHT_SHIFT             = 0xb1,
    NBP_KEY_LEFT_CONTROL            = 0xb2,
    NBP_KEY_RIGHT_CONTROL           = 0xb3,
    NBP_KEY_LEFT_ALT                = 0xb4,
    NBP_KEY_RIGHT_ALT               = 0xb5,
    NBP_KEY_LEFT_SUPER              = 0xb6,
    NBP_KEY_RIGHT_SUPER             = 0xb7,
    NBP_KEY_MENU                    = 0xb8,
    NBP_KEY_ALTGR                   = 0xb9,
    NBP_KEY_NUM_LOCK                = 0xba,
    NBP_KEY_CAPS_LOCK               = 0xbb,
    NBP_KEY_SCROLL_LOCK             = 0xbc,
    NBP_KEY_LAST                    = 0x100
} nbp_key;

typedef enum nbp_button {
    NBP_MOUSE_BUTTON_1              = 0x01,
    NBP_MOUSE_BUTTON_2              = 0x02,
    NBP_MOUSE_BUTTON_3              = 0x03,
    NBP_MOUSE_BUTTON_4              = 0x04,
    NBP_MOUSE_BUTTON_5              = 0x05,
    NBP_MOUSE_BUTTON_6              = 0x05,
    NBP_MOUSE_BUTTON_7              = 0x07,
    NBP_MOUSE_BUTTON_LAST           = 0x08,
    NBP_MOUSE_BUTTON_LEFT           = NBP_MOUSE_BUTTON_1,
    NBP_MOUSE_BUTTON_MIDDLE         = NBP_MOUSE_BUTTON_2,
    NBP_MOUSE_BUTTON_RIGHT          = NBP_MOUSE_BUTTON_3,
} nbp_button;

typedef enum nbp_mod {
    NBP_MOD_SHIFT                   = 1U << 0,
    NBP_MOD_CONTROL                 = 1U << 1,
    NBP_MOD_ALT                     = 1U << 2,
    NBP_MOD_SUPER                   = 1U << 3,
    NBP_MOD_NUM_LOCK                = 1U << 4,
    NBP_MOD_CAPS_LOCK               = 1U << 5,
    NBP_MOD_LAST
} nbp_mod;

typedef enum nbp_event_type {
    NBP_EVENT_TYPE_NONE             = 0,
    NBP_EVENT_TYPE_QUIT,            // A quit has been requested
    NBP_EVENT_TYPE_WINDOWEXPOSE,    // A window was partially exposed or hidden
    NBP_EVENT_TYPE_WINDOWRESIZE,    // A window's size was changed
    NBP_EVENT_TYPE_WINDOWFOCUS,     // A window's focus was changed
    NBP_EVENT_TYPE_MOUSEBUTTON,     // A mouse button was pressed or released
    NBP_EVENT_TYPE_MOUSEENTER,      // The mouse entered the window space
    NBP_EVENT_TYPE_MOUSELEAVE,      // The mouse left the window space
    NBP_EVENT_TYPE_MOUSEMOTION,     // The mouse changed position
    NBP_EVENT_TYPE_MOUSESCROLL,     // The scroll wheel was moved
    NBP_EVENT_TYPE_KEY,             // A key was pressed or released
} nbp_event_type;

typedef enum nbp_wnd_flags {
    NBP_WINDOW_FLAG_DEFAULT         = 0,
    NBP_WINDOW_FLAG_CENTERED        = 1U << 0,
    NBP_WINDOW_FLAG_VISIBLE         = 1U << 1,
    NBP_WINDOW_FLAG_VSYNC           = 1U << 2,
    NBP_WINDOW_FLAG_FULLSCREEN      = 1U << 3,
} nbp_wnd_flags;

typedef struct nbp_window nbp_window;

typedef struct nbp_wnd_desc {
    char const     *title;
    int             x;
    int             y;
    int             w;
    int             h;
    unsigned        flags;
} nbp_wnd_desc;

typedef struct nbp_expose_event {
    nbp_event_type  type;
    double          time;
    nbp_window     *wnd;
    int            visible;
} nbp_expose_event;

typedef struct nbp_focus_event {
    nbp_event_type  type;
    double          time;
    nbp_window     *wnd;
    int             focused;
} nbp_focus_event;

typedef struct nbp_resize_event {
    nbp_event_type  type;
    double          time;
    nbp_window     *wnd;
    int             w;
    int             h;
} nbp_resize_event;

typedef struct nbp_button_event {
    nbp_event_type  type;
    double          time;
    nbp_button      sym;
    unsigned        mods;
    int             pressed;
    int             x;
    int             y;
} nbp_button_event;

typedef struct nbp_motion_event {
    nbp_event_type  type;
    double          time;
    double          dx;
    double          dy;
} nbp_motion_event;

typedef struct nbp_scroll_event {
    nbp_event_type  type;
    double          time;
    double          dx;
    double          dy;
} nbp_scroll_event;

typedef struct nbp_key_event {
    nbp_event_type  type;
    double          time;
    nbp_key         sym;
    unsigned        mods;
    int             pressed;
} nbp_key_event;

typedef union nbp_event {
    nbp_event_type          type;
    double                  time;
    nbp_expose_event        expose;
    nbp_focus_event         focus;
    nbp_resize_event        resize;
    nbp_button_event        button;
    nbp_motion_event        motion;
    nbp_scroll_event        scroll;
    nbp_key_event           key;
} nbp_event;

typedef void (*nbp_event_callback)(nbp_event const *event);

int         nbp_init                    (void);
void        nbp_exit                    (void);
void        nbp_poll_events             (nbp_event_callback callback);

nbp_window *nbp_wnd_create           (nbp_wnd_desc const *desc);
void        nbp_wnd_destroy          (nbp_window *wnd);
void        nbp_wnd_get_pos          (nbp_window const *wnd, int *x, int *y);
void        nbp_wnd_set_pos          (nbp_window *wnd, int x, int y);
void        nbp_wnd_get_size         (nbp_window const *wnd, int *w, int *h);
void        nbp_wnd_set_size         (nbp_window *wnd, int w, int h);
int         nbp_wnd_get_visible      (nbp_window const *wnd);
void        nbp_wnd_set_visible      (nbp_window *wnd, int visible);
int         nbp_wnd_get_should_close (nbp_window const *wnd);
void        nbp_wnd_set_should_close (nbp_window *wnd, int should_close);
void        nbp_wnd_set_title        (nbp_window *wnd, char const *title);

/***********************************************************************************************************************
************************************************************************************************************************
****                                                                                                                ****
****                                                                                                                ****
****                                                 Implementation                                                 ****
****                                                                                                                ****
****                                                                                                                ****
************************************************************************************************************************
***********************************************************************************************************************/


// #if defined(NB_PLATFORM_IMPLEMENTATION) || defined(NB_IMPLEMENTATION)
#ifndef _nb_platform_c_
#define _nb_platform_c_

#if !defined(NBP_USE_X11) && !defined(NBP_USE_COCOA)
    #ifdef __linux__
        #ifndef NBP_USE_X11
            #define NBP_USE_X11
        #endif
    #endif
    #ifdef __APPLE__
        #ifndef NBP_USE_COCOA
            #define NBP_USE_COCOA
        #endif
    #endif
#endif

#ifndef nbp_assert
    #ifdef nb_assert
        #define nbp_assert nb_assert
    #else
        #include <assert.h>
        #define nbp_assert assert
    #endif
#endif

#ifndef nbp_calloc
    #ifdef nb_calloc
        #define nbp_calloc nb_calloc
    #else
        #include <stdlib.h>
        #define nbp_calloc calloc
    #endif
#endif

#ifndef nbp_free
    #ifdef nb_free
        #define nbp_free nb_free
    #else
        #include <stdlib.h>
        #define nbp_free free
    #endif
#endif

#ifndef nbp_fprintf
    #ifdef nb_fprintf
        #define nbp_fprintf nb_fprintf
    #else
        #include <stdio.h>
        #define nbp_fprintf fprintf
    #endif
#endif

#ifndef nbp_memset
    #ifdef nb_memset
        #define nbp_memset nb_memset
    #else
        #include <string.h>
        #define nbp_memset memset
    #endif
#endif

#if defined(NBP_USE_X11)
    #include <X11/Xlib.h>
    #include <sys/time.h> // clock_gettime, CLOCK_REALTIME, CLOCK_MONOTONIC
#elif defined(NBP_USE_COCOA) && defined(__OBJC__)
    #import <Cocoa/Cocoa.h>
    #import <mach/mach_time.h>
#endif

struct nbp_window {
#if defined(NBP_USE_X11)
    struct {
            Window wnd;
            Atom wm_del_wnd;
    } x11;
#elif defined(NBP_USE_COCOA) && defined(__OBJC__)
    struct {
            id wnd;
            id delegate;
    } cocoa;
#endif
    nbp_wnd_desc desc;
    int should_close;
};

static struct {
#if defined(NBP_USE_X11)
    struct {
            Display *dpy;
            Visual *vis;
            Window root_wnd;
            int screen;
            int depth;
    } x11;
#elif defined(NBP_USE_COCOA)  && defined(__OBJC__)
    struct {
            id app;
    } cocoa;
#endif
    nbp_window **wnds;
    double start_time;
} _nbp = {0};


#if defined(NBP_USE_X11)


int nbp__init(void) {
    _nbp.x11.dpy = XOpenDisplay(NULL);
    if (!_nbp.x11.dpy) {
        nbp_fprintf(stderr, "Failed to connect to X server\n");
        return 0;
    }

    _nbp.x11.root_wnd = DefaultRootWindow(_nbp.x11.dpy);
    _nbp.x11.screen   = DefaultScreen(_nbp.x11.dpy);
    _nbp.x11.vis      = DefaultVisual(_nbp.x11.dpy, _nbp.x11.screen);
    _nbp.x11.depth    = DefaultDepth(_nbp.x11.dpy, _nbp.x11.screen);
    _nbp.start_time   = nbp_get_time();
    return 1;
}

void nbp__quit(void) {
    if (_nbp.x11.dpy) {
        XCloseDisplay(_nbp.x11.dpy);
    }
}

int nbp_wnd__init(nbp_window *wnd) {
    XSetWindowAttributes swa = {
        .background_pixel = WhitePixel(_nbp.x11.dpy, _nbp.x11.screen),
        .event_mask       = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
    };
    unsigned long swa_mask = CWEventMask | CWBorderPixel | CWBackPixel;

    wnd->x11.wnd = XCreateWindow(dpy, root_wnd, wnd->desc.x, wnd->desc.y, wnd->desc.w, wnd->desc.h, 0, depth, InputOutput, _nbp.x11.vis, swa_mask, &swa);

    if (!wnd->x11.wnd) {
        nbp_fprintf(stderr, "Failed to create x11 window\n");
        return 1;
    }

    wnd->x11.wm_del_wnd = XInternAtom(_nbp.x11.dpy, "WM_DELETE_WINDOW", 0);
    XSetWMProtocols(_nbp.x11.dpy, wnd->x11.wnd, &wnd->x11.wm_del_wnd, 1);
    return 0;
}

void nbp_wnd__deinit(nbp_window *wnd) {
    XDestroyWindow(_nbp.x11.dpy, wnd->x11.wnd);
}

void nbp__poll_events(nbp_event_callback callback) {
    (void)callback;
}

void nbp_wnd__set_pos(nbp_window *wnd, int x, int y) {
    if (nbp_wnd_get_visible(wnd) == 0) {
        long unused;
        XSizeHints *hints = XAllocSizeHints();
        if (XGetWMNormalHints(_nbp.x11.dpy, wnd->x11.wnd, hints, &unused)) {
            hints->flags |= PPosition;
            hints->x = hints->y = 0;
            XSetWMNormalHints(_nbp.x11.dpy, wnd->x11.wnd, hints);
        }
        XFree(hints);
    }

    XMoveWindow(_nbp.x11.dpy, wnd->x11.wnd, x, y);
    wnd->desc.x = x;
    wnd->desc.y = y;
}

void nbp_wnd__set_size(nbp_window *wnd, int w, int h) {
    XResizeWindow(_nbp.x11.dpy, wnd->x11.wnd, w, h);
    XFlush(_nbp.x11.dpy);
}

void nbp_wnd__set_visible(nbp_window *wnd, int visible) {
    if (visible) {
        XMapWindow(_nbp.x11.dpy, wnd->x11.wnd);
        XMoveWindow(_nbp.x11.dpy, wnd->x11.wnd, wnd->desc.x, wnd->desc.y);
    } else {
        XUnmapWindow(_nbp.x11.dpy, wnd->x11.wnd);
    }
}

void nbp_wnd__set_title(nbp_window *wnd, char const *title) {
    XStoreName(_nbp.x11.dpy, wnd->x11.wnd, title);
}

double nbp__get_time(void) {
    struct timespec ts;
#ifdef CLOCK_MONOTONIC
    clock_gettime(CLOCK_MONOTONIC, &ts);
#else
    clock_gettime(CLOCK_REALTIME, &ts);
#endif
    // Convert to seconds
    double now = ts.tv_sec + (double)ts.tv_nsec * 1e-9;
    return now - _nbp.start_time;
}


#elif defined(NBP_USE_COCOA) && defined(__OBJC__)


@interface nbp__app: NSObject <NSApplicationDelegate>
@end

@implementation nbp__app

-(void)applicationWillFinishLaunching:(NSNotification *)notification {
    id menubar = [[NSMenu new] autorelease];
    id nbpMenuItem = [ [ NSMenuItem new ] autorelease];
    [menubar addItem:nbpMenuItem];
    [NSApp setMainMenu:menubar];
    id nbpMenu = [[NSMenu new ] autorelease];
    id nbpName = [[NSProcessInfo processInfo] processName];
    id quitTitle = [@"Quit " stringByAppendingString:nbpName];
    id quitMenuItem = [[[NSMenuItem alloc] initWithTitle:quitTitle action:@selector(terminate:)keyEquivalent:@"q"] autorelease];
    [nbpMenu addItem:quitMenuItem];
    [nbpMenuItem setSubmenu:nbpMenu];

    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
}

-(void)applicationDidFinishLaunching:(NSNotification *)notification {
    [NSApp activateIgnoringOtherApps:YES];
}

-(BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}

@end

@interface nbp__delegate : NSObject <NSWindowDelegate> {
    nbp_window *wnd_;
}
@end

@implementation nbp__delegate

-(id)initWithWindow:(nbp_window *)wnd {
    if ((self = [super init])) {
        wnd_ = wnd;
    }
    return self;
}

-(BOOL)acceptsFirstResponder {
    return YES;
}

-(BOOL)windowShouldClose:(NSWindow *)sender {
    nbp_wnd_set_should_close(wnd_, 1);
    return NO;
}

-(void)windowWillClose:(id)sender {
    nbp_wnd_set_should_close(wnd_, 1);
}

@end

int nbp__init(void) {
    @autoreleasepool {

    _nbp.cocoa.app = [[nbp__app alloc] init];
    [NSApplication sharedApplication];
    [NSApp setDelegate:_nbp.cocoa.app];
    [NSApp finishLaunching];

    return 1;

    }
}

void nbp__quit(void) {
    @autoreleasepool {

    [NSApp terminate:nil];
    [_nbp.cocoa.app release];
    _nbp.cocoa.app = nil;

    } // autoreleasepool
}

void nbp__poll_events(nbp_event_callback callback) {
    @autoreleasepool {

    (void)callback; // TODO

    NSEvent* event = nil;
    do {
        event = [NSApp nextEventMatchingMask:NSEventMaskAny untilDate:nil inMode:NSDefaultRunLoopMode dequeue:YES];
        [NSApp sendEvent:event];
    } while (event != nil);

    } // autoreleasepool
}


int nbp_wnd__init(nbp_window *wnd) {
    @autoreleasepool {

    NSRect frame = NSMakeRect(wnd->desc.x, wnd->desc.y, wnd->desc.w, wnd->desc.h);
    unsigned style = NSWindowStyleMaskClosable | NSWindowStyleMaskTitled | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable; // TODO: Custom wnd style

    wnd->cocoa.wnd = [[NSWindow alloc] initWithContentRect:frame styleMask:style backing:NSBackingStoreBuffered defer:NO];
    if (wnd->cocoa.wnd == nil) {
        nbp_fprintf(stderr, "Failed to create cocoa wnd\n");
        return 0;
    }

    wnd->cocoa.delegate = [[nbp__delegate alloc] initWithWindow:wnd];
    if (wnd->cocoa.delegate == nil) {
        nbp_fprintf(stderr, "Failed to create cocoa wnd delegate\n");
        return 0;
    }

    [wnd->cocoa.wnd setDelegate:wnd->cocoa.delegate];
    [wnd->cocoa.wnd setBackgroundColor:[NSColor colorWithRed:1 green:1 blue:1 alpha:1]];

    if (((wnd->desc.flags >> NBP_WINDOW_FLAG_CENTERED) & 1U) == 1) {
        [(NSWindow *)wnd->cocoa.wnd center];
    }

    return 1;

    } // autoreleasepool
}

void nbp_wnd__deinit(nbp_window *wnd) {
    @autoreleasepool {

    if (wnd->cocoa.delegate != nil) {
        [wnd->cocoa.wnd setDelegate:nil];
        [wnd->cocoa.delegate release];
        wnd->cocoa.delegate = nil;
    }

    if (wnd->cocoa.wnd != nil) {
        [wnd->cocoa.wnd close];
        wnd->cocoa.wnd = nil;
    }

    } // autoreleasepool
}

void nbp_wnd__set_pos(nbp_window *wnd, int x, int y) {
    @autoreleasepool {

    NSScreen* screen = [NSScreen mainScreen];
    CGSize frame     = [screen frame].size;
    NSRect visframe  = [screen visibleFrame];
    CGFloat height   = frame.height - visframe.size.height - visframe.origin.y;

    [wnd->cocoa.wnd setFrameTopLeftPoint:NSMakePoint(x, frame.height - height - y)];

    } // autoreleasepool
}

void nbp_wnd__set_size(nbp_window *wnd, int w, int h) {
    @autoreleasepool {

    NSRect contentRect    = [wnd->cocoa.wnd contentRectForFrameRect:[wnd->cocoa.wnd frame]];
    contentRect.origin.y += contentRect.size.height - h;
    contentRect.size      = NSMakeSize(w, h);
    [wnd->cocoa.wnd setFrame:[wnd->cocoa.wnd frameRectForContentRect:contentRect] display:YES];

    } // autoreleasepool
}

void nbp_wnd__set_visible(nbp_window *wnd, int visible) {
    @autoreleasepool {

    if (visible == 1) {
        [wnd->cocoa.wnd makeKeyAndOrderFront:nil];
    } else {
        [wnd->cocoa.wnd orderOut:nil];
    }

    } // autoreleasepool
}

void nbp_wnd__set_title(nbp_window *wnd, char const *title) {
    @autoreleasepool {

    if (wnd != NULL && wnd->cocoa.wnd != nil) {
        [wnd->cocoa.wnd setTitle:[NSString stringWithUTF8String:title]];
    }

    } // autoreleasepool
}


#endif // defined(NBP_USE_X11) || (defined(NBP_USE_COCOA) && defined(__OBJC__))


int nbp_init(void) {
    return nbp__init();
}

void nbp_quit(void) {
    nbp__quit();
    nbp_memset(&_nbp, 0, sizeof _nbp);
}

nbp_window *nbp_wnd_create(nbp_wnd_desc const *desc) {
    nbp_window *wnd = nbp_calloc(1, sizeof *wnd);
    if (wnd == NULL) {
        nbp_fprintf(stderr, "Failed to create window, out of memory");
        return NULL;
    }

    wnd->desc = (nbp_wnd_desc){
        .title = desc->title ? desc->title : "Untitled",
        .x = desc->x,
        .y = desc->y,
        .w = desc->w ? desc->w : 640,
        .h = desc->h ? desc->h : 480,
        .flags = desc->flags != NBP_WINDOW_FLAG_DEFAULT ? desc->flags : NBP_WINDOW_FLAG_CENTERED
    };

    if (nbp_wnd__init(wnd) == 0) {
        nbp_wnd_destroy(wnd);
        return NULL;
    }

    nbp_wnd_set_title(wnd, wnd->desc.title);
    nbp_wnd_set_visible(wnd, 1);
    return wnd;
}

void nbp_wnd_destroy(nbp_window *wnd) {
    nbp_wnd__deinit(wnd);
    *wnd = (nbp_window){0};
    nbp_free(wnd);
}

void nbp_poll_events(nbp_event_callback callback) {
    nbp__poll_events(callback);
}

void nbp_wnd_get_pos(nbp_window const *wnd, int *x, int *y) {
    nbp_assert(wnd && "Window cannot be null");
    if (x != NULL) { *x = wnd->desc.x; }
    if (y != NULL) { *y = wnd->desc.y; }
}

void nbp_wnd_set_pos(nbp_window *wnd, int x, int y) {
    nbp_assert(wnd && "Window cannot be null");
    if (x < 0) { x = 0; }
    if (y < 0) { y = 0; }
    wnd->desc.x = x;
    wnd->desc.y = y;
    nbp_wnd__set_pos(wnd, x, y);
}

void nbp_wnd_get_size(nbp_window const *wnd, int *w, int *h) {
    nbp_assert(wnd && "Window cannot be null");
    if (w != NULL) { *w = wnd->desc.w; }
    if (h != NULL) { *h = wnd->desc.h; }
}

void nbp_wnd_set_size(nbp_window *wnd, int w, int h) {
    nbp_assert(wnd && "Window cannot be null");
    if (w < 0) { w = 0; }
    if (h < 0) { h = 0; }
    wnd->desc.w = w;
    wnd->desc.h = h;
    nbp_wnd__set_size(wnd, w, h);
}

int nbp_wnd_get_visible(nbp_window const *wnd) {
    nbp_assert(wnd && "Window cannot be null");
    return (wnd->desc.flags >> NBP_WINDOW_FLAG_VISIBLE) & 1U;
}

void nbp_wnd_set_visible(nbp_window *wnd, int visible) {
    nbp_assert(wnd && "Window cannot be null");
    if (visible == 1) {
        wnd->desc.flags |=  NBP_WINDOW_FLAG_VISIBLE;
    } else {
        wnd->desc.flags &= ~NBP_WINDOW_FLAG_VISIBLE;
    }
    nbp_wnd__set_visible(wnd, visible);
}

int nbp_wnd_get_should_close(nbp_window const *wnd) {
    nbp_assert(wnd && "Window cannot be null");
    return wnd->should_close;
}

void nbp_wnd_set_should_close(nbp_window *wnd, int should_close) {
    nbp_assert(wnd && "Window cannot be null");
    wnd->should_close = should_close;
}

void nbp_wnd_set_title(nbp_window *wnd, char const *title) {
    nbp_assert(wnd   && "Window cannot be null");
    nbp_assert(title && "Title cannot be null");
    nbp_wnd__set_title(wnd, title);
}

#endif // !_nb_platform_c_
// #endif // NB_PLATFORM_IMPLEMENTATION || NB_IMPLEMENTATION
#endif // !_nb_platform_h_
