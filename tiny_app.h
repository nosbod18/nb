#ifndef __tiny_app_h__
#define __tiny_app_h__

#include <stdint.h>
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
        tapp_Key_ForwardSlash           = '/',
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
        tapp_Key_Keypad_ForwardSlash    = 0x8b,
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
        tapp_Key_Last                   = 0x100
} tapp_Key;

typedef struct tapp_Event {
        tapp_EventType type;
        union {

        };
} tapp_Event;

typedef struct tapp_AppDesc {
        char const *title;
        int width;
        int height;
        void (*onInit)(void);
        bool (*onUpdate)(float dt);
        void (*onEvent)(void *userData, tapp_Event event);
        void (*onQuit)(void);
} tapp_AppDesc;


tapp_AppDesc    tapp_Main               (int argc, char **argv);

// ---- Input ------------------

bool            tapp_IsKeyDown          (int key);
bool            tapp_IsKeyPressed       (int key);
bool            tapp_IsKeyReleased      (int key);
bool            tapp_IsMouseDown        (int button);
bool            tapp_IsMousePressed     (int button);
bool            tapp_IsMouseReleased    (int button);

void            tapp_GetMousePosition   (float *x, float *y);
void            tapp_GetMouseScroll     (float *x, float *y);
void            tapp_GetMouseDelta      (float *x, float *y);

bool            tapp_IsMouseTrapped     (void);
bool            tapp_IsMouseHidden      (void);
void            tapp_SetMouseTrapped    (bool trapped);
void            tapp_SetMouseHidden     (bool hidden);


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

typedef struct tapp_Input {
        struct {
                uint64_t keys[4]; // tapp_Key_Last / 64
        } keyboard[2];

        struct {
                uint8_t buttons;
                float xposition, yposition;
                float xscroll, yscroll;
                bool isTrapped;
                bool isHidden;
        } mouse[2];
} tapp_Input;


static void    *tapp_CreateWindow       (char const *title, int width, int height);
static void     tapp_DeleteWindow       (void *window);
static void     tapp_ProcessEvents      (void *window);
static void     tapp_Present            (void const *window);


//==============================================================
// Linux

#if defined(__linux__)

int main(int argc, char **argv) {
        tapp_AppDesc desc = tapp_Main(argc, argv);

        XInitThreads();

        Display *display = XOpenDisplay(NULL);
        assert(display && "XOpenDisplay() failed");

        int screen = DefaultScreen(display);
        Window root = DefaultRootWindow(display);
        tapp__InitGLX();

        Visual *visual = NULL;
        int depth = 0;
        tapp__ChooseGLXVisual(&visual, &depth);
        tapp__CreateX11Window(desc->title, desc->width, desc->height, visual, depth);
        tapp__CreateGLXContext();
        tapp__ShowX11Window();

        if (desc->fullscreen) {
                tapp__SetX11WindowFullscreen(true);
        }

        tapp__SetGLXSwapInterval(desc->swapInterval);
        XFlush(display);

        while (tapp__ProcessX11Events(window)) {
                if (!desc.update(dt)) {
                        break;
                }

                tapp_Present(window);
        }

        tapp_DeleteWindow(window);
        return 0;
}


void *tapp_CreateWindow(char const *title, int width, int height) {
        Display *display  = XOpenDisplay(NULL);
        int screen        = DefaultScreen(display);
        Visual* visual    = DefaultVisual(display, screen);
        int depth         = DefaultDepth(display, screen);
        Colormap colormap = XCreateColormap(display, RootWindow(display, screen), visual, AllocNone);

        XSetWindowAttributes swa = {
                .colormap = colormap,
                .background_pixel = BlackPixel(display, screen),
                .border_pixel = 0,
                .event_mask = KeyPressMask | KeyReleaseMask | StructureNotifyMask | ExposureMask,
        };

        window = XCreateWindow(
                display,
                RootWindow(display, screen),
                0,
                0,
                desc.width,
                desc.height,
                0,
                depth,
                InputOutput,
                visual,
                CWBackPixel | CWBorderPixel | CWEventMask | CWColormap,
                &swa);

        XSelectInput(display, window, ExposureMask | KeyPressMask);
        XMapWindow(display, window);
        XFlush(display);

}

void tapp_DeleteWindow(void *window) {
        XUnmapWindow(display, window);
        XDestroyWindow(display, window);
        XFreeColormap(display, colormap);
        XFlush(display);
        XCloseDisplay(display);
}

#endif // __linux__

#endif // !__tiny_app_c__
#endif // tapp_IMPLEMENTATION
#endif // !__tiny_app_h__

