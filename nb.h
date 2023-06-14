/*
        ██╗███╗   ██╗████████╗███████╗██████╗ ███████╗ █████╗  ██████╗███████╗
        ██║████╗  ██║╚══██╔══╝██╔════╝██╔══██╗██╔════╝██╔══██╗██╔════╝██╔════╝
        ██║██╔██╗ ██║   ██║   █████╗  ██████╔╝█████╗  ███████║██║     █████╗  
        ██║██║╚██╗██║   ██║   ██╔══╝  ██╔══██╗██╔══╝  ██╔══██║██║     ██╔══╝  
        ██║██║ ╚████║   ██║   ███████╗██║  ██║██║     ██║  ██║╚██████╗███████╗
        ╚═╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝  ╚═╝ ╚═════╝╚══════╝
 */


#ifndef NB_NB_H
#define NB_NB_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>


//////////////////////////////////////////////////////////////////////////////
/// Constants

typedef enum {
    NB_ERROR_NONE,
    NB_ERROR_OUT_OF_MEM,
    NB_ERROR_INVALID_PARAMS,
} nb_error;

typedef enum {
    NB_INPUTSTATE_RELEASED,
    NB_INPUTSTATE_JUST_RELEASED,
    NB_INPUTSTATE_PRESSED,
    NB_INPUTSTATE_JUST_PRESSED,
} nb_input_state;

typedef enum {
    NB_KEY_BACKSPACE, NB_KEY_TAB, NB_KEY_ENTER, NB_KEY_ESCAPE,
    NB_KEY_UP = 128, NB_KEY_DOWN, NB_KEY_LEFT, NB_KEY_RIGHT,
    NB_KEY_SHIFT, NB_KEY_CTRL, NB_KEY_ALT, NB_KEY_SUPER,
    NB_KEY_COUNT
} nb_key;

typedef enum {
    NB_BUTTON_LEFT = 1, NB_BUTTON_RIGHT, NB_BUTTON_MIDDLE,
    NB_BUTTON_COUNT
} nb_button;

//////////////////////////////////////////////////////////////////////////////
/// Types

typedef struct {
    float x, y;
} nb_vec2;

typedef struct {
    float x, y, z;
} nb_vec3;

typedef struct {
    float x, y, z, w;
} nb_vec4;

typedef union {
    struct { uint8_t r, g, b, a; };
    uint32_t rgba;
} nb_color;

typedef struct {
    int x, y;
} nb_point;

typedef struct {
    int w, h;
} nb_size;

typedef struct {
    int x, y, w, h;
} nb_rect;

typedef struct {
    int x, y, r;
} nb_circle;

typedef struct {
    char const *path;
    uint8_t *data;
    int width, height, stride;
} nb_image;

typedef struct {
    void *window, *bitmap;
    char const *title;
    int x, y, width, height;
    bool closed, focused;

    struct {
        bool keys[NB_KEY_COUNT];
    } keyboard[2];
    struct {
        bool buttons[NB_BUTTON_COUNT];
        nb_point pos;
    } mouse[2];
} nb_context;

//////////////////////////////////////////////////////////////////////////////
/// Functions

bool            nb_context_init     (nb_context *ctx);
bool            nb_context_update   (nb_context *ctx);
void            nb_context_free     (nb_context *ctx);

nb_input_state  nb_key_state        (nb_context const *ctx, nb_key key);
nb_input_state  nb_button_state     (nb_context const *ctx, nb_button button);

bool            nb_image_init       (nb_image *img);
void            nb_image_free       (nb_image *img);

void            nb_screen_fill      (nb_context *ctx, nb_color color);
void            nb_point_draw       (nb_context *ctx, nb_point point, nb_color color);
void            nb_line_draw        (nb_context *ctx, nb_point point1, nb_point point2, nb_color color);
void            nb_rect_draw        (nb_context *ctx, nb_rect rect, nb_color color);
void            nb_rect_fill        (nb_context *ctx, nb_rect rect, nb_color color);
void            nb_circle_draw      (nb_context *ctx, nb_circle circle, nb_color color);
void            nb_circle_fill      (nb_context *ctx, nb_circle circle, nb_color color);
void            nb_image_draw       (nb_context *ctx, nb_image *img, nb_point pos);
void            nb_image_draw_ex    (nb_context *ctx, nb_image *img, nb_rect dst, nb_rect src, nb_color tint, float rotation);

nb_vec2         nb_vec2_add         (nb_vec2 a, nb_vec2 b);
nb_vec2         nb_vec2_sub         (nb_vec2 a, nb_vec2 b);
nb_vec2         nb_vec2_mul         (nb_vec2 a, nb_vec2 b);
nb_vec2         nb_vec2_adds        (nb_vec2 a, float b);
nb_vec2         nb_vec2_subs        (nb_vec2 a, float b);
nb_vec2         nb_vec2_muls        (nb_vec2 a, float b);
float           nb_vec2_dot         (nb_vec2 a, nb_vec2 b);
float           nb_vec2_mag2        (nb_vec2 a);
float           nb_vec2_mag         (nb_vec2 a);
nb_vec2         nb_vec2_norm        (nb_vec2 a);

nb_vec3         nb_vec3_add         (nb_vec3 a, nb_vec3 b);
nb_vec3         nb_vec3_sub         (nb_vec3 a, nb_vec3 b);
nb_vec3         nb_vec3_mul         (nb_vec3 a, nb_vec3 b);
nb_vec3         nb_vec3_adds        (nb_vec3 a, float b);
nb_vec3         nb_vec3_subs        (nb_vec3 a, float b);
nb_vec3         nb_vec3_muls        (nb_vec3 a, float b);
float           nb_vec3_dot         (nb_vec3 a, nb_vec3 b);
float           nb_vec3_mag2        (nb_vec3 a);
float           nb_vec3_mag         (nb_vec3 a);
nb_vec3         nb_vec3_norm        (nb_vec3 a);
nb_vec3         nb_vec3_cross       (nb_vec3 a, nb_vec3 b);

nb_vec4         nb_vec4_add         (nb_vec4 a, nb_vec4 b);
nb_vec4         nb_vec4_sub         (nb_vec4 a, nb_vec4 b);
nb_vec4         nb_vec4_mul         (nb_vec4 a, nb_vec4 b);
nb_vec4         nb_vec4_adds        (nb_vec4 a, float b);
nb_vec4         nb_vec4_subs        (nb_vec4 a, float b);
nb_vec4         nb_vec4_muls        (nb_vec4 a, float b);
float           nb_vec4_dot         (nb_vec4 a, nb_vec4 b);
float           nb_vec4_mag2        (nb_vec4 a);
float           nb_vec4_mag         (nb_vec4 a);
nb_vec4         nb_vec4_norm        (nb_vec4 a);


#endif // NB_NB_H

/*
        ██╗███╗   ███╗██████╗ ██╗     ███████╗███╗   ███╗███████╗███╗   ██╗████████╗ █████╗ ████████╗██╗ ██████╗ ███╗   ██╗
        ██║████╗ ████║██╔══██╗██║     ██╔════╝████╗ ████║██╔════╝████╗  ██║╚══██╔══╝██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║
        ██║██╔████╔██║██████╔╝██║     █████╗  ██╔████╔██║█████╗  ██╔██╗ ██║   ██║   ███████║   ██║   ██║██║   ██║██╔██╗ ██║
        ██║██║╚██╔╝██║██╔═══╝ ██║     ██╔══╝  ██║╚██╔╝██║██╔══╝  ██║╚██╗██║   ██║   ██╔══██║   ██║   ██║██║   ██║██║╚██╗██║
        ██║██║ ╚═╝ ██║██║     ███████╗███████╗██║ ╚═╝ ██║███████╗██║ ╚████║   ██║   ██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║
        ╚═╝╚═╝     ╚═╝╚═╝     ╚══════╝╚══════╝╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝
*/


#ifdef NB_IMPL
#ifndef NB_NB_C
#define NB_NB_C


bool nb_context_init(nb_context *ctx) {
    return 0;
}

bool nb_context_update(nb_context *ctx) {
    return 0;
}

void nb_context_free(nb_context *ctx) {
    return;
}

bool nb_image_init(nb_image *img) {
    return 0;
}

void nb_image_free(nb_image *img) {
    return;
}

void nb_screen_fill(nb_context *ctx, nb_color color) {
    return;
}

void nb_point_draw(nb_context *ctx, nb_point point, nb_color color) {
    return;
}

void nb_line_draw(nb_context *ctx, nb_point point1, nb_point point2, nb_color color) {
    return;
}

void nb_rect_draw(nb_context *ctx, nb_rect rect, nb_color color) {
    return;
}

void nb_rect_fill(nb_context *ctx, nb_rect rect, nb_color color) {
    return;
}

void nb_circle_draw(nb_context *ctx, nb_circle circle, nb_color color) {
    return;
}

void nb_circle_fill(nb_context *ctx, nb_circle circle, nb_color color) {
    return;
}

void nb_image_draw(nb_context *ctx, nb_image *img, nb_point pos) {
    return;
}

void nb_image_draw_ex(nb_context *ctx, nb_image *img, nb_rect dst, nb_rect src, nb_color tint, float rotation) {
    return;
}

nb_vec2 nb_vec2_add(nb_vec2 a, nb_vec2 b) {
    return (nb_vec2){0};
}

nb_vec2 nb_vec2_sub(nb_vec2 a, nb_vec2 b) {
    return (nb_vec2){0};
}

nb_vec2 nb_vec2_mul(nb_vec2 a, nb_vec2 b) {
    return (nb_vec2){0};
}

nb_vec2 nb_vec2_adds(nb_vec2 a, float b) {
    return (nb_vec2){0};
}

nb_vec2 nb_vec2_subs(nb_vec2 a, float b) {
    return (nb_vec2){0};
}

nb_vec2 nb_vec2_muls(nb_vec2 a, float b) {
    return (nb_vec2){0};
}

float nb_vec2_dot(nb_vec2 a, nb_vec2 b) {
    return 0;
}

float nb_vec2_mag2(nb_vec2 a) {
    return 0;
}

float nb_vec2_mag(nb_vec2 a) {
    return 0;
}

nb_vec2 nb_vec2_norm(nb_vec2 a) {
    return (nb_vec2){0};
}

nb_vec3 nb_vec3_add(nb_vec3 a, nb_vec3 b) {
    return (nb_vec3){0};
}

nb_vec3 nb_vec3_sub(nb_vec3 a, nb_vec3 b) {
    return (nb_vec3){0};
}

nb_vec3 nb_vec3_mul(nb_vec3 a, nb_vec3 b) {
    return (nb_vec3){0};
}

nb_vec3 nb_vec3_adds(nb_vec3 a, float b) {
    return (nb_vec3){0};
}

nb_vec3 nb_vec3_subs(nb_vec3 a, float b) {
    return (nb_vec3){0};
}

nb_vec3 nb_vec3_muls(nb_vec3 a, float b) {
    return (nb_vec3){0};
}

float nb_vec3_dot(nb_vec3 a, nb_vec3 b) {
    return 0;
}

float nb_vec3_mag2(nb_vec3 a) {
    return 0;
}

float nb_vec3_mag(nb_vec3 a) {
    return 0;
}

nb_vec3 nb_vec3_norm(nb_vec3 a) {
    return (nb_vec3){0};
}

nb_vec3 nb_vec3_cross(nb_vec3 a, nb_vec3 b) {
    return (nb_vec3){0};
}

nb_vec4 nb_vec4_add(nb_vec4 a, nb_vec4 b) {
    return (nb_vec4){0};
}

nb_vec4 nb_vec4_sub(nb_vec4 a, nb_vec4 b) {
    return (nb_vec4){0};
}

nb_vec4 nb_vec4_mul(nb_vec4 a, nb_vec4 b) {
    return (nb_vec4){0};
}

nb_vec4 nb_vec4_adds(nb_vec4 a, float b) {
    return (nb_vec4){0};
}

nb_vec4 nb_vec4_subs(nb_vec4 a, float b) {
    return (nb_vec4){0};
}

nb_vec4 nb_vec4_muls(nb_vec4 a, float b) {
    return (nb_vec4){0};
}

float nb_vec4_dot(nb_vec4 a, nb_vec4 b) {
    return (nb_vec4){0};
}

float nb_vec4_mag2(nb_vec4 a) {
    return (nb_vec4){0};
}

float nb_vec4_mag(nb_vec4 a) {
    return (nb_vec4){0};
}

nb_vec4 nb_vec4_norm(nb_vec4 a) {
    return (nb_vec4){0};
}


#endif // NB_NB_C
#endif // NB_IMPL
