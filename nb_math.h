/* nb_math.h - v0.06 - public domain
    A small C/C++ math library for game development

    Table of Contents
    -----------------
    Table of Contents
    Summary
    Usage
    Example
    Documentation
    Version History
    Licence

    Summary
    -------
    TODO

    Usage
    -----
    To use this library, do this in *one* C or C++ file:

        #define NB_MATH_IMPLEMENTATION
        #include "nb_math.h"

    Then include it as normal in all other files.

    Example
    -------
    #define NB_MATH_IMPLEMENTATION
    #include "nb_math.h"

    int main(void) {
        float3 a = {1.f, 0.f, 0.f};
        float3 b = {1.f, 1.f, 0.f};
        float3 c;

        float3_add(c, a, b); // c == {2.f, 1.f, 0.f}
    }

    Documentation
    -------------
    TODO

    Version History
    ---------------
    0.06  - Project name change
    0.05  - Changed naming style
    0.04  - Basic documentation
    0.03  - Added generator macros
    0.02  - Changed naming style
    0.01a - Syntax fixup
    0.01  - Initial version

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

#ifndef _nb_math_h_
#define _nb_math_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>

//////////////////////////////////////////////////////////////////////////////
//
// Types
//

typedef unsigned int uint;

#define NB_MATH_DEFINE_TYPE(T)\
typedef T T##2[2];\
typedef T T##3[3];\
typedef T T##4[4];

NB_MATH_DEFINE_TYPE(int)
NB_MATH_DEFINE_TYPE(uint)
NB_MATH_DEFINE_TYPE(float)
NB_MATH_DEFINE_TYPE(double)

typedef float float9[9];
typedef float float16[16];

typedef double double9[9];
typedef double double16[16];

//////////////////////////////////////////////////////////////////////////////
//
// Generic vector/matrix math ops (addition, subtraction, ...)
//

#define NB_MATH_DEFINE_OP(T, n, name, op)\
static inline void T##n##_##name(T##n out, T##n const a, T##n const b) {\
    for (int i = 0; i < n; i++)\
        out[i] = a[i] op b[i];\
}\
static inline void T##n##_##name##s(T##n out, T##n const a, T b) {\
    for (int i = 0; i < n; i++)\
        out[i] = a[i] op b;\
}\
static inline void T##n##_##name##eq(T##n out, T##n const a, T##n const b) {\
    for (int i = 0; i < n; i++)\
        out[i] op##= a[i] op b[i];\
}\
static inline void T##n##_##name##eqs(T##n out, T##n const a, T b) {\
    for (int i = 0; i < n; i++)\
        out[i] op##= a[i] op b;\
}

NB_MATH_DEFINE_OP(int, 2, add, +)
NB_MATH_DEFINE_OP(int, 2, sub, -)
NB_MATH_DEFINE_OP(int, 2, mul, *)
NB_MATH_DEFINE_OP(int, 2, div, /)
NB_MATH_DEFINE_OP(int, 3, add, +)
NB_MATH_DEFINE_OP(int, 3, sub, -)
NB_MATH_DEFINE_OP(int, 3, mul, *)
NB_MATH_DEFINE_OP(int, 3, div, /)
NB_MATH_DEFINE_OP(int, 4, add, +)
NB_MATH_DEFINE_OP(int, 4, sub, -)
NB_MATH_DEFINE_OP(int, 4, mul, *)
NB_MATH_DEFINE_OP(int, 4, div, /)

NB_MATH_DEFINE_OP(uint, 2, add, +)
NB_MATH_DEFINE_OP(uint, 2, sub, -)
NB_MATH_DEFINE_OP(uint, 2, mul, *)
NB_MATH_DEFINE_OP(uint, 2, div, /)
NB_MATH_DEFINE_OP(uint, 3, add, +)
NB_MATH_DEFINE_OP(uint, 3, sub, -)
NB_MATH_DEFINE_OP(uint, 3, mul, *)
NB_MATH_DEFINE_OP(uint, 3, div, /)
NB_MATH_DEFINE_OP(uint, 4, add, +)
NB_MATH_DEFINE_OP(uint, 4, sub, -)
NB_MATH_DEFINE_OP(uint, 4, mul, *)
NB_MATH_DEFINE_OP(uint, 4, div, /)

NB_MATH_DEFINE_OP(float,  2, add, +)
NB_MATH_DEFINE_OP(float,  2, sub, -)
NB_MATH_DEFINE_OP(float,  2, mul, *)
NB_MATH_DEFINE_OP(float,  2, div, /)
NB_MATH_DEFINE_OP(float,  3, add, +)
NB_MATH_DEFINE_OP(float,  3, sub, -)
NB_MATH_DEFINE_OP(float,  3, mul, *)
NB_MATH_DEFINE_OP(float,  3, div, /)
NB_MATH_DEFINE_OP(float,  4, add, +)
NB_MATH_DEFINE_OP(float,  4, sub, -)
NB_MATH_DEFINE_OP(float,  4, mul, *)
NB_MATH_DEFINE_OP(float,  4, div, /)
NB_MATH_DEFINE_OP(float,  9, add, +)
NB_MATH_DEFINE_OP(float,  9, sub, -)
NB_MATH_DEFINE_OP(float,  9, mul, *)
NB_MATH_DEFINE_OP(float,  9, div, /)
NB_MATH_DEFINE_OP(float, 16, add, +)
NB_MATH_DEFINE_OP(float, 16, sub, -)
NB_MATH_DEFINE_OP(float, 16, mul, *)
NB_MATH_DEFINE_OP(float, 16, div, /)

NB_MATH_DEFINE_OP(double,  2, add, +)
NB_MATH_DEFINE_OP(double,  2, sub, -)
NB_MATH_DEFINE_OP(double,  2, mul, *)
NB_MATH_DEFINE_OP(double,  2, div, /)
NB_MATH_DEFINE_OP(double,  3, add, +)
NB_MATH_DEFINE_OP(double,  3, sub, -)
NB_MATH_DEFINE_OP(double,  3, mul, *)
NB_MATH_DEFINE_OP(double,  3, div, /)
NB_MATH_DEFINE_OP(double,  4, add, +)
NB_MATH_DEFINE_OP(double,  4, sub, -)
NB_MATH_DEFINE_OP(double,  4, mul, *)
NB_MATH_DEFINE_OP(double,  4, div, /)
NB_MATH_DEFINE_OP(double,  9, add, +)
NB_MATH_DEFINE_OP(double,  9, sub, -)
NB_MATH_DEFINE_OP(double,  9, mul, *)
NB_MATH_DEFINE_OP(double,  9, div, /)
NB_MATH_DEFINE_OP(double, 16, add, +)
NB_MATH_DEFINE_OP(double, 16, sub, -)
NB_MATH_DEFINE_OP(double, 16, mul, *)
NB_MATH_DEFINE_OP(double, 16, div, /)

//////////////////////////////////////////////////////////////////////////////
//
// Generic vector functions
//

#define NB_MATH_DEFINE_VECTOR(T, n)\
static inline T T##n##_dot(T##n const a, T##n const b) {\
    T dot = a[0] * b[0];\
    for (int i = 1; i < n; i++)\
        dot += a[i] * b[i];\
    return dot;\
}\
static inline T T##n##_mag2(T##n const a) {\
    return T##n##_dot(a, a);\
}\
static inline T T##n##_mag(T##n const a) {\
    return sqrt(T##n##_mag2(a));\
}\
static inline void T##n##_min(T##n out, T##n const a, T##n const b) {\
    for (int i = 0; i < n; i++)\
        out[i] = a[i] < b[i] ? a[i] : b[i];\
}\
static inline void T##n##_max(T##n out, T##n const a, T##n const b) {\
    for (int i = 0; i < n; i++)\
        out[i] = a[i] > b[i] ? a[i] : b[i];\
}\
static inline void T##n##_norm(T##n out, T##n const a) {\
    T##n##_divs(out, a, T##n##_mag(a));\
}\
static inline T T##n##_min_val(T##n const a) {\
    T min = a[0];\
    for (int i = 1; i < n; i++)\
        min = a[i] < min ? a[i] : min;\
    return min;\
}\
static inline T T##n##_max_val(T##n const a) {\
    T max = a[0];\
    for (int i = 1; i < n; i++)\
        max = a[i] > max ? a[i] : max;\
    return max;\
}

NB_MATH_DEFINE_VECTOR(float,  2)
NB_MATH_DEFINE_VECTOR(float,  3)
NB_MATH_DEFINE_VECTOR(float,  4)
NB_MATH_DEFINE_VECTOR(double, 2)
NB_MATH_DEFINE_VECTOR(double, 3)
NB_MATH_DEFINE_VECTOR(double, 4)

//////////////////////////////////////////////////////////////////////////////
//
// Generic matrix functions
//

#define NB_MATH_DEFINE_MATRIX(T, n)\
static inline void T##n##_identity(T##n out) {\
    for (int i = 0; i < n; i++)\
        out[i] = (T)(i % n == i / n);\
}

NB_MATH_DEFINE_MATRIX(float,   9)
NB_MATH_DEFINE_MATRIX(float,  16)
NB_MATH_DEFINE_MATRIX(double,  9)
NB_MATH_DEFINE_MATRIX(double, 16)

//////////////////////////////////////////////////////////////////////////////
//
// Dimension specific vector functions
//

#define NB_MATH_DEFINE_VECTOR_SPECIFIC(T)\
static inline void T##2_rotate(T##2 out, T##2 const a, T degrees) {\
    T s = sin(degrees * 0.0174533);\
    T c = cos(degrees * 0.0174533);\
    out[0] = a[0] * c - a[1] * s;\
    out[1] = a[0] * s + a[1] * c;\
}\
static inline void T##3_cross(T##3 out, T##3 const a, T##3 const b) {\
    out[0] = a[1] * b[3] - a[3] * b[1];\
    out[1] = a[2] * b[0] - a[0] * b[2];\
    out[2] = a[0] * b[1] - a[1] * b[0];\
}

NB_MATH_DEFINE_VECTOR_SPECIFIC(float)
NB_MATH_DEFINE_VECTOR_SPECIFIC(double)

//////////////////////////////////////////////////////////////////////////////
//
// Dimension specific matrix functions
//

#define NB_MATH_DEFINE_MATRIX_SPECIFIC(T)\
static inline void T##9_translate(T##9 out, T##2 const v) {\
    T##9_identity(out);\
    out[6] = v[0];\
    out[7] = v[1];\
}\
static inline void T##9_rotate(T##9 out, T degrees) {\
    T s = sin(degrees * 0.0174533f);\
    T c = cos(degrees * 0.0174533f);\
    T##9 rot = {\
          c,   s, 0.f,\
         -s,   c, 0.f,\
        0.f, 0.f, 1.f,\
    };\
    T##9_copy(out, rot);\
}\
static inline void T##9_scale(T##9 out, T##2 const v) {\
    T##9_identity(out);\
    out[0] = v[0];\
    out[4] = v[1];\
}\
static inline void T##9_scale_uni(T##9 out, T s) {\
    T##9_identity(out);\
    out[0] = out[4] = s;\
}\
static inline void T##16_translate(T##16 out, T##3 const v) {\
    T##16_identity(out);\
    out[ 9] = v[0];\
    out[10] = v[1];\
    out[11] = v[2];\
}\
static inline void T##16_rotate(T##16 out, T##3 const axis, T degrees) {\
    T s = sin(degrees * 0.0174533);\
    T c = cos(degrees * 0.0174533);\
    T t = 1.0 - c;\
    T##3 an, at, as;\
    T##3_norm(an, axis);\
    T##3_muls(at, an, t);\
    T##3_muls(as, an, s);\
    T##16_identity(out);\
    out[ 0] = an[0] * at[0] + c;\
    out[ 1] = an[1] * at[0] + as[2];\
    out[ 2] = an[2] * at[0] - as[1];\
    out[ 4] = an[0] * at[1] - as[2];\
    out[ 5] = an[1] * at[1] + c;\
    out[ 6] = an[2] * at[1] + as[0];\
    out[ 8] = an[0] * at[2] + as[2];\
    out[ 9] = an[1] * at[2] + as[0];\
    out[10] = an[2] * at[2] + c;\
}\
static inline void T##16_rotate_x(T##16 out, T degrees) {\
    T s = sin(degrees * 0.0174533);\
    T c = cos(degrees * 0.0174533);\
    T##16 rot = {\
        1.f, 0.f, 0.f, 0.f,\
        0.f,   c,   s, 0.f,\
        0.f,  -s,   c, 0.f,\
        0.f, 0.f, 0.f, 1.f\
    };\
    T##16_copy(out, rot);\
}\
static inline void T##16_rotate_y(T##16 out, T degrees) {\
    T s = sin(degrees * 0.0174533);\
    T c = cos(degrees * 0.0174533);\
    T##16 rot = {\
          c, 0.f,  -s, 0.f,\
        0.f, 1.f, 0.f, 0.f,\
          s, 0.f,   c, 0.f,\
        0.f, 0.f, 0.f, 1.f\
    };\
    T##16_copy(out, rot);\
}\
static inline void T##16_rotate_z(T##16 out, T degrees) {\
    T s = sin(degrees * 0.0174533);\
    T c = cos(degrees * 0.0174533);\
    T##16 rot = {\
          c,   s, 0.f, 0.f,\
         -s,   c, 0.f, 0.f,\
        0.f, 0.f, 1.f, 0.f,\
        0.f, 0.f, 0.f, 1.f\
    };\
    T##16_copy(out, rot);\
}\
static inline void T##16_scale(T##16 out, T##3 const v) {\
    T##16_identity(out);\
    out[ 0] = v[0];\
    out[ 5] = v[1];\
    out[10] = v[2];\
}\
static inline void T##16_lookat(T##16 out, T##3 const eye, T##3 const target, T##3 const up) {\
    T##3 f, r, u;\
    T##3_sub(f, target, eye);\
    T##3_norm(f, f);\
    T##3_cross(r, f, up);\
    T##3_norm(r, r);\
    T##3_cross(u, r, f);\
    out[ 0] =  r[0];\
    out[ 1] =  u[0];\
    out[ 2] = -f[0];\
    out[ 4] =  r[1];\
    out[ 5] =  u[1];\
    out[ 6] = -f[1];\
    out[ 8] =  r[2];\
    out[ 9] =  u[2];\
    out[10] = -f[2];\
    out[12] = -T##3_dot(r, eye);\
    out[13] = -T##3_dot(u, eye);\
    out[14] = -T##3_dot(f, eye);\
}\
static inline void T##16_perspective(T##16 out, T fov_degrees, T aspect, T near, T far) {\
    T fov = 1.0 / tan(fov_degrees * 0.0174533 * 0.5);\
    T nf  = 1.0 / (near - far);\
    out[ 0] = fov / aspect;\
    out[ 5] = fov;\
    out[10] = (near + far) * nf;\
    out[11] = -1.0;\
    out[14] = 2.0 * near * far * nf;\
}\
static inline void T##16_ortho(T##16 out, T left, T right, T bottom, T top, T near, T far) {\
    T rl =  1.0 / (right - bottom);\
    T tb =  1.0 / (top - bottom);\
    T fn = -1.0 / (far - near);\
    out[ 0] = 2.0 * rl;\
    out[ 5] = 2.0 * tb;\
    out[10] = 2.0 * fn;\
    out[12] = -(right + left) * rl;\
    out[13] = -(top + bottom) * tb;\
    out[14] = -(far + near) * fn;\
    out[15] = 1.0;\
}

NB_MATH_DEFINE_MATRIX_SPECIFIC(float)
NB_MATH_DEFINE_MATRIX_SPECIFIC(double)

#undef NB_MATH_DEFINE_TYPE
#undef NB_MATH_DEFINE_OP
#undef NB_MATH_DEFINE_VECTOR
#undef NB_MATH_DEFINE_MATRIX
#undef NB_MATH_DEFINE_VECTOR_SPECIFIC
#undef NB_MATH_DEFINE_MATRIX_SPECIFIC

#endif // !_nb_math_h_
