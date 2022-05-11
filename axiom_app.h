#ifndef AXIOM_APP_H_
#define AXIOM_APP_H_

#include <stdbool.h> // bool

typedef enum axa_key {
    AXA_KEY_INVALID                 = 0x00,
    AXA_KEY_BACKSPACE               = 0x08,
    AXA_KEY_TAB                     = 0x09,
    AXA_KEY_ESCAPE                  = 0x1b,
    AXA_KEY_SPACE                   = ' ',
    AXA_KEY_BANG                    = '!',
    AXA_KEY_QUOTE                   = '\"',
    AXA_KEY_POUND                   = '#',
    AXA_KEY_DOLLAR                  = '$',
    AXA_KEY_PERCENT                 = '%',
    AXA_KEY_AMPERSAN                = '&',
    AXA_KEY_APOSTROPHE              = '\'',
    AXA_KEY_LEFT_PARENTHESES        = '(',
    AXA_KEY_RIGHT_PARENTHESES       = ')',
    AXA_KEY_ASTERISK                = '*',
    AXA_KEY_PLUS                    = '+',
    AXA_KEY_COMMA                   = ',',
    AXA_KEY_MINUS                   = '-',
    AXA_KEY_PERIOD                  = '.',
    AXA_KEY_FORWARD_SLASH           = '/',
    AXA_KEY_0                       = '0',
    AXA_KEY_1                       = '1',
    AXA_KEY_2                       = '2',
    AXA_KEY_3                       = '3',
    AXA_KEY_4                       = '4',
    AXA_KEY_5                       = '5',
    AXA_KEY_6                       = '6',
    AXA_KEY_7                       = '7',
    AXA_KEY_8                       = '8',
    AXA_KEY_9                       = '9',
    AXA_KEY_COLON                   = ':',
    AXA_KEY_SEMICOLON               = ';',
    AXA_KEY_LEFT_ANGLE_BRACKET      = '<',
    AXA_KEY_EQUALS                  = '=',
    AXA_KEY_RIGHT_ANGLE_BRACKET     = '>',
    AXA_KEY_QUESTION_MARK           = '?',
    AXA_KEY_AT                      = '@',
    AXA_KEY_A                       = 'A',
    AXA_KEY_B                       = 'B',
    AXA_KEY_C                       = 'C',
    AXA_KEY_D                       = 'D',
    AXA_KEY_E                       = 'E',
    AXA_KEY_F                       = 'F',
    AXA_KEY_G                       = 'G',
    AXA_KEY_H                       = 'H',
    AXA_KEY_I                       = 'I',
    AXA_KEY_J                       = 'J',
    AXA_KEY_K                       = 'K',
    AXA_KEY_L                       = 'L',
    AXA_KEY_M                       = 'M',
    AXA_KEY_N                       = 'N',
    AXA_KEY_O                       = 'O',
    AXA_KEY_P                       = 'P',
    AXA_KEY_Q                       = 'Q',
    AXA_KEY_R                       = 'R',
    AXA_KEY_S                       = 'S',
    AXA_KEY_T                       = 'T',
    AXA_KEY_U                       = 'U',
    AXA_KEY_V                       = 'V',
    AXA_KEY_W                       = 'W',
    AXA_KEY_X                       = 'X',
    AXA_KEY_Y                       = 'Y',
    AXA_KEY_Z                       = 'Z',
    AXA_KEY_LEFT_BRACKET            = '[',
    AXA_KEY_BACKSLASH               = '\\',
    AXA_KEY_RIGHT_BRACKET           = ']',
    AXA_KEY_CARROT                  = '^',
    AXA_KEY_UNDERSCORE              = '_',
    AXA_KEY_GRAVE_ACCENT            = '`',
    AXA_KEY_LEFT_CURLY_BRACE        = '{',
    AXA_KEY_VERTICALBAR             = '|',
    AXA_KEY_RIGHT_CURLY_BRACE       = '}',
    AXA_KEY_TILDA                   = '~',
    AXA_KEY_DELETE                  = 0x7f,
    AXA_KEY_KEYPAD_0                = 0x80,
    AXA_KEY_KEYPAD_1                = 0x81,
    AXA_KEY_KEYPAD_2                = 0x82,
    AXA_KEY_KEYPAD_3                = 0x83,
    AXA_KEY_KEYPAD_4                = 0x84,
    AXA_KEY_KEYPAD_5                = 0x85,
    AXA_KEY_KEYPAD_6                = 0x86,
    AXA_KEY_KEYPAD_7                = 0x87,
    AXA_KEY_KEYPAD_8                = 0x88,
    AXA_KEY_KEYPAD_9                = 0x89,
    AXA_KEY_KEYPAD_SEPARATOR        = 0x8a,
    AXA_KEY_KEYPAD_FORWARD_SLASH    = 0x8b,
    AXA_KEY_KEYPAD_ASTERISK         = 0x8c,
    AXA_KEY_KEYPAD_PLUS             = 0x8d,
    AXA_KEY_KEYPAD_MINUS            = 0x8e,
    AXA_KEY_KEYPAD_ENTER            = 0x8f,
    AXA_KEY_UP                      = 0x90,
    AXA_KEY_DOWN                    = 0x91,
    AXA_KEY_LEFT                    = 0x92,
    AXA_KEY_RIGHT                   = 0x93,
    AXA_KEY_PAGE_UP                 = 0x94,
    AXA_KEY_PAGE_DOWN               = 0x95,
    AXA_KEY_HOME                    = 0x96,
    AXA_KEY_END                     = 0x97,
    AXA_KEY_INSERT                  = 0x98,
    AXA_KEY_F1                      = 0xa0,
    AXA_KEY_F2                      = 0xa2,
    AXA_KEY_F3                      = 0xa3,
    AXA_KEY_F4                      = 0xa4,
    AXA_KEY_F5                      = 0xa5,
    AXA_KEY_F6                      = 0xa6,
    AXA_KEY_F7                      = 0xa7,
    AXA_KEY_F8                      = 0xa8,
    AXA_KEY_F9                      = 0xa9,
    AXA_KEY_F10                     = 0xaa,
    AXA_KEY_F11                     = 0xab,
    AXA_KEY_F12                     = 0xac,
    AXA_KEY_LEFT_SHIFT              = 0xb0,
    AXA_KEY_RIGHT_SHIFT             = 0xb1,
    AXA_KEY_LEFT_CONTROL            = 0xb2,
    AXA_KEY_RIGHT_CONTROL           = 0xb3,
    AXA_KEY_LEFT_ALT                = 0xb4,
    AXA_KEY_RIGHT_ALT               = 0xb5,
    AXA_KEY_LEFT_SUPER              = 0xb6,
    AXA_KEY_RIGHT_SUPER             = 0xb7,
    AXA_KEY_MENU                    = 0xb8,
    AXA_KEY_ALTGR                   = 0xb9,
    AXA_KEY_NUM_LOCK                = 0xba,
    AXA_KEY_CAPS_LOCK               = 0xbb,
    AXA_KEY_SCROLL_LOCK             = 0xbc,
    AXA_KEY_LAST                    = 0x100 // 256
} axa_key;

typedef enum axa_button {
    AXA_MOUSE_BUTTON_1              = 0x01,
    AXA_MOUSE_BUTTON_2              = 0x02,
    AXA_MOUSE_BUTTON_3              = 0x03,
    AXA_MOUSE_BUTTON_4              = 0x04,
    AXA_MOUSE_BUTTON_5              = 0x05,
    AXA_MOUSE_BUTTON_6              = 0x05,
    AXA_MOUSE_BUTTON_7              = 0x07,
    AXA_MOUSE_BUTTON_LAST           = 0x08,
    AXA_MOUSE_BUTTON_LEFT           = AXA_MOUSE_BUTTON_1,
    AXA_MOUSE_BUTTON_MIDDLE         = AXA_MOUSE_BUTTON_2,
    AXA_MOUSE_BUTTON_RIGHT          = AXA_MOUSE_BUTTON_3,
} axa_button;

typedef enum axa_mod {
    AXA_MOD_SHIFT                   = 1U << 0,
    AXA_MOD_CONTROL                 = 1U << 1,
    AXA_MOD_ALT                     = 1U << 2,
    AXA_MOD_SUPER                   = 1U << 3,
    AXA_MOD_NUM_LOCK                = 1U << 4,
    AXA_MOD_CAPS_LOCK               = 1U << 5,
    AXA_MOD_LAST
} axa_mod;

typedef enum axa_event_type {
    AXA_EVENT_TYPE_NONE             = 0,
    AXA_EVENT_TYPE_QUIT,            // A quit has been requested
    AXA_EVENT_TYPE_WINDOWEXPOSE,    // A window was partially exposed or hidden
    AXA_EVENT_TYPE_WINDOWRESIZE,    // A window's size was changed
    AXA_EVENT_TYPE_WINDOWFOCUS,     // A window's focus was changed
    AXA_EVENT_TYPE_MOUSEBUTTON,     // A mouse button was pressed or released
    AXA_EVENT_TYPE_MOUSEENTER,      // The mouse entered the window space
    AXA_EVENT_TYPE_MOUSELEAVE,      // The mouse left the window space
    AXA_EVENT_TYPE_MOUSEMOTION,     // The mouse changed position
    AXA_EVENT_TYPE_MOUSESCROLL,     // The scroll wheel was moved
    AXA_EVENT_TYPE_KEY,             // A key was pressed or released
} axa_event_type;

typedef enum axa_window_flags {
    AXA_WINDOW_FLAG_DEFAULT         = 0,
    AXA_WINDOW_FLAG_CENTERED        = 1U << 0,
    AXA_WINDOW_FLAG_VISIBLE         = 1U << 1,
    AXA_WINDOW_FLAG_VSYNC           = 1U << 2,
    AXA_WINDOW_FLAG_FULLSCREEN      = 1U << 3,
} axa_window_flags;

typedef struct axa_window axa_window;

typedef struct axa_window_desc {
    char const     *title;
    int             x;
    int             y;
    int             width;
    int             height;
    unsigned        flags;
} axa_window_desc;

typedef struct axa_expose_event {
    axa_event_type  type;
    double          time;
    axa_window     *window;
    bool            visible;
} axa_expose_event;

typedef struct axa_focus_event {
    axa_event_type  type;
    double          time;
    axa_window     *window;
    int             focused;
} axa_focus_event;

typedef struct axa_resize_event {
    axa_event_type  type;
    double          time;
    axa_window     *window;
    int             width;
    int             height;
} axa_resize_event;

typedef struct axa_button_event {
    axa_event_type  type;
    double          time;
    axa_button      sym;
    unsigned        mods;
    int             pressed;
    int             x;
    int             y;
} axa_button_event;

typedef struct axa_motion_event {
    axa_event_type type;
    double          time;
    double          dx;
    double          dy;
} axa_motion_event;

typedef struct axa_scroll_event {
    axa_event_type type;
    double          time;
    double          dx;
    double          dy;
} axa_scroll_event;

typedef struct axa_key_event {
    axa_event_type type;
    double          time;
    axa_key        sym;
    unsigned        mods;
    int             pressed;
} axa_key_event;

typedef union axa_event {
    axa_event_type         type;
    axa_expose_event       expose;
    axa_focus_event        focus;
    axa_resize_event       resize;
    axa_button_event       button;
    axa_motion_event       motion;
    axa_scroll_event       scroll;
    axa_key_event          key;
} axa_event;

typedef bool (*axa_init_callback)(void);
typedef void (*axa_event_callback)(axa_event const *event);
typedef void (*axa_tick_callback)(double dt);
typedef void (*axa_quit_callback)(void);

typedef struct axa_desc {
    axa_window_desc        window;
    axa_init_callback      on_init;
    axa_event_callback     on_event;
    axa_tick_callback      on_tick;
    axa_quit_callback      on_quit;
} axa_desc;


axa_desc    axa_main                    (int argc, char **argv);
axa_window *axa_get_main_window         (void);
double      axa_get_time                (void);
char const *axa_event_type_string       (axa_event_type type);

#define     axa_get_pos(intarr)         axa_window_get_pos(axa_get_main_window(), intarr)
#define     axa_set_pos(x, y)           axa_window_set_pos(axa_get_main_window(), xptr, yptr)
#define     axa_get_size(intarr)        axa_window_get_size(axa_get_main_window(), intarr)
#define     axa_set_size(w, h)          axa_window_set_size(axa_get_main_window(), w, h)
#define     axa_get_visible()           axa_window_get_visible(axa_get_main_window())
#define     axa_set_visible(visible)    axa_window_set_visible(axa_get_main_window())
#define     axa_get_should_quit()       axa_window_get_should_close(axa_get_main_window())
#define     axa_set_should_quit(quit)   axa_window_set_should_close(axa_get_main_window(), quit)
#define     axa_set_title(title)        axa_window_set_title(axa_get_main_window(), title)

// Semi internal, use when AXA_CUSTOM_ENTRY is defined or if more control is needed
bool        axa_init                    (axa_desc const *desc);
void        axa_quit                    (void);
void        axa_poll_events             (axa_event_callback callback);

// Semi internal, use if multiple windows are needed
axa_window *axa_window_alloc            (axa_window_desc const *desc);
void        axa_window_free             (axa_window *window);
void        axa_window_get_pos          (axa_window const *window, int pos[]);
void        axa_window_set_pos          (axa_window *window, int x, int y);
void        axa_window_get_size         (axa_window const *window, int size[]);
void        axa_window_set_size         (axa_window *window, int w, int h);
bool        axa_window_get_visible      (axa_window const *window);
void        axa_window_set_visible      (axa_window *window, bool visible);
bool        axa_window_get_should_close (axa_window const *window);
void        axa_window_set_should_close (axa_window *window, bool should_close);
void        axa_window_set_title        (axa_window *window, char const *title);

/*************************************************************************************************************************************************************
**************************************************************************************************************************************************************
****                                                                                                                                                      ****
****                                                                                                                                                      ****
****                                                                    Implementation                                                                    ****
****                                                                                                                                                      ****
****                                                                                                                                                      ****
**************************************************************************************************************************************************************
*************************************************************************************************************************************************************/


#if defined(AXA_IMPL) || defined(AXIOM_IMPL)
#ifndef AXIOM_APP_C_
#define AXIOM_APP_C_

#if !defined(AXA_USE_X11) && !defined(AXA_USE_COCOA)
    #ifdef __linux__
        #ifndef AXA_USE_X11
            #define AXA_USE_X11
        #endif
    #endif
    #ifdef __APPLE__
        #ifndef AXA_USE_COCOA
            #define AXA_USE_COCOA
        #endif
    #endif
#endif

#if defined(AXA_USE_X11)
    #include <X11/Xlib.h>
    #include <sys/time.h> // clock_gettime, CLOCK_REALTIME, CLOCK_MONOTONIC
#elif defined(AXA_USE_COCOA)  && defined(__objc__)
    #import <Cocoa/Cocoa.h>
    #import <mach/mach_time.h>
#endif

#include <string.h> // memset
#include <stdio.h>  // fprintf
#include <stdlib.h> // calloc, free, exit

#define axa_log(...)           do { fprintf(stderr, "[axiom_app.h:%04d] ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); } while (0)
#define axa_assert(x, ...)     do { if ((x) == 0) { axa_log("Assert failed: %s", #x); exit(1); }} while (0)


struct axa_window {
#if defined(AXA_USE_X11)
    struct {
            Window wnd;
            Atom wm_del_wnd;
    } x11;
#elif defined(AXA_USE_COCOA) && defined(__objc__)
    struct {
            id wnd;
            id delegate;
    } cocoa;
#endif
    axa_window_desc desc;
    bool should_close;
};

static struct {
#if defined(AXA_USE_X11)
    struct {
            Display *dpy;
            Visual *vis;
            Window root_wnd;
            int screen;
            int depth;
    } x11;
#elif defined(AXA_USE_COCOA)  && defined(__objc__)
    struct {
            id app;
    } cocoa;
#endif
    axa_desc desc;
    axa_window *main_window;
    double start_time;
    bool should_quit;
} _axa = {0};


axa_window *axa_get_main_window(void) {
    return _axa.main_window;
}

double axa_get_time(void) {
    return axa__get_time();
}

char const *axa_event_type_string(axa_event_type type) {
#define SWITCH_ENUM_STR(x) case x: return #x
    switch (type) {
            SWITCH_ENUM_STR(AXA_EVENT_TYPE_NONE);
            SWITCH_ENUM_STR(AXA_EVENT_TYPE_QUIT);
            SWITCH_ENUM_STR(AXA_EVENT_TYPE_WINDOWEXPOSE);
            SWITCH_ENUM_STR(AXA_EVENT_TYPE_WINDOWRESIZE);
            SWITCH_ENUM_STR(AXA_EVENT_TYPE_WINDOWFOCUS);
            SWITCH_ENUM_STR(AXA_EVENT_TYPE_MOUSEBUTTON);
            SWITCH_ENUM_STR(AXA_EVENT_TYPE_MOUSEENTER);
            SWITCH_ENUM_STR(AXA_EVENT_TYPE_MOUSELEAVE);
            SWITCH_ENUM_STR(AXA_EVENT_TYPE_MOUSEMOTION);
            SWITCH_ENUM_STR(AXA_EVENT_TYPE_MOUSESCROLL);
            SWITCH_ENUM_STR(AXA_EVENT_TYPE_KEY);
            default: break;
    }
    return "Unknown event";
#undef SWITCH_ENUM_STR
}


#if defined(AXA_USE_X11)


bool axa__init(void) {
    _axa.x11.dpy = XOpenDisplay(NULL);
    if (!_axa.x11.dpy) {
        axa_log("Failed to connect to X server");
        return false;
    }

    _axa.x11.root_wnd = DefaultRootWindow(_axa.x11.dpy);
    _axa.x11.screen   = DefaultScreen(_axa.x11.dpy);
    _axa.x11.vis      = DefaultVisual(_axa.x11.dpy, _axa.x11.screen);
    _axa.x11.depth    = DefaultDepth(_axa.x11.dpy, _axa.x11.screen);
    _axa.start_time   = axa_get_time();
    return true;
}

void axa__quit(void) {
    if (_axa.x11.dpy) {
        XCloseDisplay(_axa.x11.dpy);
    }
}

bool axa_window__init(axa_window *window) {
    XSetWindowAttributes swa = {
        .background_pixel = WhitePixel(_axa.x11.dpy, _axa.x11.screen),
        .event_mask       = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
    };
    unsigned long swa_mask = CWEventMask | CWBorderPixel | CWBackPixel;

    window->x11.wnd = XCreateWindow(dpy, root_wnd, window->desc.x, window->desc.y, window->desc.width, window->desc.height, 0, depth, InputOutput, _axa.x11.vis, swa_mask, &swa);

    if (!window->x11.wnd) {
        axa_log("Failed to create x11 window");
        return false;
    }

    window->x11.wm_del_wnd = XInternAtom(_axa.x11.dpy, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(_axa.x11.dpy, window->x11.wnd, &window->x11.wm_del_wnd, 1);
    return true;
}

void axa_window__deinit(axa_window *window) {
    XDestroyWindow(_axa.x11.dpy, window->x11.wnd);
}

int axa__translate_key(int key) {
    (void)key;
    return 0;
}

// TODO
void axa__poll_events(axa_event_callback callback) {
    (void)window;
    (void)callback;
}

void axa_window__set_pos(axa_window *window, int x, int y) {
    if (!axa_window_get_visible(window)) {
        long unused;
        XSizeHints *hints = XAllocSizeHints();
        if (XGetWMNormalHints(_axa.x11.dpy, window->x11.wnd, hints, &unused)) {
            hints->flags |= PPosition;
            hints->x = hints->y = 0;
            XSetWMNormalHints(_axa.x11.dpy, window->x11.wnd, hints);
        }
        XFree(hints);
    }

    XMoveWindow(_axa.x11.dpy, window->x11.wnd, x, y);
    window->desc.x = x;
    window->desc.y = y;
}

void axa_window__set_size(axa_window *window, int w, int h) {
    XResizeWindow(_axa.x11.dpy, window->x11.wnd, w, h);
    XFlush(_axa.x11.dpy);
}

void axa_window__set_visible(axa_window *window, int visible) {
    if (visible) {
        XMapWindow(_axa.x11.dpy, window->x11.wnd);
        XMoveWindow(_axa.x11.dpy, window->x11.wnd, window->desc.x, window->desc.y);
    } else {
        XUnmapWindow(_axa.x11.dpy, window->x11.wnd);
    }
}

void axa_window__set_title(axa_window *window, char const *title) {
    XStoreName(_axa.x11.dpy, window->x11.wnd, title);
}

double axa__get_time(void) {
    struct timespec ts;
#ifdef CLOCK_MONOTONIC
    clock_gettime(CLOCK_MONOTONIC, &ts);
#else
    clock_gettime(CLOCK_REALTIME, &ts);
#endif
    // Convert to seconds
    double now = ts.tv_sec + (double)ts.tv_nsec * 1e-9;
    return now - _axa.start_time;
}


#elif defined(AXA_USE_COCOA)  && defined(__objc__)


@interface axa__app: NSObject <NSApplicationDelegate>
@end

@implementation axa__app

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
    axa_set_should_quit(true);
}

@end

@interface axa__delegate : NSObject <NSWindowDelegate> {
    axa_window *window_;
}
@end

@implementation axa__delegate

-(id)initWithWindow:(axa_window *)window {
    if ((self = [super init])) {
        window_ = window;
    }
    return self;
}

-(BOOL)acceptsFirstResponder {
    return YES;
}

-(BOOL)windowShouldClose:(NSWindow *)sender {
    axa_window_set_should_close(window_, 1);
    return NO;
}

-(void)windowWillClose:(id)sender {
    axa_window_set_should_close(window_, 1);
}

@end

bool axa__init(void) {
    @autoreleasepool {

    _axa.cocoa.app = [[axa__app alloc] init];
    [NSApplication sharedApplication];
    [NSApp setDelegate:_axa.cocoa.app];
    [NSApp finishLaunching];

    return true;

    }
}

void axa__quit(void) {
    @autoreleasepool {

    [NSApp terminate:nil];
    [_axa.cocoa.app release];
    _axa.cocoa.app = nil;

    } // autoreleasepool
}

void axa__poll_events(axa_event_callback callback) {
    @autoreleasepool {

    (void)callback; // TODO

    NSEvent* event = nil;
    do {
        event = [NSApp nextEventMatchingMask:NSEventMaskAny untilDate:nil inMode:NSDefaultRunLoopMode dequeue:YES];
        [NSApp sendEvent:event];
    } while (event != nil);

    } // autoreleasepool
}


bool axa_window__init(axa_window *window) {
    @autoreleasepool {

    NSRect frame = NSMakeRect(window->desc.x, window->desc.y, window->desc.width, window->desc.height);
    unsigned style = NSWindowStyleMaskClosable | NSWindowStyleMaskTitled | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable; // TODO: Custom window style

    window->cocoa.wnd = [[NSWindow alloc] initWithContentRect:frame styleMask:style backing:NSBackingStoreBuffered defer:NO];
    if (window->cocoa.wnd == nil) {
        axa_log("Failed to create cocoa window");
        return false;
    }

    window->cocoa.delegate = [[axa__delegate alloc] initWithWindow:window];
    if (window->cocoa.delegate == nil) {
        axa_log("Failed to create cocoa window delegate");
        return false;
    }

    [window->cocoa.wnd setDelegate:window->cocoa.delegate];
    [window->cocoa.wnd setBackgroundColor:[NSColor colorWithRed:1 green:1 blue:1 alpha:1]];

    if ((window->desc.flags >> AXA_WINDOW_FLAG_CENTERED) & 1U == 1) {
        [(NSWindow *)window->cocoa.wnd center];
    }

    return true;

    } // autoreleasepool
}

void axa_window__deinit(axa_window *window) {
    @autoreleasepool {

    if (window->cocoa.delegate != nil) {
        [window->cocoa.wnd setDelegate:nil];
        [window->cocoa.delegate release];
        window->cocoa.delegate = nil;
    }

    if (window->cocoa.wnd != nil) {
        [window->cocoa.wnd close];
        window->cocoa.wnd = nil;
    }

    } // autoreleasepool
}

void axa_window__set_pos(axa_window *window, int x, int y) {
    @autoreleasepool {

    NSScreen* screen        = [NSScreen mainScreen];
    CGSize frame            = [screen frame].size;
    NSRect visible_frame    = [screen visibleFrame];
    CGFloat menubar_height  = frame.height - visible_frame.size.height - visible_frame.origin.y;

    [window->cocoa.wnd setFrameTopLeftPoint:NSMakePoint(x, frame.height - menubar_height - y)];

    } // autoreleasepool
}

void axa_window__set_size(axa_window *window, int w, int h) {
    @autoreleasepool {

    NSRect contentRect    = [window->cocoa.wnd contentRectForFrameRect:[window->cocoa.wnd frame]];
    contentRect.origin.y += contentRect.size.height - h;
    contentRect.size      = NSMakeSize(w, h);
    [window->cocoa.wnd setFrame:[window->cocoa.wnd frameRectForContentRect:contentRect] display:YES];

    } // autoreleasepool
}

void axa_window__set_visible(axa_window *window, bool visible) {
    @autoreleasepool {

    if (visible == true) {
        [window->cocoa.wnd makeKeyAndOrderFront:nil];
    } else {
        [window->cocoa.wnd orderOut:nil];
    }

    } // autoreleasepool
}

void axa_window__set_title(axa_window *window, char const *title) {
    @autoreleasepool {

    if (window != NULL && window->cocoa.wnd != nil) {
        [window->cocoa.wnd setTitle:[NSString stringWithUTF8String:title]];
    }

    } // autoreleasepool
}

double axa__get_time(void) {
    static bool first = true;
    static double frequency = 0.0;
    if (first == true) {
        mach_timebase_info_data_t info;
        mach_timebase_info(&info);
        frequency = (double)info.numer / (double)info.denom * 1.0e-9;
        first = false;
    }
    double now = mach_absolute_time() * frequency;
    return now - _axa.start_time;
}


#endif // defined(__linux__) || (defined(AXA_USE_COCOA) && defined(__objc__))


bool axa__default_on_init(void) {
    return true;
}

void axa__default_on_event(axa_event const *e) {
    (void)e;
}

void axa__default_on_tick(double dt) {
    (void)dt;
}

void axa__default_on_quit(void) {
}

bool axa_init(axa_desc const *desc) {
    _axa.desc = *desc;

    if (_axa.desc.on_init == NULL)  { _axa.desc.on_init  = axa__default_on_init;  }
    if (_axa.desc.on_event == NULL) { _axa.desc.on_event = axa__default_on_event; }
    if (_axa.desc.on_tick == NULL)  { _axa.desc.on_tick  = axa__default_on_tick;  }
    if (_axa.desc.on_quit == NULL)  { _axa.desc.on_quit  = axa__default_on_quit;  }

    return axa__init();
}

void axa_quit(void) {
    axa_window_free(axa_get_main_window());
    axa__quit();
    memset(&_axa, 0, sizeof _axa);
}

axa_window *axa_window_alloc(axa_window_desc const *desc) {
    axa_window *window = calloc(1, sizeof *window);
    if (window == NULL) {
        axa_log("Failed to create window, out of memory");
        return NULL;
    }

    // Set defaults if needed
    window->desc.title  = desc->title ? desc->title : "Untitled";
    window->desc.x      = desc->x;
    window->desc.y      = desc->y;
    window->desc.width  = desc->width  ? desc->width  : 640;
    window->desc.height = desc->height ? desc->height : 480;
    window->desc.flags  = desc->flags != AXA_WINDOW_FLAG_DEFAULT ? desc->flags : AXA_WINDOW_FLAG_CENTERED | AXA_WINDOW_FLAG_CENTERED;

    if (axa_window__init(window) == false) {
        axa_window_free(window);
        return NULL;
    }

    axa_window_set_title(window, window->desc.title);
    axa_window_set_visible(window, true);
    return window;
}

void axa_window_free(axa_window *window) {
    axa_window__deinit(window);
    *window = (axa_window){0};
    free(window);
}

void axa_poll_events(axa_event_callback callback) {
    axa__poll_events(callback);
}

void axa_window_get_pos(axa_window const *window, int pos[2]) {
    axa_assert(window && pos, "Invalid parameter(s)");
    pos[0] = window->desc.x;
    pos[1] = window->desc.y;
}

void axa_window_set_pos(axa_window *window, int x, int y) {
    axa_assert(window, "Invalid parameter(s)");
    if (x < 0) { x = 0; }
    if (y < 0) { y = 0; }
    window->desc.x = x;
    window->desc.y = y;
    axa_window__set_pos(window, x, y);
}

void axa_window_get_size(axa_window const *window, int size[2]) {
    axa_assert(window, "Invalid parameter(s)");
    size[0] = window->desc.width;
    size[1] = window->desc.height;
}

void axa_window_set_size(axa_window *window, int w, int h) {
    axa_assert(window, "Invalid parameter(s)");
    if (w < 0) { w = 0; }
    if (h < 0) { h = 0; }
    window->desc.width  = w;
    window->desc.height = h;
    axa_window__set_size(window, w, h);
}

bool axa_window_get_visible(axa_window const *window) {
    axa_assert(window, "Invalid parameter(s)");
    return (window->desc.flags >> AXA_WINDOW_FLAG_VISIBLE) & 1U;
}

void axa_window_set_visible(axa_window *window, bool visible) {
    axa_assert(window, "Invalid parameter(s)");
    if (visible == true) {
        window->desc.flags |=  AXA_WINDOW_FLAG_VISIBLE;
    } else {
        window->desc.flags &= ~AXA_WINDOW_FLAG_VISIBLE;
    }
    axa_window__set_visible(window, visible);
}

bool axa_window_get_should_close(axa_window const *window) {
    axa_assert(window, "Invalid parameter(s)");
    return window->should_close;
}

void axa_window_set_should_close(axa_window *window, bool should_close) {
    axa_assert(window, "Invalid parameter(s)");
    window->should_close = should_close;
}

void axa_window_set_title(axa_window *window, char const *title) {
    axa_assert(window && title, "Invalid parameter(s)");
    axa_window__set_title(window, title);
    // window->desc.title = title; // ?
}


#ifndef AXA_CUSTOM_ENTRY


int main(int argc, char **argv) {
    axa_desc desc = axa_main(argc, argv);
    if (axa_init(&desc) == false) {
        axa_log("Error on initialization, exiting...");
        return -1;
    }

    _axa.main_window = axa_window_alloc(&desc.window);
    if (_axa.main_window == NULL) {
        axa_log("Error on initialization, exiting...");
        axa_quit();
        return -1;
    }

    if (_axa.desc.on_init() == NULL) {
        axa_log("Error on initialization, exiting...");
        axa_quit();
        return -1;
    }

    double last = axa_get_time();
    while (!axa_get_should_quit()) {
        // Update frame timings
        double now = axa_get_time();
        double dt = now - last;
        last = now;

        _axa.desc.on_tick(dt);
        axa_poll_events(_axa.desc.on_event);
    }

    _axa.desc.on_quit();
    axa_quit();
    return 0;
}

#endif // !AXA_CUSTOM_ENTRY
#endif // !AXIOM_APP_C_
#endif // AXA_IMPL || AXIOM_IMPL
#endif // !AXIOM_APP_H_


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
