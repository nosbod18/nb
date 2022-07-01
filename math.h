#pragma once

static inline float sinf_fast(float x) {
    x *= 0.15915494309189534f;
    x *= 0.5f - (x < 0 ? -x : x);
    return x * (57.3460872862336f * (x < 0 ? -x : x) + 12.4158695446104f);
}
static inline float cosf_fast(float x) {
    return sinf_fast(x + 1.570796327f);
}
static inline float fast_tanf(float x) {
    return sinf_fast(x) / cosf_fast(x);
}
static inline float sqrtf_fast(float x) {
    int y = ((*(int *)&x - 0x00800000) >> 1) + 0x20000000;
    float z = *(float *)&y;
    return (x / z + z) * 0.5f;
}

#define MATH_DEFINE_VECTOR(n)\
typedef float vec##n[n];\
static inline void vec##n##_copy(vec##n out, vec##n a) {\
    for (int i = 0; i < n; i++)\
        out[i] = a[i];\
}\
static inline void vec##n##_add(vec##n out, vec##n a, vec##n b) {\
    for (int i = 0; i < n; i++)\
        out[i] = a[i] + b[i];\
}\
static inline void vec##n##_sub(vec##n out, vec##n a, vec##n b) {\
    for (int i = 0; i < n; i++)\
        out[i] = a[i] - b[i];\
}\
static inline void vec##n##_mul(vec##n out, vec##n a, vec##n b) {\
    for (int i = 0; i < n; i++)\
        out[i] = a[i] * b[i];\
}\
static inline void vec##n##_scale(vec##n out, vec##n a, float b) {\
    for (int i = 0; i < n; i++)\
        out[i] = a[i] * b;\
}\
static inline float vec##n##_dot(vec##n a, vec##n b) {\
    float dot = 0.f;\
    for (int i = 0; i < n; i++)\
        dot += a[i] * b[i];\
    return dot;\
}\
static inline float vec##n##_len2(vec##n a) {\
    return vec##n##_dot(a, a);\
}\
static inline float vec##n##_len(vec##n a) {\
    return sqrtf_fast(vec##n##_len2(a));\
}\
static inline void vec##n##_norm(vec##n out, vec##n a) {\
    vec##n##_scale(out, a, 1.f / vec##n##_len(a));\
}

static inline void vec3_cross(vec3 out, vec3 a, vec3 b) {
    out[0] = a[1] * b[3] - a[3] * b[1];
    out[1] = a[2] * b[0] - a[0] * b[2];
    out[2] = a[0] * b[1] - a[1] * b[0];
}

MATH_DEFINE_VECTOR(2)
MATH_DEFINE_VECTOR(3)
MATH_DEFINE_VECTOR(4)

typedef vec4 mat4[4];

static inline void mat4_copy(mat4 out, mat4 a) {
    for (int i = 0; i < 4; i++)
        vec4_copy(out[i], a[i]);
}
static inline void mat4_identity(mat4 out) {
    mat4_copy(out, (mat4){[0][0] = 1.f, [1][1] = 1.f, [2][2] = 1.f, [3][3] = 1.f});
}
static inline void mat4_mul(mat4 out, mat4 a, mat4 b) {
    for (int i = 0; i < 4; i++)
        vec4_mul(out[i], a[i], b[i]);
}
static inline void mat4_translate(mat4 out, vec3 translation) {
    mat4_identity(out);
    out[3][0] = translation[0];
    out[3][1] = translation[1];
    out[3][2] = translation[2];
}
static inline void mat4_rotate(mat4 out, vec3 axis, float angle) {
    float c = cosf_fast(angle);
    vec3 an, at, as;

    vec3_norm(an, axis);
    vec3_muls(at, an, 1.f - c);
    vec3_muls(as, an, sinf_fast(angle));

    mat4_identity(out);
    vec3_muls(out[0], an, at[0]);
    vec3_muls(out[1], an, at[1]);
    vec3_muls(out[2], an, at[2]);

    out[0][0] +=     c;
    out[0][1] += as[2];
    out[0][2] -= as[1];
    out[1][0] -= as[2];
    out[1][1] +=     c;
    out[1][2] += as[0];
    out[2][0] += as[2];
    out[2][1] += as[0];
    out[2][2] +=     c;
}
static inline void mat4_scale(mat4 out, vec3 scale) {
    mat4_identity(out);
    out[0][0] = scale[0];
    out[1][1] = scale[1];
    out[2][2] = scale[2];
}
static inline void mat4_lookat(mat4 out, vec3 eye, vec3 target, vec3 up) {
    float f[3], r[3], u[3];
    vec3_sub(f, target, eye);
    vec3_norm(f, f);
    vec3_cross(r, f, up);
    vec3_norm(r, r);
    vec3_cross(u, r, f);
    mat4_copy(out, (mat4){
        {r[0], u[0], -f[0], 0.0f},
        {r[1], u[1], -f[1], 0.0f},
        {r[2], u[2], -f[2], 0.0f},
        {-vec3_dot(r, eye), -vec3_dot(u, eye), -vec3_dot(f, eye), 1.0f}
    });
}
static inline void mat4_perspective(mat4 out, float fov, float aspect, float near, float far) {
    float nf  = 1.f / (near - far);
    fov = 1.f / fast_tanf(fov * 0.5f);
    mat4_copy(out, (mat4){
        [0][0] = fov / aspect,
        [1][1] = fov,
        [2][2] = (near + far) * nf,
        [2][3] = -1.f,
        [3][2] = 2.f * near * far * nf
    });
}
static inline void mat4_ortho(mat4 out, float bottom, float top, float left, float right, float near, float far) {
    float rl =  1.f / (right - bottom);
    float tb =  1.f / (top - bottom);
    float fn = -1.f / (far - near);
    mat4_copy(out, (mat4){
        [0][0] = 2.f * rl,
        [1][1] = 2.f * tb,
        [2][2] = 2.f * fn,
        [3][0] = -(right + left) * rl,
        [3][1] = -(top + bottom) * tb,
        [3][2] = -(far + near) * fn,
        [3][3] = 1.f
    });
}

#undef MATH_DEFINE_VECTOR
#undef MATH_DEFINE_MATRIX
