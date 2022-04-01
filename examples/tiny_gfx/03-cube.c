#define TAPP_IMPL
#define TGFX_IMPL
#include "tiny_app.h"
#include "tiny_gfx.h"
#include "tiny_math.h"

tgfx_buffer   *vbo;
tgfx_buffer   *ibo;
tgfx_buffer   *cbo;
tgfx_program  *prg;
tgfx_pipeline *pip;
tm_float2      rot;

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

        vbo = tgfx_buffer_create(&(tgfx_buffer_desc){
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

        ibo = tgfx_buffer_create(&(tgfx_buffer_desc){
                .data = indices,
                .size = sizeof indices,
                .type = TGFX_BUFFER_TYPE_INDEX,
        });

        cbo = tgfx_buffer_create(&(tgfx_buffer_desc){
                .type = TGFX_BUFFER_TYPE_COMMAND,
        });

        prg = tgfx_program_create(&(tgfx_program_desc){
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
                                [0] = { .name = "u_mvp", .type = TGFX_UNIFORM_TYPE_MATRIX },
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

        pip = tgfx_pipeline_create(&(tgfx_pipeline_desc){
                .layout.attributes = {
                        [0] = { .type = TGFX_VERTEX_TYPE_FLOAT, .count = 3 },
                        [1] = { .type = TGFX_VERTEX_TYPE_FLOAT, .count = 4 },
                },
                .program = prg,
                .index_type = TGFX_INDEX_TYPE_UINT16,
        });

        return true;
}

void tick(double dt) {
        rot[0] += 1.0f * dt;
        rot[1] += 2.0f * dt;

        tm_int2 size;
        tapp_get_size(size);

        tm_float4x4 rxm, rym, proj, view, m, vp, mvp;
        tm_float4x4_rotate_x(rxm, rot[0]);
        tm_float4x4_rotate_y(rym, rot[1]);
        tm_float4x4_perspective(proj, 60.0f, (float)size[0] / (float)size[1], 0.01f, 10.0f);
        tm_float4x4_lookat(view, (tm_float3){0.0f, 1.5f, 6.0f}, (tm_float3){0}, (tm_float3){0.0f, 1.0f, 0.0f});

        tm_float4x4_mul(m, rxm, rym);
        tm_float4x4_mul(vp, proj, view);
        tm_float4x4_mul(mvp, vp, m);

        tgfx_pass_begin(cbo, &(tgfx_pass_desc){0});
                tgfx_program_update(prg, 0, &mvp); // 0 is the index from the .vs.uniforms array above
                tgfx_buffer_bind(cbo, vbo);
                tgfx_buffer_bind(cbo, ibo);
                tgfx_pipeline_bind(cbo, pip);
                tgfx_draw(cbo, 36, 0, 0);
        tgfx_pass_end(cbo);
        tgfx_submit(cbo);
        tgfx_present();
}

void quit(void) {
        tgfx_buffer_delete(vbo);
        tgfx_buffer_delete(ibo);
        tgfx_buffer_delete(cbo);
        tgfx_program_delete(prg);
        tgfx_pipeline_delete(pip);
}

tapp_desc tapp_main(int argc, char **argv) {
        return (tapp_desc){
                .on_init = init,
                .on_tick = tick,
                .on_quit = quit
        };
}
