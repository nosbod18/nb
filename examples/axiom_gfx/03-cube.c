#define AXA_IMPL
#define AXG_IMPL
#include "axiom_app.h"
#include "axiom_gfx.h"
#include "axiom_math.h"

axg_buffer   *vbo;
axg_buffer   *ibo;
axg_buffer   *cbo;
axg_program  *prg;
axg_pipeline *pip;
axm_float2      rot;

bool init(void) {
    float const vertices[] = {
        -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, // -z
         1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
         1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f, // +z
         1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
         1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 1.0f, // -x
        -1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,  1.0f, 0.5f, 0.0f, 1.0f, // +x
         1.0f,  1.0f, -1.0f,  1.0f, 0.5f, 0.0f, 1.0f,
         1.0f,  1.0f,  1.0f,  1.0f, 0.5f, 0.0f, 1.0f,
         1.0f, -1.0f,  1.0f,  1.0f, 0.5f, 0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,  0.0f, 0.5f, 1.0f, 1.0f, // -y
        -1.0f, -1.0f,  1.0f,  0.0f, 0.5f, 1.0f, 1.0f,
         1.0f, -1.0f,  1.0f,  0.0f, 0.5f, 1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,  0.0f, 0.5f, 1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.5f, 1.0f, // +y
        -1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.5f, 1.0f,
         1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.5f, 1.0f,
         1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.5f, 1.0f
    };

    vbo = axg_buffer_create(&(axg_buffer_desc){
        .data = vertices,
        .size = sizeof vertices
    });

    unsigned short const indices[] = {
        0,  1,  2,   2,  3,  0, // -z
        4,  5,  6,   6,  7,  4, // +z
        8,  9, 10,  10, 11,  8, // -x
        12, 13, 14,  14, 15, 12, // +x
        16, 17, 18,  18, 19, 16, // -y
        20, 21, 22,  22, 23, 20  // +y
    };

    ibo = axg_buffer_create(&(axg_buffer_desc){
        .data = indices,
        .size = sizeof indices,
        .type = AXG_BUFFER_TYPE_INDEX,
    });

    cbo = axg_buffer_create(&(axg_buffer_desc){
        .type = AXG_BUFFER_TYPE_COMMAND,
    });

    prg = axg_program_create(&(axg_program_desc){
        .vs = {
            .source =
                "#version 330 core\n"
                "layout(location = 0) in vec3 a_pos;\n"
                "layout(location = 1) in vec4 a_color;\n"
                "uniform mat4 u_mvp;\n"
                "out vec4 v_color;\n"
                "void main(void) {\n"
                "       gl_Position = u_mvp * vec4(a_pos, 1.0);\n"
                "       v_color = a_color;\n"
                "}\n",
            .uniforms = {
                [0] = { .name = "u_mvp", .type = AXG_UNIFORM_TYPE_MATRIX },
            },
        },
        .fs.source =
            "#version 330 core\n"
            "in vec4 v_color;\n"
            "out vec4 f_color;\n"
            "void main(void) {\n"
            "       f_color = v_color;\n"
            "}\n",
    });

    pip = axg_pipeline_create(&(axg_pipeline_desc){
        .layout.attributes = {
            [0] = { .type = AXG_VERTEX_TYPE_FLOAT, .count = 3 },
            [1] = { .type = AXG_VERTEX_TYPE_FLOAT, .count = 4 },
        },
        .program = prg,
        .index_type = AXG_INDEX_TYPE_UINT16,
    });

    return true;
}

void tick(double dt) {
    rot[0] += 1.0f * dt;
    rot[1] += 2.0f * dt;

    axm_int2 size;
    axa_get_size(size);

    axm_float4x4 rxm, rym, proj, view, m, vp, mvp;
    axm_float4x4_rotate_x(rxm, rot[0]);
    axm_float4x4_rotate_y(rym, rot[1]);
    axmfloat4x4_perspective(proj, 60.0f, (float)size[0] / (float)size[1], 0.01f, 10.0f);
    axmfloat4x4_lookat(view, (axm_float3){0.0f, 1.5f, 6.0f}, (axm_float3){0}, (axm_float3){0.0f, 1.0f, 0.0f});

    axm_float4x4_mul(m, rxm, rym);
    axm_float4x4_mul(vp, proj, view);
    axm_float4x4_mul(mvp, vp, m);

    axg_pass_begin(cbo, &(axg_pass_desc){0});
    axg_program_update(prg, 0, &mvp); // 0 is the index from the .vs.uniforms array above
    axg_buffer_bind(cbo, vbo);
    axg_buffer_bind(cbo, ibo);
    axg_pipeline_bind(cbo, pip);
    axg_draw(cbo, 36, 0, 0);
    axg_pass_end(cbo);
    axg_submit(cbo);
    axg_present();
}

void quit(void) {
    axg_buffer_delete(vbo);
    axg_buffer_delete(ibo);
    axg_buffer_delete(cbo);
    axg_program_delete(prg);
    axg_pipeline_delete(pip);
}

axa_desc axa_main(int argc, char **argv) {
    return (axa_desc){
        .on_init = init,
        .on_tick = tick,
        .on_quit = quit
    };
}
