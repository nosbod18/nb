#include "math.h"

float nbSinf(float x) {
    x *= 0.15915494309189534f;
    x *= 0.5f - (x < 0 ? -x : x);
    return x * (57.3460872862336f * (x < 0 ? -x : x) + 12.4158695446104f);
}

float nbCosf(float x) {
    return nbSinf(x + 1.570796327f);
}

float nbTanf(float x) {
    return nbSinf(x) / nbCosf(x);
}

float nbSqrtf(float x) {
    int y = ((*(int *)&x - 0x00800000) >> 1) + 0x20000000;
    float z = *(float *)&y;
    return (x / z + z) * 0.5f;
}

NbVector2   nbVector2Add(NbVector2 a, NbVector2 b)      { return (NbVector2){a.x + b.x, a.y + b.y}; }
NbVector2   nbVector2Subtract(NbVector2 a, NbVector2 b) { return (NbVector2){a.x - b.x, a.y - b.y}; }
NbVector2   nbVector2Multiply(NbVector2 a, NbVector2 b) { return (NbVector2){a.x * b.x, a.y * b.y}; }
NbVector2   nbVector2Scale(NbVector2 a, float b)        { return (NbVector2){a.x * b,   a.y * b  }; }
float       nbVector2Dot(NbVector2 a, NbVector2 b)      { return a.x * b.x + a.y * b.y; }
float       nbVector2LengthSquared(NbVector2 a)         { return nbVector2Dot(a, a); }
float       nbVector2Length(NbVector2 a)                { return nbSqrtf(nbVector2LengthSquared(a)); }
NbVector2   nbVector2Normalize(NbVector2 a)             { return nbVector2Scale(a, 1.f / nbVector2Length(a)); }

NbVector3   nbVector3Add(NbVector3 a, NbVector3 b)      { return (NbVector3){a.x + b.x, a.y + b.y, a.z + b.z}; }
NbVector3   nbVector3Subtract(NbVector3 a, NbVector3 b) { return (NbVector3){a.x - b.x, a.y - b.y, a.z - b.z}; }
NbVector3   nbVector3Multiply(NbVector3 a, NbVector3 b) { return (NbVector3){a.x * b.x, a.y * b.y, a.z * b.z}; }
NbVector3   nbVector3Scale(NbVector3 a, float b)        { return (NbVector3){a.x * b,   a.y * b,   a.z * b  }; }
float       nbVector3Dot(NbVector3 a, NbVector3 b)      { return a.x * b.x + a.y * b.y + a.z * b.z; }
float       nbVector3LengthSquared(NbVector3 a)         { return nbVector3Dot(a, a); }
float       nbVector3Length(NbVector3 a)                { return nbSqrtf(nbVector3LengthSquared(a)); }
NbVector3   nbVector3Normalize(NbVector3 a)             { return nbVector3Scale(a, 1.f / nbVector3Length(a)); }

NbVector3   nbVector3Cross(NbVector3 a, NbVector3 b) {
    return (NbVector3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

NbVector4   nbVector4Add(NbVector4 a, NbVector4 b)      { return (NbVector4){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w}; }
NbVector4   nbVector4Subtract(NbVector4 a, NbVector4 b) { return (NbVector4){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w}; }
NbVector4   nbVector4Multiply(NbVector4 a, NbVector4 b) { return (NbVector4){a.x * b.x, a.y * b.y, a.z * b.z, a.z * b.z}; }
NbVector4   nbVector4Scale(NbVector4 a, float b)        { return (NbVector4){a.x * b,   a.y * b,   a.z * b,   a.w * b   }; }
float       nbVector4Dot(NbVector4 a, NbVector4 b)      { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
float       nbVector4LengthSquared(NbVector4 a)         { return nbVector4Dot(a, a); }
float       nbVector4Length(NbVector4 a)                { return nbSqrtf(nbVector4LengthSquared(a)); }
NbVector4   nbVector4Normalize(NbVector4 a)             { return nbVector4Scale(a, 1.f / nbVector4Length(a)); }

NbMatrix4 nbIdentityMatrix4(void) {
    return (NbMatrix4){.m00 = 1.f, .m11 = 1.f, .m22 = 1.f, .m33 = 1.f};
}

NbMatrix4 nbMultiplyMatrix4(NbMatrix4 a, NbMatrix4 b) {
    return (NbMatrix4){
        a.m00 * b.m00, a.m01 * b.m01, a.m02 * b.m02, a.m03 * b.m03,
        a.m10 * b.m10, a.m11 * b.m11, a.m12 * b.m12, a.m13 * b.m13,
        a.m20 * b.m20, a.m21 * b.m21, a.m22 * b.m22, a.m23 * b.m23,
        a.m30 * b.m30, a.m31 * b.m31, a.m32 * b.m32, a.m33 * b.m33,
    };
}

NbMatrix4 nbTranslateMatrix4(NbVector3 translation) {
    return (NbMatrix4){
        .m30 = translation.x,
        .m31 = translation.y,
        .m32 = translation.z,
        .m33 = 1.f
    };
}

NbMatrix4 nbRotateMatrix4(NbVector3 axis, float angle) {
    float   c = nbCosf(angle);
    NbVector3 an = nbVector3Normalize(axis);
    NbVector3 at = nbVector3Scale(an, 1.f - c);
    NbVector3 as = nbVector3Scale(an, nbSinf(angle));

    return (NbMatrix4){
        an.x * at.x    + c, an.y * at.x + as.z, an.z * at.x - as.y, 0.f,
        an.x * at.y - as.z, an.y * at.y    + c, an.z * at.y + as.x, 0.f,
        an.x * at.z + as.z, an.y * at.z + as.x, an.z * at.z    + c, 0.f,
        0.f, 0.f, 0.f, 1.f
    };
}

NbMatrix4 nbScaleMatrix4(NbVector3 scale) {
    return (NbMatrix4){
        .m00 = scale.x,
        .m11 = scale.y,
        .m22 = scale.z
    };
}

NbMatrix4 nbLookAtMatrix4(NbVector3 eye, NbVector3 target, NbVector3 up) {
    NbVector3 f = nbVector3Normalize(nbVector3Subtract(target, eye));
    NbVector3 r = nbVector3Normalize(nbVector3Cross(f, up));
    NbVector3 u = nbVector3Cross(r, f);
    return (NbMatrix4){
        r.x, u.x, -f.x, 0.0f,
        r.y, u.y, -f.y, 0.0f,
        r.z, u.z, -f.z, 0.0f,
        -nbVector3Dot(r, eye), -nbVector3Dot(u, eye), -nbVector3Dot(f, eye), 1.0f
    };
}

NbMatrix4 nbPerspectiveMatrix4(float fov, float aspect, float near, float far) {
    float nf  = 1.f / (near - far);
    fov = 1.f / nbTanf(fov * 0.5f);
    return (NbMatrix4){
        .m00 = fov / aspect,
        .m11 = fov,
        .m22 = (near + far) * nf,
        .m23 = -1.f,
        .m32 = 2.f * near * far * nf
    };
}

NbMatrix4 nbOrthographicMatrix4(float bottom, float top, float left, float right, float near, float far) {
    float rl =  1.f / (right - bottom);
    float tb =  1.f / (top - bottom);
    float fn = -1.f / (far - near);
    return (NbMatrix4){
        .m00 = 2.f * rl,
        .m11 = 2.f * tb,
        .m22 = 2.f * fn,
        .m30 = -(right + left) * rl,
        .m31 = -(top + bottom) * tb,
        .m32 = -(far + near) * fn,
        .m33 = 1.f
    };
}
