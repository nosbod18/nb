/* axiom_math.h - OpenGL oriented math library - v0.06 - public domain

========================================================================================================================

	YOU MUST

		#define AXIOM_MATH_IMPL

	in EXACTLY _one_ C or C++ file that includes this header, BEFORE the
	include like this:

		#define AXIOM_MATH_IMPL
		#include "axiom_math.h"

	All other files should just #include "axiom_math.h" without the #define

========================================================================================================================

LICENSE
	This software is placed under the public domain. See the end of this file
    for the full license.

CREDITS
	Written by Evan Dobson

TODOS
    - Rect
    - AABB
    - Plane
    - Frustum
    - Ray
    - Quaternions
    - Documentation ( >:( )

VERSION HISTORY
    0.06  - Project name change
    0.05  - Changed naming style
    0.04  - Basic documentation
    0.03  - Added generator macros
    0.02  - Changed naming style
    0.01a - Syntax fixup
    0.01  - Initial version
*/

#ifndef AXIOM_MATH_H
#define AXIOM_MATH_H

#define GEN_VECTOR_HEADER(T, N)\
typedef T T##N[N];\
void T##N##_copy            (T##N out, T##N a);\
void T##N##_add             (T##N out, T##N const a, T##N const b);\
void T##N##_sub             (T##N out, T##N const a, T##N const b);\
void T##N##_mul             (T##N out, T##N const a, T##N const b);\
void T##N##_div             (T##N out, T##N const a, T##N const b);\
void T##N##_adds            (T##N out, T##N const a, T b);\
void T##N##_subs            (T##N out, T##N const a, T b);\
void T##N##_muls            (T##N out, T##N const a, T b);\
void T##N##_divs            (T##N out, T##N const a, T b);\
T    T##N##_dot             (T##N const a, T##N const b);\
T    T##N##_mag2            (T##N const a);\
T    T##N##_mag             (T##N const a);\
void T##N##_min             (T##N out, T##N const a, T##N const b);\
void T##N##_max             (T##N out, T##N const a, T##N const b);\
void T##N##_norm            (T##N out, T##N const a);\
T    T##N##_min_val         (T##N const a);\
T    T##N##_max_val         (T##N const a);

#define GEN_VECTOR_HEADER_SPECIFIC(T)\
void T##2_rotate            (T##2 out, T##2 const a, T degrees);\
void T##3_cross             (T##3 out, T##3 const a, T##3 const b);

#define GEN_MATRIX_HEADER(T, R, C)\
typedef T T##R##x##C[R][C];\
void T##R##x##C##_copy      (T##R##x##C out, T##R##x##C a);\
void T##R##x##C##_identity  (T##R##x##C out);\
void T##R##x##C##_add       (T##R##x##C out, T##R##x##C const a, T##R##x##C const b);\
void T##R##x##C##_sub       (T##R##x##C out, T##R##x##C const a, T##R##x##C const b);\
void T##R##x##C##_mul       (T##R##x##C out, T##R##x##C const a, T##R##x##C const b);\
void T##R##x##C##_div       (T##R##x##C out, T##R##x##C const a, T##R##x##C const b);\
void T##R##x##C##_adds      (T##R##x##C out, T##R##x##C const a, T b);\
void T##R##x##C##_subs      (T##R##x##C out, T##R##x##C const a, T b);\
void T##R##x##C##_muls      (T##R##x##C out, T##R##x##C const a, T b);\
void T##R##x##C##_divs      (T##R##x##C out, T##R##x##C const a, T b);\
void T##R##x##C##_addn      (T##R##x##C out, T##R##x##C const in[], int n);\
void T##R##x##C##_subn      (T##R##x##C out, T##R##x##C const in[], int n);\
void T##R##x##C##_muln      (T##R##x##C out, T##R##x##C const in[], int n);\
void T##R##x##C##_divn      (T##R##x##C out, T##R##x##C const in[], int n);

#define GEN_MATRIX_HEADER_SPECIFIC(T)\
void T##3x3_translate       (T##3x3 out, T##2 const v);\
void T##3x3_rotate          (T##3x3 out, T degrees);\
void T##3x3_scale           (T##3x3 out, T##2 const v);\
void T##3x3_scale_uni       (T##3x3 out, T s);\
void T##4x4_translate       (T##4x4 out, T##3 const v);\
void T##4x4_rotate          (T##4x4 out, T##3 const axis, T degrees);\
void T##4x4_rotate_x        (T##4x4 out, T degrees);\
void T##4x4_rotate_y        (T##4x4 out, T degrees);\
void T##4x4_rotate_z        (T##4x4 out, T degrees);\
void T##4x4_scale           (T##4x4 out, T##3 const v);\
void T##4x4_lookat          (T##4x4 out, T##3 const eye, T##3 const target, T##3 const up);\
void T##4x4_perspective     (T##4x4 out, T fov_degrees, T aspect, T near, T far);\
void T##4x4_ortho           (T##4x4 out, T left, T right, T bottom, T top, T near, T far);

GEN_VECTOR_HEADER(int,    2)
GEN_VECTOR_HEADER(int,    3)
GEN_VECTOR_HEADER(int,    4)
GEN_VECTOR_HEADER(float,  2)
GEN_VECTOR_HEADER(float,  3)
GEN_VECTOR_HEADER(float,  4)
GEN_VECTOR_HEADER(double, 2)
GEN_VECTOR_HEADER(double, 3)
GEN_VECTOR_HEADER(double, 4)
GEN_MATRIX_HEADER(float,  3, 3)
GEN_MATRIX_HEADER(float,  4, 4)
GEN_MATRIX_HEADER(double, 3, 3)
GEN_MATRIX_HEADER(double, 4, 4)
GEN_VECTOR_HEADER_SPECIFIC(float)
GEN_VECTOR_HEADER_SPECIFIC(double)
GEN_MATRIX_HEADER_SPECIFIC(float)
GEN_MATRIX_HEADER_SPECIFIC(double)

/***********************************************************************************************************************
************************************************************************************************************************
****                                                                                                               *****
****                                                                                                               *****
****                                                 Implementation                                                *****
****                                                                                                               *****
****                                                                                                               *****
************************************************************************************************************************
***********************************************************************************************************************/

#if defined(AXIOM_MATH_IMPL) || defined(AXIOM_IMPL)
#ifndef AXIOM_MATH_C_
#define AXIOM_MATH_C_

#include <math.h> // sin, cos, tan, sqrt

#define GEN_VECTOR_SOURCE(T, N)\
void T##N##_copy(T##N out, T##N a) {\
    for (int i = 0; i < N; i++)\
        out[i] = a[i];\
}\
void T##N##_add(T##N out, T##N const a, T##N const b) {\
    for (int i = 0; i < N; i++)\
        out[i] = a[i] + b[i];\
}\
void T##N##_sub(T##N out, T##N const a, T##N const b) {\
    for (int i = 0; i < N; i++)\
        out[i] = a[i] - b[i];\
}\
void T##N##_mul(T##N out, T##N const a, T##N const b) {\
    for (int i = 0; i < N; i++)\
        out[i] = a[i] * b[i];\
}\
void T##N##_div(T##N out, T##N const a, T##N const b) {\
    for (int i = 0; i < N; i++)\
        out[i] = a[i] / b[i];\
}\
void T##N##_adds(T##N out, T##N const a, T b) {\
    for (int i = 0; i < N; i++)\
        out[i] = a[i] + b;\
}\
void T##N##_subs(T##N out, T##N const a, T b) {\
    for (int i = 0; i < N; i++)\
        out[i] = a[i] - b;\
}\
void T##N##_muls(T##N out, T##N const a, T b) {\
    for (int i = 0; i < N; i++)\
        out[i] = a[i] * b;\
}\
void T##N##_divs(T##N out, T##N const a, T b) {\
    for (int i = 0; i < N; i++)\
        out[i] = a[i] / b;\
}\
T T##N##_dot(T##N const a, T##N const b) {\
    T dot = 0;\
    for (int i = 0; i < N; i++)\
        dot += a[i] * b[i];\
    return dot;\
}\
T T##N##_mag2(T##N const a) {\
    return T##N##_dot(a, a);\
}\
T T##N##_mag(T##N const a) {\
    return sqrt(T##N##_mag2(a));\
}\
void T##N##_min(T##N out, T##N const a, T##N const b) {\
    for (int i = 0; i < N; i++)\
        out[i] = a[i] < b[i] ? a[i] : b[i];\
}\
void T##N##_max(T##N out, T##N const a, T##N const b) {\
    for (int i = 0; i < N; i++)\
        out[i] = a[i] > b[i] ? a[i] : b[i];\
}\
void T##N##_norm(T##N out, T##N const a) {\
    T##N##_divs(out, a, T##N##_mag(a));\
}\
T T##N##_min_val(T##N const a) {\
    T min = a[0];\
    for (int i = 1; i < N; i++)\
        min = a[i] < min ? a[i] : min;\
    return min;\
}\
T T##N##_max_val(T##N const a) {\
    T max = a[0];\
    for (int i = 1; i < N; i++)\
        max = a[i] > max ? a[i] : max;\
    return max;\
}\

#define GEN_VECTOR_SOURCE_SPECIFIC(T)\
void T##2_rotate(T##2 out, T##2 const a, T degrees) {\
    T s = sin(degrees * 0.0174533);\
    T c = cos(degrees * 0.0174533);\
    out[0] = a[0] * c - a[1] * s;\
    out[1] = a[0] * s + a[1] * c;\
}\
void T##3_cross(T##3 out, T##3 const a, T##3 const b) {\
    out[0] = a[1] * b[3] - a[3] * b[1];\
    out[1] = a[2] * b[0] - a[0] * b[2];\
    out[2] = a[0] * b[1] - a[1] * b[0];\
}

#define GEN_MATRIX_SOURCE(T, R, C)\
void T##R##x##C##_copy(T##R##x##C out, T##R##x##C a) {\
    for (int i = 0; i < N; i++)\
        for (int j = 0; j < C; j++)\
            out[i][j] = a[i][j];\
}\
void T##R##x##C##_identity(T##R##x##C out) {\
    for (int i = 0; i < R; i++)\
        for (int j = 0; j < C; j++)\
            out[i][j] = (T)(i == j);\
}\
void T##R##x##C##_add(T##R##x##C out, T##R##x##C const a, T##R##x##C const b) {\
    for (int i = 0; i < R; i++)\
        for (int j = 0; j < C; j++)\
            out[i][j] = a[i][j] + b[i][j];\
}\
void T##R##x##C##_sub(T##R##x##C out, T##R##x##C const a, T##R##x##C const b) {\
    for (int i = 0; i < R; i++)\
        for (int j = 0; j < C; j++)\
            out[i][j] = a[i][j] - b[i][j];\
}\
void T##R##x##C##_mul(T##R##x##C out, T##R##x##C const a, T##R##x##C const b) {\
    for (int i = 0; i < R; i++)\
        for (int j = 0; j < C; j++)\
            out[i][j] = a[i][j] * b[i][j];\
}\
void T##R##x##C##_div(T##R##x##C out, T##R##x##C const a, T##R##x##C const b) {\
    for (int i = 0; i < R; i++)\
        for (int j = 0; j < C; j++)\
            out[i][j] = a[i][j] / b[i][j];\
}\
void T##R##x##C##_adds(T##R##x##C out, T##R##x##C const a, T b) {\
    for (int i = 0; i < R; i++)\
        for (int j = 0; j < C; j++)\
            out[i][j] = a[i][j] + b;\
}\
void T##R##x##C##_subs(T##R##x##C out, T##R##x##C const a, T b) {\
    for (int i = 0; i < R; i++)\
        for (int j = 0; j < C; j++)\
            out[i][j] = a[i][j] - b;\
}\
void T##R##x##C##_muls(T##R##x##C out, T##R##x##C const a, T b) {\
    for (int i = 0; i < R; i++)\
        for (int j = 0; j < C; j++)\
            out[i][j] = a[i][j] * b;\
}\
void T##R##x##C##_divs(T##R##x##C out, T##R##x##C const a, T b) {\
    for (int i = 0; i < R; i++)\
        for (int j = 0; j < C; j++)\
            out[i][j] = a[i][j] / b;\
}\
void T##R##x##C##_addn(T##R##x##C out, T##R##x##C const in[], int n) {\
    for (int i = 0; i < n; i++)\
        T##R##x##C##_add(out, out, in[i]);\
}\
void T##R##x##C##_subn(T##R##x##C out, T##R##x##C const in[], int n) {\
    for (int i = 0; i < n; i++)\
        T##R##x##C##_sub(out, out, in[i]);\
}\
void T##R##x##C##_muln(T##R##x##C out, T##R##x##C const in[], int n) {\
    for (int i = 0; i < n; i++)\
        T##R##x##C##_mul(out, out, in[i]);\
}\
void T##R##x##C##_divn(T##R##x##C out, T##R##x##C const in[], int n) {\
    for (int i = 0; i < n; i++)\
        T##R##x##C##_div(out, out, in[i]);\
}\

#define GEN_MATRIX_SOURCE_SPECIFIC(T)\
void T##3x3_translate(T##3x3 out, T##2 const v) {\
    T##3x3_identity(out);\
    out[2][0] = v[0];\
    out[2][1] = v[1];\
}\
void T##3x3_rotate(T##3x3 out, T degrees) {\
    T c = cos(degrees * 0.0174533);\
    T s = sin(degrees * 0.0174533);\
    T##3x3_identity(out);\
    out[0][0] =  c;\
    out[0][1] =  s;\
    out[1][0] = -s;\
    out[1][1] =  c;\
    out[0][2] = out[1][2] = out[2][0] = out[2][1] = 0;\
    out[2][2] = 1.0;\
}\
void T##3x3_scale(T##3x3 out, T##2 const v) {\
    T##3x3_identity(out);\
    out[0][0] = v[0];\
    out[1][1] = v[1];\
}\
void T##3x3_scale_uni(T##3x3 out, T s) {\
    T##3x3_identity(out);\
    out[0][0] = s;\
    out[1][1] = s;\
}\
void T##4x4_translate(T##4x4 out, T##3 const v) {\
    T##4x4_identity(out);\
    out[3][0] = v[0];\
    out[3][1] = v[1];\
    out[3][2] = v[2];\
    out[0][0] = out[1][1] = out[2][2] = out[3][3] = 1.0;\
}\
void T##4x4_rotate(T##4x4 out, T##3 const axis, T degrees) {\
    T c = cos(degrees * 0.0174533);\
    T s = sin(degrees * 0.0174533);\
    T t = 1.0 - c;\
    T##3 an, at, as;\
    T##3_norm(an, axis);\
    T##3_muls(at, an, t);\
    T##3_muls(as, an, s);\
    T##4x4_identity(out);\
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
void T##4x4_rotate_x(T##4x4 out, T degrees) {\
    T s = sin(degrees * 0.0174533);\
    T c = cos(degrees * 0.0174533);\
    T##4x4 rot = {\
        {1.f, 0.f, 0.f, 0.f},\
        {0.f,   c,   s, 0.f},\
        {0.f,  -s,   c, 0.f},\
        {0.f, 0.f, 0.f, 1.f}\
    };\
    T##4x4_copy(out, rot);\
}\
void T##4x4_rotate_y(T##4x4 out, T degrees) {\
    T s = sin(degrees * 0.0174533);\
    T c = cos(degrees * 0.0174533);\
    T##4x4 rot = {\
        {   c, 0.f,  -s, 0.f},\
        { 0.f, 1.f, 0.f, 0.f},\
        {   s, 0.f,   c, 0.f},\
        { 0.f, 0.f, 0.f, 1.f}\
    };\
    T##4x4_copy(out, rot);\
}\
void T##4x4_rotate_z(T##4x4 out, T degrees) {\
    T s = sin(degrees * 0.0174533);\
    T c = cos(degrees * 0.0174533);\
    T##4x4 rot = {\
        {   c,   s, 0.f, 0.f},\
        {  -s,   c, 0.f, 0.f},\
        { 0.f, 0.f, 1.f, 0.f},\
        { 0.f, 0.f, 0.f, 1.f}\
    };\
    T##4x4_copy(out, rot);\
}\
void T##4x4_scale(T##4x4 out, T##3 const v) {\
    T##4x4_identity(out);\
    out[0][0] = v[0];\
    out[1][1] = v[1];\
    out[2][2] = v[2];\
    out[3][3] = 1.0;\
}\
void T##4x4_lookat(T##4x4 out, T##3 const eye, T##3 const target, T##3 const up) {\
    T##3 f, r, u;\
    T##3_sub(f, target, eye);\
    T##3_norm(f, f);\
    T##3_cross(r, f, up);\
    T##3_norm(r, r);\
    T##3_cross(u, r, f);\
    out[0][0] =  r[0];\
    out[0][1] =  u[0];\
    out[0][2] = -f[0];\
    out[1][0] =  r[1];\
    out[1][1] =  u[1];\
    out[1][2] = -f[1];\
    out[2][0] =  r[2];\
    out[2][1] =  u[2];\
    out[2][2] = -f[2];\
    out[3][1] = -T##3_dot(u, eye);\
    out[3][0] = -T##3_dot(r, eye);\
    out[3][2] = -T##3_dot(f, eye);\
}\
void T##4x4_perspective(T##4x4 out, T fov_degrees, T aspect, T near, T far) {\
    T fov = 1.0 / tan(fov_degrees * 0.0174533 * 0.5);\
    T nf  = 1.0 / (near - far);\
    out[0][0] = fov / aspect;\
    out[1][1] = fov;\
    out[2][2] = (near + far) * nf;\
    out[2][3] = -1.0;\
    out[3][2] = 2.0 * near * far * nf;\
}\
void T##4x4_ortho(T##4x4 out, T left, T right, T bottom, T top, T near, T far) {\
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

GEN_VECTOR_SOURCE(int,    2)
GEN_VECTOR_SOURCE(int,    3)
GEN_VECTOR_SOURCE(int,    4)
GEN_VECTOR_SOURCE(float,  2)
GEN_VECTOR_SOURCE(float,  3)
GEN_VECTOR_SOURCE(float,  4)
GEN_VECTOR_SOURCE(double, 2)
GEN_VECTOR_SOURCE(double, 3)
GEN_VECTOR_SOURCE(double, 4)
GEN_VECTOR_SOURCE_SPECIFIC(float)
GEN_VECTOR_SOURCE_SPECIFIC(double)

GEN_MATRIX_SOURCE(float,  3, 3)
GEN_MATRIX_SOURCE(float,  4, 4)
GEN_MATRIX_SOURCE(double, 3, 3)
GEN_MATRIX_SOURCE(double, 4, 4)
GEN_MATRIX_SOURCE_SPECIFIC(float)
GEN_MATRIX_SOURCE_SPECIFIC(double)


#endif // !AXIOM_MATH_C_
#endif // AXIOM_MATH_IMPL || AXIOM_IMPL
#endif // !AXIOM_MATH_H_

/// ## License
/// This is free and unencumbered software released into the public domain.
/// Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
/// software, either in source code form or as a compiled binary, for any purpose,
/// commercial or non-commercial, and by any means.
///
/// In jurisdictions that recognize copyright laws, the author or authors of this
/// software dedicate any and all copyright interest in the software to the public
/// domain. We make this dedication for the benefit of the public at large and to
/// the detriment of our heirs and successors. We intend this dedication to be an
/// overt act of relinquishment in perpetuity of all present and future rights to
/// this software under copyright law.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
/// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
/// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///
/// For more information, please refer to <http://unlicense.org/>
