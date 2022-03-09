/// # tiny_math.h
///
/// ## About
/// Vector, matrix, and affine transformation math
///
/// ## Usage
/// Do this in **one** C/C++ file
/// ```c
/// #define tm_IMPLEMENTATION
/// #include "tiny_math.h"
/// ````
///
/// ## History
/// - v0.4.1 - Missing semicolons and parenthesis
/// - v0.4.0 - Added affine logic
/// - v0.3.0 - Added matrix logic
/// - v0.2.0 - Added Vector{2, 3, 4} logic
/// - v0.1.0 - Added types and interface functions

#ifndef __tiny_math_h__
#define __tiny_math_h__

// ======== Types ==============================================

typedef struct tm_Vector2 {
        float x, y;
} tm_Vector2;

typedef struct tm_Vector3 {
        float x, y, z;
} tm_Vector3;

typedef struct tm_Vector4 {
        float x, y, z, w;
} tm_Vector4;

typedef struct tm_Matrix {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
} tm_Matrix;

// ======== General ============================================

#define tm_Min(x, y)                            ((x) < (y) ? (x) : (y))
#define tm_Max(x, y)                            ((x) > (y) ? (x) : (y))
#define tm_Clamp(x, min, max)                   (tm_Max(tm_Min(x, max), min))
#define tm_Abs(x)                               ((x) < 0 ? -(x) : (x))
#define tm_DegToRad(x)                          ((x) * 0.017453294f)
#define tm_RadToDeg(x)                          ((x) * 57.29577951f)

// ======== Vector =============================================

#define tm_VECTOR_DEFINE(n)\
tm_Vector##n    tm_Vector##n##Add               (tm_Vector##n a, tm_Vector##n b);\
tm_Vector##n    tm_Vector##n##Sub               (tm_Vector##n a, tm_Vector##n b);\
tm_Vector##n    tm_Vector##n##Mul               (tm_Vector##n a, tm_Vector##n b);\
tm_Vector##n    tm_Vector##n##Div               (tm_Vector##n a, tm_Vector##n b);\
tm_Vector##n    tm_Vector##n##AddScalar         (tm_Vector##n a, float b);\
tm_Vector##n    tm_Vector##n##SubScalar         (tm_Vector##n a, float b);\
tm_Vector##n    tm_Vector##n##MulScalar         (tm_Vector##n a, float b);\
tm_Vector##n    tm_Vector##n##DivScalar         (tm_Vector##n a, float b);\
tm_Vector##n    tm_Vector##n##Min               (tm_Vector##n a, tm_Vector##n b);\
tm_Vector##n    tm_Vector##n##Max               (tm_Vector##n a, tm_Vector##n b);\
tm_Vector##n    tm_Vector##n##Normalize         (tm_Vector##n a);\
float           tm_Vector##n##Dot               (tm_Vector##n a, tm_Vector##n b);\
float           tm_Vector##n##Length            (tm_Vector##n a);\
float           tm_Vector##n##LengthSquared     (tm_Vector##n a);\
float           tm_Vector##n##MinComponent      (tm_Vector##n a);\
float           tm_Vector##n##MaxComponent      (tm_Vector##n a);

tm_VECTOR_DEFINE(2)
tm_VECTOR_DEFINE(3)
tm_VECTOR_DEFINE(4)

tm_Vector3      tm_Vector3Cross                 (tm_Vector3 a, tm_Vector3 b);

// ======== Matrix ==============================================

tm_Matrix       tm_MatrixIdentity               (void);
tm_Matrix       tm_MatrixAdd                    (tm_Matrix a, tm_Matrix b);
tm_Matrix       tm_MatrixSub                    (tm_Matrix a, tm_Matrix b);
tm_Matrix       tm_MatrixMul                    (tm_Matrix a, tm_Matrix b);
tm_Matrix       tm_MatrixDiv                    (tm_Matrix a, tm_Matrix b);
tm_Matrix       tm_MatrixAddScalar              (tm_Matrix a, float b);
tm_Matrix       tm_MatrixSubScalar              (tm_Matrix a, float b);
tm_Matrix       tm_MatrixMulScalar              (tm_Matrix a, float b);
tm_Matrix       tm_MatrixDivScalar              (tm_Matrix a, float b);

// ======== Affine / Projection ================================

tm_Matrix       tm_Translate                    (tm_Vector3 translation);
tm_Matrix       tm_Rotate                       (tm_Vector3 axis, float degrees);
tm_Matrix       tm_Scale                        (tm_Vector3 scale);
tm_Matrix       tm_LookAt                       (tm_Vector3 eye, tm_Vector3 target, tm_Vector3 up);
tm_Matrix       tm_Perspective                  (float fovDegrees, float aspect, float near, float far);
tm_Matrix       tm_Orthographic                 (float left, float right, float bottom, float top, float near, float far);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                                                                                    ////
////                                                                                                                                                    ////
////                                                                   Implementation                                                                   ////
////                                                                                                                                                    ////
////                                                                                                                                                    ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef tm_IMPLEMENTATION
#ifndef __tiny_math_c__
#define __tiny_math_c__

#include <math.h> // sqrtf, sinf, cosf, tanf

// ======== Vector2 ============================================

tm_Vector2 tm_Vector2Add(tm_Vector2 a, tm_Vector2 b) {
        return (tm_Vector2){ a.x + b.x, a.y + b.y };
}

tm_Vector2 tm_Vector2Sub(tm_Vector2 a, tm_Vector2 b) {
        return (tm_Vector2){ a.x - b.x, a.y - b.y };
}

tm_Vector2 tm_Vector2Mul(tm_Vector2 a, tm_Vector2 b) {
        return (tm_Vector2){ a.x * b.x, a.y * b.y };
}

tm_Vector2 tm_Vector2Div(tm_Vector2 a, tm_Vector2 b) {
        return (tm_Vector2){ a.x / b.x, a.y / b.y };
}

tm_Vector2 tm_Vector2AddScalar(tm_Vector2 a, float b) {
        return (tm_Vector2){ a.x + b, a.y + b };
}

tm_Vector2 tm_Vector2SubScalar(tm_Vector2 a, float b) {
        return (tm_Vector2){ a.x - b, a.y - b };
}

tm_Vector2 tm_Vector2MulScalar(tm_Vector2 a, float b) {
        return (tm_Vector2){ a.x * b, a.y * b };
}

tm_Vector2 tm_Vector2DivScalar(tm_Vector2 a, float b) {
        return (tm_Vector2){ a.x / b, a.y / b };
}

tm_Vector2 tm_Vector2Min(tm_Vector2 a, tm_Vector2 b) {
        return (tm_Vector2){ tm_Min(a.x, b.x), tm_Min(a.y, b.y) };
}

tm_Vector2 tm_Vector2Max(tm_Vector2 a, tm_Vector2 b) {
        return (tm_Vector2){ tm_Max(a.x, b.x), tm_Max(a.y, b.y) };
}

tm_Vector2 tm_Vector2Normalize(tm_Vector2 a) {
        return tm_Vector2DivScalar(a, tm_Vector2Length(a));
}

float tm_Vector2Dot(tm_Vector2 a, tm_Vector2 b) {
        return a.x * b.x + a.y * b.y;
}

float tm_Vector2Length(tm_Vector2 a) {
        return sqrtf(tm_Vector2LengthSquared(a));
}

float tm_Vector2LengthSquared(tm_Vector2 a) {
        return tm_Vector2Dot(a, a);
}

float tm_Vector2MinComponent(tm_Vector2 a) {
        return tm_Min(a.x, a.y);
}

float tm_Vector2MaxComponent(tm_Vector2 a) {
        return tm_Max(a.x, a.y);
}

// ======== Vector3 ============================================

tm_Vector3 tm_Vector3Add(tm_Vector3 a, tm_Vector3 b) {
        return (tm_Vector3){ a.x + b.x, a.y + b.y, a.z + b.z };
}

tm_Vector3 tm_Vector3Sub(tm_Vector3 a, tm_Vector3 b) {
        return (tm_Vector3){ a.x - b.x, a.y - b.y, a.z - b.z };
}

tm_Vector3 tm_Vector3Mul(tm_Vector3 a, tm_Vector3 b) {
        return (tm_Vector3){ a.x * b.x, a.y * b.y, a.z * b.z };
}

tm_Vector3 tm_Vector3Div(tm_Vector3 a, tm_Vector3 b) {
        return (tm_Vector3){ a.x / b.x, a.y / b.y, a.z / b.z };
}

tm_Vector3 tm_Vector3AddScalar(tm_Vector3 a, float b) {
        return (tm_Vector3){ a.x + b, a.y + b, a.z + b };
}

tm_Vector3 tm_Vector3SubScalar(tm_Vector3 a, float b) {
        return (tm_Vector3){ a.x - b, a.y - b, a.z - b };
}

tm_Vector3 tm_Vector3MulScalar(tm_Vector3 a, float b) {
        return (tm_Vector3){ a.x * b, a.y * b, a.z * b };
}

tm_Vector3 tm_Vector3DivScalar(tm_Vector3 a, float b) {
        return (tm_Vector3){ a.x / b, a.y / b, a.z / b };
}

tm_Vector3 tm_Vector3Min(tm_Vector3 a, tm_Vector3 b) {
        return (tm_Vector3){ tm_Min(a.x, b.x), tm_Min(a.y, b.y), tm_Min(a.z, b.z) };
}

tm_Vector3 tm_Vector3Max(tm_Vector3 a, tm_Vector3 b) {
        return (tm_Vector3){ tm_Max(a.x, b.x), tm_Max(a.y, b.y), tm_Max(a.z, b.z) };
}

tm_Vector3 tm_Vector3Normalize(tm_Vector3 a) {
        return tm_Vector3DivScalar(a, tm_Vector3Length(a));
}

float tm_Vector3Dot(tm_Vector3 a, tm_Vector3 b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
}

float tm_Vector3Length(tm_Vector3 a) {
        return sqrtf(tm_Vector3LengthSquared(a));
}

float tm_Vector3LengthSquared(tm_Vector3 a) {
        return tm_Vector3Dot(a, a);
}

float tm_Vector3MinComponent(tm_Vector3 a) {
        return tm_Min(tm_Min(a.x, a.y), a.z);
}

float tm_Vector3MaxComponent(tm_Vector3 a) {
        return tm_Max(tm_Max(a.x, a.y), a.z);
}

tm_Vector3 tm_Vector3Cross(tm_Vector3 a, tm_Vector3 b) {
        return (tm_Vector3){
                a.y * b.x - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x
        };
}

// ======== Vector4 ============================================

tm_Vector4 tm_Vector4Add(tm_Vector4 a, tm_Vector4 b) {
        return (tm_Vector4){ a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}

tm_Vector4 tm_Vector4Sub(tm_Vector4 a, tm_Vector4 b) {
        return (tm_Vector4){ a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
}

tm_Vector4 tm_Vector4Mul(tm_Vector4 a, tm_Vector4 b) {
        return (tm_Vector4){ a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
}

tm_Vector4 tm_Vector4Div(tm_Vector4 a, tm_Vector4 b) {
        return (tm_Vector4){ a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
}

tm_Vector4 tm_Vector4AddScalar(tm_Vector4 a, float b) {
        return (tm_Vector4){ a.x + b, a.y + b, a.z + b, a.w + b };
}

tm_Vector4 tm_Vector4SubScalar(tm_Vector4 a, float b) {
        return (tm_Vector4){ a.x - b, a.y - b, a.z - b, a.w - b };
}

tm_Vector4 tm_Vector4MulScalar(tm_Vector4 a, float b) {
        return (tm_Vector4){ a.x * b, a.y * b, a.z * b, a.w * b };
}

tm_Vector4 tm_Vector4DivScalar(tm_Vector4 a, float b) {
        return (tm_Vector4){ a.x / b, a.y / b, a.z / b, a.w / b };
}

tm_Vector4 tm_Vector4Min(tm_Vector4 a, tm_Vector4 b) {
        return (tm_Vector4){ tm_Min(a.x, b.x), tm_Min(a.y, b.y), tm_Min(a.z, b.z), tm_Min(a.w, b.w) };
}

tm_Vector4 tm_Vector4Max(tm_Vector4 a, tm_Vector4 b) {
        return (tm_Vector4){ tm_Max(a.x, b.x), tm_Max(a.y, b.y), tm_Max(a.z, b.z), tm_Max(a.w, b.w) };
}

tm_Vector4 tm_Vector4Normalize(tm_Vector4 a) {
        return tm_Vector4DivScalar(a, tm_Vector4Length(a));
}

float tm_Vector4Dot(tm_Vector4 a, tm_Vector4 b) {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float tm_Vector4Length(tm_Vector4 a) {
        return sqrtf(tm_Vector4LengthSquared(a));
}

float tm_Vector4LengthSquared(tm_Vector4 a) {
        return tm_Vector4Dot(a, a);
}

float tm_Vector4MinComponent(tm_Vector4 a) {
        return tm_Min(tm_Min(a.x, a.y), tm_Min(a.z, a.w));
}

float tm_Vector4MaxComponent(tm_Vector4 a) {
        return tm_Max(tm_Max(a.x, a.y), tm_Max(a.z, a.w));
}

// ======== Matrix =============================================

tm_Matrix tm_MatrixIdentity(void) {
        return (tm_Matrix){ .m00 = 1.0f, .m11 = 1.0f, .m22 = 1.0f, .m33 = 1.0f };
}

tm_Matrix tm_MatrixAdd(tm_Matrix a, tm_Matrix b) {
        return (tm_Matrix){
                a.m00 + b.m00, a.m01 + b.m01, a.m02 + b.m02, a.m03 + b.m03,
                a.m10 + b.m10, a.m11 + b.m11, a.m12 + b.m12, a.m13 + b.m13,
                a.m20 + b.m20, a.m21 + b.m21, a.m22 + b.m22, a.m23 + b.m23,
                a.m30 + b.m30, a.m31 + b.m31, a.m32 + b.m32, a.m33 + b.m33,
        };
}

tm_Matrix tm_MatrixSub(tm_Matrix a, tm_Matrix b) {
        return (tm_Matrix){
                a.m00 - b.m00, a.m01 - b.m01, a.m02 - b.m02, a.m03 - b.m03,
                a.m10 - b.m10, a.m11 - b.m11, a.m12 - b.m12, a.m13 - b.m13,
                a.m20 - b.m20, a.m21 - b.m21, a.m22 - b.m22, a.m23 - b.m23,
                a.m30 - b.m30, a.m31 - b.m31, a.m32 - b.m32, a.m33 - b.m33,
        };
}

tm_Matrix tm_MatrixMul(tm_Matrix a, tm_Matrix b) {
        return (tm_Matrix){
                a.m00 * b.m00, a.m01 * b.m01, a.m02 * b.m02, a.m03 * b.m03,
                a.m10 * b.m10, a.m11 * b.m11, a.m12 * b.m12, a.m13 * b.m13,
                a.m20 * b.m20, a.m21 * b.m21, a.m22 * b.m22, a.m23 * b.m23,
                a.m30 * b.m30, a.m31 * b.m31, a.m32 * b.m32, a.m33 * b.m33,
        };
}

tm_Matrix tm_MatrixDiv(tm_Matrix a, tm_Matrix b) {
        return (tm_Matrix){
                a.m00 / b.m00, a.m01 / b.m01, a.m02 / b.m02, a.m03 / b.m03,
                a.m10 / b.m10, a.m11 / b.m11, a.m12 / b.m12, a.m13 / b.m13,
                a.m20 / b.m20, a.m21 / b.m21, a.m22 / b.m22, a.m23 / b.m23,
                a.m30 / b.m30, a.m31 / b.m31, a.m32 / b.m32, a.m33 / b.m33,
        };
}

tm_Matrix tm_MatrixAddScalar(tm_Matrix a, float b) {
        return (tm_Matrix){
                a.m00 + b, a.m01 + b, a.m02 + b, a.m03 + b,
                a.m10 + b, a.m11 + b, a.m12 + b, a.m13 + b,
                a.m20 + b, a.m21 + b, a.m22 + b, a.m23 + b,
                a.m30 + b, a.m31 + b, a.m32 + b, a.m33 + b,
        };
}

tm_Matrix tm_MatrixSubScalar(tm_Matrix a, float b) {
        return (tm_Matrix){
                a.m00 - b, a.m01 - b, a.m02 - b, a.m03 - b,
                a.m10 - b, a.m11 - b, a.m12 - b, a.m13 - b,
                a.m20 - b, a.m21 - b, a.m22 - b, a.m23 - b,
                a.m30 - b, a.m31 - b, a.m32 - b, a.m33 - b,
        };
}

tm_Matrix tm_MatrixMulScalar(tm_Matrix a, float b) {
        return (tm_Matrix){
                a.m00 * b, a.m01 * b, a.m02 * b, a.m03 * b,
                a.m10 * b, a.m11 * b, a.m12 * b, a.m13 * b,
                a.m20 * b, a.m21 * b, a.m22 * b, a.m23 * b,
                a.m30 * b, a.m31 * b, a.m32 * b, a.m33 * b,
        };
}

tm_Matrix tm_MatrixDivScalar(tm_Matrix a, float b) {
        return (tm_Matrix){
                a.m00 / b, a.m01 / b, a.m02 / b, a.m03 / b,
                a.m10 / b, a.m11 / b, a.m12 / b, a.m13 / b,
                a.m20 / b, a.m21 / b, a.m22 / b, a.m23 / b,
                a.m30 / b, a.m31 / b, a.m32 / b, a.m33 / b,
        };
}

// ======== Affine =============================================

tm_Matrix tm_Translate(tm_Vector3 translation) {
        return (tm_Matrix){
                .m00 = 1.0f,
                .m11 = 1.0f,
                .m22 = 1.0f,
                .m30 = translation.x,
                .m31 = translation.y,
                .m32 = translation.z,
                .m33 = 1.0f,
        };
}

// http://fastgraph.com/makegames/3drotation/
tm_Matrix tm_Rotate(tm_Vector3 axis, float degrees) {
        float c = cosf(tm_DegToRad(degrees));
        float s = sinf(tm_DegToRad(degrees));
        float t = 1.0f - c;

        tm_Vector3 an = tm_Vector3Normalize(axis);
        tm_Vector3 at = tm_Vector3MulScalar(an, t);
        tm_Vector3 as = tm_Vector3MulScalar(an, s);

        return (tm_Matrix){
                an.x * at.x + c,    an.y * at.x + as.z, an.z * at.x - as.y, 0.0f,
                an.x * at.y - as.z, an.y * at.y + c,    an.z * at.y + as.x, 0.0f,
                an.x * at.z + as.y, an.y * at.z + as.x, an.z * at.z + c,    0.0f,
                0.0f,               0.0f,               0.0f,               1.0f
        };
}

tm_Matrix tm_Scale(tm_Vector3 scale) {
        return (tm_Matrix){
                .m00 = scale.x,
                .m11 = scale.y,
                .m22 = scale.z,
                .m33 = 1.0f
        };
}

tm_Matrix tm_LookAt(tm_Vector3 eye, tm_Vector3 target, tm_Vector3 up) {
        tm_Vector3 f = tm_Vector3Normalize(tm_Vector3Sub(target, eye));
        tm_Vector3 r = tm_Vector3Normalize(tm_Vector3Cross(f, up));
        tm_Vector3 u = tm_Vector3Cross(r, f);

        float rdot = -tm_Vector3Dot(r, eye);
        float udot = -tm_Vector3Dot(u, eye);
        float fdot = -tm_Vector3Dot(f, eye);

        return (tm_Matrix){
                 r.x,  u.x, -f.x, 0.0f,
                 r.y,  u.y, -f.y, 0.0f,
                 r.z,  u.z, -f.z, 0.0f,
                rdot, udot, fdot, 1.0f
        };
}

tm_Matrix tm_Perspective(float fovDegrees, float aspect, float near, float far) {
        float fov = 1.0f / tanf(tm_DegToRad(fovDegrees) * 0.5f);
        float nf  = 1.0f / (near - far);

        return (tm_Matrix){
                .m00 = fov / aspect,
                .m11 = fov,
                .m22 = (near + far) * nf,
                .m23 = -1.0f,
                .m32 = 2.0f * near * far * nf
        };
}

tm_Matrix tm_Orthographic(float left, float right, float bottom, float top, float near, float far) {
        float rl =  1.0f / (right - left);
        float tb =  1.0f / (top - bottom);
        float fn = -1.0f / (far - near);

        return (tm_Matrix){
                .m00 = 2.0f * rl,
                .m11 = 2.0f * tb,
                .m22 = 2.0f * fn,
                .m30 = -(right + left) * rl,
                .m31 = -(top + bottom) * tb,
                .m32 = -(far + near) * fn,
                .m33 = 1.0f
        };
}

#endif // !__tiny_math_c__
#endif // tm_IMPLEMENTATION
#endif // !__tiny_math_h
