#pragma once

typedef struct NbVector2 {
    float x;
    float y;
} NbVector2;

typedef struct NbVector3 {
    float x;
    float y;
    float z;
} NbVector3;

typedef struct NbVector4 {
    float x;
    float y;
    float z;
    float w;
} NbVector4;

typedef struct NbMatrix4 {
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;
} NbMatrix4;


float       nbSinf                  (float x);
float       nbCosf                  (float x);
float       nbTanf                  (float x);
float       nbSqrtf                 (float x);

NbVector2   nbVector2Add            (NbVector2 a, NbVector2 b);
NbVector2   nbVector2Subtract       (NbVector2 a, NbVector2 b);
NbVector2   nbVector2Multiply       (NbVector2 a, NbVector2 b);
NbVector2   nbVector2Scale          (NbVector2 a, float b);
float       nbVector2Dot            (NbVector2 a, NbVector2 b);
float       nbVector2LengthSquared  (NbVector2 a);
float       nbVector2Length         (NbVector2 a);
NbVector2   nbVector2Normalize      (NbVector2 a);

NbVector3   nbVector3Add            (NbVector3 a, NbVector3 b);
NbVector3   nbVector3Subtract       (NbVector3 a, NbVector3 b);
NbVector3   nbVector3Multiply       (NbVector3 a, NbVector3 b);
NbVector3   nbVector3Scale          (NbVector3 a, float b);
float       nbVector3Dot            (NbVector3 a, NbVector3 b);
float       nbVector3LengthSquared  (NbVector3 a);
float       nbVector3Length         (NbVector3 a);
NbVector3   nbVector3Normalize      (NbVector3 a);

NbVector4   nbVector4Add            (NbVector4 a, NbVector4 b);
NbVector4   nbVector4Subtract       (NbVector4 a, NbVector4 b);
NbVector4   nbVector4Multiply       (NbVector4 a, NbVector4 b);
NbVector4   nbVector4Scale          (NbVector4 a, float b);
float       nbVector4Dot            (NbVector4 a, NbVector4 b);
float       nbVector4LengthSquared  (NbVector4 a);
float       nbVector4Length         (NbVector4 a);
NbVector4   nbVector4Normalize      (NbVector4 a);

NbMatrix4   nbMatrix4Identity        (void);
NbMatrix4   nbMatrix4Multiply        (NbMatrix4 a, NbMatrix4 b);
NbMatrix4   nbMatrix4Translate       (NbVector3 translation);
NbMatrix4   nbMatrix4Rotate          (NbVector3 axis, float angle);
NbMatrix4   nbMatrix4Scale           (NbVector3 scale);
NbMatrix4   nbMatrix4LookAt          (NbVector3 eye, NbVector3 target, NbVector3 up);
NbMatrix4   nbMatrix4Perspective     (float fov, float aspect, float near, float far);
NbMatrix4   nbMatrix4Orthographic    (float bottom, float top, float left, float right, float near, float far);

