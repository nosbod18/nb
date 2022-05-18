/* nb_math.h - v0.06 - public domain
    A C/C++ math library for game development

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
    TODO

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

#define NBM_GEN_VECTOR_HEADER(n)\
    typedef float nbm_vec##n[n];\
    float nbm_vec##n##_dot      (nbm_vec##n const a, nbm_vec##n const b);\
    float nbm_vec##n##_mag2     (nbm_vec##n const a);\
    float nbm_vec##n##_mag      (nbm_vec##n const a);\
    void  nbm_vec##n##_min      (nbm_vec##n out, nbm_vec##n const a, nbm_vec##n const b);\
    void  nbm_vec##n##_max      (nbm_vec##n out, nbm_vec##n const a, nbm_vec##n const b);\
    void  nbm_vec##n##_norm     (nbm_vec##n out, nbm_vec##n const a);\
    float nbm_vec##n##_min_val  (nbm_vec##n const a);\
    float nbm_vec##n##_max_val  (nbm_vec##n const a);

NBM_GEN_VECTOR_HEADER(2)
NBM_GEN_VECTOR_HEADER(3)
NBM_GEN_VECTOR_HEADER(4)

#define NBM_GEN_MATRIX_HEADER(n)\
    typedef float nbm_mat##n[n * n];\
    void nbm_mat##n##_identity  (nbm_mat##n out);\

NBM_GEN_MATRIX_HEADER(3)
NBM_GEN_MATRIX_HEADER(4)

#define NBM_GEN_COMMON_HEADER(name, n)\
    void nbm_##name##n##_copy   (nbm_##name##n out, nbm_##name##n a);\
    void nbm_##name##n##_add    (nbm_##name##n out, nbm_##name##n const a, nbm_##name##n const b);\
    void nbm_##name##n##_sub    (nbm_##name##n out, nbm_##name##n const a, nbm_##name##n const b);\
    void nbm_##name##n##_mul    (nbm_##name##n out, nbm_##name##n const a, nbm_##name##n const b);\
    void nbm_##name##n##_div    (nbm_##name##n out, nbm_##name##n const a, nbm_##name##n const b);\
    void nbm_##name##n##_adds   (nbm_##name##n out, nbm_##name##n const a, float b);\
    void nbm_##name##n##_subs   (nbm_##name##n out, nbm_##name##n const a, float b);\
    void nbm_##name##n##_muls   (nbm_##name##n out, nbm_##name##n const a, float b);\
    void nbm_##name##n##_divs   (nbm_##name##n out, nbm_##name##n const a, float b);

NBM_GEN_COMMON_HEADER(vec, 2)
NBM_GEN_COMMON_HEADER(vec, 3)
NBM_GEN_COMMON_HEADER(vec, 4)
NBM_GEN_COMMON_HEADER(mat, 3)
NBM_GEN_COMMON_HEADER(mat, 4)


void nbm_vec2_rotate        (nbm_vec2 out, nbm_vec2 const a, float degrees);
void nbm_vec3_cross         (nbm_vec3 out, nbm_vec3 const a, nbm_vec3 const b);

void nbm_mat3_translate     (nbm_mat3 out, nbm_vec2 const v);
void nbm_mat3_rotate        (nbm_mat3 out, float degrees);
void nbm_mat3_scale         (nbm_mat3 out, nbm_vec2 const v);
void nbm_mat3_scale_uni     (nbm_mat3 out, float s);
void nbm_mat4_translate     (nbm_mat4 out, nbm_vec3 const v);
void nbm_mat4_rotate        (nbm_mat4 out, nbm_vec3 const axis, float degrees);
void nbm_mat4_rotate_x      (nbm_mat4 out, float degrees);
void nbm_mat4_rotate_y      (nbm_mat4 out, float degrees);
void nbm_mat4_rotate_z      (nbm_mat4 out, float degrees);
void nbm_mat4_scale         (nbm_mat4 out, nbm_vec3 const v);
void nbm_mat4_lookat        (nbm_mat4 out, nbm_vec3 const eye, nbm_vec3 const target, nbm_vec3 const up);
void nbm_mat4_perspective   (nbm_mat4 out, float fov_degrees, float aspect, float near, float far);
void nbm_mat4_ortho         (nbm_mat4 out, float left, float right, float bottom, float top, float near, float far);

#undef NBM_GEN_VECTOR_HEADER
#undef NBM_GEN_MATRIX_HEADER
#undef NBM_GEN_COMMON_HEADER

#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
************************************************************************************************************************
****                                                                                                               *****
****                                                                                                               *****
****                                                 Implementation                                                *****
****                                                                                                               *****
****                                                                                                               *****
************************************************************************************************************************
***********************************************************************************************************************/

#if defined(NB_MATH_IMPLEMENTATION) || defined(NB_IMPLEMENTATION)
#ifndef _nb_math_c_
#define _nb_math_c_

#ifndef nbm_sin
    #ifdef nb_sin
        #define nbm_sin nb_sin
    #else
        #include <math.h>
        #define nbm_sin sinf
    #endif
#endif

#ifndef nbm_cos
    #ifdef nb_cos
        #define nbm_cos nb_cos
    #else
        #include <math.h>
        #define nbm_cos cosf
    #endif
#endif

#ifndef nbm_tan
    #ifdef nb_tan
        #define nbm_tan nb_tan
    #else
        #include <math.h>
        #define nbm_tan tanf
    #endif
#endif

#ifndef nbm_sqrt
    #ifdef nb_sqrt
        #define nbm_sqrt nb_sqrt
    #else
        #include <math.h>
        #define nbm_sqrt sqrtf
    #endif
#endif

#define NBM_GEN_VECTOR_SOURCE(n)\
    float nbm_vec##n##_dot(nbm_vec##n const a, nbm_vec##n const b) {\
        float dot = 0;\
        for (int i = 0; i < n; i++)\
            dot += a[i] * b[i];\
        return dot;\
    }\
    float nbm_vec##n##_mag2(nbm_vec##n const a) {\
        return nbm_vec##n##_dot(a, a);\
    }\
    float nbm_vec##n##_mag(nbm_vec##n const a) {\
        return nbm_sqrt(nbm_vec##n##_mag2(a));\
    }\
    void nbm_vec##n##_min(nbm_vec##n out, nbm_vec##n const a, nbm_vec##n const b) {\
        for (int i = 0; i < n; i++)\
            out[i] = a[i] < b[i] ? a[i] : b[i];\
    }\
    void nbm_vec##n##_max(nbm_vec##n out, nbm_vec##n const a, nbm_vec##n const b) {\
        for (int i = 0; i < n; i++)\
            out[i] = a[i] > b[i] ? a[i] : b[i];\
    }\
    void nbm_vec##n##_norm(nbm_vec##n out, nbm_vec##n const a) {\
        nbm_vec##n##_divs(out, a, nbm_vec##n##_mag(a));\
    }\
    float nbm_vec##n##_min_val(nbm_vec##n const a) {\
        float min = a[0];\
        for (int i = 1; i < n; i++)\
            min = a[i] < min ? a[i] : min;\
        return min;\
    }\
    float nbm_vec##n##_max_val(nbm_vec##n const a) {\
        float max = a[0];\
        for (int i = 1; i < n; i++)\
            max = a[i] > max ? a[i] : max;\
        return max;\
    }

NBM_GEN_VECTOR_SOURCE(2)
NBM_GEN_VECTOR_SOURCE(3)
NBM_GEN_VECTOR_SOURCE(4)

#define NBM_GEN_MATRIX_SOURCE(n)\
    void nbm_mat##n##_identity(nbm_mat##n out) {\
        for (int i = 0; i < n; i++)\
            out[i] = (float)(i % n == i / n);\
    }

NBM_GEN_MATRIX_SOURCE(3)
NBM_GEN_MATRIX_SOURCE(4)

#define NBM_GEN_COMMON_SOURCE(name, n)\
    void nbm_##name##n##_copy(nbm_##name##n out, nbm_##name##n a) {\
        for (int i = 0; i < n; i++)\
            out[i] = a[i];\
    }\
    void nbm_##name##n##_add(nbm_##name##n out, nbm_##name##n const a, nbm_##name##n const b) {\
        for (int i = 0; i < n; i++)\
            out[i] = a[i] + b[i];\
    }\
    void nbm_##name##n##_sub(nbm_##name##n out, nbm_##name##n const a, nbm_##name##n const b) {\
        for (int i = 0; i < n; i++)\
            out[i] = a[i] - b[i];\
    }\
    void nbm_##name##n##_mul(nbm_##name##n out, nbm_##name##n const a, nbm_##name##n const b) {\
        for (int i = 0; i < n; i++)\
            out[i] = a[i] * b[i];\
    }\
    void nbm_##name##n##_div(nbm_##name##n out, nbm_##name##n const a, nbm_##name##n const b) {\
        for (int i = 0; i < n; i++)\
            out[i] = a[i] / b[i];\
    }\
    void nbm_##name##n##_adds(nbm_##name##n out, nbm_##name##n const a, float b) {\
        for (int i = 0; i < n; i++)\
            out[i] = a[i] + b;\
    }\
    void nbm_##name##n##_subs(nbm_##name##n out, nbm_##name##n const a, float b) {\
        for (int i = 0; i < n; i++)\
            out[i] = a[i] - b;\
    }\
    void nbm_##name##n##_muls(nbm_##name##n out, nbm_##name##n const a, float b) {\
        for (int i = 0; i < n; i++)\
            out[i] = a[i] * b;\
    }\
    void nbm_##name##n##_divs(nbm_##name##n out, nbm_##name##n const a, float b) {\
        for (int i = 0; i < n; i++)\
            out[i] = a[i] / b;\
    }

NBM_GEN_COMMON_SOURCE(vec, 2)
NBM_GEN_COMMON_SOURCE(vec, 3)
NBM_GEN_COMMON_SOURCE(vec, 4)
NBM_GEN_COMMON_SOURCE(mat, 3)
NBM_GEN_COMMON_SOURCE(mat, 4)


void nbm_vec2_rotate(nbm_vec2 out, nbm_vec2 const a, float degrees) {
    float s = nbm_sin(degrees * 0.0174533);
    float c = nbm_cos(degrees * 0.0174533);
    out[0] = a[0] * c - a[1] * s;
    out[1] = a[0] * s + a[1] * c;
}

void nbm_vec3_cross(nbm_vec3 out, nbm_vec3 const a, nbm_vec3 const b) {
    out[0] = a[1] * b[3] - a[3] * b[1];
    out[1] = a[2] * b[0] - a[0] * b[2];
    out[2] = a[0] * b[1] - a[1] * b[0];
}

void nbm_mat3_translate(nbm_mat3 out, nbm_vec2 const v) {
    nbm_mat3_identity(out);
    out[6] = v[0];
    out[7] = v[1];
}

void nbm_mat3_rotate(nbm_mat3 out, float degrees) {
    float s = nbm_sin(degrees * 0.0174533f);
    float c = nbm_cos(degrees * 0.0174533f);
    nbm_mat3 rot = {
          c,   s, 0.f,
         -s,   c, 0.f,
        0.f, 0.f, 1.f,
    };
    nbm_mat3_copy(out, rot);
}

void nbm_mat3_scale(nbm_mat3 out, nbm_vec2 const v) {
    nbm_mat3_identity(out);
    out[0] = v[0];
    out[4] = v[1];
}

void nbm_mat3_scale_uni(nbm_mat3 out, float s) {
    nbm_mat3_identity(out);
    out[0] = s;
    out[4] = s;
}

void nbm_mat4_translate(nbm_mat4 out, nbm_vec3 const v) {
    nbm_mat4_identity(out);
    out[ 9] = v[0];
    out[10] = v[1];
    out[11] = v[2];
}

void nbm_mat4_rotate(nbm_mat4 out, nbm_vec3 const axis, float degrees) {
    float c = nbm_cos(degrees * 0.0174533);
    float s = nbm_sin(degrees * 0.0174533);
    float t = 1.0 - c;
    nbm_vec3 an, at, as;
    nbm_vec3_norm(an, axis);
    nbm_vec3_muls(at, an, t);
    nbm_vec3_muls(as, an, s);
    nbm_mat4_identity(out);
    out[ 0] = an[0] * at[0] + c;
    out[ 1] = an[1] * at[0] + as[2];
    out[ 2] = an[2] * at[0] - as[1];
    out[ 4] = an[0] * at[1] - as[2];
    out[ 5] = an[1] * at[1] + c;
    out[ 6] = an[2] * at[1] + as[0];
    out[ 8] = an[0] * at[2] + as[2];
    out[ 9] = an[1] * at[2] + as[0];
    out[10] = an[2] * at[2] + c;
}

void nbm_mat4_rotate_x(nbm_mat4 out, float degrees) {
    float s = nbm_sin(degrees * 0.0174533);
    float c = nbm_cos(degrees * 0.0174533);
    nbm_mat4 rot = {
        1.f, 0.f, 0.f, 0.f,
        0.f,   c,   s, 0.f,
        0.f,  -s,   c, 0.f,
        0.f, 0.f, 0.f, 1.f
    };
    nbm_mat4_copy(out, rot);
}

void nbm_mat4_rotate_y(nbm_mat4 out, float degrees) {
    float s = nbm_sin(degrees * 0.0174533);
    float c = nbm_cos(degrees * 0.0174533);
    nbm_mat4 rot = {
          c, 0.f,  -s, 0.f,
        0.f, 1.f, 0.f, 0.f,
          s, 0.f,   c, 0.f,
        0.f, 0.f, 0.f, 1.f
    };
    nbm_mat4_copy(out, rot);
}

void nbm_mat4_rotate_z(nbm_mat4 out, float degrees) {
    float s = nbm_sin(degrees * 0.0174533);
    float c = nbm_cos(degrees * 0.0174533);
    nbm_mat4 rot = {
          c,   s, 0.f, 0.f,
         -s,   c, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    };
    nbm_mat4_copy(out, rot);
}

void nbm_mat4_scale(nbm_mat4 out, nbm_vec3 const v) {
    nbm_mat4_identity(out);
    out[ 0] = v[0];
    out[ 5] = v[1];
    out[10] = v[2];
}

void nbm_mat4_lookat(nbm_mat4 out, nbm_vec3 const eye, nbm_vec3 const target, nbm_vec3 const up) {
    nbm_vec3 f, r, u;
    nbm_vec3_sub(f, target, eye);
    nbm_vec3_norm(f, f);
    nbm_vec3_cross(r, f, up);
    nbm_vec3_norm(r, r);
    nbm_vec3_cross(u, r, f);
    out[ 0] =  r[0];
    out[ 1] =  u[0];
    out[ 2] = -f[0];
    out[ 4] =  r[1];
    out[ 5] =  u[1];
    out[ 6] = -f[1];
    out[ 8] =  r[2];
    out[ 9] =  u[2];
    out[10] = -f[2];
    out[12] = -nbm_vec3_dot(r, eye);
    out[13] = -nbm_vec3_dot(u, eye);
    out[14] = -nbm_vec3_dot(f, eye);
}

void nbm_mat4_perspective(nbm_mat4 out, float fov_degrees, float aspect, float near, float far) {
    float fov = 1.0 / nbm_tan(fov_degrees * 0.0174533 * 0.5);
    float nf  = 1.0 / (near - far);
    out[ 0] = fov / aspect;
    out[ 5] = fov;
    out[10] = (near + far) * nf;
    out[11] = -1.0;
    out[14] = 2.0 * near * far * nf;
}

void nbm_mat4_ortho(nbm_mat4 out, float left, float right, float bottom, float top, float near, float far) {
    float rl =  1.0 / (right - bottom);
    float tb =  1.0 / (top - bottom);
    float fn = -1.0 / (far - near);
    out[ 0] = 2.0 * rl;
    out[ 5] = 2.0 * tb;
    out[10] = 2.0 * fn;
    out[12] = -(right + left) * rl;
    out[13] = -(top + bottom) * tb;
    out[14] = -(far + near) * fn;
    out[15] = 1.0;
}

#undef NBM_GEN_COMMON_SOURCE
#undef NBM_GEN_VECTOR_SOURCE
#undef NBM_GEN_MATRIX_SOURCE

#endif // !_nb_math_c_
#endif // NB_MATH_IMPLEMENTATION || NB_IMPLEMENTATION
#endif // !NB_MATH_H_
