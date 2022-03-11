#ifndef __tiny_app_h__
#define __tiny_app_h__

#include <stdbool.h>

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
        TAPP_KEY_LAST                   = 0x100
} tapp_key;

typedef enum tapp_mouse_button {
        TAPP_MOUSE_BUTTON_1 = 0,
        TAPP_MOUSE_BUTTON_2,
        TAPP_MOUSE_BUTTON_3,
        TAPP_MOUSE_BUTTON_4,
        TAPP_MOUSE_BUTTON_5,
        tapp_mouse_button_LAST,
        TAPP_MOUSE_BUTTON_LEFT          = TAPP_MOUSE_BUTTON_1,
        TAPP_MOUSE_BUTTON_MIDDLE        = TAPP_MOUSE_BUTTON_2,
        TAPP_MOUSE_BUTTON_RIGHT         = TAPP_MOUSE_BUTTON_3,
} tapp_mouse_button;

typedef enum tapp_mod {
        TAPP_MOD_SHIFT     = 1 << 0,
        TAPP_MOD_CONTROL   = 1 << 1,
        TAPP_MOD_ALT       = 1 << 2,
        TAPP_MOD_SUPER     = 1 << 3,
        TAPP_MOD_NUM_LOCK  = 1 << 4,
        TAPP_MOD_CAPS_LOCK = 1 << 5,
        TAPP_MOD_LAST,
} tapp_mod;

typedef enum tapp_event_type {
        TAPP_NONE = 0,
        TAPP_KEYUP,
        TAPP_KEYDOWN,
        TAPP_MOUSEBUTTONDOWN,
        TAPP_MOUSEBUTTONUP,
        TAPP_MOUSEENTER,
        TAPP_MOUSELEAVE,
        TAPP_MOUSEMOTION,
        TAPP_MOUSESCROLL,
        TAPP_WINDOWVISIBLE,
        TAPP_WINDOWRESIZE,
        TAPP_WINDOWFOCUS,
        TAPP_QUITREQUEST,
        TAPP_LAST
} tapp_event_type;

typedef struct tapp_event {
        tapp_event_type type;
        union {
                struct { int dummy;             } nop;
                struct { bool focused;          } focus;
                struct { int width, height;     } resize;
                struct { int sym, mods;         } key;
                struct { int x, y, button, mods;} mouse;
                struct { int x, y, buttons;     } motion;
                struct { double x, y;           } scroll;
        };
} tapp_event;

typedef void (*tapp_init_callback)(void);
typedef bool (*tapp_event_callback)(tapp_event event);
typedef void (*tapp_update_callback)(float dt);
typedef void (*tapp_quit_callback)(void);

typedef struct tapp_desc {
        struct {
                char const *title;
                int  width;
                int  height;
                bool fullscreen;
                bool vsync;
        } window;

        struct {
                struct { int major, minor; } version;
        } context;

        tapp_init_callback     on_init;
        tapp_event_callback    on_event;
        tapp_update_callback   on_update;
        tapp_quit_callback     on_quit;
} tapp_desc;


tapp_desc       tapp_main               (int argc, char **argv);
void            tapp_request_quit       (void);
float           tapp_aspect_ratio       (void);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                                                                                    ////
////                                                                                                                                                    ////
////                                                                   Implementation                                                                   ////
////                                                                                                                                                    ////
////                                                                                                                                                    ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#if defined(TAPP_IMPLEMENTATION) || defined(TINY_IMPLEMENTATION)
#ifndef __tiny_app_c__
#define __tiny_app_c__

#include <assert.h>

static struct {
        tapp_init_callback on_init;
        tapp_event_callback on_event;
        tapp_update_callback on_update;
        tapp_quit_callback on_quit;
        bool should_quit;
        bool will_quit;
} TAPP = {0};


//==============================================================
// General

bool tapp__init(tapp_desc const *desc) {
        TAPP.on_init     = desc->on_init;
        TAPP.on_event    = desc->on_event;
        TAPP.on_update   = desc->on_update;
        TAPP.on_quit     = desc->on_quit;
        return true;
}

//==============================================================
// Linux

#if defined(__linux__)

int main(int argc, char **argv) {
        tapp_desc desc = tapp_main(argc, argv);

        if (!tapp__init(&desc) || !tapp__window_create_xcb(&desc) {
                return -1;
        }

        TAPP.on_init();

        while (!TAPP.will_quit) {
                while (1) {
                        if (!TAPP.on_event(tapp__translate_event_xcb(&event))) {
                                TAPP.will_quit = true;
                        }
                }

                TAPP.on_update(dt);
        }

        TAPP.on_quit();

        tapp__window_delete_xcb();
        tapp__quit();
        return 0;
}

#endif // __linux__

#endif // !__tiny_app_c__
#endif // TAPP_IMPLEMENTATION || TINY_IMPLEMENTATION
#endif // !__tiny_app_h__
