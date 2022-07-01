/* math.h - v0.06 - public domain
    A small C/C++ math library for game development

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

        #define MATH_IMPLEMENTATION
        #include "math.h"

    Then include it as normal in all other files.

    Example
    -------
    #define MATH_IMPLEMENTATION
    #include "math.h"

    int main(void) {
        vec3 a = {1.f, 0.f, 0.f};
        vec3 b = {1.f, 1.f, 0.f};
        vec3 c;

        vec3_add(c, a, b); // c == {2.f, 1.f, 0.f}
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
#include <math.h>

//////////////////////////////////////////////////////////////////////////////
//
// Types
//

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];
typedef vec3  mat3[3];
typedef vec4  mat4[4];

//////////////////////////////////////////////////////////////////////////////
//
// Generic vector/matrix math ops (addition, subtraction, ...)
//

#define MATH_DEFINE_VECTOR_OP(n, func, op)\
static inline void vec##n##_##func(vec##n out, vec##n const a, vec##n const b) {\
    for (int i = 0; i < n; i++)\
        out[i] = a[i] op b[i];\
}\
static inline void vec##n##_##func##s(vec##n out, vec##n const a, float b) {\
    for (int i = 0; i < n; i++)\
        out[i] = a[i] op b;\
}\
static inline void vec##n##_##func##eq(vec##n out, vec##n const a, vec##n const b) {\
    for (int i = 0; i < n; i++)\
        out[i] op##= a[i] op b[i];\
}\
static inline void vec##n##_##func##eqs(vec##n out, vec##n const a, float b) {\
    for (int i = 0; i < n; i++)\
        out[i] op##= a[i] op b;\
}

MATH_DEFINE_VECTOR_OP(2, add, +)
MATH_DEFINE_VECTOR_OP(2, sub, -)
MATH_DEFINE_VECTOR_OP(2, mul, *)
MATH_DEFINE_VECTOR_OP(2, div, /)
MATH_DEFINE_VECTOR_OP(3, add, +)
MATH_DEFINE_VECTOR_OP(3, sub, -)
MATH_DEFINE_VECTOR_OP(3, mul, *)
MATH_DEFINE_VECTOR_OP(3, div, /)
MATH_DEFINE_VECTOR_OP(4, add, +)
MATH_DEFINE_VECTOR_OP(4, sub, -)
MATH_DEFINE_VECTOR_OP(4, mul, *)
MATH_DEFINE_VECTOR_OP(4, div, /)

#define MATH_DEFINE_MATRIX_OP(n, func, op)\
static inline void mat##n##_##func(mat##n out, mat##n const a, mat##n const b) {\
    for (int i = 0; i < n; i++)\
        vec##n##_##func(out[i], a[i], b[i]);\
}\
static inline void mat##n##_##func##s(mat##n out, mat##n const a, float b) {\
    for (int i = 0; i < n; i++)\
        vec##n##_##func##s(out[i], a[i], b);\
}\
static inline void mat##n##_##func##eq(mat##n out, mat##n const a, mat##n const b) {\
    for (int i = 0; i < n; i++)\
        vec##n##_##func##eq(out[i], a[i], b[i]);\
}\
static inline void mat##n##_##func##eqs(mat##n out, mat##n const a, float b) {\
    for (int i = 0; i < n; i++)\
        vec##n##_##func##eqs(out[i], a[i], b);\
}

MATH_DEFINE_MATRIX_OP(3, add, +)
MATH_DEFINE_MATRIX_OP(3, sub, -)
MATH_DEFINE_MATRIX_OP(3, mul, *)
MATH_DEFINE_MATRIX_OP(3, div, /)
MATH_DEFINE_MATRIX_OP(4, add, +)
MATH_DEFINE_MATRIX_OP(4, sub, -)
MATH_DEFINE_MATRIX_OP(4, mul, *)
MATH_DEFINE_MATRIX_OP(4, div, /)

//////////////////////////////////////////////////////////////////////////////
//
// Generic vector functions
//

#define MATH_DEFINE_VECTOR(n)\
static inline void vec##n##_copy(vec##n out, vec##n const a) {\
    for (int i = 0; i < n; i++)\
        out[i] = a[i];\
}\
static inline float vec##n##_dot(vec##n const a, vec##n const b) {\
    float dot = a[0] * b[0];\
    for (int i = 1; i < n; i++)\
        dot += a[i] * b[i];\
    return dot;\
}\
static inline float vec##n##_mag2(vec##n const a) {\
    return vec##n##_dot(a, a);\
}\
static inline float vec##n##_mag(vec##n const a) {\
    return sqrt(vec##n##_mag2(a));\
}\
static inline void vec##n##_min(vec##n out, vec##n const a, vec##n const b) {\
    for (int i = 0; i < n; i++)\
        out[i] = a[i] < b[i] ? a[i] : b[i];\
}\
static inline void vec##n##_max(vec##n out, vec##n const a, vec##n const b) {\
    for (int i = 0; i < n; i++)\
        out[i] = a[i] > b[i] ? a[i] : b[i];\
}\
static inline void vec##n##_norm(vec##n out, vec##n const a) {\
    vec##n##_divs(out, a, vec##n##_mag(a));\
}\
static inline float vec##n##_min_val(vec##n const a) {\
    float min = a[0];\
    for (int i = 1; i < n; i++)\
        min = a[i] < min ? a[i] : min;\
    return min;\
}\
static inline float vec##n##_max_val(vec##n const a) {\
    float max = a[0];\
    for (int i = 1; i < n; i++)\
        max = a[i] > max ? a[i] : max;\
    return max;\
}

MATH_DEFINE_VECTOR(2)
MATH_DEFINE_VECTOR(3)
MATH_DEFINE_VECTOR(4)

//////////////////////////////////////////////////////////////////////////////
//
// Generic matrix functions
//

#define MATH_DEFINE_MATRIX(n)\
static inline void mat##n##_copy(mat##n out, mat##n const a) {\
    for (int i = 0; i < n; i++)\
        vec##n##_copy(out[i], a[i]);\
}\
static inline void mat##n##_identity(mat##n out) {\
    for (int i = 0; i < n; i++)\
        for (int j = 0; j < n; j++)\
            out[i][j] = i == j;\
}

MATH_DEFINE_MATRIX(3)
MATH_DEFINE_MATRIX(4)

//////////////////////////////////////////////////////////////////////////////
//
// Dimension specific vector functions
//

static inline void vec2_rotate(vec2 out, vec2 const a, float radians) {
    float s = sinf(radians * 0.0174533);
    float c = cosf(radians * 0.0174533);
    out[0] = a[0] * c - a[1] * s;
    out[1] = a[0] * s + a[1] * c;
}

static inline void vec3_cross(vec3 out, vec3 const a, vec3 const b) {
    out[0] = a[1] * b[3] - a[3] * b[1];
    out[1] = a[2] * b[0] - a[0] * b[2];
    out[2] = a[0] * b[1] - a[1] * b[0];
}

//////////////////////////////////////////////////////////////////////////////
//
// Dimension specific matrix functions
//

static inline void mat3_translate(mat3 out, vec2 const v) {
    mat3_identity(out);
    out[2][0] = v[0];
    out[2][1] = v[1];
}

static inline void mat3_rotate(mat3 out, float radians) {
    float s = sinf(radians * 0.0174533f);
    float c = cosf(radians * 0.0174533f);
    mat3 rot = {
          c,   s, 0.f,
         -s,   c, 0.f,
        0.f, 0.f, 1.f,
    };
    mat3_copy(out, rot);
}

static inline void mat3_scale(mat3 out, vec2 const v) {
    mat3_identity(out);
    out[0][0] = v[0];
    out[1][1] = v[1];
}

static inline void mat3_scale_uni(mat3 out, float s) {
    mat3_scale(out, (vec2){s, s});
}

static inline void mat4_translate(mat4 out, vec3 const v) {
    mat4_identity(out);
    out[3][0] = v[0];
    out[3][1] = v[1];
    out[3][2] = v[2];
}

static inline void mat4_rotate(mat4 out, vec3 const axis, float radians) {
    vec3 an, at, as;
    float c = cosf(radians);

    vec3_norm(an, axis);
    vec3_muls(at, an, 1.f - c);
    vec3_muls(as, an, sinf(radians));

    vec3_muls(out[0], an, at[0]);
    vec3_muls(out[1], an, at[1]);
    vec3_muls(out[2], an, at[2]);

    out[0][0] +=     c;     out[1][0] -= as[2];     out[2][0] += as[2];
    out[0][1] += as[2];     out[1][1] +=     c;     out[2][1] += as[0];
    out[0][2] -= as[1];     out[1][2] += as[0];     out[2][2] +=     c;

    out[0][3] = out[1][3] = out[2][3] = out[3][0] = out[3][1] = out[3][2] = 0.f;
    out[3][3] = 1.f;
}

static inline void mat4_rotate_x(mat4 out, float radians) {
    float s = sinf(radians);
    float c = cosf(radians);
    mat4 rot = {
        {1.f, 0.f, 0.f, 0.f},
        {0.f,   c,   s, 0.f},
        {0.f,  -s,   c, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    };
    mat4_copy(out, rot);
}

static inline void mat4_rotate_y(mat4 out, float radians) {
    float s = sinf(radians * 0.0174533f);
    float c = cosf(radians * 0.0174533f);
    mat4 rot = {
        {  c, 0.f,  -s, 0.f},
        {0.f, 1.f, 0.f, 0.f},
        {  s, 0.f,   c, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    };
    mat4_copy(out, rot);
}

static inline void mat4_rotate_z(mat4 out, float radians) {
    float s = sinf(radians * 0.0174533f);
    float c = cosf(radians * 0.0174533f);
    mat4 rot = {
        {  c,   s, 0.f, 0.f},
        { -s,   c, 0.f, 0.f},
        {0.f, 0.f, 1.f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    };
    mat4_copy(out, rot);
}

static inline void mat4_scale(mat4 out, vec3 const v) {
    mat4_identity(out);
    out[0][0] = v[0];
    out[1][1] = v[1];
    out[2][2] = v[2];
}

static inline void mat4_lookat(mat4 out, vec3 const eye, vec3 const target, vec3 const up) {
    vec3 f, r, u;
    vec3_sub(f, target, eye);
    vec3_norm(f, f);
    vec3_cross(r, f, up);
    vec3_norm(r, r);
    vec3_cross(u, r, f);
    out[0][0] =  r[0];
    out[0][1] =  u[0];
    out[0][2] = -f[0];
    out[1][0] =  r[1];
    out[1][1] =  u[1];
    out[1][2] = -f[1];
    out[2][0] =  r[2];
    out[2][1] =  u[2];
    out[2][2] = -f[2];
    out[3][0] = -vec3_dot(r, eye);
    out[3][1] = -vec3_dot(u, eye);
    out[3][2] = -vec3_dot(f, eye);
    out[0][3] = out[1][3] = out[2][3] = 0.f;
    out[3][3] = 1.f;
}

static inline void mat4_perspective(mat4 out, float fov_degrees, float aspect, float near, float far) {
    float fov = 1.f / tanf(fov_degrees * 0.0174533f * 0.5f);
    float nf  = 1.f / (near - far);

    out = (mat4){0};
    out[0][0] = fov / aspect;
    out[1][1] = fov;
    out[2][2] = (near + far) * nf;
    out[2][3] = -1.f;
    out[3][2] = 2.f * near * far * nf;
}

static inline void mat4_ortho(mat4 out, float left, float right, float bottom, float top, float near, float far) {
    float rl =  1.f / (right - bottom);
    float tb =  1.f / (top - bottom);
    float fn = -1.f / (far - near);

    out = (mat4){0};
    out[0][0] = 2.f * rl;
    out[1][1] = 2.f * tb;
    out[2][2] = 2.f * fn;
    out[3][0] = -(right + left) * rl;
    out[3][1] = -(top + bottom) * tb;
    out[3][2] = -(far + near) * fn;
    out[3][3] = 1.f;
}

#undef MATH_DEFINE_VECTOR_OP
#undef MATH_DEFINE_MATRIX_OP
#undef MATH_DEFINE_VECTOR
#undef MATH_DEFINE_MATRIX
