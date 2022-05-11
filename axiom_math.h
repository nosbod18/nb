#ifndef AXIOM_MATH_H
#define AXIOM_MATH_H

#include <math.h> // sin, cos, tan, sqrt

#define axm__var(x) axm__var_##x##__LINE__##__

#define AXM_VECTOR(T, N)\
typedef T axm_##T##N[N];\
static inline void axm_##T##N##_copy(axm_##T##N out, axm_##T##N a) {\
        for (int axm__var(i) = 0; axm__var(i) < N; axm__var(i)++)\
                out[axm__var(i)] = a[axm__var(i)];\
}\
static inline void axm_##T##N##_add(axm_##T##N out, axm_##T##N const a, axm_##T##N const b) {\
        for (int axm__var(i) = 0; axm__var(i) < N; axm__var(i)++)\
                out[axm__var(i)] = a[axm__var(i)] + b[axm__var(i)];\
}\
static inline void axm_##T##N##_sub(axm_##T##N out, axm_##T##N const a, axm_##T##N const b) {\
        for (int axm__var(i) = 0; axm__var(i) < N; axm__var(i)++)\
                out[axm__var(i)] = a[axm__var(i)] - b[axm__var(i)];\
}\
static inline void axm_##T##N##_mul(axm_##T##N out, axm_##T##N const a, axm_##T##N const b) {\
        for (int axm__var(i) = 0; axm__var(i) < N; axm__var(i)++)\
                out[axm__var(i)] = a[axm__var(i)] * b[axm__var(i)];\
}\
static inline void axm_##T##N##_div(axm_##T##N out, axm_##T##N const a, axm_##T##N const b) {\
        for (int axm__var(i) = 0; axm__var(i) < N; axm__var(i)++)\
                out[axm__var(i)] = a[axm__var(i)] / b[axm__var(i)];\
}\
static inline void axm_##T##N##_adds(axm_##T##N out, axm_##T##N const a, T b) {\
        for (int axm__var(i) = 0; axm__var(i) < N; axm__var(i)++)\
                out[axm__var(i)] = a[axm__var(i)] + b;\
}\
static inline void axm_##T##N##_subs(axm_##T##N out, axm_##T##N const a, T b) {\
        for (int axm__var(i) = 0; axm__var(i) < N; axm__var(i)++)\
                out[axm__var(i)] = a[axm__var(i)] - b;\
}\
static inline void axm_##T##N##_muls(axm_##T##N out, axm_##T##N const a, T b) {\
        for (int axm__var(i) = 0; axm__var(i) < N; axm__var(i)++)\
                out[axm__var(i)] = a[axm__var(i)] * b;\
}\
static inline void axm_##T##N##_divs(axm_##T##N out, axm_##T##N const a, T b) {\
        for (int axm__var(i) = 0; axm__var(i) < N; axm__var(i)++)\
                out[axm__var(i)] = a[axm__var(i)] / b;\
}\
static inline T axm_##T##N##_dot(axm_##T##N const a, axm_##T##N const b) {\
        T dot = 0;\
        for (int axm__var(i) = 0; axm__var(i) < N; axm__var(i)++)\
                dot += a[axm__var(i)] * b[axm__var(i)];\
        return dot;\
}\
static inline T axm_##T##N##_mag2(axm_##T##N const a) {\
        return axm_##T##N##_dot(a, a);\
}\
static inline T axm_##T##N##_mag(axm_##T##N const a) {\
        return sqrt(axm_##T##N##_mag2(a));\
}\
static inline void axm_##T##N##_min(axm_##T##N out, axm_##T##N const a, axm_##T##N const b) {\
        for (int axm__var(i) = 0; axm__var(i) < N; axm__var(i)++)\
                out[axm__var(i)] = a[axm__var(i)] < b[axm__var(i)] ? a[axm__var(i)] : b[axm__var(i)];\
}\
static inline void axm_##T##N##_max(axm_##T##N out, axm_##T##N const a, axm_##T##N const b) {\
        for (int axm__var(i) = 0; axm__var(i) < N; axm__var(i)++)\
                out[axm__var(i)] = a[axm__var(i)] > b[axm__var(i)] ? a[axm__var(i)] : b[axm__var(i)];\
}\
static inline void axm_##T##N##_norm(axm_##T##N out, axm_##T##N const a) {\
        axm_##T##N##_divs(out, a, axm_##T##N##_mag(a));\
}\
static inline T axm_##T##N##_min_val(axm_##T##N const a) {\
        T min = a[0];\
        for (int axm__var(i) = 1; axm__var(i) < N; axm__var(i)++)\
                min = a[axm__var(i)] < min ? a[axm__var(i)] : min;\
        return min;\
}\
static inline T axm_##T##N##_max_val(axm_##T##N const a) {\
        T max = a[0];\
        for (int axm__var(i) = 1; axm__var(i) < N; axm__var(i)++)\
                max = a[axm__var(i)] > max ? a[axm__var(i)] : max;\
        return max;\
}\

#define AXM_VECTOR_SPECIFIC(T)\
static inline void axm_##T##2_rotate(axm_##T##2 out, axm_##T##2 const a, T degrees) {\
        T s = sin(degrees * 0.0174533);\
        T c = cos(degrees * 0.0174533);\
        out[0] = a[0] * c - a[1] * s;\
        out[1] = a[0] * s + a[1] * c;\
}\
static inline void axm_##T##3_cross(axm_##T##3 out, axm_##T##3 const a, axm_##T##3 const b) {\
        out[0] = a[1] * b[3] - a[3] * b[1];\
        out[1] = a[2] * b[0] - a[0] * b[2];\
        out[2] = a[0] * b[1] - a[1] * b[0];\
}

#define AXM_MATRIX(T, R, C)\
typedef T axm_##T##R##x##C[R][C];\
static inline void axm_##T##R##x##C##_copy(axm_##T##R##x##C out, axm_##T##R##x##C a) {\
        for (int axm__var(i) = 0; axm__var(i) < R; axm__var(i)++)\
                for (int axm__var(j) = 0; axm__var(j) < C; axm__var(j)++)\
                        out[axm__var(i)][axm__var(j)] = a[axm__var(i)][axm__var(j)]; /* Could do memset here, would have to include string.h */\
}\
static inline void axm_##T##R##x##C##_identity(axm_##T##R##x##C out) {\
        for (int axm__var(i) = 0; axm__var(i) < R; axm__var(i)++)\
                for (int axm__var(j) = 0; axm__var(j) < C; axm__var(j)++)\
                     out[axm__var(i)][axm__var(j)] = (T)(axm__var(i) == axm__var(j));\
}\
static inline void axm_##T##R##x##C##_add(axm_##T##R##x##C out, axm_##T##R##x##C const a, axm_##T##R##x##C const b) {\
        for (int axm__var(i) = 0; axm__var(i) < R; axm__var(i)++)\
                for (int axm__var(j) = 0; axm__var(j) < C; axm__var(j)++)\
                     out[axm__var(i)][axm__var(j)] = a[axm__var(i)][axm__var(j)] + b[axm__var(i)][axm__var(j)];\
}\
static inline void axm_##T##R##x##C##_sub(axm_##T##R##x##C out, axm_##T##R##x##C const a, axm_##T##R##x##C const b) {\
        for (int axm__var(i) = 0; axm__var(i) < R; axm__var(i)++)\
                for (int axm__var(j) = 0; axm__var(j) < C; axm__var(j)++)\
                     out[axm__var(i)][axm__var(j)] = a[axm__var(i)][axm__var(j)] - b[axm__var(i)][axm__var(j)];\
}\
static inline void axm_##T##R##x##C##_mul(axm_##T##R##x##C out, axm_##T##R##x##C const a, axm_##T##R##x##C const b) {\
        for (int axm__var(i) = 0; axm__var(i) < R; axm__var(i)++)\
                for (int axm__var(j) = 0; axm__var(j) < C; axm__var(j)++)\
                     out[axm__var(i)][axm__var(j)] = a[axm__var(i)][axm__var(j)] * b[axm__var(i)][axm__var(j)];\
}\
static inline void axm_##T##R##x##C##_div(axm_##T##R##x##C out, axm_##T##R##x##C const a, axm_##T##R##x##C const b) {\
        for (int axm__var(i) = 0; axm__var(i) < R; axm__var(i)++)\
                for (int axm__var(j) = 0; axm__var(j) < C; axm__var(j)++)\
                     out[axm__var(i)][axm__var(j)] = a[axm__var(i)][axm__var(j)] / b[axm__var(i)][axm__var(j)];\
}\
static inline void axm_##T##R##x##C##_adds(axm_##T##R##x##C out, axm_##T##R##x##C const a, T b) {\
        for (int axm__var(i) = 0; axm__var(i) < R; axm__var(i)++)\
                for (int axm__var(j) = 0; axm__var(j) < C; axm__var(j)++)\
                     out[axm__var(i)][axm__var(j)] = a[axm__var(i)][axm__var(j)] + b;\
}\
static inline void axm_##T##R##x##C##_subs(axm_##T##R##x##C out, axm_##T##R##x##C const a, T b) {\
        for (int axm__var(i) = 0; axm__var(i) < R; axm__var(i)++)\
                for (int axm__var(j) = 0; axm__var(j) < C; axm__var(j)++)\
                     out[axm__var(i)][axm__var(j)] = a[axm__var(i)][axm__var(j)] - b;\
}\
static inline void axm_##T##R##x##C##_muls(axm_##T##R##x##C out, axm_##T##R##x##C const a, T b) {\
        for (int axm__var(i) = 0; axm__var(i) < R; axm__var(i)++)\
                for (int axm__var(j) = 0; axm__var(j) < C; axm__var(j)++)\
                     out[axm__var(i)][axm__var(j)] = a[axm__var(i)][axm__var(j)] * b;\
}\
static inline void axm_##T##R##x##C##_divs(axm_##T##R##x##C out, axm_##T##R##x##C const a, T b) {\
        for (int axm__var(i) = 0; axm__var(i) < R; axm__var(i)++)\
                for (int axm__var(j) = 0; axm__var(j) < C; axm__var(j)++)\
                     out[axm__var(i)][axm__var(j)] = a[axm__var(i)][axm__var(j)] / b;\
}\
static inline void axm_##T##R##x##C##_addn(axm_##T##R##x##C out, axm_##T##R##x##C const in[], int n) {\
        for (int axm__var(i) = 0; axm__var(i) < n; axm__var(i)++)\
                axm_##T##R##x##C##_add(out, out, in[axm__var(i)]);\
}\
static inline void axm_##T##R##x##C##_subn(axm_##T##R##x##C out, axm_##T##R##x##C const in[], int n) {\
        for (int axm__var(i) = 0; axm__var(i) < n; axm__var(i)++)\
                axm_##T##R##x##C##_sub(out, out, in[axm__var(i)]);\
}\
static inline void axm_##T##R##x##C##_muln(axm_##T##R##x##C out, axm_##T##R##x##C const in[], int n) {\
        for (int axm__var(i) = 0; axm__var(i) < n; axm__var(i)++)\
                axm_##T##R##x##C##_mul(out, out, in[axm__var(i)]);\
}\
static inline void axm_##T##R##x##C##_divn(axm_##T##R##x##C out, axm_##T##R##x##C const in[], int n) {\
        for (int axm__var(i) = 0; axm__var(i) < n; axm__var(i)++)\
                axm_##T##R##x##C##_div(out, out, in[axm__var(i)]);\
}\

#define AXM_MATRIX_SPECIFIC(T)\
static inline void axm_##T##3x3_translate(axm_##T##3x3 out, axm_##T##2 const v) {\
        axm_##T##3x3_identity(out);\
        out[2][0] = v[0];\
        out[2][1] = v[1];\
}\
static inline void axm_##T##3x3_rotate(axm_##T##3x3 out, T degrees) {\
        T c = cos(degrees * 0.0174533);\
        T s = sin(degrees * 0.0174533);\
        axm_##T##3x3_identity(out);\
        out[0][0] =  c;\
        out[0][1] =  s;\
        out[1][0] = -s;\
        out[1][1] =  c;\
        out[0][2] = out[1][2] = out[2][0] = out[2][1] = 0;\
        out[2][2] = 1.0;\
}\
static inline void axm_##T##3x3_scale(axm_##T##3x3 out, axm_##T##2 const v) {\
        axm_##T##3x3_identity(out);\
        out[0][0] = v[0];\
        out[1][1] = v[1];\
}\
static inline void axm_##T##3x3_scale_uni(axm_##T##3x3 out, T s) {\
        axm_##T##3x3_identity(out);\
        out[0][0] = s;\
        out[1][1] = s;\
}\
static inline void axm_##T##4x4_translate(axm_##T##4x4 out, axm_##T##3 const v) {\
        axm_##T##4x4_identity(out);\
        out[3][0] = v[0];\
        out[3][1] = v[1];\
        out[3][2] = v[2];\
        out[0][0] = out[1][1] = out[2][2] = out[3][3] = 1.0;\
}\
static inline void axm_##T##4x4_rotate(axm_##T##4x4 out, axm_##T##3 const axis, T degrees) {\
        T c = cos(degrees * 0.0174533);\
        T s = sin(degrees * 0.0174533);\
        T t = 1.0 - c;\
        axm_##T##3 an, at, as;\
        axm_##T##3_norm(an, axis);\
        axm_##T##3_muls(at, an, t);\
        axm_##T##3_muls(as, an, s);\
        axm_##T##4x4_identity(out);\
        out[0][0] = an[0] * at[0] + c;\
        out[0][1] = an[1] * at[0] + as[2];\
        out[0][2] = an[2] * at[0] - as[1];\
        out[1][0] = an[0] * at[1] - as[2];\
        out[1][1] = an[1] * at[1] + c;\
        out[1][2] = an[2] * at[1] + as[0];\
        out[2][0] = an[0] * at[2] + as[2];\
        out[2][1] = an[1] * at[2] + as[0];\
        out[2][2] = an[2] * at[2] + c;\
        out[0][3] = out[1][3] = out[2][3] = out[3][0] = out[3][1] = out[3][2] = 0;\
        out[3][3] = 1.0;\
}\
static inline void axm_##T##4x4_rotate_x(axm_##T##4x4 out, T degrees) {\
        T s = sin(degrees * 0.0174533);\
        T c = cos(degrees * 0.0174533);\
        axm_##T##4x4 rot = {\
                {1.f, 0.f, 0.f, 0.f},\
                {0.f,   c,   s, 0.f},\
                {0.f,  -s,   c, 0.f},\
                {0.f, 0.f, 0.f, 1.f}\
        };\
        axm_##T##4x4_copy(out, rot);\
}\
static inline void axm_##T##4x4_rotate_y(axm_##T##4x4 out, T degrees) {\
        T s = sin(degrees * 0.0174533);\
        T c = cos(degrees * 0.0174533);\
        axm_##T##4x4 rot = {\
                {   c, 0.f,  -s, 0.f},\
                { 0.f, 1.f, 0.f, 0.f},\
                {   s, 0.f,   c, 0.f},\
                { 0.f, 0.f, 0.f, 1.f}\
        };\
        axm_##T##4x4_copy(out, rot);\
}\
static inline void axm_##T##4x4_rotate_z(axm_##T##4x4 out, T degrees) {\
        T s = sin(degrees * 0.0174533);\
        T c = cos(degrees * 0.0174533);\
        axm_##T##4x4 rot = {\
                {   c,   s, 0.f, 0.f},\
                {  -s,   c, 0.f, 0.f},\
                { 0.f, 0.f, 1.f, 0.f},\
                { 0.f, 0.f, 0.f, 1.f}\
        };\
        axm_##T##4x4_copy(out, rot);\
}\
static inline void axm_##T##4x4_scale(axm_##T##4x4 out, axm_##T##3 const v) {\
        axm_##T##4x4_identity(out);\
        out[0][0] = v[0];\
        out[1][1] = v[1];\
        out[2][2] = v[2];\
        out[3][3] = 1.0;\
}\
static inline void axm_##T##4x4_lookat(axm_##T##4x4 out, axm_##T##3 const eye, axm_##T##3 const target, axm_##T##3 const up) {\
        axm_##T##3 f, r, u;\
        axm_##T##3_sub(f, target, eye);\
        axm_##T##3_norm(f, f);\
        axm_##T##3_cross(r, f, up);\
        axm_##T##3_norm(r, r);\
        axm_##T##3_cross(u, r, f);\
        out[0][0] =  r[0];\
        out[0][1] =  u[0];\
        out[0][2] = -f[0];\
        out[1][0] =  r[1];\
        out[1][1] =  u[1];\
        out[1][2] = -f[1];\
        out[2][0] =  r[2];\
        out[2][1] =  u[2];\
        out[2][2] = -f[2];\
        out[3][1] = -axm_##T##3_dot(u, eye);\
        out[3][0] = -axm_##T##3_dot(r, eye);\
        out[3][2] = -axm_##T##3_dot(f, eye);\
}\
static inline void axm_##T##4x4_perspective(axm_##T##4x4 out, T fov_degrees, T aspect, T near, T far) {\
        T fov = 1.0 / tan(fov_degrees * 0.0174533 * 0.5);\
        T nf  = 1.0 / (near - far);\
        out[0][0] = fov / aspect;\
        out[1][1] = fov;\
        out[2][2] = (near + far) * nf;\
        out[2][3] = -1.0;\
        out[3][2] = 2.0 * near * far * nf;\
}\
static inline void axm_##T##4x4_ortho(axm_##T##4x4 out, T left, T right, T bottom, T top, T near, T far) {\
        T rl =  1.0 / (right - bottom);\
        T tb =  1.0 / (top - bottom);\
        T fn = -1.0 / (far - near);\
        out[0][0] = 2.0 * rl;\
        out[1][1] = 2.0 * tb;\
        out[2][2] = 2.0 * fn;\
        out[3][0] = -(right + left) * rl;\
        out[3][1] = -(top + bottom) * tb;\
        out[3][2] = -(far + near) * fn;\
        out[3][3] = 1.0;\
}\

#ifdef __cplusplus
extern "C" {
#endif

AXM_VECTOR(int,    2)
AXM_VECTOR(int,    3)
AXM_VECTOR(int,    4)
AXM_VECTOR(float,  2)
AXM_VECTOR(float,  3)
AXM_VECTOR(float,  4)
AXM_VECTOR(double, 2)
AXM_VECTOR(double, 3)
AXM_VECTOR(double, 4)
AXM_VECTOR_SPECIFIC(float)
AXM_VECTOR_SPECIFIC(double)

AXM_MATRIX(float,  3, 3)
AXM_MATRIX(float,  4, 4)
AXM_MATRIX(double, 3, 3)
AXM_MATRIX(double, 4, 4)
AXM_MATRIX_SPECIFIC(float)
AXM_MATRIX_SPECIFIC(double)


#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
#endif // AXIOM_MATH_H

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
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXaxm_SS OR
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
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXaxm_SS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
/// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
/// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
