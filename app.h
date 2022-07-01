/* app.h - v0.06 - public domain
    Platform window, input, and main loop abstraction for C/C++

    Table of Contents
    -----------------
    Table of Contents
    Summary
    Usage
    Example
    Documentation
    Licence

    Summary
    -------
    TODO

    Usage
    -----
    To use this library, do this in *one* C or C++ file:

        #define APP_IMPLEMENTATION
        #include "app.h"

    Then include it as normal in all other files.

    Example
    -------
    #define APP_IMPLEMENTATION
    #include "app.h"

    int init(void) {
        // Called as the program is starting up
        // Return 0 for a successful initialization, or non-zero for failed initialization (if memory wasn't allocated or something)
        // If a non-zero number is returned, the program will exit
        return 0;
    }

    void event(app_event const *event) {
        printf("Event type: %d\n", event->type);
    }

    void tick(float dt) {
        // Called once per frame, update your program here
        printf("FPS: %.2f\n", 1.f / dt);
    }

    void exit(void) {
        // Called as the program is about to exit
        // Clean up your program here (free memory, close files, etc.)
    }

    app_desc app_main(int argc, char **argv) {
        return (app_desc){
            .window = {
                .title  = "Example",
                .w      = 800,
                .h      = 600
            },
            .init_cb    = init,
            .event_cb   = event,
            .tick_cb    = tick,
            .exit_cb    = exit,
        };
    }

    Documentation
    -------------
    TODO

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

#pragma once
#include <stddef.h> // size_t

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
    APP_KEY_LAST                    = 0x100
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

typedef enum app_flags {
    APP_WINDOW_FLAG_NONE            = 0,
    APP_WINDOW_FLAG_CENTERED        = 1U << 0,
    APP_WINDOW_FLAG_VISIBLE         = 1U << 1,
    APP_WINDOW_FLAG_VSYNC           = 1U << 2,
    APP_WINDOW_FLAG_FULLSCREEN      = 1U << 3,
} app_flags;

typedef struct app app;

typedef struct app_window_desc {    // Defaults:
    char const     *title;          // "Untitled"
    int             x;              // Centered
    int             y;              // Centered
    int             w;              // 640
    int             h;              // 480
    unsigned        flags;          // APP_WINDOW_FLAG_CENTERED | APP_WINDOW_FLAG_VISIBLE
} app_window_desc;

typedef struct app_expose_event {
    app_event_type  type;
    double          time;
    int             visible;
} app_expose_event;

typedef struct app_focus_event {
    app_event_type  type;
    double          time;
    int             focused;
} app_focus_event;

typedef struct app_resize_event {
    app_event_type  type;
    double          time;
    int             w;
    int             h;
} app_resize_event;

typedef struct app_button_event {
    app_event_type  type;
    double          time;
    app_button      button;
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
    app_key         key;
    unsigned        mods;
    int             pressed;
} app_key_event;

typedef union app_event {
    app_event_type      type;
    double              time;
    app_expose_event    expose;
    app_focus_event     focus;
    app_resize_event    resize;
    app_button_event    button;
    app_motion_event    motion;
    app_scroll_event    scroll;
    app_key_event       key;
} app_event;

typedef struct app_allocator_desc {
    void *(*malloc)(size_t size);
    void *(*calloc)(size_t count, size_t size);
    void *(*free)(void *ptr);
} app_allocator_desc;

typedef int     (*app_init_callback)(void);
typedef void    (*app_event_callback)(app_event const *event);
typedef void    (*app_update_callback)(float dt);
typedef void    (*app_exit_callback)(void);

typedef struct app_desc {
    app_init_callback   init;
    app_event_callback  event;
    app_update_callback update;
    app_exit_callback   exit;
    app_window_desc     window;
    app_allocator_desc  allocator;
} app_desc;

app_desc    app_main            (int argc, char **argv);
void        app_pos             (int *x, int *y);
void        app_size            (int *w, int *h);
int         app_visible         (void);
int         app_should_quit     (void);
void        app_set_pos         (int x, int y);
void        app_set_size        (int w, int h);
void        app_set_visible     (int visible);
void        app_set_should_quit (int should_quit);
void        app_set_title       (char const *title);

/***********************************************************************************************************************
************************************************************************************************************************
****                                                                                                                ****
****                                                                                                                ****
****                                                 Implementation                                                 ****
****                                                                                                                ****
****                                                                                                                ****
************************************************************************************************************************
***********************************************************************************************************************/


#if defined(APP_IMPLEMENTATION)

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

static struct {
#if defined(APP_USE_X11)
    struct {
        Display *dpy;
        Visual *vis;
        Window root_wnd;
        Window wnd;
        Atom wm_del_wnd;
        int screen;
        int depth;
    } x11;
#elif defined(APP_USE_COCOA)  && defined(__OBJC__)
    struct {
        id app;
        id wnd;
        id delegate;
    } cocoa;
#endif
    app_desc desc;
} _app = {0};


#if defined(APP_USE_X11)


int app__init(void) {
    _app.x11.dpy = XOpenDisplay(NULL);
    if (!_app.x11.dpy) {
        app_fprintf(stderr, "Failed to connect to X server\n");
        return 0;
    }

    _app.x11.root_wnd = DefaultRootWindow(_app.x11.dpy);
    _app.x11.screen   = DefaultScreen(_app.x11.dpy);
    _app.x11.vis      = DefaultVisual(_app.x11.dpy, _app.x11.screen);
    _app.x11.depth    = DefaultDepth(_app.x11.dpy, _app.x11.screen);
    return 1;
}

void app__exit(void) {
    if (_app.x11.dpy) {
        XCloseDisplay(_app.x11.dpy);
    }
}

int app__init(void) {
    XSetWindowAttributes swa = {
        .background_pixel = WhitePixel(_app.x11.dpy, _app.x11.screen),
        .event_mask       = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
    };
    unsigned long swa_mask = CWEventMask | CWBorderPixel | CWBackPixel;

    wnd->x11.wnd = XCreateWindow(dpy, root_wnd, wnd->desc.x, wnd->desc.y, wnd->desc.w, wnd->desc.h, 0, depth, InputOutput, _app.x11.vis, swa_mask, &swa);

    if (!wnd->x11.wnd) {
        app_fprintf(stderr, "Failed to create x11 window\n");
        return 1;
    }

    wnd->x11.wm_del_wnd = XInternAtom(_app.x11.dpy, "WM_DELETE_WINDOW", 0);
    XSetWMProtocols(_app.x11.dpy, wnd->x11.wnd, &wnd->x11.wm_del_wnd, 1);
    return 0;
}

void app__deinit(void) {
    XDestroyWindow(_app.x11.dpy, wnd->x11.wnd);
}

void app__poll_events(void (*event_callback)(app_event const *event)) {
    (void)event_callback;
}

void app__set_pos(int x, int y) {
    if (app_visible(wnd) == 0) {
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

void app__set_size(int w, int h) {
    XResizeWindow(_app.x11.dpy, wnd->x11.wnd, w, h);
    XFlush(_app.x11.dpy);
}

void app__set_visible(int visible) {
    if (visible) {
        XMapWindow(_app.x11.dpy, wnd->x11.wnd);
        XMoveWindow(_app.x11.dpy, wnd->x11.wnd, wnd->desc.x, wnd->desc.y);
    } else {
        XUnmapWindow(_app.x11.dpy, wnd->x11.wnd);
    }
}

void app__set_title(char const *title) {
    XStoreName(_app.x11.dpy, wnd->x11.wnd, title);
}


#elif defined(APP_USE_COCOA) && defined(__OBJC__)


@interface app__app: NSObject <NSApplicationDelegate>
@end

@implementation app__app

-(void)applicationWillFinishLaunching:(NSNotification *)notification {
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

@end

@interface app__delegate : NSObject <NSWindowDelegate> {
    app *wnd_;
}
@end

@implementation app__delegate

-(id)initWithWindow:(app *)wnd {
    if ((self = [super init])) {
        wnd_ = wnd;
    }
    return self;
}

-(BOOL)acceptsFirstResponder {
    return YES;
}

-(BOOL)windowShouldClose:(NSWindow *)sender {
    app_set_should_close(wnd_, 1);
    return NO;
}

-(void)windowWillClose:(id)sender {
    app_set_should_close(wnd_, 1);
}

@end

int app__init(void) {
    @autoreleasepool {

    _app.cocoa.app = [[app__app alloc] init];
    [NSApplication sharedApplication];
    [NSApp setDelegate:_app.cocoa.app];
    [NSApp finishLaunching];

    return 1;

    }
}

void app__exit(void) {
    @autoreleasepool {

    [NSApp terminate:nil];
    [_app.cocoa.app release];
    _app.cocoa.app = nil;

    } // autoreleasepool
}

void app__poll_events(void (*event_callback)(app_event const *event)) {
    @autoreleasepool {

    (void)event_callback; // TODO

    NSEvent* event = nil;
    do {
        event = [NSApp nextEventMatchingMask:NSEventMaskAny untilDate:nil inMode:NSDefaultRunLoopMode dequeue:YES];
        [NSApp sendEvent:event];
    } while (event != nil);

    } // autoreleasepool
}


int app__init(void) {
    @autoreleasepool {

    NSRect frame = NSMakeRect(wnd->desc.x, wnd->desc.y, wnd->desc.w, wnd->desc.h);
    unsigned style = NSWindowStyleMaskClosable | NSWindowStyleMaskTitled | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable; // TODO: Custom wnd style

    wnd->cocoa.wnd = [[NSWindow alloc] initWithContentRect:frame styleMask:style backing:NSBackingStoreBuffered defer:NO];
    if (wnd->cocoa.wnd == nil) {
        app_fprintf(stderr, "Failed to create cocoa wnd\n");
        return 0;
    }

    wnd->cocoa.delegate = [[app__delegate alloc] initWithWindow:wnd];
    if (wnd->cocoa.delegate == nil) {
        app_fprintf(stderr, "Failed to create cocoa wnd delegate\n");
        return 0;
    }

    [wnd->cocoa.wnd setDelegate:wnd->cocoa.delegate];
    [wnd->cocoa.wnd setBackgroundColor:[NSColor colorWithRed:1 green:1 blue:1 alpha:1]];

    if (((wnd->desc.flags >> APP_WINDOW_FLAG_CENTERED) & 1U) == 1) {
        [(NSWindow *)wnd->cocoa.wnd center];
    }

    return 1;

    } // autoreleasepool
}

void app__deinit(void) {
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

void app__set_pos(int x, int y) {
    @autoreleasepool {

    NSScreen* screen = [NSScreen mainScreen];
    CGSize frame     = [screen frame].size;
    NSRect visframe  = [screen visibleFrame];
    CGFloat height   = frame.height - visframe.size.height - visframe.origin.y;

    [wnd->cocoa.wnd setFrameTopLeftPoint:NSMakePoint(x, frame.height - height - y)];

    } // autoreleasepool
}

void app__set_size(int w, int h) {
    @autoreleasepool {

    NSRect contentRect    = [wnd->cocoa.wnd contentRectForFrameRect:[wnd->cocoa.wnd frame]];
    contentRect.origin.y += contentRect.size.height - h;
    contentRect.size      = NSMakeSize(w, h);
    [wnd->cocoa.wnd setFrame:[wnd->cocoa.wnd frameRectForContentRect:contentRect] display:YES];

    } // autoreleasepool
}

void app__set_visible(int visible) {
    @autoreleasepool {

    if (visible == 1) {
        [wnd->cocoa.wnd makeKeyAndOrderFront:nil];
    } else {
        [wnd->cocoa.wnd orderOut:nil];
    }

    } // autoreleasepool
}

void app__set_title(char const *title) {
    @autoreleasepool {

    if (wnd != NULL && wnd->cocoa.wnd != nil) {
        [wnd->cocoa.wnd setTitle:[NSString stringWithUTF8String:title]];
    }

    } // autoreleasepool
}


#endif // APP_USE_X11 || (APP_USE_COCOA && __OBJC__)

int app__default_init_callback(void) {
    return 1;
}
void app__default_event_callback(app_event const *e) {
}
void app__default_update_callback(float dt) {
}
void app__default_exit_callback(void) {
}

int app_init(app_desc const *desc) {
    _app.desc = (app_desc){
        .init   = desc->init ? desc->init : app__default_init_callback,
        .event  = desc->event ? desc->event : app__default_event_callback,
        .update = desc->update ? desc->update : app__default_update_callback,
        .exit   = desc->exit ? desc->exit : app__default_exit_callback,
        .window = {
            .title  = desc->window.title ? desc->window.title : "Untitled",
            .x      = desc->window.x,
            .y      = desc->window.y,
            .w      = desc->window.w ? desc->window.w : 640,
            .h      = desc->window.h ? desc->window.h : 480,
            .flags  = desc->window.flags != APP_WINDOW_FLAG_NONE ? desc->window.flags : APP_WINDOW_FLAG_CENTERED | APP_WINDOW_FLAG_VISIBLE
        },
        .allocator = {
            .malloc = desc->allocator.malloc ? desc->allocator.malloc : malloc,
            .calloc = desc->allocator.malloc ? desc->allocator.malloc : malloc,
            .free   = desc->allocator.malloc ? desc->allocator.malloc : malloc,
        }
    };

    if (app__init() == 0) {
        app_set_title(_app.desc.window.title);
        app_set_visible(1);
        app_set_should_close(0);
    } else {
        return -1;
    }
}

void app_exit(void) {
    app__exit();
    app_memset(&_app, 0, sizeof _app);
}

void app_poll_events(void (*event_callback)(app_event const *event)) {
    app__poll_events(event_callback);
}

app *app_create(app_window_desc const *desc) {
    void = app_calloc(1, sizeof *wnd);
    if (wnd == NULL) {
        return NULL;
    }

    if (app__init(wnd) != 0) {
        app_destroy(wnd);
        return NULL;
    }

    return wnd;
}

void app_destroy(void) {
    app__deinit(wnd);
    *wnd = (app){0};
    app_free(wnd);
}

void app_swap_buffers(app const *wnd) {
    (void)wnd;
}

void app_pos(app const *wnd, int *x, int *y) {
    app_assert(wnd && "Window cannot be null");
    if (x != NULL) { *x = wnd->desc.x; }
    if (y != NULL) { *y = wnd->desc.y; }
}

void app_size(app const *wnd, int *w, int *h) {
    app_assert(wnd && "Window cannot be null");
    if (w != NULL) { *w = wnd->desc.w; }
    if (h != NULL) { *h = wnd->desc.h; }
}

int app_visible(app const *wnd) {
    app_assert(wnd && "Window cannot be null");
    return (wnd->desc.flags >> APP_WINDOW_FLAG_VISIBLE) & 1U;
}

int app_should_close(app const *wnd) {
    app_assert(wnd && "Window cannot be null");
    return wnd->should_close;
}

void app_set_pos(int x, int y) {
    app_assert(wnd && "Window cannot be null");
    if (x < 0) { x = 0; }
    if (y < 0) { y = 0; }
    wnd->desc.x = x;
    wnd->desc.y = y;
    app__set_pos(wnd, x, y);
}

void app_set_size(int w, int h) {
    app_assert(wnd && "Window cannot be null");
    if (w < 0) { w = 0; }
    if (h < 0) { h = 0; }
    wnd->desc.w = w;
    wnd->desc.h = h;
    app__set_size(wnd, w, h);
}

void app_set_visible(int visible) {
    app_assert(wnd && "Window cannot be null");
    if (visible == 1) {
        wnd->desc.flags |=  APP_WINDOW_FLAG_VISIBLE;
    } else {
        wnd->desc.flags &= ~APP_WINDOW_FLAG_VISIBLE;
    }
    app__set_visible(wnd, visible);
}

void app_set_should_close(int should_close) {
    app_assert(wnd && "Window cannot be null");
    wnd->should_close = should_close;
}

void app_set_title(char const *title) {
    app_assert(wnd   && "Window cannot be null");
    app_assert(title && "Title cannot be null");
    app__set_title(wnd, title);
}

#endif // APP_IMPLEMENTATION
