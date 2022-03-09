#ifndef __tiny_app_h__
#define __tiny_app_h__

#include <stdbool.h>

typedef enum tapp_Key {
        tapp_Key_Invalid                = 0x00,
        tapp_Key_Backspace              = 0x08,
        tapp_Key_Tab                    = 0x09,
        tapp_Key_Escape                 = 0x1b,
        tapp_Key_Space                  = ' ',
        tapp_Key_Bang                   = '!',
        tapp_Key_Quote                  = '\"',
        tapp_Key_Pound                  = '#',
        tapp_Key_Dollar                 = '$',
        tapp_Key_Percent                = '%',
        tapp_Key_Ampersan               = '&',
        tapp_Key_Apostrophe             = '\'',
        tapp_Key_LeftParentheses        = '(',
        tapp_Key_RightParentheses       = ')',
        tapp_Key_Asterisk               = '*',
        tapp_Key_Plus                   = '+',
        tapp_Key_Comma                  = ',',
        tapp_Key_Minus                  = '-',
        tapp_Key_Period                 = '.',
        tapp_Key_ForswardSlash           = '/',
        tapp_Key_0                      = '0',
        tapp_Key_1                      = '1',
        tapp_Key_2                      = '2',
        tapp_Key_3                      = '3',
        tapp_Key_4                      = '4',
        tapp_Key_5                      = '5',
        tapp_Key_6                      = '6',
        tapp_Key_7                      = '7',
        tapp_Key_8                      = '8',
        tapp_Key_9                      = '9',
        tapp_Key_Colon                  = ':',
        tapp_Key_SemiColon              = ';',
        tapp_Key_LeftAngleBracket       = '<',
        tapp_Key_Equals                 = '=',
        tapp_Key_RightAngleBracket      = '>',
        tapp_Key_QuestionMark           = '?',
        tapp_Key_At                     = '@',
        tapp_Key_A                      = 'A',
        tapp_Key_B                      = 'B',
        tapp_Key_C                      = 'C',
        tapp_Key_D                      = 'D',
        tapp_Key_E                      = 'E',
        tapp_Key_F                      = 'F',
        tapp_Key_G                      = 'G',
        tapp_Key_H                      = 'H',
        tapp_Key_I                      = 'I',
        tapp_Key_J                      = 'J',
        tapp_Key_K                      = 'K',
        tapp_Key_L                      = 'L',
        tapp_Key_M                      = 'M',
        tapp_Key_N                      = 'N',
        tapp_Key_O                      = 'O',
        tapp_Key_P                      = 'P',
        tapp_Key_Q                      = 'Q',
        tapp_Key_R                      = 'R',
        tapp_Key_S                      = 'S',
        tapp_Key_T                      = 'T',
        tapp_Key_U                      = 'U',
        tapp_Key_V                      = 'V',
        tapp_Key_W                      = 'W',
        tapp_Key_X                      = 'X',
        tapp_Key_Y                      = 'Y',
        tapp_Key_Z                      = 'Z',
        tapp_Key_LeftBracket            = '[',
        tapp_Key_Backslash              = '\\',
        tapp_Key_RightBracket           = ']',
        tapp_Key_Carrot                 = '^',
        tapp_Key_Underscore             = '_',
        tapp_Key_GraveAccent            = '`',
        tapp_Key_LeftCurlyBrace         = '{',
        tapp_Key_VerticalBar            = '|',
        tapp_Key_RightCurlyBrace        = '}',
        tapp_Key_Tilda                  = '~',
        tapp_Key_Delete                 = 0x7f,
        tapp_Key_Keypad_0               = 0x80,
        tapp_Key_Keypad_1               = 0x81,
        tapp_Key_Keypad_2               = 0x82,
        tapp_Key_Keypad_3               = 0x83,
        tapp_Key_Keypad_4               = 0x84,
        tapp_Key_Keypad_5               = 0x85,
        tapp_Key_Keypad_6               = 0x86,
        tapp_Key_Keypad_7               = 0x87,
        tapp_Key_Keypad_8               = 0x88,
        tapp_Key_Keypad_9               = 0x89,
        tapp_Key_Keypad_Separator       = 0x8a,
        tapp_Key_Keypad_ForswardSlash    = 0x8b,
        tapp_Key_Keypad_Asterisk        = 0x8c,
        tapp_Key_Keypad_Plus            = 0x8d,
        tapp_Key_Keypad_Minus           = 0x8e,
        tapp_Key_Keypad_Enter           = 0x8f,
        tapp_Key_Up                     = 0x90,
        tapp_Key_Down                   = 0x91,
        tapp_Key_Left                   = 0x92,
        tapp_Key_Right                  = 0x93,
        tapp_Key_PageUp                 = 0x94,
        tapp_Key_PageDown               = 0x95,
        tapp_Key_Home                   = 0x96,
        tapp_Key_End                    = 0x97,
        tapp_Key_Insert                 = 0x98,
        tapp_Key_F1                     = 0xa0,
        tapp_Key_F2                     = 0xa2,
        tapp_Key_F3                     = 0xa3,
        tapp_Key_F4                     = 0xa4,
        tapp_Key_F5                     = 0xa5,
        tapp_Key_F6                     = 0xa6,
        tapp_Key_F7                     = 0xa7,
        tapp_Key_F8                     = 0xa8,
        tapp_Key_F9                     = 0xa9,
        tapp_Key_F10                    = 0xaa,
        tapp_Key_F11                    = 0xab,
        tapp_Key_F12                    = 0xac,
        tapp_Key_LeftShift              = 0xb0,
        tapp_Key_RightShift             = 0xb1,
        tapp_Key_LeftControl            = 0xb2,
        tapp_Key_RightControl           = 0xb3,
        tapp_Key_LeftAlt                = 0xb4,
        tapp_Key_RightAlt               = 0xb5,
        tapp_Key_LeftSuper              = 0xb6,
        tapp_Key_RightSuper             = 0xb7,
        tapp_Key_Menu                   = 0xb8,
        tapp_Key_AltGR                  = 0xb9,
        tapp_Key_NumLock                = 0xba,
        tapp_Key_CapsLock               = 0xbb,
        tapp_Key_ScrollLock             = 0xbc,
        tapp_Key_COUNT                  = 0x100
} tapp_Key;

typedef enum tapp_Mouse {
        tapp_Mouse_Left                 = 0,
        tapp_Mouse_Middle               = 1,
        tapp_Mouse_Right                = 2,
        tapp_Mouse_COUNT,
} tapp_Mouse;

typedef enum tapp_Mod {
        tapp_Mod_Shift                  = 1 << 0,
        tapp_Mod_Control                = 1 << 1,
        tapp_Mod_Alt                    = 1 << 2,
        tapp_Mod_Super                  = 1 << 3,
        tapp_Mod_AltGR                  = 1 << 4,
        tapp_Mod_NumLock                = 1 << 5,
        tapp_Mod_CapsLock               = 1 << 6,
        tapp_Mod_COUNT,
} tapp_Mod;

typedef enum tapp_EventType {
        tapp_EventType_None = 0,
        tapp_EventType_Quit,
        tapp_EventType_WindowShown,
        tapp_EventType_WindowHidden,
        tapp_EventType_WindowResized,
        tapp_EventType_WindowFocused,
        tapp_EventType_WindowUnfocused,
        tapp_EventType_KeyPress,
        tapp_EventType_KeyRelease,
        tapp_EventType_MousePress,
        tapp_EventType_MouseRelease,
        tapp_EventType_MouseEnter,
        tapp_EventType_MouseLeave,
        tapp_EventType_MouseMotion,
        tapp_EventType_MouseScroll,
        tapp_EventType_COUNT
} tapp_EventType;

typedef struct tapp_Event {
        tapp_EventType type;
        union {
                struct { int dummy;             } none;
                struct { int width, height;     } resize;
                struct { int sym, mods;         } key;
                struct { int x, y, button, mods;} mouse;
                struct { int x, y, buttons;     } motion;
                struct { double x, y;           } scroll;
        };
} tapp_Event;

typedef struct tapp_AppDesc {
        struct {
                struct { int major, minor; } version;
        } context;

        struct {
                char const *title;
                int  width;
                int  height;
                bool fullscreen;
                bool vsync;
        } window;

        void (*onInit)(void);
        bool (*onEvent)(tapp_Event event);
        void (*onUpdate)(float dt);
        void (*onQuit)(void);
} tapp_AppDesc;


tapp_AppDesc    tapp_Main               (int argc, char **argv);
float           tapp_GetAspectRatio     (void);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                                                                                    ////
////                                                                                                                                                    ////
////                                                                   Implementation                                                                   ////
////                                                                                                                                                    ////
////                                                                                                                                                    ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef tapp_IMPLEMENTATION
#ifndef __tiny_app_c__
#define __tiny_app_c__

#include <assert.h>

#if defined(__linux__)
        #include <X11/Xlib.h>
        #include <X11/Xutil.h>
        #include <X11/XKBlib.h>
        #include <X11/Xresource.h>
#endif // __linux__

static struct {
#if defined(__linux__)
        struct {
                struct {
                        Atom    wmDeleteWindow;
                        Atom    netWmPing;
                } atoms;

                Display        *display;
                Visual         *visual;
                Colormap        colormap;
                Window          window;
                XIM             im;
                XIC             ic;
                int             screen;
                int             depth;
        } x11;

        struct {
                GLXFBConfig     fbconfig;
                GLXWindow       surface;
                GLXContext      context;
                int             visualId;
        } glx;
#endif // __linux__


        struct {
                struct { int major, minor; } version;
        } gl;

        bool quitRequested;
} TAPP = {0};


//==============================================================
// General

bool tapp__Init(tapp_AppDesc const *desc) {
        TAPP.onInit     = desc->onInit;
        TAPP.onEvent    = desc->onEvent;
        TAPP.onUpdate   = desc->onUpdate;
        TAPP.onQuit     = desc->onQuit;

        return true;
}

//==============================================================
// Linux

#if defined(__linux__)

static void tapp_deleteWindowX11(void) {
        if (TAPP.x11.window) {
                XUnmapWindow(TAPP.x11.display, TAPP.x11.window);
                XDestroyWindow(TAPP.x11.display, TAPP.x11.window);
                TAPP.x11.window = 0;
        }

        if (TAPP.x11.colormap) {
                XFreeColormap(TAPP.x11.display, TAPP.x11.colormap);
                TAPP.x11.colormap = 0;
        }
        XFlush(TAPP.x11.display);
}

static bool tapp_initWindowX11(tapp_AppDesc const *desc, Visual *vi, int depth) {
        const uint32_t swamask = CWBorderPixel | CWColormap | CWEventMask;
        XSetWindowAttributes swa = {
                .colormap = TAPP.x11.colormap;
                .border_pixel = 0;
                .event_mask = StructureNotifyMask
                                | KeyPressMask
                                | KeyReleaseMask
                                | PointerMotionMask
                                | ButtonPressMask
                                | ButtonReleaseMask
                                | ExposureMask
                                | FocusChangeMask
                                | VisibilityChangeMask
                                | EnterWindowMask
                                | LeaveWindowMask
                                | PropertyChangeMask;
        };

        int dpyWidth    = DisplayWidth(TAPP.x11.display, TAPP.x11.screen);
        int dpyHeight   = DisplayHeight(TAPP.x11.display, TAPP.x11.screen);
        int width       = TAPP.width  ? TAPP.width  : tapp_Defaults_WindowWidth;
        int height      = TAPP.height ? TAPP.height : tapp_Defaults_WindowHeight;
        int xpos        = (dpyWidth  - width)  / 2;
        int ypos        = (dpyHeight - height) / 2;

        TAPP_x11_grab_error_handler();
        TAPP.x11.window = XCreateWindow(TAPP.x11.display, TAPP.x11.root, xpos, ypos, width, height, 0, depth, InputOutput, visual, swamask, &swa);
        TAPP_x11_release_error_handler();

        if (!TAPP.x11.window) {
                tapp_fail("X11: Failed to create window");
        }

        Atom protocols[] = {
            TAPP.x11.atoms.wmDeleteWindow,
        };
        XSetWMProtocols(TAPP.x11.display, TAPP.x11.window, protocols, 1);

        XSizeHints* hints = XAllocSizeHints();
        hints->flags = (PWinGravity | PPosition | PSize);
        hints->win_gravity = StaticGravity;
        hints->x = xpos;
        hints->y = ypos;
        hints->width = width;
        hints->height = height;
        XSetWMNormalHints(TAPP.x11.display, TAPP.x11.window, hints);
        XFree(hints);

        Xutf8SetWMProperties(TAPP.x11.display, TAPP.x11.window, TAPP.title, TAPP.title, NULL, 0, NULL, NULL, NULL);
        XChangeProperty(TAPP.x11.display, TAPP.x11.window, TAPP.x11.netWmName, TAPP.x11.utf8String, 8, PropModeReplace, (unsigned char *)TAPP.title, strlen(TAPP.title));
        XChangeProperty(TAPP.x11.display, TAPP.x11.window, TAPP.x11.netWmIconName, TAPP.x11.utf8String, 8, PropModeReplace, (unsigned char *)TAPP.title, strlen(TAPP.title));
        XFlush(TAPP.x11.display);

        XWindowAttributes attribs;
        XGetWindowAttributes(TAPP.x11.display, TAPP.x11.window, &attribs);
        TAPP.width  = attribs.width;
        TAPP.height = attribs.height;
        return true;
}

void tapp_deleteContextGLX(void) {
        // Nothing
}

bool tapp_createContextGLX(tapp_AppDesc const *desc) {
        GLXFBConfig native = TAPP_glx_choosefbconfig();
        if (!native) {
                tapp_fail("GLX: Failed to find a suitable GLXFBConfig (2)");
        }
        if (!(TAPP.glx.ARB_create_context && TAPP.glx.ARB_create_context_profile)) {
            tapp_fail("GLX: ARB_create_context and ARB_create_context_profile required");
        }
        TAPP_x11_grab_error_handler();
        const int attribs[] = {
            GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
            GLX_CONTEXT_MINOR_VERSION_ARB, 3,
            GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
            GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            0, 0
        };
        TAPP.glx.ctx = TAPP.glx.CreateContextAttribsARB(TAPP.x11.display, native, NULL, True, attribs);
        if (!TAPP.glx.ctx) {
            tapp_fail("GLX: failed to create GL context");
        }
        TAPP_x11_release_error_handler();
        TAPP.glx.window = TAPP.glx.CreateWindow(TAPP.x11.display, native, TAPP.x11.window, NULL);
        if (!TAPP.glx.window) {
            tapp_fail("GLX: failed to create window");
        }
        return true;
}

int main(int argc, char **argv) {
        tapp_AppDesc desc = tapp_Main(argc, argv);

        if (!tapp_init(&desc)
                || !tapp_createX11(&desc)
                || !tapp_createWindowX11(&desc)
                || !tapp_createContextGLX(&desc)
        {
                return 1;
        }

        TAPP.onInit();

        while (!TAPP.quitRequested) {
                int pending = XPending(TAPP.x11.display);
                while (pending--) {
                        XEvent event;
                        XNextEvent(TAPP.x11.display, &event);
                        if (!TAPP.OnEvent(tapp_createEventX11(&event))) {
                                TAPP.quitRequested = true;
                        }
                }

                TAPP.onUpdate(dt);
                tapp_swapBuffersGLX();
        }

        TAPP.onQuit();

        tapp_deleteWindowX11();
        tapp_uitX11();
        tapp_quit();
        return 0;
}

#endif // __linux__

#endif // !__tiny_app_c__
#endif // tapp_IMPLEMENTATION
#endif // !__tiny_app_h__

