/* axiom_app.h - A C/C++ window, input, and main loop abstraction - v0.06 - public domain

========================================================================================================================

	YOU MUST

		#define AXIOM_APP_IMPL

	in EXACTLY _one_ C or C++ file that includes this header, BEFORE the
	include like this:

		#define AXIOM_APP_IMPL
		#include "axiom_app.h"

	All other files should just #include "axiom_app.h" without the #define

========================================================================================================================

LICENSE
	This software is placed under the public domain. See the end of this file
    for the full license.

CREDITS
	Written by Evan Dobson

TODOS
    -

VERSION HISTORY
    0.06  - Project name change
    0.05b - Cocoa window now works
    0.05a - Separated platform code into distinct sections
    0.05  - Added window and event API
    0.04  - Basic cocoa window
    0.03  - Changed naming style
    0.02a - More X11 stuff
    0.02  - X11 basics
    0.01  - Initial version
*/

#ifndef AXIOM_APP_H_
#define AXIOM_APP_H_

#include <stdbool.h> // bool

typedef enum app_key {
    APP_KEY_INVALID                 = 0x00,
    APP_KEY_BACKSPACE               = 0x08,
    APP_KEY_TAB                     = 0x09,
    APP_KEY_ESCAPE                  = 0x1b,
    APP_KEY_SPACE                   = ' ',
    APP_KEY_BANG                    = '!',
    APP_KEY_QUOTE                   = '\"',
    APP_KEY_POUND                   = '#',
    APP_KEY_DOLLAR                  = '$',
    APP_KEY_PERCENT                 = '%',
    APP_KEY_AMPERSAN                = '&',
    APP_KEY_APOSTROPHE              = '\'',
    APP_KEY_LEFT_PARENTHESES        = '(',
    APP_KEY_RIGHT_PARENTHESES       = ')',
    APP_KEY_ASTERISK                = '*',
    APP_KEY_PLUS                    = '+',
    APP_KEY_COMMA                   = ',',
    APP_KEY_MINUS                   = '-',
    APP_KEY_PERIOD                  = '.',
    APP_KEY_FORWARD_SLASH           = '/',
    APP_KEY_0                       = '0',
    APP_KEY_1                       = '1',
    APP_KEY_2                       = '2',
    APP_KEY_3                       = '3',
    APP_KEY_4                       = '4',
    APP_KEY_5                       = '5',
    APP_KEY_6                       = '6',
    APP_KEY_7                       = '7',
    APP_KEY_8                       = '8',
    APP_KEY_9                       = '9',
    APP_KEY_COLON                   = ':',
    APP_KEY_SEMICOLON               = ';',
    APP_KEY_LEFT_ANGLE_BRACKET      = '<',
    APP_KEY_EQUALS                  = '=',
    APP_KEY_RIGHT_ANGLE_BRACKET     = '>',
    APP_KEY_QUESTION_MARK           = '?',
    APP_KEY_AT                      = '@',
    APP_KEY_A                       = 'A',
    APP_KEY_B                       = 'B',
    APP_KEY_C                       = 'C',
    APP_KEY_D                       = 'D',
    APP_KEY_E                       = 'E',
    APP_KEY_F                       = 'F',
    APP_KEY_G                       = 'G',
    APP_KEY_H                       = 'H',
    APP_KEY_I                       = 'I',
    APP_KEY_J                       = 'J',
    APP_KEY_K                       = 'K',
    APP_KEY_L                       = 'L',
    APP_KEY_M                       = 'M',
    APP_KEY_N                       = 'N',
    APP_KEY_O                       = 'O',
    APP_KEY_P                       = 'P',
    APP_KEY_Q                       = 'Q',
    APP_KEY_R                       = 'R',
    APP_KEY_S                       = 'S',
    APP_KEY_T                       = 'T',
    APP_KEY_U                       = 'U',
    APP_KEY_V                       = 'V',
    APP_KEY_W                       = 'W',
    APP_KEY_X                       = 'X',
    APP_KEY_Y                       = 'Y',
    APP_KEY_Z                       = 'Z',
    APP_KEY_LEFT_BRACKET            = '[',
    APP_KEY_BACKSLASH               = '\\',
    APP_KEY_RIGHT_BRACKET           = ']',
    APP_KEY_CARROT                  = '^',
    APP_KEY_UNDERSCORE              = '_',
    APP_KEY_GRAVE_ACCENT            = '`',
    APP_KEY_LEFT_CURLY_BRACE        = '{',
    APP_KEY_VERTICALBAR             = '|',
    APP_KEY_RIGHT_CURLY_BRACE       = '}',
    APP_KEY_TILDA                   = '~',
    APP_KEY_DELETE                  = 0x7f,
    APP_KEY_KEYPAD_0                = 0x80,
    APP_KEY_KEYPAD_1                = 0x81,
    APP_KEY_KEYPAD_2                = 0x82,
    APP_KEY_KEYPAD_3                = 0x83,
    APP_KEY_KEYPAD_4                = 0x84,
    APP_KEY_KEYPAD_5                = 0x85,
    APP_KEY_KEYPAD_6                = 0x86,
    APP_KEY_KEYPAD_7                = 0x87,
    APP_KEY_KEYPAD_8                = 0x88,
    APP_KEY_KEYPAD_9                = 0x89,
    APP_KEY_KEYPAD_SEPARATOR        = 0x8a,
    APP_KEY_KEYPAD_FORWARD_SLASH    = 0x8b,
    APP_KEY_KEYPAD_ASTERISK         = 0x8c,
    APP_KEY_KEYPAD_PLUS             = 0x8d,
    APP_KEY_KEYPAD_MINUS            = 0x8e,
    APP_KEY_KEYPAD_ENTER            = 0x8f,
    APP_KEY_UP                      = 0x90,
    APP_KEY_DOWN                    = 0x91,
    APP_KEY_LEFT                    = 0x92,
    APP_KEY_RIGHT                   = 0x93,
    APP_KEY_PAGE_UP                 = 0x94,
    APP_KEY_PAGE_DOWN               = 0x95,
    APP_KEY_HOME                    = 0x96,
    APP_KEY_END                     = 0x97,
    APP_KEY_INSERT                  = 0x98,
    APP_KEY_F1                      = 0xa0,
    APP_KEY_F2                      = 0xa2,
    APP_KEY_F3                      = 0xa3,
    APP_KEY_F4                      = 0xa4,
    APP_KEY_F5                      = 0xa5,
    APP_KEY_F6                      = 0xa6,
    APP_KEY_F7                      = 0xa7,
    APP_KEY_F8                      = 0xa8,
    APP_KEY_F9                      = 0xa9,
    APP_KEY_F10                     = 0xaa,
    APP_KEY_F11                     = 0xab,
    APP_KEY_F12                     = 0xac,
    APP_KEY_LEFT_SHIFT              = 0xb0,
    APP_KEY_RIGHT_SHIFT             = 0xb1,
    APP_KEY_LEFT_CONTROL            = 0xb2,
    APP_KEY_RIGHT_CONTROL           = 0xb3,
    APP_KEY_LEFT_ALT                = 0xb4,
    APP_KEY_RIGHT_ALT               = 0xb5,
    APP_KEY_LEFT_SUPER              = 0xb6,
    APP_KEY_RIGHT_SUPER             = 0xb7,
    APP_KEY_MENU                    = 0xb8,
    APP_KEY_ALTGR                   = 0xb9,
    APP_KEY_NUM_LOCK                = 0xba,
    APP_KEY_CAPS_LOCK               = 0xbb,
    APP_KEY_SCROLL_LOCK             = 0xbc,
    APP_KEY_LAST                    = 0x100 // 256
} app_key;

typedef enum app_button {
    APP_MOUSE_BUTTON_1              = 0x01,
    APP_MOUSE_BUTTON_2              = 0x02,
    APP_MOUSE_BUTTON_3              = 0x03,
    APP_MOUSE_BUTTON_4              = 0x04,
    APP_MOUSE_BUTTON_5              = 0x05,
    APP_MOUSE_BUTTON_6              = 0x05,
    APP_MOUSE_BUTTON_7              = 0x07,
    APP_MOUSE_BUTTON_LAST           = 0x08,
    APP_MOUSE_BUTTON_LEFT           = APP_MOUSE_BUTTON_1,
    APP_MOUSE_BUTTON_MIDDLE         = APP_MOUSE_BUTTON_2,
    APP_MOUSE_BUTTON_RIGHT          = APP_MOUSE_BUTTON_3,
} app_button;

typedef enum app_mod {
    APP_MOD_SHIFT                   = 1U << 0,
    APP_MOD_CONTROL                 = 1U << 1,
    APP_MOD_ALT                     = 1U << 2,
    APP_MOD_SUPER                   = 1U << 3,
    APP_MOD_NUM_LOCK                = 1U << 4,
    APP_MOD_CAPS_LOCK               = 1U << 5,
    APP_MOD_LAST
} app_mod;

typedef enum app_event_type {
    APP_EVENT_TYPE_NONE             = 0,
    APP_EVENT_TYPE_QUIT,            // A quit has been requested
    APP_EVENT_TYPE_WINDOWEXPOSE,    // A window was partially exposed or hidden
    APP_EVENT_TYPE_WINDOWRESIZE,    // A window's size was changed
    APP_EVENT_TYPE_WINDOWFOCUS,     // A window's focus was changed
    APP_EVENT_TYPE_MOUSEBUTTON,     // A mouse button was pressed or released
    APP_EVENT_TYPE_MOUSEENTER,      // The mouse entered the window space
    APP_EVENT_TYPE_MOUSELEAVE,      // The mouse left the window space
    APP_EVENT_TYPE_MOUSEMOTION,     // The mouse changed position
    APP_EVENT_TYPE_MOUSESCROLL,     // The scroll wheel was moved
    APP_EVENT_TYPE_KEY,             // A key was pressed or released
} app_event_type;

typedef enum app_window_flags {
    APP_WINDOW_FLAG_DEFAULT         = 0,
    APP_WINDOW_FLAG_CENTERED        = 1U << 0,
    APP_WINDOW_FLAG_VISIBLE         = 1U << 1,
    APP_WINDOW_FLAG_VSYNC           = 1U << 2,
    APP_WINDOW_FLAG_FULLSCREEN      = 1U << 3,
} app_window_flags;

typedef struct app_window app_window;

typedef struct app_window_desc {
    char const     *title;
    int             x;
    int             y;
    int             w;
    int             h;
    unsigned        flags;
} app_window_desc;

typedef struct app_expose_event {
    app_event_type  type;
    double          time;
    app_window     *wnd;
    bool            visible;
} app_expose_event;

typedef struct app_focus_event {
    app_event_type  type;
    double          time;
    app_window     *wnd;
    int             focused;
} app_focus_event;

typedef struct app_resize_event {
    app_event_type  type;
    double          time;
    app_window     *wnd;
    int             w;
    int             h;
} app_resize_event;

typedef struct app_button_event {
    app_event_type  type;
    double          time;
    app_button      sym;
    unsigned        mods;
    int             pressed;
    int             x;
    int             y;
} app_button_event;

typedef struct app_motion_event {
    app_event_type  type;
    double          time;
    double          dx;
    double          dy;
} app_motion_event;

typedef struct app_scroll_event {
    app_event_type  type;
    double          time;
    double          dx;
    double          dy;
} app_scroll_event;

typedef struct app_key_event {
    app_event_type  type;
    double          time;
    app_key         sym;
    unsigned        mods;
    int             pressed;
} app_key_event;

typedef union app_event {
    app_event_type          type;
    double                  time;
    app_expose_event        expose;
    app_focus_event         focus;
    app_resize_event        resize;
    app_button_event        button;
    app_motion_event        motion;
    app_scroll_event        scroll;
    app_key_event           key;
} app_event;

typedef bool (*app_init_callback)(void);
typedef void (*app_event_callback)(app_event const *event);
typedef void (*app_tick_callback)(double dt);
typedef void (*app_quit_callback)(void);

typedef struct app_desc {
    app_window_desc        window;
    app_init_callback      on_init;
    app_event_callback     on_event;
    app_tick_callback      on_tick;
    app_quit_callback      on_quit;
} app_desc;


app_desc    app_main                    (int argc, char **argv);

void        app_get_pos                 (int *x, int *y);
void        app_set_pos                 (int x, int y);
void        app_get_size                (int *w, int *h);
void        app_set_size                (int w, int h);
bool        app_get_visible             (void);
void        app_set_visible             (bool visible);
bool        app_get_should_quit         (void);
void        app_set_should_quit         (bool quit);
void        app_set_title               (char const *title);
double      app_get_time                (void);

// Semi internal, use when APP_CUSTOM_ENTRY is defined or if more control is needed
bool        app_init                    (app_desc const *desc);
void        app_quit                    (void);
void        app_poll_events             (app_event_callback callback);

// Semi internal, use if multiple windows are needed
app_window *app_window_alloc            (app_window_desc const *desc);
void        app_window_free             (app_window *wnd);
void        app_window_get_pos          (app_window const *wnd, int *x, int *y);
void        app_window_set_pos          (app_window *wnd, int x, int y);
void        app_window_get_size         (app_window const *wnd, int *w, int *h);
void        app_window_set_size         (app_window *wnd, int w, int h);
bool        app_window_get_visible      (app_window const *wnd);
void        app_window_set_visible      (app_window *wnd, bool visible);
bool        app_window_get_should_close (app_window const *wnd);
void        app_window_set_should_close (app_window *wnd, bool should_close);
void        app_window_set_title        (app_window *wnd, char const *title);

/***********************************************************************************************************************
************************************************************************************************************************
****                                                                                                                ****
****                                                                                                                ****
****                                                 Implementation                                                 ****
****                                                                                                                ****
****                                                                                                                ****
************************************************************************************************************************
***********************************************************************************************************************/


#if defined(AXIOM_APP_IMPL) || defined(AXIOM_IMPL)
#ifndef AXIOM_APP_C_
#define AXIOM_APP_C_

#if !defined(APP_USE_X11) && !defined(APP_USE_COCOA)
    #ifdef __linux__
        #ifndef APP_USE_X11
            #define APP_USE_X11
        #endif
    #endif
    #ifdef __APPLE__
        #ifndef APP_USE_COCOA
            #define APP_USE_COCOA
        #endif
    #endif
#endif

#if defined(APP_USE_X11)
    #include <X11/Xlib.h>
    #include <sys/time.h> // clock_gettime, CLOCK_REALTIME, CLOCK_MONOTONIC
#elif defined(APP_USE_COCOA) && defined(__OBJC__)
    #import <Cocoa/Cocoa.h>
    #import <mach/mach_time.h>
#endif

#include <string.h> // memset
#include <stdio.h>  // fprintf
#include <stdlib.h> // calloc, free
#include <assert.h>

struct app_window {
#if defined(APP_USE_X11)
    struct {
            Window wnd;
            Atom wm_del_wnd;
    } x11;
#elif defined(APP_USE_COCOA) && defined(__OBJC__)
    struct {
            id wnd;
            id delegate;
    } cocoa;
#endif
    app_window_desc desc;
    bool should_close;
};

static struct {
#if defined(APP_USE_X11)
    struct {
            Display *dpy;
            Visual *vis;
            Window root_wnd;
            int screen;
            int depth;
    } x11;
#elif defined(APP_USE_COCOA)  && defined(__OBJC__)
    struct {
            id app;
    } cocoa;
#endif
    app_desc desc;
    app_window *wnd;
    double start_time;
    bool should_quit;
} _app = {0};


#if defined(APP_USE_X11)


bool app__init(void) {
    _app.x11.dpy = XOpenDisplay(NULL);
    if (!_app.x11.dpy) {
        fprintf(stderr, "Failed to connect to X server\n");
        return false;
    }

    _app.x11.root_wnd = DefaultRootWindow(_app.x11.dpy);
    _app.x11.screen   = DefaultScreen(_app.x11.dpy);
    _app.x11.vis      = DefaultVisual(_app.x11.dpy, _app.x11.screen);
    _app.x11.depth    = DefaultDepth(_app.x11.dpy, _app.x11.screen);
    _app.start_time   = app_get_time();
    return true;
}

void app__quit(void) {
    if (_app.x11.dpy) {
        XCloseDisplay(_app.x11.dpy);
    }
}

bool app_window__init(app_window *wnd) {
    XSetWindowAttributes swa = {
        .background_pixel = WhitePixel(_app.x11.dpy, _app.x11.screen),
        .event_mask       = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
    };
    unsigned long swa_mask = CWEventMask | CWBorderPixel | CWBackPixel;

    wnd->x11.wnd = XCreateWindow(dpy, root_wnd, wnd->desc.x, wnd->desc.y, wnd->desc.w, wnd->desc.h, 0, depth, InputOutput, _app.x11.vis, swa_mask, &swa);

    if (!wnd->x11.wnd) {
        fprintf(stderr, "Failed to create x11 window\n");
        return false;
    }

    wnd->x11.wm_del_wnd = XInternAtom(_app.x11.dpy, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(_app.x11.dpy, wnd->x11.wnd, &wnd->x11.wm_del_wnd, 1);
    return true;
}

void app_window__deinit(app_window *wnd) {
    XDestroyWindow(_app.x11.dpy, wnd->x11.wnd);
}

int app__translate_key(int key) {
    (void)key;
    return 0;
}

// TODO
void app__poll_events(app_event_callback callback) {
    (void)wnd;
    (void)callback;
}

void app_window__set_pos(app_window *wnd, int x, int y) {
    if (!app_window_get_visible(wnd)) {
        long unused;
        XSizeHints *hints = XAllocSizeHints();
        if (XGetWMNormalHints(_app.x11.dpy, wnd->x11.wnd, hints, &unused)) {
            hints->flags |= PPosition;
            hints->x = hints->y = 0;
            XSetWMNormalHints(_app.x11.dpy, wnd->x11.wnd, hints);
        }
        XFree(hints);
    }

    XMoveWindow(_app.x11.dpy, wnd->x11.wnd, x, y);
    wnd->desc.x = x;
    wnd->desc.y = y;
}

void app_window__set_size(app_window *wnd, int w, int h) {
    XResizeWindow(_app.x11.dpy, wnd->x11.wnd, w, h);
    XFlush(_app.x11.dpy);
}

void app_window__set_visible(app_window *wnd, int visible) {
    if (visible) {
        XMapWindow(_app.x11.dpy, wnd->x11.wnd);
        XMoveWindow(_app.x11.dpy, wnd->x11.wnd, wnd->desc.x, wnd->desc.y);
    } else {
        XUnmapWindow(_app.x11.dpy, wnd->x11.wnd);
    }
}

void app_window__set_title(app_window *wnd, char const *title) {
    XStoreName(_app.x11.dpy, wnd->x11.wnd, title);
}

double app__get_time(void) {
    struct timespec ts;
#ifdef CLOCK_MONOTONIC
    clock_gettime(CLOCK_MONOTONIC, &ts);
#else
    clock_gettime(CLOCK_REALTIME, &ts);
#endif
    // Convert to seconds
    double now = ts.tv_sec + (double)ts.tv_nsec * 1e-9;
    return now - _app.start_time;
}


#elif defined(APP_USE_COCOA)  && defined(__OBJC__)


@interface app__app: NSObject <NSApplicationDelegate>
@end

@implementation app__app

-(void)applicationWillFinishLaunching:(NSNotification *)notification {
    // Setup a basic menubar
    id menubar = [[NSMenu new] autorelease];
    id appMenuItem = [ [ NSMenuItem new ] autorelease];
    [menubar addItem:appMenuItem];
    [NSApp setMainMenu:menubar];
    id appMenu = [[NSMenu new ] autorelease];
    id appName = [[NSProcessInfo processInfo] processName];
    id quitTitle = [@"Quit " stringByAppendingString:appName];
    id quitMenuItem = [[[NSMenuItem alloc] initWithTitle:quitTitle action:@selector(terminate:)keyEquivalent:@"q"] autorelease];
    [appMenu addItem:quitMenuItem];
    [appMenuItem setSubmenu:appMenu];

    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
}

-(void)applicationDidFinishLaunching:(NSNotification *)notification {
    [NSApp activateIgnoringOtherApps:YES];
}

-(BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}

-(void)applicationWillTerminate:(NSApplication *)sender {
    app_set_should_quit(true);
}

@end

@interface app__delegate : NSObject <NSWindowDelegate> {
    app_window *window_;
}
@end

@implementation app__delegate

-(id)initWithWindow:(app_window *)wnd {
    if ((self = [super init])) {
        window_ = wnd;
    }
    return self;
}

-(BOOL)acceptsFirstResponder {
    return YES;
}

-(BOOL)windowShouldClose:(NSWindow *)sender {
    app_window_set_should_close(window_, 1);
    return NO;
}

-(void)windowWillClose:(id)sender {
    app_window_set_should_close(window_, 1);
}

@end

bool app__init(void) {
    @autoreleasepool {

    _app.cocoa.app = [[app__app alloc] init];
    [NSApplication sharedApplication];
    [NSApp setDelegate:_app.cocoa.app];
    [NSApp finishLaunching];

    return true;

    }
}

void app__quit(void) {
    @autoreleasepool {

    [NSApp terminate:nil];
    [_app.cocoa.app release];
    _app.cocoa.app = nil;

    } // autoreleasepool
}

void app__poll_events(app_event_callback callback) {
    @autoreleasepool {

    (void)callback; // TODO

    NSEvent* event = nil;
    do {
        event = [NSApp nextEventMatchingMask:NSEventMaskAny untilDate:nil inMode:NSDefaultRunLoopMode dequeue:YES];
        [NSApp sendEvent:event];
    } while (event != nil);

    } // autoreleasepool
}


bool app_window__init(app_window *wnd) {
    @autoreleasepool {

    NSRect frame = NSMakeRect(wnd->desc.x, wnd->desc.y, wnd->desc.w, wnd->desc.h);
    unsigned style = NSWindowStyleMaskClosable | NSWindowStyleMaskTitled | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable; // TODO: Custom wnd style

    wnd->cocoa.wnd = [[NSWindow alloc] initWithContentRect:frame styleMask:style backing:NSBackingStoreBuffered defer:NO];
    if (wnd->cocoa.wnd == nil) {
        fprintf(stderr, "Failed to create cocoa wnd\n");
        return false;
    }

    wnd->cocoa.delegate = [[app__delegate alloc] initWithWindow:wnd];
    if (wnd->cocoa.delegate == nil) {
        fprintf(stderr, "Failed to create cocoa wnd delegate\n");
        return false;
    }

    [wnd->cocoa.wnd setDelegate:wnd->cocoa.delegate];
    [wnd->cocoa.wnd setBackgroundColor:[NSColor colorWithRed:1 green:1 blue:1 alpha:1]];

    if (((wnd->desc.flags >> APP_WINDOW_FLAG_CENTERED) & 1U) == 1) {
        [(NSWindow *)wnd->cocoa.wnd center];
    }

    return true;

    } // autoreleasepool
}

void app_window__deinit(app_window *wnd) {
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

void app_window__set_pos(app_window *wnd, int x, int y) {
    @autoreleasepool {

    NSScreen* screen = [NSScreen mainScreen];
    CGSize frame     = [screen frame].size;
    NSRect visframe  = [screen visibleFrame];
    CGFloat height   = frame.height - visframe.size.height - visframe.origin.y;

    [wnd->cocoa.wnd setFrameTopLeftPoint:NSMakePoint(x, frame.height - height - y)];

    } // autoreleasepool
}

void app_window__set_size(app_window *wnd, int w, int h) {
    @autoreleasepool {

    NSRect contentRect    = [wnd->cocoa.wnd contentRectForFrameRect:[wnd->cocoa.wnd frame]];
    contentRect.origin.y += contentRect.size.height - h;
    contentRect.size      = NSMakeSize(w, h);
    [wnd->cocoa.wnd setFrame:[wnd->cocoa.wnd frameRectForContentRect:contentRect] display:YES];

    } // autoreleasepool
}

void app_window__set_visible(app_window *wnd, bool visible) {
    @autoreleasepool {

    if (visible == true) {
        [wnd->cocoa.wnd makeKeyAndOrderFront:nil];
    } else {
        [wnd->cocoa.wnd orderOut:nil];
    }

    } // autoreleasepool
}

void app_window__set_title(app_window *wnd, char const *title) {
    @autoreleasepool {

    if (wnd != NULL && wnd->cocoa.wnd != nil) {
        [wnd->cocoa.wnd setTitle:[NSString stringWithUTF8String:title]];
    }

    } // autoreleasepool
}

double app__get_time(void) {
    static bool first = true;
    static double frequency = 0.0;
    if (first == true) {
        mach_timebase_info_data_t info;
        mach_timebase_info(&info);
        frequency = (double)info.numer / (double)info.denom * 1.0e-9;
        first = false;
    }
    double now = mach_absolute_time() * frequency;
    return now - _app.start_time;
}


#endif // defined(__linux__) || (defined(APP_USE_COCOA) && defined(__OBJC__))

void app_get_pos(int *x, int *y) {
    app_window_get_pos(_app.wnd, x, y);
}

void app_set_pos(int x, int y) {
    app_window_set_pos(_app.wnd, x, y);
}

void app_get_size(int *w, int *h) {
    app_window_get_size(_app.wnd, w, h);
}

void app_set_size(int w, int h) {
    app_window_set_size(_app.wnd, w, h);
}

bool app_get_visible(void) {
    return app_window_get_visible(_app.wnd);
}

void app_set_visible(bool visible) {
    app_window_set_visible(_app.wnd, visible);
}

bool app_get_should_quit(void) {
    return app_window_get_should_close(_app.wnd);
}

void app_set_should_quit(bool quit) {
    app_window_set_should_close(_app.wnd, quit);
}

void app_set_title(char const *title) {
    app_window_set_title(_app.wnd, title);
}


bool app__default_on_init(void) {
    return true;
}

void app__default_on_event(app_event const *e) {
    (void)e;
}

void app__default_on_tick(double dt) {
    (void)dt;
}

void app__default_on_quit(void) {
}


double app_get_time(void) {
    return app__get_time();
}

bool app_init(app_desc const *desc) {
    _app.desc = *desc;

    if (_app.desc.on_init == NULL)  { _app.desc.on_init  = app__default_on_init;  }
    if (_app.desc.on_event == NULL) { _app.desc.on_event = app__default_on_event; }
    if (_app.desc.on_tick == NULL)  { _app.desc.on_tick  = app__default_on_tick;  }
    if (_app.desc.on_quit == NULL)  { _app.desc.on_quit  = app__default_on_quit;  }

    return app__init();
}

void app_quit(void) {
    app_window_free(_app.wnd);
    app__quit();
    memset(&_app, 0, sizeof _app);
}

app_window *app_window_alloc(app_window_desc const *desc) {
    app_window *wnd = calloc(1, sizeof *wnd);
    if (wnd == NULL) {
        fprintf(stderr, "Failed to create window, out of memory");
        return NULL;
    }

    wnd->desc = (app_window_desc){
        .title = desc->title ? desc->title : "Untitled",
        .x = desc->x,
        .y = desc->y,
        .w = desc->w ? desc->w : 640,
        .h = desc->h ? desc->h : 480,
        .flags = desc->flags != APP_WINDOW_FLAG_DEFAULT ? desc->flags : APP_WINDOW_FLAG_CENTERED
    };

    if (app_window__init(wnd) == false) {
        app_window_free(wnd);
        return NULL;
    }

    app_window_set_title(wnd, wnd->desc.title);
    app_window_set_visible(wnd, true);
    return wnd;
}

void app_window_free(app_window *wnd) {
    app_window__deinit(wnd);
    *wnd = (app_window){0};
    free(wnd);
}

void app_poll_events(app_event_callback callback) {
    app__poll_events(callback);
}

void app_window_get_pos(app_window const *wnd, int *x, int *y) {
    assert(wnd && "Invalid parameter(s)");
    if (x != NULL) { *x = wnd->desc.x; }
    if (y != NULL) { *y = wnd->desc.y; }
}

void app_window_set_pos(app_window *wnd, int x, int y) {
    assert(wnd && "Invalid parameter(s)");
    if (x < 0) { x = 0; }
    if (y < 0) { y = 0; }
    wnd->desc.x = x;
    wnd->desc.y = y;
    app_window__set_pos(wnd, x, y);
}

void app_window_get_size(app_window const *wnd, int *w, int *h) {
    assert(wnd && "Invalid parameter(s)");
    if (w != NULL) { *w = wnd->desc.w; }
    if (h != NULL) { *h = wnd->desc.h; }
}

void app_window_set_size(app_window *wnd, int w, int h) {
    assert(wnd && "Invalid parameter(s)");
    if (w < 0) { w = 0; }
    if (h < 0) { h = 0; }
    wnd->desc.w = w;
    wnd->desc.h = h;
    app_window__set_size(wnd, w, h);
}

bool app_window_get_visible(app_window const *wnd) {
    assert(wnd && "Invalid parameter(s)");
    return (wnd->desc.flags >> APP_WINDOW_FLAG_VISIBLE) & 1U;
}

void app_window_set_visible(app_window *wnd, bool visible) {
    assert(wnd && "Invalid parameter(s)");
    if (visible == true) {
        wnd->desc.flags |=  APP_WINDOW_FLAG_VISIBLE;
    } else {
        wnd->desc.flags &= ~APP_WINDOW_FLAG_VISIBLE;
    }
    app_window__set_visible(wnd, visible);
}

bool app_window_get_should_close(app_window const *wnd) {
    assert(wnd && "Invalid parameter(s)");
    return wnd->should_close;
}

void app_window_set_should_close(app_window *wnd, bool should_close) {
    assert(wnd && "Invalid parameter(s)");
    wnd->should_close = should_close;
}

void app_window_set_title(app_window *wnd, char const *title) {
    assert(wnd && title && "Invalid parameter(s)");
    app_window__set_title(wnd, title);
}


#ifndef APP_CUSTOM_ENTRY


int main(int argc, char **argv) {
    app_desc desc = app_main(argc, argv);
    if (app_init(&desc) == false) {
        fprintf(stderr, "Error on initialization, exiting...");
        return -1;
    }

    _app.wnd = app_window_alloc(&desc.window);
    if (_app.wnd == NULL) {
        fprintf(stderr, "Error on initialization, exiting...");
        app_quit();
        return -1;
    }

    if (_app.desc.on_init() == false) {
        fprintf(stderr, "Error on initialization, exiting...");
        app_quit();
        return -1;
    }

    double last = app_get_time();
    while (!app_get_should_quit()) {
        // Update frame timings
        double now = app_get_time();
        double dt = now - last;
        last = now;

        _app.desc.on_tick(dt);
        app_poll_events(_app.desc.on_event);
    }

    _app.desc.on_quit();
    app_quit();
    return 0;
}

#endif // !APP_CUSTOM_ENTRY
#endif // !AXIOM_APP_C_
#endif // AXIOM_APP_IMPL || AXIOM_IMPL
#endif // !AXIOM_APP_H_

/// ## License
/// This is free and unencumbered software released into the public domain.
/// Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
/// software, either in source code form or as a compiled binary, for any purpose,
/// commercial or non-commercial, and by any means.
///
/// In jurisdictions that recognize copyright laws, the author or authors of this
/// software dedicate any and all copyright interest in the software to the public
/// domain. We make this dedication for the benefit of the public at large and to
/// the detriment of our heirs and successors. We intend this dedication to be an
/// overt act of relinquishment in perpetuity of all present and future rights to
/// this software under copyright law.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
/// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
/// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///
/// For more information, please refer to <http://unlicense.org/>
