#define AXIOM_APP_IMPL
#define AXIOM_GFX_IMPL
#include "axiom_app.h"
#include "axiom_gfx.h"
#include "axiom_math.h"

gfx_buffer   *vbo;
gfx_buffer   *ibo;
gfx_buffer   *cbo;
gfx_program  *prg;
gfx_pipeline *pip;
float2        rot;

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

    vbo = gfx_buffer_create(&(gfx_buffer_desc){
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

    ibo = gfx_buffer_create(&(gfx_buffer_desc){
        .data = indices,
        .size = sizeof indices,
        .type = GFX_BUFFER_TYPE_INDEX,
    });

    cbo = gfx_buffer_create(&(gfx_buffer_desc){
        .type = GFX_BUFFER_TYPE_COMMAND,
    });

    prg = gfx_program_create(&(gfx_program_desc){
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
                [0] = { .name = "u_mvp", .type = GFX_UNIFORM_TYPE_MATRIX },
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

    pip = gfx_pipeline_create(&(gfx_pipeline_desc){
        .layout.attributes = {
            [0] = { .type = GFX_VERTEX_TYPE_FLOAT, .count = 3 },
            [1] = { .type = GFX_VERTEX_TYPE_FLOAT, .count = 4 },
        },
        .program = prg,
        .index_type = GFX_INDEX_TYPE_UINT16,
    });

    return true;
}

void tick(double dt) {
    rot[0] += 1.0f * dt;
    rot[1] += 2.0f * dt;

    int2 size;
    app_get_size(&size[0], &size[1]);

    float4x4 rxm, rym, proj, view, m, vp, mvp;
    float4x4_rotate_x(rxm, rot[0]);
    float4x4_rotate_y(rym, rot[1]);
    float4x4_perspective(proj, 60.0f, (float)size[0] / (float)size[1], 0.01f, 10.0f);
    float4x4_lookat(view, (float3){0.0f, 1.5f, 6.0f}, (float3){0}, (float3){0.0f, 1.0f, 0.0f});

    float4x4_mul(m, rxm, rym);
    float4x4_mul(vp, proj, view);
    float4x4_mul(mvp, vp, m);

    gfx_pass_begin(cbo, &(gfx_pass_desc){0});
    gfx_program_update(prg, 0, &mvp); // 0 is the index from the .vs.uniforms array above
    gfx_buffer_bind(cbo, vbo);
    gfx_buffer_bind(cbo, ibo);
    gfx_pipeline_bind(cbo, pip);
    gfx_draw(cbo, 36, 0, 0);
    gfx_pass_end(cbo);
    gfx_submit(cbo);
    gfx_present();
}

void quit(void) {
    gfx_buffer_delete(vbo);
    gfx_buffer_delete(ibo);
    gfx_buffer_delete(cbo);
    gfx_program_delete(prg);
    gfx_pipeline_delete(pip);
}

app_desc app_main(int argc, char **argv) {
    return (app_desc){
        .on_init = init,
        .on_tick = tick,
        .on_quit = quit
    };
}
