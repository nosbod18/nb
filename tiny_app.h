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
} TAPP_Key;

typedef enum tapp_mouse_button {
        TAPP_MOUSE_BUTTON_1 = 0,
        TAPP_MOUSE_BUTTON_2,
        TAPP_MOUSE_BUTTON_3,
        TAPP_MOUSE_BUTTON_4,
        TAPP_MOUSE_BUTTON_5,
        TAPP_MOUSE_BUTTON_LAST,
        TAPP_MOUSE_BUTTON_LEFT          = TAPP_MOUSE_BUTTON_1,
        TAPP_MOUSE_BUTTON_MIDDLE        = TAPP_MOUSE_BUTTON_2,
        TAPP_MOUSE_BUTTON_RIGHT         = TAPP_MOUSE_BUTTON_3,
} tapp_mouse_button;

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
        TAPP_EVENT_TYPE_NONE = 0,
        TAPP_EVENT_TYPE_WINDOWEXPOSE,
        TAPP_EVENT_TYPE_WINDOWRESIZE,
        TAPP_EVENT_TYPE_WINDOWFOCUS,
        TAPP_EVENT_TYPE_MOUSEBUTTONDOWN,
        TAPP_EVENT_TYPE_MOUSEBUTTONUP,
        TAPP_EVENT_TYPE_MOUSEENTER,
        TAPP_EVENT_TYPE_MOUSELEAVE,
        TAPP_EVENT_TYPE_MOUSEMOTION,
        TAPP_EVENT_TYPE_MOUSESCROLL,
        TAPP_EVENT_TYPE_KEYDOWN,
        TAPP_EVENT_TYPE_KEYUP,
        TAPP_EVENT_TYPE_QUIT,
        TAPP_EVENT_TYPE_LAST
} tapp_event_type;

typedef union tapp_event {
        int                                               type;
        struct { int type, visible;                     } expose;
        struct { int type, focused;                     } focus;
        struct { int type, width, height;               } resize;
        struct { int type,       sym, mods, pressed;    } key;
        struct { int type, x, y, sym, mods, pressed;    } button;
        struct { int type, x, y, sym;                   } motion;
        struct { int type; double x, y;                 } scroll;
} tapp_event;

typedef void (*tapp_init_callback)(void);
typedef void (*tapp_event_callback)(tapp_event const *event);
typedef void (*tapp_update_callback)(float dt);
typedef void (*tapp_quit_callback)(void);

typedef struct tapp_desc {
        char const             *title;
        int                     width;
        int                     height;
        int                     fullscreen;
        int                     vsync;
        tapp_init_callback      on_init;
        tapp_event_callback     on_event;
        tapp_update_callback    on_update;
        tapp_quit_callback      on_quit;
} tapp_desc;


tapp_desc       tapp_main               (int argc, char **argv);
void            tapp_request_quit       (void);
float           tapp_aspect_ratio       (void);


/***********************************************************************************************************************************************************
************************************************************************************************************************************************************
****                                                                                                                                                    ****
****                                                                                                                                                    ****
****                                                                   Implementation                                                                   ****
****                                                                                                                                                    ****
****                                                                                                                                                    ****
************************************************************************************************************************************************************
***********************************************************************************************************************************************************/


#if defined(TINY_APP_IMPL) || defined(TINY_IMPL)
#ifndef __tiny_app_c__
#define __tiny_app_c__

#if defined(__linux__)
        #include <xcb/xcb.h>
#endif

static struct {
#if defined(__linux__)
        struct {
                xcb_connection_t        *con;
                xcb_screen_t            *screen;
                xcb_window_t             win;
                xcb_intern_atom_reply_t *wm_del_win;
        } xcb;
#endif // __linux__

        tapp_desc desc;
        int should_quit;
} _tapp = {0};


void tapp_request_quit(void) {
        _tapp.should_quit = 1;
}

float tapp_aspect_ratio(void) {
        return (float)_tapp.desc.width / (float)_tapp.desc.height;
}

void tapp__handle_quit_event(void) {
        if (!_tapp.desc.on_event)
                return;

        _tapp.desc.on_event(&(tapp_event){
                .type = TAPP_EVENT_TYPE_QUIT
        });
}

void tapp__handle_resize_event(int w, int h) {
        if (!_tapp.desc.on_event)
                return;

        _tapp.desc.on_event(&(tapp_event){
                .type = TAPP_EVENT_TYPE_WINDOWRESIZE,
                .resize = { .width = w, .height = h },
        });

        _tapp.desc.width  = w;
        _tapp.desc.height = h;
}

void tapp__handle_button_event(int sym, int x, int y, int pressed) {
        if (!_tapp.desc.on_event)
                return;

        _tapp.desc.on_event(&(tapp_event){
                .type = pressed ? TAPP_EVENT_TYPE_MOUSEBUTTONDOWN : TAPP_EVENT_TYPE_MOUSEBUTTONUP,
                .button = { .sym = sym, .pressed = pressed },
        });
}

void tapp__handle_key_event(int sym, int pressed) {
        if (!_tapp.desc.on_event)
                return;

        _tapp.desc.on_event(&(tapp_event){
                .type = pressed ? TAPP_EVENT_TYPE_KEYDOWN : TAPP_EVENT_TYPE_KEYUP,
                .key = { .sym = sym, .pressed = pressed },
        });
}

//==============================================================
// Linux

#if defined(__linux__)

int tapp__window_create(tapp_desc const *desc) {
        static int first = 1;

        if (first) {
                int screenp = 0;
                _tapp.xcb.con = xcb_connect(NULL, &screenp);

                if (!_tapp.xcb.con)
                        return 0;

                xcb_setup_t const *setup = xcb_get_setup(_tapp.xcb.con);
                xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);

                while (screenp-- > 0)
                        xcb_screen_next(&iter);

                _tapp.xcb.screen = iter.data;
                first = 0;
        }

        unsigned mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
        unsigned list[] = {
                screen->black_pixel,
                XCB_EVENT_MASK_KEY_RELEASE
                        | XCB_EVENT_MASK_KEY_PRESS
                        | XCB_EVENT_MASK_EXPOSURE
                        | XCB_EVENT_MASK_STRUCTURE_NOTIFY
                        | XCB_EVENT_MASK_POINTER_MOTION
                        | XCB_EVENT_MASK_BUTTON_PRESS
                        | XCB_EVENT_MASK_BUTTON_RELEASE
        };

        int x = desc->x;
        int y = desc->y;
        int w = desc->w ? desc->w : 640;
        int x = desc->x ? desc->w : 480;

        _tapp.xcb.win = xcb_generate_id(con);
        xcb_create_window(con, XCB_COPY_FROM_PARENT, _tapp.xcb.win, _tapp.xcb.screen->root, x, y, w, h, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, mask, list);

        xcb_intern_atom_cookie_t cookie  = xcb_intern_atom(_tapp.xcb.con, 1, 12, "WM_PROTOCOLS");
        xcb_intern_atom_reply_t *reply   = xcb_intern_atom_reply(_tapp.xcb.con, cookie, 0);
        xcb_intern_atom_cookie_t cookie2 = xcb_intern_atom(_tapp.xcb.con, 0, 16, "WM_DELETE_WINDOW");

        _tapp.xcb.wm_del_win = xcb_intern_atom_reply(_tapp.xcb.con, cookie2, 0);

        xcb_change_property(_tapp.xcb.con, XCB_PROP_MODE_REPLACE, win, reply->atom, 4, 32, 1, &wm_del_win->atom);
        free(reply);
        xcb_map_window(_tapp.xcb.con, _tapp.xcb.win);
        xcb_flush(_tapp.xcb.con);
        return 1;
}

void tapp__delete_window(void) {
        xcb_destroy_window(_tapp.xcb.con, _tapp.xcb.win);
        xcb_disconnect(_tapp.xcb.con);
        free(_tapp.xcb.wm_del_win);
}

int tapp__translate_key(int key) {
        return 0; // TODO
}

void tapp__pump_events(void) {
        static int mousex = 0;
        static int mousey = 0;

        xcb_generic_event_t* event = NULL;
        while ((event = xcb_poll_for_event(_tapp.xcb.con))) {
                int type = event->response_type & 0x7f;

                switch (type) {
                        case XCB_CLIENT_MESSAGE:
                                if (((xcb_client_message_event_t *)event)->data.data32[0] != _tapp.xcb.wm_del_win->atom)
                                        break; // Fall through otherwise
                        case XCB_DESTROY_NOTIFY: {
                                tapp__handle_quit_event();
                        } break;
                        case XCB_CONFIGURE_NOTIFY: {
                                xcb_configure_notify_event_t const *cfg = (xcb_configure_notify_event_t const *)event;
                                if (cfg->width != _tapp.desc.width || cfg->height != _tapp.desc.height)
                                        tapp__handle_resize_event(cfg->width, cfg->height);
                        } break;
                        case XCB_MOTION_NOTIFY: {
                                xcb_motion_notify_event_t const *motion = (xcb_motion_notify_event_t const *)event;
                                mousex = (int)motion->event_x;
                                mousey = (int)motion->event_y;
                                tapp__handle_motion_event(mousex, mousey);
                        } break;
                        case XCB_BUTTON_PRESS:
                        case XCB_BUTTON_RELEASE: {
                                xcb_button_press_event_t const *button = (xcb_button_press_event_t const *)event;
                                if (button->detail == XCB_BUTTON_INDEX_1)
                                        tapp__handle_button_event(TAPP_MOUSE_BUTTON_1, mousex, mousey, type == XCB_BUTTON_PRESS);
                                if (button->detail == XCB_BUTTON_INDEX_2)
                                        tapp__handle_button_event(TAPP_MOUSE_BUTTON_2, mousex, mousey, type == XCB_BUTTON_PRESS);
                                if (button->detail == XCB_BUTTON_INDEX_3)
                                        tapp__handle_button_event(TAPP_MOUSE_BUTTON_3, mousex, mousey, type == XCB_BUTTON_PRESS);
                        } break;
                        case XCB_KEY_PRESS:
                        case XCB_KEY_RELEASE: {
                                xcb_key_release_event_t const *key = (xcb_key_release_event_t const *)event;
                                int sym = tapp__translate_key(key->detail);
                                tapp__handle_key_event(sym, type == XCB_KEY_PRESS);
                        } break;
                }
                free(event);
        }
}

#endif // __linux__

//==============================================================
// Entry point

int tapp__init(tapp_desc const *desc) {
        _tapp.on_init     = desc->on_init;
        _tapp.on_event    = desc->on_event;
        _tapp.on_update   = desc->on_update;
        _tapp.on_quit     = desc->on_quit;
        return tapp__window_create(desc);
}

void tapp__quit(void) {
        tapp__delete_window();
}

int main(int argc, char **argv) {
        tapp_desc desc = tapp_main(argc, argv);

        if (!tapp__init(&desc))
                return -1;

        if (_tapp.on_init && !_tapp.on_init())
                return -1;

        // TODO: Update dt
        float dt = 0.0f;
        while (tapp__running()) {
                tapp__pump_events()

                if (_tapp.on_update)
                        _tapp.on_update(dt);
        }

        if (_tapp.on_quit)
                _tapp.on_quit();

        tapp__quit();
        return 0;
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
