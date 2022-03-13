#ifndef __tiny_math_h__
#define __tiny_math_h__

#include <math.h> // sin, cos, tan, sqrt

#ifndef TM_API
        #ifdef TM_NO_INLINE
                #define TM_API static
        #else
                #define TM_API static inline
        #endif
#endif

#ifndef TM
        #ifdef TM_NO_SHORT_NAMES
                #define TM(x) tm_##x
        #else
                #define TM(x) x
        #endif
#endif


#define TM_VECTOR(T, N)\
typedef T TM(T##N[N]);\
TM_API void TM(T##N##_add)(TM(T##N) out, TM(T##N) const a, TM(T##N) const b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] + b[_i];\
}\
TM_API void TM(T##N##_sub)(TM(T##N) out, TM(T##N) const a, TM(T##N) const b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] - b[_i];\
}\
TM_API void TM(T##N##_mul)(TM(T##N) out, TM(T##N) const a, TM(T##N) const b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] * b[_i];\
}\
TM_API void TM(T##N##_div)(TM(T##N) out, TM(T##N) const a, TM(T##N) const b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] / b[_i];\
}\
TM_API void TM(T##N##_adds)(TM(T##N) out, TM(T##N) const a, T b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] + b;\
}\
TM_API void TM(T##N##_subs)(TM(T##N) out, TM(T##N) const a, T b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] - b;\
}\
TM_API void TM(T##N##_muls)(TM(T##N) out, TM(T##N) const a, T b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] * b;\
}\
TM_API void TM(T##N##_divs)(TM(T##N) out, TM(T##N) const a, T b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] / b;\
}\
TM_API T TM(T##N##_dot)(TM(T##N) const a, TM(T##N) const b) {\
        T dot = 0;\
        for (int _i = 0; _i < N; _i++)\
                dot += a[_i] * b[_i];\
        return dot;\
}\
TM_API T TM(T##N##_mag2)(TM(T##N) const a) {\
        return T##N##_dot(a, a);\
}\
TM_API T TM(T##N##_mag)(TM(T##N) const a) {\
        return sqrt(T##N##_mag2(a));\
}\
TM_API void TM(T##N##_min)(TM(T##N) out, TM(T##N) const a, TM(T##N) const b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] < b[_i] ? a[_i] : b[_i];\
}\
TM_API void TM(T##N##_max)(TM(T##N) out, TM(T##N) const a, TM(T##N) const b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] > b[_i] ? a[_i] : b[_i];\
}\
TM_API void TM(T##N##_norm)(TM(T##N) out, TM(T##N) const a) {\
        T##N##_divs(out, a, T##N##_mag(a));\
}\
TM_API T TM(T##N##_min_component)(TM(T##N) const a) {\
        T min = a[0];\
        for (int _i = 1; _i < N; _i++)\
                min = a[_i] < min ? a[_i] : min;\
        return min;\
}\
TM_API T TM(T##N##_max_component)(TM(T##N) const a) {\
        T max = a[0];\
        for (int _i = 1; _i < N; _i++)\
                max = a[_i] > max ? a[_i] : max;\
        return max;\
}\

// Dimension specific vector functions
#define TM_VECTOR_SPECIFIC(T)\
TM_API void TM(T##3_cross)(TM(T##3) out, TM(T##3) const a, TM(T##3) const b) {\
        out[0] = a[1] * b[3] - a[3] * b[1];\
        out[1] = a[2] * b[0] - a[0] * b[2];\
        out[2] = a[0] * b[1] - a[1] * b[0];\
}

#define TM_MATRIX(T, R, C)\
typedef T TM(T##R##x##C[R][C]);\
TM_API void TM(T##R##x##C##_identity)(TM(T##R##x##C) out) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = (T)(_i == _j);\
}\
TM_API void TM(T##R##x##C##_add)(TM(T##R##x##C) out, TM(T##R##x##C) const a, TM(T##R##x##C) const b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] + b[_i][_j];\
}\
TM_API void TM(T##R##x##C##_sub)(TM(T##R##x##C) out, TM(T##R##x##C) const a, TM(T##R##x##C) const b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] - b[_i][_j];\
}\
TM_API void TM(T##R##x##C##_mul)(TM(T##R##x##C) out, TM(T##R##x##C) const a, TM(T##R##x##C) const b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] * b[_i][_j];\
}\
TM_API void TM(T##R##x##C##_div)(TM(T##R##x##C) out, TM(T##R##x##C) const a, TM(T##R##x##C) const b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] / b[_i][_j];\
}\
TM_API void TM(T##R##x##C##_adds)(TM(T##R##x##C) out, TM(T##R##x##C) const a, T b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] + b;\
}\
TM_API void TM(T##R##x##C##_subs)(TM(T##R##x##C) out, TM(T##R##x##C) const a, T b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] - b;\
}\
TM_API void TM(T##R##x##C##_muls)(TM(T##R##x##C) out, TM(T##R##x##C) const a, T b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] * b;\
}\
TM_API void TM(T##R##x##C##_divs)(TM(T##R##x##C) out, TM(T##R##x##C) const a, T b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] / b;\
}\

// Dimension specific matrix functions
#define TM_MATRIX_SPECIFIC(T)\
TM_API void TM(T##3x3_translate)(TM(T##3x3) out, TM(T##2) const v) {\
        TM(T##3x3_identity)(out);\
        out[2][0] = v[0];\
        out[2][1] = v[1];\
}\
TM_API void TM(T##3x3_rotate)(TM(T##3x3) out, T degrees) {\
        T c = cos(degrees * 0.0174533);\
        T s = sin(degrees * 0.0174533);\
        TM(T##3x3_identity)(out);\
        out[0][0] =  c;\
        out[0][1] =  s;\
        out[1][0] = -s;\
        out[1][1] =  c;\
        out[0][2] = out[1][2] = out[2][0] = out[2][1] = 0;\
        out[2][2] = 1.0;\
}\
TM_API void TM(T##3x3_scale)(TM(T##3x3) out, TM(T##2) const v) {\
        TM(T##3x3_identity)(out);\
        out[0][0] = v[0];\
        out[1][1] = v[1];\
}\
TM_API void TM(T##3x3_scale_uni)(TM(T##3x3) out, T s) {\
        TM(T##3x3_identity)(out);\
        out[0][0] = s;\
        out[1][1] = s;\
}\
TM_API void TM(T##4x4_translate)(TM(T##4x4) out, TM(T##3) const v) {\
        TM(T##4x4_identity)(out);\
        out[3][0] = v[0];\
        out[3][1] = v[1];\
        out[3][2] = v[2];\
        out[0][0] = out[1][1] = out[2][2] = out[3][3] = 1.0;\
}\
TM_API void TM(T##4x4_rotate)(TM(T##4x4) out, TM(T##3) const axis, T degrees) {\
        T c = cos(degrees * 0.0174533);\
        T s = sin(degrees * 0.0174533);\
        T t = 1.0 - c;\
        TM(T##3) an, at, as;\
        TM(T##3_norm)(an, axis);\
        TM(T##3_muls)(at, an, t);\
        TM(T##3_muls)(as, an, s);\
        TM(T##4x4_identity)(out);\
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
TM_API void TM(T##4x4_scale)(TM(T##4x4) out, TM(T##3) const v) {\
        TM(T##4x4_identity)(out);\
        out[0][0] = v[0];\
        out[1][1] = v[1];\
        out[2][2] = v[2];\
        out[3][3] = 1.0;\
}\
TM_API void TM(T##4x4_lookat)(TM(T##4x4) out, TM(T##3) const eye, TM(T##3) const target, TM(T##3) const up) {\
        TM(T##3) f, r, u;\
        TM(T##3_sub)(f, target, eye);\
        TM(T##3_norm)(f, f);\
        TM(T##3_cross)(r, f, up);\
        TM(T##3_norm)(r, r);\
        TM(T##3_cross)(u, r, f);\
        out[0][0] =  r[0];\
        out[0][1] =  u[0];\
        out[0][2] = -f[0];\
        out[1][0] =  r[1];\
        out[1][1] =  u[1];\
        out[1][2] = -f[1];\
        out[2][0] =  r[2];\
        out[2][1] =  u[2];\
        out[2][2] = -f[2];\
        out[3][1] = -TM(T##3_dot)(u, eye);\
        out[3][0] = -TM(T##3_dot)(r, eye);\
        out[3][2] = -TM(T##3_dot)(f, eye);\
}\
TM_API void TM(T##4x4_perspective)(TM(T##4x4) out, T fov_degrees, T aspect, T near, T far) {\
        T fov = 1.0 / tan(fov_degrees * 0.0174533 * 0.5);\
        T nf  = 1.0 / (near - far);\
        out[0][0] = fov / aspect;\
        out[1][1] = fov;\
        out[2][2] = (near + far) * nf;\
        out[2][3] = -1.0;\
        out[3][2] = 2.0 * near * far * nf;\
}\
TM_API void TM(T##4x4_ortho)(TM(T##4x4) out, T left, T right, T bottom, T top, T near, T far) {\
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

#endif // __tiny_math_h__
