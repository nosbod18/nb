/// # tiny_math.h
/// A header only vector and matrix math library. Depends on `<math.h>` for `sin`, `cos`, `tan`, `sqrt` only.
///
/// ## Note
/// All types defined in this library are nothing more that `typedef`'d arrays, and as such new ones cannot be returned from functions.
/// An `out` variable must be provided to each function where the result is a vector.


#ifndef __tiny_math_h__
#define __tiny_math_h__

#include <math.h> // sin, cos, tan, sqrt

/// ## Vector
/// A vector is defined by the type and number of elements it holds. For example, a vector of 3 floats would be `tm_float3`. Generally, a vector
/// of type T that holds N elements is defined as `tm_TN`.
///
/// ### API
/// ```c
/// void tm_TN_copy   (tm_TN out, tm_TN a)
/// void tm_TN_add    (tm_TN out, tm_TN a, tm_TN b)
/// void tm_TN_sub    (tm_TN out, tm_TN a, tm_TN b)
/// void tm_TN_mul    (tm_TN out, tm_TN a, tm_TN b)
/// void tm_TN_div    (tm_TN out, tm_TN a, tm_TN b)
/// void tm_TN_adds   (tm_TN out, tm_TN a, T b)
/// void tm_TN_subs   (tm_TN out, tm_TN a, T b)
/// void tm_TN_muls   (tm_TN out, tm_TN a, T b)
/// void tm_TN_divs   (tm_TN out, tm_TN a, T b)
/// T    tm_TN_dot    (tm_TN a, tm_TN b)
/// T    tm_TN_mag2   (tm_TN a) // Returns the magnitude of `a` squared
/// T    tm_TN_mag    (tm_TN a)
/// T    tm_TN_min_val(tm_TN a) // Returns the smallest component of `a`
/// T    tm_TN_max_val(tm_TN a) // Returns the largest component of `a`
/// void tm_TN_min    (tm_TN out, tm_TN a, tm_TN b)
/// void tm_TN_max    (tm_TN out, tm_TN a, tm_TN b)
/// void tm_TN_norm   (tm_TN out, tm_TN a, tm_TN b)
/// ```

#define TM_VECTOR(T, N)\
typedef T tm_##T##N[N];\
static inline void tm_##T##N##_copy(tm_##T##N out, tm_##T##N a) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i];\
}\
static inline void tm_##T##N##_add(tm_##T##N out, tm_##T##N const a, tm_##T##N const b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] + b[_i];\
}\
static inline void tm_##T##N##_sub(tm_##T##N out, tm_##T##N const a, tm_##T##N const b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] - b[_i];\
}\
static inline void tm_##T##N##_mul(tm_##T##N out, tm_##T##N const a, tm_##T##N const b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] * b[_i];\
}\
static inline void tm_##T##N##_div(tm_##T##N out, tm_##T##N const a, tm_##T##N const b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] / b[_i];\
}\
static inline void tm_##T##N##_adds(tm_##T##N out, tm_##T##N const a, T b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] + b;\
}\
static inline void tm_##T##N##_subs(tm_##T##N out, tm_##T##N const a, T b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] - b;\
}\
static inline void tm_##T##N##_muls(tm_##T##N out, tm_##T##N const a, T b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] * b;\
}\
static inline void tm_##T##N##_divs(tm_##T##N out, tm_##T##N const a, T b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] / b;\
}\
static inline T tm_##T##N##_dot(tm_##T##N const a, tm_##T##N const b) {\
        T dot = 0;\
        for (int _i = 0; _i < N; _i++)\
                dot += a[_i] * b[_i];\
        return dot;\
}\
static inline T tm_##T##N##_mag2(tm_##T##N const a) {\
        return tm_##T##N##_dot(a, a);\
}\
static inline T tm_##T##N##_mag(tm_##T##N const a) {\
        return sqrt(tm_##T##N##_mag2(a));\
}\
static inline void tm_##T##N##_min(tm_##T##N out, tm_##T##N const a, tm_##T##N const b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] < b[_i] ? a[_i] : b[_i];\
}\
static inline void tm_##T##N##_max(tm_##T##N out, tm_##T##N const a, tm_##T##N const b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] > b[_i] ? a[_i] : b[_i];\
}\
static inline void tm_##T##N##_norm(tm_##T##N out, tm_##T##N const a) {\
        tm_##T##N##_divs(out, a, tm_##T##N##_mag(a));\
}\
static inline T tm_##T##N##_min_val(tm_##T##N const a) {\
        T min = a[0];\
        for (int _i = 1; _i < N; _i++)\
                min = a[_i] < min ? a[_i] : min;\
        return min;\
}\
static inline T tm_##T##N##_max_val(tm_##T##N const a) {\
        T max = a[0];\
        for (int _i = 1; _i < N; _i++)\
                max = a[_i] > max ? a[_i] : max;\
        return max;\
}\

/// #### Dimension specific functions
/// ```c
/// void tm_T2_rotate   (tm_T2 out, tm_T2 a, T degrees)
/// void tm_T3_cross    (tm_T3 out, tm_T3 a, tm_T3 b)
/// ```

#define TM_VECTOR_SPECIFIC(T)\
static inline void tm_##T##2_rotate(tm_##T##2 out, tm_##T##2 const a, T degrees) {\
        T s = sin(degrees * 0.0174533);\
        T c = cos(degrees * 0.0174533);\
        out[0] = a[0] * c - a[1] * s;\
        out[1] = a[0] * s + a[1] * c;\
}\
static inline void tm_##T##3_cross(tm_##T##3 out, tm_##T##3 const a, tm_##T##3 const b) {\
        out[0] = a[1] * b[3] - a[3] * b[1];\
        out[1] = a[2] * b[0] - a[0] * b[2];\
        out[2] = a[0] * b[1] - a[1] * b[0];\
}

/// ## Matrix
/// A matrix is exactly the same as a vector, except it a two demensional array instead of a one dimensional one. A matrix is named the same way
/// as a vector with a small change to represent the second dimension, e.g. `float4x4` represents a 4x4 matrix of floats. In general, a matrix of
/// type T and holds R rows and C columns is defined as `tm_TRxC`.
///
/// ### API
/// ```c
/// void tm_TRxC_copy   (tm_TRxC out, tm_TRxC a)
/// void tm_TRxC_add    (tm_TRxC out, tm_TRxC a, tm_TRxC b)
/// void tm_TRxC_sub    (tm_TRxC out, tm_TRxC a, tm_TRxC b)
/// void tm_TRxC_mul    (tm_TRxC out, tm_TRxC a, tm_TRxC b)
/// void tm_TRxC_div    (tm_TRxC out, tm_TRxC a, tm_TRxC b)
/// void tm_TRxC_adds   (tm_TRxC out, tm_TRxC a, T b)
/// void tm_TRxC_subs   (tm_TRxC out, tm_TRxC a, T b)
/// void tm_TRxC_muls   (tm_TRxC out, tm_TRxC a, T b)
/// void tm_TRxC_divs   (tm_TRxC out, tm_TRxC a, T b)
/// void tm_TRxC_addn   (tm_TRxC out, int n, tm_TRxC in[]) // These 4 functions operate on `n` matrices passed in as an array
/// void tm_TRxC_subn   (tm_TRxC out, int n, tm_TRxC in[])
/// void tm_TRxC_muln   (tm_TRxC out, int n, tm_TRxC in[])
/// void tm_TRxC_divn   (tm_TRxC out, int n, tm_TRxC in[])
/// ```

#define TM_MATRIX(T, R, C)\
typedef T tm_##T##R##x##C[R][C];\
static inline void tm_##T##R##x##C##_copy(tm_##T##R##x##C out, tm_##T##R##x##C a) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                        out[_i][_j] = a[_i][_j]; /* Could do memset here, would have to include string.h */\
}\
static inline void tm_##T##R##x##C##_identity(tm_##T##R##x##C out) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = (T)(_i == _j);\
}\
static inline void tm_##T##R##x##C##_add(tm_##T##R##x##C out, tm_##T##R##x##C const a, tm_##T##R##x##C const b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] + b[_i][_j];\
}\
static inline void tm_##T##R##x##C##_sub(tm_##T##R##x##C out, tm_##T##R##x##C const a, tm_##T##R##x##C const b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] - b[_i][_j];\
}\
static inline void tm_##T##R##x##C##_mul(tm_##T##R##x##C out, tm_##T##R##x##C const a, tm_##T##R##x##C const b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] * b[_i][_j];\
}\
static inline void tm_##T##R##x##C##_div(tm_##T##R##x##C out, tm_##T##R##x##C const a, tm_##T##R##x##C const b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] / b[_i][_j];\
}\
static inline void tm_##T##R##x##C##_adds(tm_##T##R##x##C out, tm_##T##R##x##C const a, T b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] + b;\
}\
static inline void tm_##T##R##x##C##_subs(tm_##T##R##x##C out, tm_##T##R##x##C const a, T b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] - b;\
}\
static inline void tm_##T##R##x##C##_muls(tm_##T##R##x##C out, tm_##T##R##x##C const a, T b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] * b;\
}\
static inline void tm_##T##R##x##C##_divs(tm_##T##R##x##C out, tm_##T##R##x##C const a, T b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] / b;\
}\
static inline void tm_##T##R##x##C##_addn(tm_##T##R##x##C out, int n, tm_##T##R##x##C const in[]) {\
        for (int _i = 0; _i < n; _i++)\
                tm_##T##R##x##C##_add(out, out, in[_i]);\
}\
static inline void tm_##T##R##x##C##_subn(tm_##T##R##x##C out, int n, tm_##T##R##x##C const in[]) {\
        for (int _i = 0; _i < n; _i++)\
                tm_##T##R##x##C##_sub(out, out, in[_i]);\
}\
static inline void tm_##T##R##x##C##_muln(tm_##T##R##x##C out, int n, tm_##T##R##x##C const in[]) {\
        for (int _i = 0; _i < n; _i++)\
                tm_##T##R##x##C##_mul(out, out, in[_i]);\
}\
static inline void tm_##T##R##x##C##_divn(tm_##T##R##x##C out, int n, tm_##T##R##x##C const in[]) {\
        for (int _i = 0; _i < n; _i++)\
                tm_##T##R##x##C##_div(out, out, in[_i]);\
}\

/// #### Dimension specific functions
/// ```c
/// void tm_T3x3_translate      (tm_T3x3 out, T2 t)
/// void tm_T3x3_rotate         (tm_T3x3 out, T degrees)
/// void tm_T3x3_scale          (tm_T3x3 out, T2 s)
/// void tm_T3x3_scale_uni      (tm_T3x3 out, T s)
/// void tm_T4x4_translate      (tm_T4x4 out, T3 v)
/// void tm_T4x4_rotate         (tm_T4x4 out, T3 axis, T degrees)
/// void tm_T4x4_rotate_x       (tm_T4x4 out, T degrees)
/// void tm_T4x4_rotate_y       (tm_T4x4 out, T degrees)
/// void tm_T4x4_rotate_z       (tm_T4x4 out, T degrees)
/// void tm_T4x4_scale          (tm_T4x4 out, T3 s)
/// void tm_T4x4_scale_uni      (tm_T4x4 out, T s)
/// void tm_T4x4_lookat         (tm_T4x4 out, T3 eye, T3 target, T3 up)
/// void tm_T4x4_perspective    (tm_T4x4 out, T fov_degrees, T aspect, T near, T far)
/// void tm_T4x4_ortho          (tm_T4x4 out, T left, T right, T bottom, T top, T near, T far)
/// ```

#define TM_MATRIX_SPECIFIC(T)\
static inline void tm_##T##3x3_translate(tm_##T##3x3 out, tm_##T##2 const v) {\
        tm_##T##3x3_identity(out);\
        out[2][0] = v[0];\
        out[2][1] = v[1];\
}\
static inline void tm_##T##3x3_rotate(tm_##T##3x3 out, T degrees) {\
        T c = cos(degrees * 0.0174533);\
        T s = sin(degrees * 0.0174533);\
        tm_##T##3x3_identity(out);\
        out[0][0] =  c;\
        out[0][1] =  s;\
        out[1][0] = -s;\
        out[1][1] =  c;\
        out[0][2] = out[1][2] = out[2][0] = out[2][1] = 0;\
        out[2][2] = 1.0;\
}\
static inline void tm_##T##3x3_scale(tm_##T##3x3 out, tm_##T##2 const v) {\
        tm_##T##3x3_identity(out);\
        out[0][0] = v[0];\
        out[1][1] = v[1];\
}\
static inline void tm_##T##3x3_scale_uni(tm_##T##3x3 out, T s) {\
        tm_##T##3x3_identity(out);\
        out[0][0] = s;\
        out[1][1] = s;\
}\
static inline void tm_##T##4x4_translate(tm_##T##4x4 out, tm_##T##3 const v) {\
        tm_##T##4x4_identity(out);\
        out[3][0] = v[0];\
        out[3][1] = v[1];\
        out[3][2] = v[2];\
        out[0][0] = out[1][1] = out[2][2] = out[3][3] = 1.0;\
}\
static inline void tm_##T##4x4_rotate(tm_##T##4x4 out, tm_##T##3 const axis, T degrees) {\
        T c = cos(degrees * 0.0174533);\
        T s = sin(degrees * 0.0174533);\
        T t = 1.0 - c;\
        tm_##T##3 an, at, as;\
        tm_##T##3_norm(an, axis);\
        tm_##T##3_muls(at, an, t);\
        tm_##T##3_muls(as, an, s);\
        tm_##T##4x4_identity(out);\
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
static inline void tm_##T##4x4_rotate_x(tm_##T##4x4 out, T degrees) {\
        T s = sin(degrees * 0.0174533);\
        T c = cos(degrees * 0.0174533);\
        tm_##T##4x4 rot = {\
                {1.f, 0.f, 0.f, 0.f},\
                {0.f,   c,   s, 0.f},\
                {0.f,  -s,   c, 0.f},\
                {0.f, 0.f, 0.f, 1.f}\
        };\
        tm_##T##4x4_copy(out, rot);\
}\
static inline void tm_##T##4x4_rotate_y(tm_##T##4x4 out, T degrees) {\
        T s = sin(degrees * 0.0174533);\
        T c = cos(degrees * 0.0174533);\
        tm_##T##4x4 rot = {\
                {   c, 0.f,  -s, 0.f},\
                { 0.f, 1.f, 0.f, 0.f},\
                {   s, 0.f,   c, 0.f},\
                { 0.f, 0.f, 0.f, 1.f}\
        };\
        tm_##T##4x4_copy(out, rot);\
}\
static inline void tm_##T##4x4_rotate_z(tm_##T##4x4 out, T degrees) {\
        T s = sin(degrees * 0.0174533);\
        T c = cos(degrees * 0.0174533);\
        tm_##T##4x4 rot = {\
                {   c,   s, 0.f, 0.f},\
                {  -s,   c, 0.f, 0.f},\
                { 0.f, 0.f, 1.f, 0.f},\
                { 0.f, 0.f, 0.f, 1.f}\
        };\
        tm_##T##4x4_copy(out, rot);\
}\
static inline void tm_##T##4x4_scale(tm_##T##4x4 out, tm_##T##3 const v) {\
        tm_##T##4x4_identity(out);\
        out[0][0] = v[0];\
        out[1][1] = v[1];\
        out[2][2] = v[2];\
        out[3][3] = 1.0;\
}\
static inline void tm_##T##4x4_lookat(tm_##T##4x4 out, tm_##T##3 const eye, tm_##T##3 const target, tm_##T##3 const up) {\
        tm_##T##3 f, r, u;\
        tm_##T##3_sub(f, target, eye);\
        tm_##T##3_norm(f, f);\
        tm_##T##3_cross(r, f, up);\
        tm_##T##3_norm(r, r);\
        tm_##T##3_cross(u, r, f);\
        out[0][0] =  r[0];\
        out[0][1] =  u[0];\
        out[0][2] = -f[0];\
        out[1][0] =  r[1];\
        out[1][1] =  u[1];\
        out[1][2] = -f[1];\
        out[2][0] =  r[2];\
        out[2][1] =  u[2];\
        out[2][2] = -f[2];\
        out[3][1] = -tm_##T##3_dot(u, eye);\
        out[3][0] = -tm_##T##3_dot(r, eye);\
        out[3][2] = -tm_##T##3_dot(f, eye);\
}\
static inline void tm_##T##4x4_perspective(tm_##T##4x4 out, T fov_degrees, T aspect, T near, T far) {\
        T fov = 1.0 / tan(fov_degrees * 0.0174533 * 0.5);\
        T nf  = 1.0 / (near - far);\
        out[0][0] = fov / aspect;\
        out[1][1] = fov;\
        out[2][2] = (near + far) * nf;\
        out[2][3] = -1.0;\
        out[3][2] = 2.0 * near * far * nf;\
}\
static inline void tm_##T##4x4_ortho(tm_##T##4x4 out, T left, T right, T bottom, T top, T near, T far) {\
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

/// ## Predefined types
/// ```c
TM_VECTOR(int,    2)
TM_VECTOR(int,    3)
TM_VECTOR(int,    4)
TM_VECTOR(float,  2)
TM_VECTOR(float,  3)
TM_VECTOR(float,  4)
TM_VECTOR(double, 2)
TM_VECTOR(double, 3)
TM_VECTOR(double, 4)
TM_VECTOR_SPECIFIC(float)
TM_VECTOR_SPECIFIC(double)

TM_MATRIX(float,  3, 3)
TM_MATRIX(float,  4, 4)
TM_MATRIX(double, 3, 3)
TM_MATRIX(double, 4, 4)
TM_MATRIX_SPECIFIC(float)
TM_MATRIX_SPECIFIC(double)
///```

#endif // __tiny_math_h__

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
