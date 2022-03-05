/*
 * tiny_math.h
 * Defines tm_Vector{2,3,4}, tm_Matrix{2,3}, tm_Rectangle, tm_Box, tm_Circle, and tm_Sphere (more later)
 *
 */

#ifndef __tiny_math_h__
#define __tiny_math_h__


typedef struct tm_Vector2 {
        float x, y;
} tm_Vector2;

typedef struct tm_Vector3 {
        float x, y, z;
} tm_Vector3;

typedef struct tm_Vector4 {
        float x, y, z, w;
} tm_Vector4;

typedef struct tm_Matrix3 {
        float m00, m01, m02;
        float m10, m11, m12;
        float m20, m21, m22;
} tm_Matrix3;

typedef struct tm_Matrix4 {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
} tm_Matrix4;

typedef struct tm_Quaternion {
        float x, y, z, w;
} tm_Quaternion;

typedef struct tm_Rectangle {
        tm_Vector2 position, size;
} tm_Rectangle;

typedef struct tm_Circle {
        tm_Vector2 position;
        float radius;
} tm_Circle;

typedef struct tm_Box {
        tm_Vector3 position;
        tm_Vector3 size;
} tm_Box;

typedef struct tm_Sphere {
        tm_Vector3 position;
        float radius;
} tm_Sphere;


#define tm_VECTOR_DEFINE(n)\
tm_Vector##n    tm_AddVector##n                 (tm_Vector##n a, tm_Vector##n b);\
tm_Vector##n    tm_SubVector##n                 (tm_Vector##n a, tm_Vector##n b);\
tm_Vector##n    tm_MulVector##n                 (tm_Vector##n a, tm_Vector##n b);\
tm_Vector##n    tm_DivVector##n                 (tm_Vector##n a, tm_Vector##n b);\
tm_Vector##n    tm_AddVector##n##f              (tm_Vector##n a, float b);\
tm_Vector##n    tm_SubVector##n##f              (tm_Vector##n a, float b);\
tm_Vector##n    tm_MulVector##n##f              (tm_Vector##n a, float b);\
tm_Vector##n    tm_DivVector##n##f              (tm_Vector##n a, float b);\
tm_Vector##n    tm_MinVector##n                 (tm_Vector##n a, tm_Vector##n b);\
tm_Vector##n    tm_MaxVector##n                 (tm_Vector##n a, tm_Vector##n b);\
tm_Vector##n    tm_NormalizeVector##n           (tm_Vector##n a);\
float           tm_DotVector##n                 (tm_Vector##n a);\
float           tm_LengthVector##n              (tm_Vector##n a);\
float           tm_LengthSquaredVector##n       (tm_Vector##n a);\
float           tm_MinComponentVector##n        (tm_Vector##n a);\
float           tm_MaxComponentVector##n        (tm_Vector##n a);

tm_VECTOR_DEFINE(2)
tm_VECTOR_DEFINE(3)
tm_VECTOR_DEFINE(4)

tm_Vector2      tm_RotateVector2                (tm_Vector2 a, float radians);
tm_Vector3      tm_CrossVector3                 (tm_Vector3 a, tm_Vector3 b);


#define tm_MATRIX_DEFINE(n)\
tm_Matrix##n    tm_IdentityMatrix##n            (void);\
tm_Matrix##n    tm_AddMatrix##n                 (tm_Matrix##n a, tm_Matrix##n b);\
tm_Matrix##n    tm_SubMatrix##n                 (tm_Matrix##n a, tm_Matrix##n b);\
tm_Matrix##n    tm_MulMatrix##n                 (tm_Matrix##n a, tm_Matrix##n b);\
tm_Matrix##n    tm_DivMatrix##n                 (tm_Matrix##n a, tm_Matrix##n b);\
tm_Matrix##n    tm_AddMatrix##n##f              (tm_Matrix##n a, float b);\
tm_Matrix##n    tm_SubMatrix##n##f              (tm_Matrix##n a, float b);\
tm_Matrix##n    tm_MulMatrix##n##f              (tm_Matrix##n a, float b);\
tm_Matrix##n    tm_DivMatrix##n##f              (tm_Matrix##n a, float b);

tm_MATRIX_DEFINE(3)
tm_MATRIX_DEFINE(4)


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




#endif // !__tiny_math_c__
#endif // tm_IMPLEMENTATION
#endif // !__tiny_math_h__
