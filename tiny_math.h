/// # tiny_math.h
/// A header only vector and matrix math library. Depends on `<math.h>` for `sin`, `cos`, `tan`, `sqrt` only.
///
/// ## Note
/// All types defined in this library are nothing more that `typedef`'d arrays, and as such new ones cannot be returned from functions.
/// An `out` variable must be provided to each function where the result is a vector.


#ifndef __tiny_math_h__
#define __tiny_math_h__

#include <math.h> // sin, cos, tan, sqrt

/// ## Defines

/// #### `TM_NO_INLINE`
/// If `TM_NO_INLINE` is defined, inlining won't be done on the functions. `TM_FUNC` can also be defined to whatever the user wants
/// if a custom function scoping or attribute is wanted.
#ifndef TM_FUNC
        #ifdef TM_NO_INLINE
                #define TM_FUNC static
        #else
                #define TM_FUNC static inline
        #endif
#endif

/// #### `TM_NO_SHORT_NAMES`
/// If `TM_NO_SHORT_NAMES` is defined, each type and function will have the tm_ prefix. This is useful if a function or type
/// has a naming conflict with another type or function in the project. Alternatively, the user can define `TM_PREFIX` to create a custom
/// naming prefix, so long as it is of the form `#define TM_PREFIX(x) CUSTOM_PREFIX##x`.
#ifndef TM_PREFIX
        #ifdef TM_NO_SHORT_NAMES
                #define TM_PREFIX(x) tm_##x
        #else
                #define TM_PREFIX(x) x
        #endif
#endif

/// ## Vector
/// A vector is defined by the type and number of elements it holds. For example, a vector of 3 floats would be `float3`. Generally, a vector
/// of type T that holds N elements is defined as `TN`.
///
/// ### API
/// ```c
/// void TN_copy   (TN out, TN a)
/// void TN_add    (TN out, TN a, TN b)
/// void TN_sub    (TN out, TN a, TN b)
/// void TN_mul    (TN out, TN a, TN b)
/// void TN_div    (TN out, TN a, TN b)
/// void TN_adds   (TN out, TN a, T b)
/// void TN_subs   (TN out, TN a, T b)
/// void TN_muls   (TN out, TN a, T b)
/// void TN_divs   (TN out, TN a, T b)
/// T    TN_dot    (TN a, TN b)
/// T    TN_mag2   (TN a) // Returns the magnitude of `a` squared
/// T    TN_mag    (TN a)
/// T    TN_min_val(TN a) // Returns the smallest component of `a`
/// T    TN_max_val(TN a) // Returns the largets component of `a`
/// void TN_min    (Tout, TN a, TN b)
/// void TN_max    (Tout, TN a, TN b)
/// void TN_norm   (Tout, TN a, TN b)
/// ```
#define TM_VECTOR(T, N)\
typedef T TM_PREFIX(T##N[N]);\
TM_FUNC void TM_PREFIX(T##N##_copy)(TM_PREFIX(T##N) out, TM_PREFIX(T##N) a) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i];\
}\
TM_FUNC void TM_PREFIX(T##N##_add)(TM_PREFIX(T##N) out, TM_PREFIX(T##N) const a, TM_PREFIX(T##N) const b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] + b[_i];\
}\
TM_FUNC void TM_PREFIX(T##N##_sub)(TM_PREFIX(T##N) out, TM_PREFIX(T##N) const a, TM_PREFIX(T##N) const b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] - b[_i];\
}\
TM_FUNC void TM_PREFIX(T##N##_mul)(TM_PREFIX(T##N) out, TM_PREFIX(T##N) const a, TM_PREFIX(T##N) const b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] * b[_i];\
}\
TM_FUNC void TM_PREFIX(T##N##_div)(TM_PREFIX(T##N) out, TM_PREFIX(T##N) const a, TM_PREFIX(T##N) const b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] / b[_i];\
}\
TM_FUNC void TM_PREFIX(T##N##_adds)(TM_PREFIX(T##N) out, TM_PREFIX(T##N) const a, T b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] + b;\
}\
TM_FUNC void TM_PREFIX(T##N##_subs)(TM_PREFIX(T##N) out, TM_PREFIX(T##N) const a, T b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] - b;\
}\
TM_FUNC void TM_PREFIX(T##N##_muls)(TM_PREFIX(T##N) out, TM_PREFIX(T##N) const a, T b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] * b;\
}\
TM_FUNC void TM_PREFIX(T##N##_divs)(TM_PREFIX(T##N) out, TM_PREFIX(T##N) const a, T b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] / b;\
}\
TM_FUNC T TM_PREFIX(T##N##_dot)(TM_PREFIX(T##N) const a, TM_PREFIX(T##N) const b) {\
        T dot = 0;\
        for (int _i = 0; _i < N; _i++)\
                dot += a[_i] * b[_i];\
        return dot;\
}\
TM_FUNC T TM_PREFIX(T##N##_mag2)(TM_PREFIX(T##N) const a) {\
        return T##N##_dot(a, a);\
}\
TM_FUNC T TM_PREFIX(T##N##_mag)(TM_PREFIX(T##N) const a) {\
        return sqrt(T##N##_mag2(a));\
}\
TM_FUNC void TM_PREFIX(T##N##_min)(TM_PREFIX(T##N) out, TM_PREFIX(T##N) const a, TM_PREFIX(T##N) const b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] < b[_i] ? a[_i] : b[_i];\
}\
TM_FUNC void TM_PREFIX(T##N##_max)(TM_PREFIX(T##N) out, TM_PREFIX(T##N) const a, TM_PREFIX(T##N) const b) {\
        for (int _i = 0; _i < N; _i++)\
                out[_i] = a[_i] > b[_i] ? a[_i] : b[_i];\
}\
TM_FUNC void TM_PREFIX(T##N##_norm)(TM_PREFIX(T##N) out, TM_PREFIX(T##N) const a) {\
        T##N##_divs(out, a, T##N##_mag(a));\
}\
TM_FUNC T TM_PREFIX(T##N##_min_val)(TM_PREFIX(T##N) const a) {\
        T min = a[0];\
        for (int _i = 1; _i < N; _i++)\
                min = a[_i] < min ? a[_i] : min;\
        return min;\
}\
TM_FUNC T TM_PREFIX(T##N##_max_val)(TM_PREFIX(T##N) const a) {\
        T max = a[0];\
        for (int _i = 1; _i < N; _i++)\
                max = a[_i] > max ? a[_i] : max;\
        return max;\
}\

/// #### Dimension specific functions
/// ```c
/// void T2_rotate(T2 out, T2 a, T degrees)
/// void T3_cross(T3 out, T3 a, T3 b)
/// ```
#define TM_VECTOR_SPECIFIC(T)\
TM_FUNC void TM_PREFIX(T##2_rotate)(TM_PREFIX(T##2) out, TM_PREFIX(T##2) const a, T degrees) {\
        T s = sin(degrees * 0.0174533);\
        T c = cos(degrees * 0.0174533);\
        out[0] = a[0] * c - a[1] * s;\
        out[1] = a[0] * s + a[1] * c;\
}\
TM_FUNC void TM_PREFIX(T##3_cross)(TM_PREFIX(T##3) out, TM_PREFIX(T##3) const a, TM_PREFIX(T##3) const b) {\
        out[0] = a[1] * b[3] - a[3] * b[1];\
        out[1] = a[2] * b[0] - a[0] * b[2];\
        out[2] = a[0] * b[1] - a[1] * b[0];\
}

/// ## Matrix
/// A matrix is exactly the same as a vector, except it a two demensional array instead of a one dimensional one. A matrix is named the same way
/// as a vector with a small change to represent the second dimension, e.g. `float4x4` represents a 4x4 matrix of floats. In general, a matrix of
/// type T and holds R rows and C columns is defined as `TRxC`.
///
/// ### API
/// ```c
/// void TRxC_copy   (TRxC out, TRxC a)
/// void TRxC_add    (TRxC out, TRxC a, TRxC b)
/// void TRxC_sub    (TRxC out, TRxC a, TRxC b)
/// void TRxC_mul    (TRxC out, TRxC a, TRxC b)
/// void TRxC_div    (TRxC out, TRxC a, TRxC b)
/// void TRxC_adds   (TRxC out, TRxC a, T b)
/// void TRxC_subs   (TRxC out, TRxC a, T b)
/// void TRxC_muls   (TRxC out, TRxC a, T b)
/// void TRxC_divs   (TRxC out, TRxC a, T b)
/// void TRxC_addn   (TRxC out, int n, TRxC in[]) // These 4 functions operate on `n` matrices passed in as an array
/// void TRxC_subn   (TRxC out, int n, TRxC in[])
/// void TRxC_muln   (TRxC out, int n, TRxC in[])
/// void TRxC_divn   (TRxC out, int n, TRxC in[])
/// ```
#define TM_MATRIX(T, R, C)\
typedef T TM_PREFIX(T##R##x##C[R][C]);\
TM_FUNC void TM_PREFIX(T##R##x##C##_copy)(TM_PREFIX(T##R##x##C) out, TM_PREFIX(T##R##x##C) a) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                        out[_i][_j] = a[_i][_j]; /* Could do memset here, but would have to include string.h */\
}\
TM_FUNC void TM_PREFIX(T##R##x##C##_identity)(TM_PREFIX(T##R##x##C) out) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = (T)(_i == _j);\
}\
TM_FUNC void TM_PREFIX(T##R##x##C##_add)(TM_PREFIX(T##R##x##C) out, TM_PREFIX(T##R##x##C) const a, TM_PREFIX(T##R##x##C) const b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] + b[_i][_j];\
}\
TM_FUNC void TM_PREFIX(T##R##x##C##_sub)(TM_PREFIX(T##R##x##C) out, TM_PREFIX(T##R##x##C) const a, TM_PREFIX(T##R##x##C) const b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] - b[_i][_j];\
}\
TM_FUNC void TM_PREFIX(T##R##x##C##_mul)(TM_PREFIX(T##R##x##C) out, TM_PREFIX(T##R##x##C) const a, TM_PREFIX(T##R##x##C) const b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] * b[_i][_j];\
}\
TM_FUNC void TM_PREFIX(T##R##x##C##_div)(TM_PREFIX(T##R##x##C) out, TM_PREFIX(T##R##x##C) const a, TM_PREFIX(T##R##x##C) const b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] / b[_i][_j];\
}\
TM_FUNC void TM_PREFIX(T##R##x##C##_adds)(TM_PREFIX(T##R##x##C) out, TM_PREFIX(T##R##x##C) const a, T b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] + b;\
}\
TM_FUNC void TM_PREFIX(T##R##x##C##_subs)(TM_PREFIX(T##R##x##C) out, TM_PREFIX(T##R##x##C) const a, T b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] - b;\
}\
TM_FUNC void TM_PREFIX(T##R##x##C##_muls)(TM_PREFIX(T##R##x##C) out, TM_PREFIX(T##R##x##C) const a, T b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] * b;\
}\
TM_FUNC void TM_PREFIX(T##R##x##C##_divs)(TM_PREFIX(T##R##x##C) out, TM_PREFIX(T##R##x##C) const a, T b) {\
        for (int _i = 0; _i < R; _i++)\
                for (int _j = 0; _j < C; _j++)\
                     out[_i][_j] = a[_i][_j] / b;\
}\
TM_FUNC void TM_PREFIX(T##R##x##C##_addn)(TM_PREFIX(T##R##x##C) out, int n, TM_PREFIX(T##R##x##C) const in[]) {\
        for (int _i = 0; _i < n; _i++)\
                T##R##x##C##_add(out, out, in[_i]);\
}\
TM_FUNC void TM_PREFIX(T##R##x##C##_subn)(TM_PREFIX(T##R##x##C) out, int n, TM_PREFIX(T##R##x##C) const in[]) {\
        for (int _i = 0; _i < n; _i++)\
                T##R##x##C##_sub(out, out, in[_i]);\
}\
TM_FUNC void TM_PREFIX(T##R##x##C##_muln)(TM_PREFIX(T##R##x##C) out, int n, TM_PREFIX(T##R##x##C) const in[]) {\
        for (int _i = 0; _i < n; _i++)\
                T##R##x##C##_mul(out, out, in[_i]);\
}\
TM_FUNC void TM_PREFIX(T##R##x##C##_divn)(TM_PREFIX(T##R##x##C) out, int n, TM_PREFIX(T##R##x##C) const in[]) {\
        for (int _i = 0; _i < n; _i++)\
                T##R##x##C##_div(out, out, in[_i]);\
}\

/// #### Dimension specific functions
/// ```c
/// void T3x3_translate                 (T3x3 out, T2 t)
/// void T3x3_rotate                    (T3x3 out, T degrees)
/// void T3x3_scale                     (T3x3 out, T2 s)
/// void T3x3_scale_uni                 (T3x3 out, T s)
/// void T4x4_translate                 (T4x4 out, T3 v)
/// void T4x4_rotate                    (T4x4 out, T3 axis, T degrees)
/// void T4x4_rotate_x                  (T4x4 out, T degrees)
/// void T4x4_rotate_y                  (T4x4 out, T degrees)
/// void T4x4_rotate_z                  (T4x4 out, T degrees)
/// void T4x4_scale                     (T4x4 out, T3 s)
/// void T4x4_scale_uni                 (T4x4 out, T s)
/// void T4x4_lookat                    (T4x4 out, T3 eye, T3 target, T3 up)
/// void T4x4_perspective               (T4x4 out, T fov_degrees, T aspect, T near, T far)
/// void T4x4_perspective_default       (T4x4 out, T aspect)
/// void T4x4_ortho                     (T4x4 out, T left, T right, T bottom, T top, T near, T far)
/// void T4x4_ortho_aabb                (T4x4 out, T3 min, T3 max)
/// void T4x4_ortho_default             (T4x4 out, float aspect)
/// ```
#define TM_MATRIX_SPECIFIC(T)\
TM_FUNC void TM_PREFIX(T##3x3_translate)(TM_PREFIX(T##3x3) out, TM_PREFIX(T##2) const v) {\
        TM_PREFIX(T##3x3_identity)(out);\
        out[2][0] = v[0];\
        out[2][1] = v[1];\
}\
TM_FUNC void TM_PREFIX(T##3x3_rotate)(TM_PREFIX(T##3x3) out, T degrees) {\
        T c = cos(degrees * 0.0174533);\
        T s = sin(degrees * 0.0174533);\
        TM_PREFIX(T##3x3_identity)(out);\
        out[0][0] =  c;\
        out[0][1] =  s;\
        out[1][0] = -s;\
        out[1][1] =  c;\
        out[0][2] = out[1][2] = out[2][0] = out[2][1] = 0;\
        out[2][2] = 1.0;\
}\
TM_FUNC void TM_PREFIX(T##3x3_scale)(TM_PREFIX(T##3x3) out, TM_PREFIX(T##2) const v) {\
        TM_PREFIX(T##3x3_identity)(out);\
        out[0][0] = v[0];\
        out[1][1] = v[1];\
}\
TM_FUNC void TM_PREFIX(T##3x3_scale_uni)(TM_PREFIX(T##3x3) out, T s) {\
        TM_PREFIX(T##3x3_identity)(out);\
        out[0][0] = s;\
        out[1][1] = s;\
}\
TM_FUNC void TM_PREFIX(T##4x4_translate)(TM_PREFIX(T##4x4) out, TM_PREFIX(T##3) const v) {\
        TM_PREFIX(T##4x4_identity)(out);\
        out[3][0] = v[0];\
        out[3][1] = v[1];\
        out[3][2] = v[2];\
        out[0][0] = out[1][1] = out[2][2] = out[3][3] = 1.0;\
}\
TM_FUNC void TM_PREFIX(T##4x4_rotate)(TM_PREFIX(T##4x4) out, TM_PREFIX(T##3) const axis, T degrees) {\
        T c = cos(degrees * 0.0174533);\
        T s = sin(degrees * 0.0174533);\
        T t = 1.0 - c;\
        TM_PREFIX(T##3) an, at, as;\
        TM_PREFIX(T##3_norm)(an, axis);\
        TM_PREFIX(T##3_muls)(at, an, t);\
        TM_PREFIX(T##3_muls)(as, an, s);\
        TM_PREFIX(T##4x4_identity)(out);\
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
TM_FUNC void T##4x4_rotate_x(T##4x4 out, T degrees) {\
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
TM_FUNC void T##4x4_rotate_y(T##4x4 out, T degrees) {\
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
TM_FUNC void T##4x4_rotate_z(T##4x4 out, T degrees) {\
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
TM_FUNC void TM_PREFIX(T##4x4_scale)(TM_PREFIX(T##4x4) out, TM_PREFIX(T##3) const v) {\
        TM_PREFIX(T##4x4_identity)(out);\
        out[0][0] = v[0];\
        out[1][1] = v[1];\
        out[2][2] = v[2];\
        out[3][3] = 1.0;\
}\
TM_FUNC void TM_PREFIX(T##4x4_lookat)(TM_PREFIX(T##4x4) out, TM_PREFIX(T##3) const eye, TM_PREFIX(T##3) const target, TM_PREFIX(T##3) const up) {\
        TM_PREFIX(T##3) f, r, u;\
        TM_PREFIX(T##3_sub)(f, target, eye);\
        TM_PREFIX(T##3_norm)(f, f);\
        TM_PREFIX(T##3_cross)(r, f, up);\
        TM_PREFIX(T##3_norm)(r, r);\
        TM_PREFIX(T##3_cross)(u, r, f);\
        out[0][0] =  r[0];\
        out[0][1] =  u[0];\
        out[0][2] = -f[0];\
        out[1][0] =  r[1];\
        out[1][1] =  u[1];\
        out[1][2] = -f[1];\
        out[2][0] =  r[2];\
        out[2][1] =  u[2];\
        out[2][2] = -f[2];\
        out[3][1] = -TM_PREFIX(T##3_dot)(u, eye);\
        out[3][0] = -TM_PREFIX(T##3_dot)(r, eye);\
        out[3][2] = -TM_PREFIX(T##3_dot)(f, eye);\
}\
TM_FUNC void TM_PREFIX(T##4x4_perspective)(TM_PREFIX(T##4x4) out, T fov_degrees, T aspect, T near, T far) {\
        T fov = 1.0 / tan(fov_degrees * 0.0174533 * 0.5);\
        T nf  = 1.0 / (near - far);\
        out[0][0] = fov / aspect;\
        out[1][1] = fov;\
        out[2][2] = (near + far) * nf;\
        out[2][3] = -1.0;\
        out[3][2] = 2.0 * near * far * nf;\
}\
TM_FUNC void TM_PREFIX(T##4x4_ortho)(TM_PREFIX(T##4x4) out, T left, T right, T bottom, T top, T near, T far) {\
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
