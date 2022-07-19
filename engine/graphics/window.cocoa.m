#define GL_SILENCE_DEPRECATION
#include "window.h"
#import <Cocoa/Cocoa.h>
#import <OpenGL/gl3.h>

#import <stdlib.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
@end

@interface ContentView : NSOpenGLView <NSWindowDelegate> {
    NbWindow *m_window;
}
@end

struct NbWindow {
    NSWindow *window;
    ContentView *view;
    NbEventHandler *handler;
    bool closed;
};


static AppDelegate *gAppDelegate = nil;


static float transformYCoordinate(float y) {
    return CGDisplayBounds(CGMainDisplayID()).size.height - y - 1;
}

static void defaultEventHandler(NbWindow *window, NbEventType type, NbEventData const *data) {
    (void)window; (void)type; (void)data;
}

static int translateKeyCode(int keyCode) {
    return keyCode; // TODO
}

static int translateModifiers(int mods) {
    return mods; // TODO
}

static void postKeyEvent(NbWindow *window, NSEvent const *event, bool pressed) {
    @autoreleasepool {

    window->handler(window, pressed ? NbEventType_KeyDown : NbEventType_KeyUp, &(NbEventData){
        .key.key  = translateKeyCode([event keyCode]),
        .key.mods = translateModifiers([event modifierFlags])
    });

    } // autoreleasepool
}

static void postMouseEvent(NbWindow *window, NbEventType type, NSEvent const *event) {
    @autoreleasepool {

    window->handler(window, type, &(NbEventData){
        .mouse.button  = [event buttonNumber],
        .mouse.mods    = [event modifierFlags],
        .mouse.x       = [event locationInWindow].x,
        .mouse.y       = [window->view frame].size.height - [event locationInWindow].y
    });

    } // autoreleasepool
}


@implementation AppDelegate
-(void)applicationWillFinishLaunching:(NSNotification *)notification {
    id menubar = [[NSMenu new] autorelease];
    id appMenuItem = [[NSMenuItem new] autorelease];
    [menubar addItem:appMenuItem];
    [NSApp setMainMenu:menubar];

    id appMenu = [[NSMenu new] autorelease];
    id appName = [[NSProcessInfo processInfo] processName];
    id quitTitle = [@"Quit " stringByAppendingString:appName];
    id quitMenuItem = [[[NSMenuItem alloc] initWithTitle:quitTitle action:@selector(terminate:) keyEquivalent:@"q"] autorelease];
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

@implementation ContentView
- (id)initWithFrame:(NSRect)frame window:(NbWindow *)window {
    NSOpenGLPixelFormatAttribute attributes[] = {
        NSOpenGLPFAOpenGLProfile,   NSOpenGLProfileVersion4_1Core,
        NSOpenGLPFAMultisample,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAColorSize,       32,
        NSOpenGLPFADepthSize,       24,
        NSOpenGLPFAAlphaSize,        8,
        0
    };

    if ((self = [super initWithFrame:frame pixelFormat:[[[NSOpenGLPixelFormat alloc] initWithAttributes:attributes] autorelease]]))
        m_window = window;

    return self;
}

- (BOOL)acceptsFirstResponder {
    return YES;
}

-(BOOL)windowShouldClose:(NSNotification *)notification {
    m_window->closed = true;
    return NO;
}

-(void)windowDidResize:(NSNotification *)notification {
    NSRect frame = [m_window->view frame];
    m_window->handler(m_window, NbEventType_WindowResize, &(NbEventData){
        .resize.width = frame.size.width,
        .resize.height = frame.size.height,
    });
}

-(void)keyDown:(NSEvent *)event {
    postKeyEvent(m_window, event, true);
}

-(void)keyUp:(NSEvent *)event {
    postKeyEvent(m_window, event, false);
}

-(void)mouseDown:(NSEvent *)event {
    postMouseEvent(m_window, NbEventType_MouseDown, event);
}

-(void)mouseUp:(NSEvent *)event {
    postMouseEvent(m_window, NbEventType_MouseUp, event);
}

-(void)mouseDragged:(NSEvent *)event {
    postMouseEvent(m_window, NbEventType_MouseMotion, event);
}

-(void)rightMouseDown:(NSEvent *)event {
    postMouseEvent(m_window, NbEventType_MouseDown, event);
}

-(void)rightMouseUp:(NSEvent *)event {
    postMouseEvent(m_window, NbEventType_MouseUp, event);
}

-(void)rightMouseDragged:(NSEvent *)event {
    postMouseEvent(m_window, NbEventType_MouseMotion, event);
}

-(void)otherMouseDown:(NSEvent *)event {
    postMouseEvent(m_window, NbEventType_MouseDown, event);
}

-(void)otherMouseUp:(NSEvent *)event {
    postMouseEvent(m_window, NbEventType_MouseUp, event);
}

-(void)otherMouseDragged:(NSEvent *)event {
    postMouseEvent(m_window, NbEventType_MouseMotion, event);
}

-(void)mouseMoved:(NSEvent *)event {
    postMouseEvent(m_window, NbEventType_MouseMotion, event);
}

@end

bool nbInit(void) {
    @autoreleasepool {

    [NSApplication sharedApplication];
    gAppDelegate = [[AppDelegate alloc] init];
    [NSApp setDelegate:gAppDelegate];
    [NSApp finishLaunching];
    return true;

    } // autoreleasepool
}

void nbQuit(void) {
    @autoreleasepool {

    [NSApp terminate:nil];
    [gAppDelegate release];
    gAppDelegate = nil;

    } // autoreleasepool
}

NbWindow *nbWindowCreate(NbWindowDescriptor const *desc) {
    @autoreleasepool {

    NbWindowDescriptor actual = {
        .eventHandler   = desc->eventHandler ? desc->eventHandler : defaultEventHandler,
        .title          = desc->title  ? desc->title  : "Untitled",
        .width          = desc->width  ? desc->width  : 640,
        .height         = desc->height ? desc->height : 480,
        .fullscreen     = desc->fullscreen,
        .hidden         = desc->hidden
    };

    unsigned styleMask = NSWindowStyleMaskTitled  | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable;
    NSRect frame = NSMakeRect(0, 0, actual.width, actual.height);

    NbWindow *window = malloc(sizeof *window);

    window->window  = [[NSWindow alloc] initWithContentRect:frame styleMask:styleMask backing:NSBackingStoreBuffered defer:NO];
    window->view    = [[ContentView alloc] initWithFrame:frame window:window];
    window->handler = actual.eventHandler;
    window->closed  = false;

    [window->window setContentView:window->view];
    [window->window setDelegate:window->view];
    [window->window setAcceptsMouseMovedEvents:YES];
    [window->window setTitle:@(actual.title)];
    [window->window setRestorable:NO];

    [window->window center];
    [window->window makeFirstResponder:window->view];
    [window->window makeKeyAndOrderFront:nil];
    [window->window orderFront:nil];

    [[window->view openGLContext] makeCurrentContext];

    return window;

    } // autoreleasepool
}

void nbWindowDelete(NbWindow *window) {
    @autoreleasepool {

    [window->window setDelegate:nil];
    [window->view release];
    window->view = nil;

    [window->window close];
    window->window = nil;

    free(window);

    } // autoreleasepool
}

void nbWindowPollEvents(void) {
    @autoreleasepool {

    while (1) {
        NSEvent *event = [NSApp
            nextEventMatchingMask:NSEventMaskAny
                        untilDate:nil
                           inMode:NSDefaultRunLoopMode
                          dequeue:YES];
        if (!event)
            break;

        [NSApp sendEvent:event];
    }

    } // autoreleasepool
}

void nbWindowSwapBuffers(NbWindow const *window) {
    if (window)
        [[window->view openGLContext] flushBuffer];
}

void nbWindowGetSize(NbWindow const *window, int *width, int *height) {
    @autoreleasepool {

    if (window) {
        NSRect frame = [window->view frame];
        if (width)  *width = frame.size.width;
        if (height) *height = frame.size.height;
    } else {
        if (width)  *width = 0;
        if (height) *height = 0;
    }

    } // autoreleasepool
}

void nbWindowGetPosition(NbWindow const *window, int *x, int *y) {
    @autoreleasepool {

    if (window) {
        NSRect frame = [window->view frame];
        if (x) *x = frame.origin.x;
        if (y) *y = frame.origin.y;
    } else {
        if (x) *x = 0;
        if (y) *y = 0;
    }

    } // autoreleasepool
}

bool nbWindowIsClosed(NbWindow const *window) {
    @autoreleasepool {

    return window->closed;

    } // autoreleasepool
}

bool nbWindowIsVisible(NbWindow const *window) {
    @autoreleasepool {

    return [window->window isVisible];

    } // autoreleasepool
}

bool nbWindowIsFullscreen(NbWindow const *window) {
    @autoreleasepool {

    return [window->window isZoomed];

    } // autoreleasepool
}

void nbWindowSetSize(NbWindow *window, int width, int height) {
    @autoreleasepool {

    NSRect contentRect = [window->window contentRectForFrameRect:[window->window frame]];
    contentRect.origin.y += contentRect.size.height - height;
    contentRect.size = NSMakeSize(width, height);
    [window->window setFrame:[window->window frameRectForContentRect:contentRect] display:YES];

    } // autoreleasepool
}

void nbWindowSetPosition(NbWindow *window, int x, int y) {
    @autoreleasepool {

    NSRect contentRect = [window->view frame];
    NSRect dummyRect = NSMakeRect(x, transformYCoordinate(y + contentRect.size.height - 1), 0, 0);
    NSRect frameRect = [window->window frameRectForContentRect:dummyRect];
    [window->window setFrameOrigin:frameRect.origin];

    } // autoreleasepool
}

void nbWindowSetFullscreen(NbWindow *window, bool fullscreen) {
    @autoreleasepool {

    (void)window; (void)fullscreen;

    } // autoreleasepool
}

void nbWindowSetVisibile(NbWindow *window, bool visible) {
    @autoreleasepool {

    (void)window; (void)visible;

    } // autoreleasepool
}

void nbWindowSetClosed(NbWindow *window, bool closed) {
    @autoreleasepool {

    window->closed = closed;

    } // autoreleasepool
}

