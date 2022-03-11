#ifndef __tiny_math_h__
#define __tiny_math_h__

// ======== Types ==============================================

typedef struct tm_vec2 {
        float x, y;
} tm_vec2;

typedef struct tm_vec3 {
        float x, y, z;
} tm_vec3;

typedef struct tm_vec4 {
        float x, y, z, w;
} tm_vec4;

typedef struct tm_mat4 {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
} tm_mat4;

// ======== General ============================================

#define tm_min(x, y)                            ((x) < (y) ? (x) : (y))
#define tm_max(x, y)                            ((x) > (y) ? (x) : (y))
#define tm_clamp(x, min, max)                   (tm_max(tm_min(x, max), min))
#define tm_abs(x)                               ((x) < 0 ? -(x) : (x))
#define tm_deg2rad(x)                           ((x) * 0.017453294f)
#define tm_rad2deg(x)                           ((x) * 57.29577951f)

// ======== vec =============================================

#define TM_VECTOR_DEFINE(n)\
tm_vec##n       tm_vec##n##_add                 (tm_vec##n a, tm_vec##n b);\
tm_vec##n       tm_vec##n##_sub                 (tm_vec##n a, tm_vec##n b);\
tm_vec##n       tm_vec##n##_mul                 (tm_vec##n a, tm_vec##n b);\
tm_vec##n       tm_vec##n##_div                 (tm_vec##n a, tm_vec##n b);\
tm_vec##n       tm_vec##n##_addf                (tm_vec##n a, float b);\
tm_vec##n       tm_vec##n##_subf                (tm_vec##n a, float b);\
tm_vec##n       tm_vec##n##_mulf                (tm_vec##n a, float b);\
tm_vec##n       tm_vec##n##_divf                (tm_vec##n a, float b);\
tm_vec##n       tm_vec##n##_min                 (tm_vec##n a, tm_vec##n b);\
tm_vec##n       tm_vec##n##_max                 (tm_vec##n a, tm_vec##n b);\
tm_vec##n       tm_vec##n##_norm                (tm_vec##n a);\
float           tm_vec##n##_dot                 (tm_vec##n a, tm_vec##n b);\
float           tm_vec##n##_mag                 (tm_vec##n a);\
float           tm_vec##n##_mag2                (tm_vec##n a);\
float           tm_vec##n##_min_component       (tm_vec##n a);\
float           tm_vec##n##_max_component       (tm_vec##n a);

TM_VECTOR_DEFINE(2)
TM_VECTOR_DEFINE(3)
TM_VECTOR_DEFINE(4)

tm_vec3         tm_vec3_cross                   (tm_vec3 a, tm_vec3 b);

// ======== mat4 ==============================================

tm_mat4         tm_mat4_identity                (void);
tm_mat4         tm_mat4_add                     (tm_mat4 a, tm_mat4 b);
tm_mat4         tm_mat4_sub                     (tm_mat4 a, tm_mat4 b);
tm_mat4         tm_mat4_mul                     (tm_mat4 a, tm_mat4 b);
tm_mat4         tm_mat4_div                     (tm_mat4 a, tm_mat4 b);
tm_mat4         tm_mat4_addf                    (tm_mat4 a, float b);
tm_mat4         tm_mat4_subf                    (tm_mat4 a, float b);
tm_mat4         tm_mat4_mulf                    (tm_mat4 a, float b);
tm_mat4         tm_mat4_divf                    (tm_mat4 a, float b);

// ======== Affine / Projection ================================

tm_mat4         tm_translate                    (tm_vec3 translation);
tm_mat4         tm_rotate                       (tm_vec3 axis, float degrees);
tm_mat4         tm_scale                        (tm_vec3 scale);
tm_mat4         tm_lookat                       (tm_vec3 eye, tm_vec3 target, tm_vec3 up);
tm_mat4         tm_perspective                  (float fov_degrees, float aspect, float near, float far);
tm_mat4         tm_orthographic                 (float left, float right, float bottom, float top, float near, float far);


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

// ======== vec2 ============================================

tm_vec2 tm_vec2_add(tm_vec2 a, tm_vec2 b) {
        return (tm_vec2){ a.x + b.x, a.y + b.y };
}

tm_vec2 tm_vec2_sub(tm_vec2 a, tm_vec2 b) {
        return (tm_vec2){ a.x - b.x, a.y - b.y };
}

tm_vec2 tm_vec2_mul(tm_vec2 a, tm_vec2 b) {
        return (tm_vec2){ a.x * b.x, a.y * b.y };
}

tm_vec2 tm_vec2_div(tm_vec2 a, tm_vec2 b) {
        return (tm_vec2){ a.x / b.x, a.y / b.y };
}

tm_vec2 tm_vec2_addf(tm_vec2 a, float b) {
        return (tm_vec2){ a.x + b, a.y + b };
}

tm_vec2 tm_vec2_subf(tm_vec2 a, float b) {
        return (tm_vec2){ a.x - b, a.y - b };
}

tm_vec2 tm_vec2_mulf(tm_vec2 a, float b) {
        return (tm_vec2){ a.x * b, a.y * b };
}

tm_vec2 tm_vec2_divf(tm_vec2 a, float b) {
        return (tm_vec2){ a.x / b, a.y / b };
}

tm_vec2 tm_vec2min(tm_vec2 a, tm_vec2 b) {
        return (tm_vec2){ tm_min(a.x, b.x), tm_min(a.y, b.y) };
}

tm_vec2 tm_vec2max(tm_vec2 a, tm_vec2 b) {
        return (tm_vec2){ tm_max(a.x, b.x), tm_max(a.y, b.y) };
}

tm_vec2 tm_vec2_norm(tm_vec2 a) {
        return tm_vec2_divf(a, tm_vec2_mag(a));
}

float tm_vec2_dot(tm_vec2 a, tm_vec2 b) {
        return a.x * b.x + a.y * b.y;
}

float tm_vec2_mag(tm_vec2 a) {
        return sqrtf(tm_vec2_mag2(a));
}

float tm_vec2_mag2(tm_vec2 a) {
        return tm_vec2_dot(a, a);
}

float tm_vec2_min_component(tm_vec2 a) {
        return tm_min(a.x, a.y);
}

float tm_vec2_max_component(tm_vec2 a) {
        return tm_max(a.x, a.y);
}

// ======== vec3 ============================================

tm_vec3 tm_vec3_add(tm_vec3 a, tm_vec3 b) {
        return (tm_vec3){ a.x + b.x, a.y + b.y, a.z + b.z };
}

tm_vec3 tm_vec3_sub(tm_vec3 a, tm_vec3 b) {
        return (tm_vec3){ a.x - b.x, a.y - b.y, a.z - b.z };
}

tm_vec3 tm_vec3_mul(tm_vec3 a, tm_vec3 b) {
        return (tm_vec3){ a.x * b.x, a.y * b.y, a.z * b.z };
}

tm_vec3 tm_vec3_div(tm_vec3 a, tm_vec3 b) {
        return (tm_vec3){ a.x / b.x, a.y / b.y, a.z / b.z };
}

tm_vec3 tm_vec3_addf(tm_vec3 a, float b) {
        return (tm_vec3){ a.x + b, a.y + b, a.z + b };
}

tm_vec3 tm_vec3_subf(tm_vec3 a, float b) {
        return (tm_vec3){ a.x - b, a.y - b, a.z - b };
}

tm_vec3 tm_vec3_mulf(tm_vec3 a, float b) {
        return (tm_vec3){ a.x * b, a.y * b, a.z * b };
}

tm_vec3 tm_vec3_divf(tm_vec3 a, float b) {
        return (tm_vec3){ a.x / b, a.y / b, a.z / b };
}

tm_vec3 tm_vec3min(tm_vec3 a, tm_vec3 b) {
        return (tm_vec3){ tm_min(a.x, b.x), tm_min(a.y, b.y), tm_min(a.z, b.z) };
}

tm_vec3 tm_vec3max(tm_vec3 a, tm_vec3 b) {
        return (tm_vec3){ tm_max(a.x, b.x), tm_max(a.y, b.y), tm_max(a.z, b.z) };
}

tm_vec3 tm_vec3_norm(tm_vec3 a) {
        return tm_vec3_divf(a, tm_vec3_mag(a));
}

float tm_vec3_dot(tm_vec3 a, tm_vec3 b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
}

float tm_vec3_mag(tm_vec3 a) {
        return sqrtf(tm_vec3_mag2(a));
}

float tm_vec3_mag2(tm_vec3 a) {
        return tm_vec3_dot(a, a);
}

float tm_vec3_min_component(tm_vec3 a) {
        return tm_min(tm_min(a.x, a.y), a.z);
}

float tm_vec3_max_component(tm_vec3 a) {
        return tm_max(tm_max(a.x, a.y), a.z);
}

tm_vec3 tm_vec3_cross(tm_vec3 a, tm_vec3 b) {
        return (tm_vec3){
                a.y * b.x - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x
        };
}

// ======== vec4 ============================================

tm_vec4 tm_vec4_add(tm_vec4 a, tm_vec4 b) {
        return (tm_vec4){ a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}

tm_vec4 tm_vec4_sub(tm_vec4 a, tm_vec4 b) {
        return (tm_vec4){ a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
}

tm_vec4 tm_vec4_mul(tm_vec4 a, tm_vec4 b) {
        return (tm_vec4){ a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
}

tm_vec4 tm_vec4_div(tm_vec4 a, tm_vec4 b) {
        return (tm_vec4){ a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
}

tm_vec4 tm_vec4_addf(tm_vec4 a, float b) {
        return (tm_vec4){ a.x + b, a.y + b, a.z + b, a.w + b };
}

tm_vec4 tm_vec4_subf(tm_vec4 a, float b) {
        return (tm_vec4){ a.x - b, a.y - b, a.z - b, a.w - b };
}

tm_vec4 tm_vec4_mulf(tm_vec4 a, float b) {
        return (tm_vec4){ a.x * b, a.y * b, a.z * b, a.w * b };
}

tm_vec4 tm_vec4_divf(tm_vec4 a, float b) {
        return (tm_vec4){ a.x / b, a.y / b, a.z / b, a.w / b };
}

tm_vec4 tm_vec4_min(tm_vec4 a, tm_vec4 b) {
        return (tm_vec4){ tm_min(a.x, b.x), tm_min(a.y, b.y), tm_min(a.z, b.z), tm_min(a.w, b.w) };
}

tm_vec4 tm_vec4_max(tm_vec4 a, tm_vec4 b) {
        return (tm_vec4){ tm_max(a.x, b.x), tm_max(a.y, b.y), tm_max(a.z, b.z), tm_max(a.w, b.w) };
}

tm_vec4 tm_vec4_norm(tm_vec4 a) {
        return tm_vec4_divf(a, tm_vec4_mag(a));
}

float tm_vec4_dot(tm_vec4 a, tm_vec4 b) {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float tm_vec4_mag(tm_vec4 a) {
        return sqrtf(tm_vec4_mag2(a));
}

float tm_vec4_mag2(tm_vec4 a) {
        return tm_vec4_dot(a, a);
}

float tm_vec4_min_component(tm_vec4 a) {
        return tm_min(tm_min(a.x, a.y), tm_min(a.z, a.w));
}

float tm_vec4_max_component(tm_vec4 a) {
        return tm_max(tm_max(a.x, a.y), tm_max(a.z, a.w));
}

// ======== mat4 =============================================

tm_mat4 tm_mat4_identity(void) {
        return (tm_mat4){ .m00 = 1.0f, .m11 = 1.0f, .m22 = 1.0f, .m33 = 1.0f };
}

tm_mat4 tm_mat4_add(tm_mat4 a, tm_mat4 b) {
        return (tm_mat4){
                a.m00 + b.m00, a.m01 + b.m01, a.m02 + b.m02, a.m03 + b.m03,
                a.m10 + b.m10, a.m11 + b.m11, a.m12 + b.m12, a.m13 + b.m13,
                a.m20 + b.m20, a.m21 + b.m21, a.m22 + b.m22, a.m23 + b.m23,
                a.m30 + b.m30, a.m31 + b.m31, a.m32 + b.m32, a.m33 + b.m33,
        };
}

tm_mat4 tm_mat4_sub(tm_mat4 a, tm_mat4 b) {
        return (tm_mat4){
                a.m00 - b.m00, a.m01 - b.m01, a.m02 - b.m02, a.m03 - b.m03,
                a.m10 - b.m10, a.m11 - b.m11, a.m12 - b.m12, a.m13 - b.m13,
                a.m20 - b.m20, a.m21 - b.m21, a.m22 - b.m22, a.m23 - b.m23,
                a.m30 - b.m30, a.m31 - b.m31, a.m32 - b.m32, a.m33 - b.m33,
        };
}

tm_mat4 tm_mat4_mul(tm_mat4 a, tm_mat4 b) {
        return (tm_mat4){
                a.m00 * b.m00, a.m01 * b.m01, a.m02 * b.m02, a.m03 * b.m03,
                a.m10 * b.m10, a.m11 * b.m11, a.m12 * b.m12, a.m13 * b.m13,
                a.m20 * b.m20, a.m21 * b.m21, a.m22 * b.m22, a.m23 * b.m23,
                a.m30 * b.m30, a.m31 * b.m31, a.m32 * b.m32, a.m33 * b.m33,
        };
}

tm_mat4 tm_mat4_div(tm_mat4 a, tm_mat4 b) {
        return (tm_mat4){
                a.m00 / b.m00, a.m01 / b.m01, a.m02 / b.m02, a.m03 / b.m03,
                a.m10 / b.m10, a.m11 / b.m11, a.m12 / b.m12, a.m13 / b.m13,
                a.m20 / b.m20, a.m21 / b.m21, a.m22 / b.m22, a.m23 / b.m23,
                a.m30 / b.m30, a.m31 / b.m31, a.m32 / b.m32, a.m33 / b.m33,
        };
}

tm_mat4 tm_mat4_addf(tm_mat4 a, float b) {
        return (tm_mat4){
                a.m00 + b, a.m01 + b, a.m02 + b, a.m03 + b,
                a.m10 + b, a.m11 + b, a.m12 + b, a.m13 + b,
                a.m20 + b, a.m21 + b, a.m22 + b, a.m23 + b,
                a.m30 + b, a.m31 + b, a.m32 + b, a.m33 + b,
        };
}

tm_mat4 tm_mat4_subf(tm_mat4 a, float b) {
        return (tm_mat4){
                a.m00 - b, a.m01 - b, a.m02 - b, a.m03 - b,
                a.m10 - b, a.m11 - b, a.m12 - b, a.m13 - b,
                a.m20 - b, a.m21 - b, a.m22 - b, a.m23 - b,
                a.m30 - b, a.m31 - b, a.m32 - b, a.m33 - b,
        };
}

tm_mat4 tm_mat4_mulf(tm_mat4 a, float b) {
        return (tm_mat4){
                a.m00 * b, a.m01 * b, a.m02 * b, a.m03 * b,
                a.m10 * b, a.m11 * b, a.m12 * b, a.m13 * b,
                a.m20 * b, a.m21 * b, a.m22 * b, a.m23 * b,
                a.m30 * b, a.m31 * b, a.m32 * b, a.m33 * b,
        };
}

tm_mat4 tm_mat4_divf(tm_mat4 a, float b) {
        return (tm_mat4){
                a.m00 / b, a.m01 / b, a.m02 / b, a.m03 / b,
                a.m10 / b, a.m11 / b, a.m12 / b, a.m13 / b,
                a.m20 / b, a.m21 / b, a.m22 / b, a.m23 / b,
                a.m30 / b, a.m31 / b, a.m32 / b, a.m33 / b,
        };
}

// ======== Affine =============================================

tm_mat4 tm_translate(tm_vec3 translation) {
        return (tm_mat4){
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
tm_mat4 tm_rotate(tm_vec3 axis, float degrees) {
        float c = cosf(tm_deg_to_rad(degrees));
        float s = sinf(tm_deg_to_rad(degrees));
        float t = 1.0f - c;

        tm_vec3 an = tm_vec3_norm(axis);
        tm_vec3 at = tm_vec3_mulf(an, t);
        tm_vec3 as = tm_vec3_mulf(an, s);

        return (tm_mat4){
                an.x * at.x + c,    an.y * at.x + as.z, an.z * at.x - as.y, 0.0f,
                an.x * at.y - as.z, an.y * at.y + c,    an.z * at.y + as.x, 0.0f,
                an.x * at.z + as.y, an.y * at.z + as.x, an.z * at.z + c,    0.0f,
                0.0f,               0.0f,               0.0f,               1.0f
        };
}

tm_mat4 tm_scale(tm_vec3 scale) {
        return (tm_mat4){
                .m00 = scale.x,
                .m11 = scale.y,
                .m22 = scale.z,
                .m33 = 1.0f
        };
}

tm_mat4 tm_lookat(tm_vec3 eye, tm_vec3 target, tm_vec3 up) {
        tm_vec3 f = tm_vec3_norm(tm_vec3_sub(target, eye));
        tm_vec3 r = tm_vec3_norm(tm_vec3_cross(f, up));
        tm_vec3 u = tm_vec3_cross(r, f);

        float rdot = -tm_vec3_dot(r, eye);
        float udot = -tm_vec3_dot(u, eye);
        float fdot = -tm_vec3_dot(f, eye);

        return (tm_mat4){
                 r.x,  u.x, -f.x, 0.0f,
                 r.y,  u.y, -f.y, 0.0f,
                 r.z,  u.z, -f.z, 0.0f,
                rdot, udot, fdot, 1.0f
        };
}

tm_mat4 tm_perspective(float fov_degrees, float aspect, float near, float far) {
        float fov = 1.0f / tanf(tm_deg2rad(fov_degrees) * 0.5f);
        float nf  = 1.0f / (near - far);

        return (tm_mat4){
                .m00 = fov / aspect,
                .m11 = fov,
                .m22 = (near + far) * nf,
                .m23 = -1.0f,
                .m32 = 2.0f * near * far * nf
        };
}

tm_mat4 tm_orthographic(float left, float right, float bottom, float top, float near, float far) {
        float rl =  1.0f / (right - left);
        float tb =  1.0f / (top - bottom);
        float fn = -1.0f / (far - near);

        return (tm_mat4){
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
