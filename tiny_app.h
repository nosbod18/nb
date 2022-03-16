#ifndef __tiny_app_h__
#define __tiny_app_h__

#include <stdbool.h> // bool

// {{{ Enums

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
        TAPP_EVENT_TYPE_NONE            = 0,
        TAPP_EVENT_TYPE_QUIT,           // A quit has been requested
        TAPP_EVENT_TYPE_WINDOWEXPOSE,   // A window was partially exposed or hidden
        TAPP_EVENT_TYPE_WINDOWRESIZE,   // A window's size was changed
        TAPP_EVENT_TYPE_WINDOWFOCUS,    // A window's focus was changed
        TAPP_EVENT_TYPE_MOUSEBUTTON,    // A mouse button was pressed or released
        TAPP_EVENT_TYPE_MOUSEENTER,     // The mouse entered the window space
        TAPP_EVENT_TYPE_MOUSELEAVE,     // The mouse left the window space
        TAPP_EVENT_TYPE_MOUSEMOTION,    // The mouse changed position
        TAPP_EVENT_TYPE_MOUSESCROLL,    // The scroll wheel was moved
        TAPP_EVENT_TYPE_KEY,            // A key was pressed or released
} tapp_event_type;

typedef enum tapp_window_flags {
        TAPP_WINDOW_FLAG_DEFAULT        = 0,
        TAPP_WINDOW_FLAG_VISIBLE        = 1 << 1,
        TAPP_WINDOW_FLAG_VSYNC          = 1 << 2,
        TAPP_WINDOW_FLAG_FULLSCREEN     = 1 << 3,
} tapp_window_flags;

// }}}
// {{{ Types

typedef struct tapp_window tapp_window;

typedef struct tapp_window_desc {
        char const     *title;
        int             x;
        int             y;
        int             width;
        int             height;
        unsigned        flags;
} tapp_window_desc;

typedef struct tapp_expose_event {
        tapp_event_type type;
        double          time;
        tapp_window    *window;
        bool            visible;
} tapp_expose_event;

typedef struct tapp_focus_event {
        tapp_event_type type;
        double          time;
        tapp_window    *window;
        int             focused;
} tapp_focus_event;

typedef struct tapp_resize_event {
        tapp_event_type type;
        double          time;
        tapp_window    *window;
        int             width;
        int             height;
} tapp_resize_event;

typedef struct tapp_button_event {
        tapp_event_type type;
        double          time;
        tapp_button     sym;
        unsigned        mods;
        int             pressed;
        int             x;
        int             y;
} tapp_button_event;

typedef struct tapp_motion_event {
        tapp_event_type type;
        double          time;
        double          dx;
        double          dy;
} tapp_motion_event;

typedef struct tapp_scroll_event {
        tapp_event_type type;
        double          time;
        double          dx;
        double          dy;
} tapp_scroll_event;

typedef struct tapp_key_event {
        tapp_event_type type;
        double          time;
        tapp_key        sym;
        unsigned        mods;
        int             pressed;
} tapp_key_event;

typedef union tapp_event {
        tapp_event_type         type;
        tapp_expose_event       expose;
        tapp_focus_event        focus;
        tapp_resize_event       resize;
        tapp_button_event       button;
        tapp_motion_event       motion;
        tapp_scroll_event       scroll;
        tapp_key_event          key;
} tapp_event;

typedef void (*tapp_init_callback)(void);
typedef void (*tapp_event_callback)(tapp_event const *event);
typedef void (*tapp_update_callback)(double dt);
typedef void (*tapp_quit_callback)(void);

typedef struct tapp_desc {
        tapp_window_desc window;
        tapp_init_callback on_init;
        tapp_event_callback on_event;
        tapp_update_callback on_update;
        tapp_quit_callback on_quit;
} tapp_desc;

// }}}
// {{{ Prototypes

tapp_desc       tapp_main                       (int argc, char **argv);
tapp_window    *tapp_get_main_window            (void);
double          tapp_get_time                   (void);

#define         tapp_get_pos(xptr, yptr)        tapp_window_get_pos(tapp_get_main_window(), xptr, yptr)
#define         tapp_set_pos(x, y)              tapp_window_set_pos(tapp_get_main_window(), xptr, yptr)
#define         tapp_get_size(wptr, hptr)       tapp_window_get_size(tapp_get_main_window(), wptr, hptr)
#define         tapp_set_size(w, h)             tapp_window_set_size(tapp_get_main_window(), wptr, hptr)
#define         tapp_get_visible()              tapp_window_get_visible(tapp_get_main_window())
#define         tapp_set_visible(visible)       tapp_window_set_visible(tapp_get_main_window())
#define         tapp_get_should_quit()          tapp_window_get_should_quit(tapp_get_main_window())
#define         tapp_set_should_quit(quit)      tapp_window_set_should_close(tapp_get_main_window(), quit)
#define         tapp_set_title(title)           tapp_window_set_title(tapp_get_main_window(), title)


// Semi internal, use when TAPP_CUSTOM_ENTRY is defined or if more control is needed

bool            tapp_init                       (tapp_desc const *desc);
void            tapp_quit                       (void);

tapp_window    *tapp_window_create              (tapp_window_desc const *desc);
void            tapp_window_delete              (tapp_window *window);
void            tapp_window_poll_events         (tapp_window const *window, tapp_event_callback callback);
void            tapp_window_get_pos             (tapp_window const *window, int *x, int *y);
void            tapp_window_set_pos             (tapp_window *window, int x, int y);
void            tapp_window_get_size            (tapp_window const *window, int *w, int *h);
void            tapp_window_set_size            (tapp_window *window, int w, int h);
bool            tapp_window_get_visible         (tapp_window const *window);
void            tapp_window_set_visible         (tapp_window const *window, bool visible);
bool            tapp_window_get_should_close    (tapp_window const *window);
void            tapp_window_set_should_close    (tapp_window const *window, bool should_close);
void            tapp_window_set_title           (tapp_window *window, char const *title);

// }}}

/*************************************************************************************************************************************************************
**************************************************************************************************************************************************************
****                                                                                                                                                      ****
****                                                                                                                                                      ****
****                                                                    Implementation                                                                    ****
****                                                                                                                                                      ****
****                                                                                                                                                      ****
**************************************************************************************************************************************************************
*************************************************************************************************************************************************************/


#if defined(TAPP_IMPL) || defined(TINY_IMPL)
#ifndef __tiny_app_c__
#define __tiny_app_c__

// {{{ Includes / Defines

#if !defined(TAPP_USE_X11) && !defined(TAPP_USE_COCOA)
        #ifdef __linux__
                #ifndef TAPP_USE_X11
                        #define TAPP_USE_X11
                #endif
        #endif
        #ifdef __APPLE__
                #ifndef TAPP_USE_COCOA
                        #define TAPP_USE_COCOA
                #endif
        #endif
#endif

#if defined(TAPP_USE_X11)
        #include <X11/Xlib.h>
        #include <sys/time.h> // clock_gettime, CLOCK_REALTIME, CLOCK_MONOTONIC
#elif defined(TAPP_USE_COCOA)
        #import <Cocoa/Cocoa.h>
        #import <mach/mach_absolute_time.h>
#endif

#include <stdlib.h> // calloc, free
#include <string.h> // memset
#include <assert.h> // assert

#ifndef TAPP_LOG
        #include <stdio.h> // fprintf
        #define TAPP_LOG(...) do { fprintf(stderr, "[%12s:%04d] ", __FILE__, __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); } while (0)
#endif

// }}}
// {{{ Types

struct tapp_window {
#if defined(TAPP_USE_X11)
        struct {
                Window wnd;
                Atom wm_del_wnd;
        } x11;

#elif defined(TAPP_USE_COCOA)
        struct {
                id wnd;
                id delegate;
        } cocoa;
#endif

        tapp_window_desc desc;
        bool should_close;
};

static struct {
#if defined(TAPP_USE_X11)
        struct {
                Display *dpy;
                Visual *vis;
                Window root_wnd;
                int screen;
                int depth;
        } x11;

#elif defined(TAPP_USE_COCOA)
        struct {
                id app;
        } ns;
#endif

        tapp_desc desc;
        tapp_window *main_window;
        double start_time;
        bool should_quit;
} _tapp = {0};

// }}}
// {{{ Platform
// {{{ X11

#if defined(TAPP_USE_X11)

bool tapp__init_x11(void) {
        _tapp.x11.dpy = XOpenDisplay(NULL);
        if (!_tapp.x11.dpy) {
                TAPP_LOG("Failed to connect to X server");
                return false;
        }

        _tapp.x11.root_wnd = DefaultRootWindow(_tapp.x11.dpy);
        _tapp.x11.screen   = DefaultScreen(_tapp.x11.dpy);
        _tapp.x11.vis      = DefaultVisual(_tapp.x11.dpy, _tapp.x11.screen);
        _tapp.x11.depth    = DefaultDepth(_tapp.x11.dpy, _tapp.x11.screen);
        _tapp.start_time   = tapp_get_time();
        return true;
}

void tapp__quit_x11(void) {
        if (_tapp.x11.dpy) {
                XCloseDisplay(_tapp.x11.dpy);
        }
}

bool tapp_window__create_x11(tapp_window *window) {
        XSetWindowAttributes swa = {
                .background_pixel = WhitePixel(_tapp.x11.dpy, _tapp.x11.screen),
                .event_mask       = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
        };
        unsigned long swa_mask = CWEventMask | CWBorderPixel | CWBackPixel;

        window->x11.wnd = XCreateWindow(dpy, root_wnd, window->desc.x, window->desc.y, window->desc.width, window->desc.height, 0, depth, InputOutput, _tapp.x11.vis, swa_mask, &swa);

        if (!window->x11.wnd) {
                TAPP_LOG("Failed to create x11 window");
                return false;
        }

        window->x11.wm_del_wnd = XInternAtom(_tapp.x11.dpy, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(_tapp.x11.dpy, window->x11.wnd, &window->x11.wm_del_wnd, 1);
        return true;
}

void tapp_window__delete_x11(tapp_window *window) {
        XDestroyWindow(_tapp.x11.dpy, window->x11.wnd);
}

int tapp__translate_key_x11(int key) {
        (void)key;
        return 0;
}

// TODO
void tapp_window__poll_events_x11(tapp_window const *window, tapp_event_callback callback) {
        (void)window;
        (void)callback;
}

void tapp_window__set_pos_x11(tapp_window *window, int x, int y) {
        if (!tapp_window_get_visible(window)) {
                long unused;
                XSizeHints *hints = XAllocSizeHints();
                if (XGetWMNormalHints(_tapp.x11.dpy, window->x11.wnd, hints, &unused)) {
                        hints->flags |= PPosition;
                        hints->x = hints->y = 0;
                        XSetWMNormalHints(_tapp.x11.dpy, window->x11.wnd, hints);
                }
                XFree(hints);
        }

        XMoveWindow(_tapp.x11.dpy, window->x11.wnd, x, y);
        window->desc.x = x;
        window->desc.y = y;
}

void tapp_window__set_size_x11(tapp_window *window, int w, int h) {
        XResizeWindow(_tapp.x11.dpy, window->x11.wnd, w, h);
        XFlush(_tapp.x11.dpy);
}

void tapp_window__set_visible_x11(tapp_window *window, int visible) {
        if (visible) {
                XMapWindow(_tapp.x11.dpy, window->x11.wnd);
                XMoveWindow(_tapp.x11.dpy, window->x11.wnd, window->desc.x, window->desc.y);
        } else {
                XUnmapWindow(_tapp.x11.dpy, window->x11.wnd);
        }
}

void tapp_window__set_title_x11(tapp_window *window, char const *title) {
        XStoreName(_tapp.x11.dpy, window->x11.wnd, title);
}

double tapp__get_time_x11(void) {
        struct timespec ts;
#ifdef CLOCK_MONOTONIC
        clock_gettime(CLOCK_MONOTONIC, &ts);
#else
        clock_gettime(CLOCK_REALTIME, &ts);
#endif
        // Convert to seconds
        double now = ts.tv_sec + (double)ts.tv_nsec * 1e-9;
        return now - _tapp.start_time;
}

// }}}
// {{{ Cocoa

#elif defined(TAPP_USE_COCOA)

// {{{ objc

@interface tapp__cocoa_app: NSObject <NSApplicationDelegate>
@end

@implementation tapp__cocoa_app

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
        tapp_set_should_quit(true);
}

@end

@interface tapp__cocoa_delegate : NSObject <NSWindowDelegate> {
        tapp_window *window_;
}
@end

@implementation tapp__cocoa_delegate

-(id)initWithWindow:(tapp_window *)window {
        if ((self = [super init])) {
                window_ = window;
        }
        return self;
}

-(BOOL)acceptsFirstResponder {
        return YES;
}

-(BOOL)windowShouldClose:(NSWindow *)sender {
        tapp_window_set_should_close(window_, 1);
        return NO;
}

-(void)windowWillClose:(id)sender {
        tapp_window_set_should_close(window_, 1);
}

@end

// }}}

bool tapp_init__cocoa(void) {
        @autoreleasepool {

        _tapp.cocoa.app = [[tapp__cocoa_app alloc] init];
        [NSApplication sharedApplication];
        [NSApp setDelegate:_tapp.cocoa.app];
        [NSApp finishLaunching];

        return true;

        }
}

void tapp_quit__cocoa(void) {
        @autoreleasepool {

        [NSApp terminate:nil];
        [_tapp.cocoa.app release]
        _tapp.cocoa.app = nil;

        } // autoreleasepool
}

bool tapp_window__create_cocoa(tapp_window *window) {
        @autoreleasepool {

        NSRect frame = NSMakeRect(window->desc.x, window->desc.y, window->desc.width, window->desc.height);
        StyleMask style = NSWindowStyleMaskClosable | NSWindowStyleMaskTitled | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable; // TODO: Custom window style

        window->cocoa.wnd = [[NSWindow alloc] initWithContentRect:frame styleMask:style backing:NSBackingStoreBuffered defer:NO];
        if (!window->cocoa.wnd) {
                TAPP_LOG("Failed to create cocoa window");
                return false;
        }

        window->cocoa.delegate = [[tapp__cocoa_delegate alloc] initWithWindow:window];
        if (!window->cocoa.delegate) {
                TAPP_LOG("Failed to create cocoa window delegate");
                return false;
        }

        [window->cocoa.wnd setDelegate:window->cocoa.delegate];
        [window->cocoa.wnd setBackgroundColor:[NSColor colorWithRed:1 green:1 blue:1 alpha:1]];
        return true;

        } // autoreleasepool
}

void tapp_window__delete_cocoa(tapp_window *window) {
        @autoreleasepool {

        if (window->cocoa.delegate) {
                [window->cocoa.wnd setDelegate:nil];
                [window->cocoa.delegate release];
                window->cocoa.delegate = nil;
        }

        if (window->cocoa.wnd) {
                [window->cocoa.wnd close];
                window->cocoa.wnd = nil;
        }

        } // autoreleasepool
}

void tapp_window__poll_events_cocoa(tapp_window const *window, tapp_event_callback callback) {
        @autoreleasepool {

        (void)window; // TODO
        (void)callback; // TODO

        NSEvent* event = nil;
        do {
                event = [NSApp nextEventMatchingMask:NSEventMaskAny untilDate:nil inMode:NSDefaultRunLoopMode dequeue:YES];
                [NSApp sendEvent:event];
        } while (event != nil);

        } // autoreleasepool
}

void tapp_window__set_pos_cocoa(tapp_window *window, int x, int y) {
        @autoreleasepool {

        NSRect frameRect = [window->cocoa.wnd frameRectForContentRect:NSMakeRect(x, y, 0, 0)];
        [window->cocoa.wnd setFrameOrigin:frameRect.origin];

        } // autoreleasepool
}

void tapp_window__set_size_cocoa(tapp_window *window, int w, int h) {
        @autoreleasepool {

        NSRect contentRect    = [window->cocoa.wnd contentRectForFrameRect:[window->cocoa.wnd frame]];
        contentRect.origin.y += contentRect.size.height - h;
        contentRect.size      = NSMakeSize(w, h);
        [window->cocoa.wnd setFrame:[window->cocoa.wnd frameRectForContentRect:contentRect] display:YES];

        } // autoreleasepool
}

void tapp_window_set_visible(tapp_window *window, bool visible) {
        @autoreleasepool {

        if (visible) {
                [window->cocoa.wnd setInitialFirstResponder:window->cocoa.delegate];
                [window->cocoa.wnd makeFirstResponder:window->cocoa.delegate];
                [window->cocoa.wnd makeKeyAndOrderFront:nil];
        } else {
                [window->cocoa.wnd orderOut:nil];
        }

        } // autoreleasepool
}

void tapp_window_set_title(tapp_window *window, char const *title) {
        @autoreleasepool {

        if (window && window->cocoa.wnd) {
                [window->cocoa.wnd setTitle:[NSString stringWithUTF8String:title]];
        }

        } // autoreleasepool
}

#endif // defined(__linux__) || defined(TAPP_USE_COCOA)

// }}}
// }}}
// {{{ Init / Quit

inline void tapp__default_on_init   (void)                {}
inline void tapp__default_on_event  (tapp_event const *)  {}
inline void tapp__default_on_update (double)              {}
inline void tapp__default_on_quit   (void)                {}

bool tapp_init(tapp_desc const *desc) {
        _tapp.desc = *desc;

        if (!_tapp.desc.on_init)   { _tapp.desc.on_init   = tapp__default_on_init; }
        if (!_tapp.desc.on_event)  { _tapp.desc.on_event  = tapp__default_on_event; }
        if (!_tapp.desc.on_update) { _tapp.desc.on_update = tapp__default_on_update; }
        if (!_tapp.desc.on_quit)   { _tapp.desc.on_quit   = tapp__default_on_quit; }

#if defined(TAPP_USE_X11)
        return tapp__init_x11();
#elif defined(TAPP_USE_COCOA)
        return tapp__init_cocoa();
#endif
}

void tapp_quit(void) {
#if defined(TAPP_USE_X11)
        tapp_quit_x11();
#elif defined(TAPP_USE_COCOA)
        tapp_quit_cocoa();
#endif
        tapp_window_delete(tapp_get_main_window());
        memset(&_tapp, 0, sizeof _tapp);
}

// }}}
// {{{ Window

tapp_window *tapp_window_create(tapp_window_desc const *desc) {
        tapp_window *window = calloc(1, sizeof *window);
        if (!window) {
                TAPP_LOG("Failed to create window, out of memory");
                return NULL;
        }

        window->desc = *desc;

#if defined(TAPP_USE_X11)
        if (!tapp_window__create_x11(window)) {
#elif defined(TAPP_USE_COCOA)
        if (!tapp_window__create_cocoa(window)) {
#endif
                tapp_window_delete(window);
                return NULL;
        }
        tapp_window_set_title(window, desc->title);
        tapp_window_set_visible(window, true);
        return window;
}

void tapp_window_delete(tapp_window *window) {
#if defined(TAPP_USE_X11)
        tapp_window__delete_x11(window);
#elif defined(TAPP_USE_COCOA)
        tapp_window__delete_cocoa(window);
#endif
        *window = (tapp_window){0};
        free(window);
}

void tapp_window_poll_events(tapp_window const *window, tapp_event_callback callback) {
        assert(window);
#if defined(TAPP_USE_X11)
        tapp_window__poll_events_x11(window, callback);
#elif defined(TAPP_USE_COCOA)
        tapp_window__poll_events_cocoa(window, callback);
#endif
}

void tapp_window_get_pos(tapp_window *window, int *x, int *y) {
        assert(window);
        if (x) { *x = window->desc.x; }
        if (y) { *y = window->desc.y; }
}

void tapp_window_set_pos(tapp_window *window, int x, int y) {
        assert(window);
        if (x < 0)   { x = 0; }
        if (y < 0)   { y = 0; }
#if defined(TAPP_USE_X11)
        tapp_window__set_pos_x11(window, x, y);
#elif defined(TAPP_USE_COCOA)
        tapp_window__set_pos_cocoa(window, x, y);
#endif
        window->desc.x = x;
        window->desc.y = y;
}

void tapp_window_get_size(tapp_window *window, int *w, int *h) {
        assert(window);
        if (w) { *w = window->desc.width; }
        if (h) { *h = window->desc.height; }
}

void tapp_window_set_size(tapp_window *window, int w, int h) {
        assert(window);
        if (w < 0)   { w = 0; }
        if (h < 0)   { h = 0; }
#if defined(TAPP_USE_X11)
        tapp_window__size_pos_x11(window, w, h);
#elif defined(TAPP_USE_COCOA)
        tapp_window__set_size_cocoa(window, w, h);
#endif
        window->desc.width  = w;
        window->desc.height = h;
}

bool tapp_window_get_visible(tapp_window *window) {
        assert(window);
        return (window->desc.flags >> TAPP_WINDOW_FLAG_VISIBLE) & 1U;
}

void tapp_window_set_visible(tapp_window *window, bool visible) {
        assert(window);
#if defined(TAPP_USE_X11)
        tapp_window__size_visible_x11(window, visible);
#elif defined(TAPP_USE_COCOA)
        tapp_window__set_visible_cocoa(window, visible);
#endif
        if (visible) {
                window->desc.flags |=  TAPP_WINDOW_FLAG_VISIBLE;
        } else {
                window->desc.flags &= ~TAPP_WINDOW_FLAG_VISIBLE
        }
}

bool tapp_wwindow_get_should_close(tapp_window *window) {
        assert(window);
        return window->should_close;
}

void tapp_window_set_should_close(tapp_window *window, bool should_close) {
        assert(window);
        window->should_close = should_close;
}

void tapp_window_set_title(tapp_window *window, char const *title) {
        assert(window);
        assert(title);
#if defined(TAPP_USE_X11)
        tapp_window__set_title_x11(window, title);
#elif defined(TAPP_USE_COCOA)
        tapp_window__set_title_cocoa(window, title);
#endif
        // window->desc.title = title; // ?
}

tapp_window *tapp_get_main_window(void) {
        return _tapp.main_window;
}

double tapp_get_time(void) {

}

// }}}
// {{{ Entry

#ifndef TAPP_CUSTOM_ENTRY

int main(int argc, char **argv) {
        tapp_desc desc = tapp_main(argc, argv);
        if (!tapp_init(&desc)) {
                TAPP_LOG("Error on initialization, exiting...");
                return -1;
        }

        _tapp.main_window = tapp_window_create(&desc.window);
        if (!_tapp.main_window) {
                TAPP_LOG("Error on initialization, exiting...");
                tapp_quit();
                return -1;
        }

        _tapp.desc.on_init();

        double last = tapp_get_time();
        while (!tapp_get_should_quit()) {
                // Update frame timings
                double now = tapp_get_time();
                double dt = now - last;
                last = now;

                _tapp.desc.on_update(dt);
                tapp_window_poll_events(tapp_get_main_window(), _tapp.desc.on_event);
        }

        _tapp.desc.on_quit();
        tapp_quit();
        return 0;
}

#endif // !TAPP_CUSTOM_ENTRY

// }}}

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
