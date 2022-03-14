#define TINY_APP_IMPL
#define TINY_GFX_IMPL
#include "../tiny_app.h"
#include "../tiny_gfx.h"
#include "../tiny_math.h"

tgfx_buffer   *vbo;
tgfx_buffer   *ibo;
tgfx_buffer   *cbo;
tgfx_program  *prg;
tgfx_pipeline *pip;
float2         rot;

void init(void) {
        float const vertices[] = {
                -1.0f, -1.0f, -1.0f,   1.0f, 0.0f, 0.0f, 1.0f, // North
                 1.0f, -1.0f, -1.0f,   1.0f, 0.0f, 0.0f, 1.0f,
                 1.0f,  1.0f, -1.0f,   1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f,  1.0f, -1.0f,   1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f,  1.0f,   0.0f, 1.0f, 0.0f, 1.0f, // South
                 1.0f, -1.0f,  1.0f,   0.0f, 1.0f, 0.0f, 1.0f,
                 1.0f,  1.0f,  1.0f,   0.0f, 1.0f, 0.0f, 1.0f,
                -1.0f,  1.0f,  1.0f,   0.0f, 1.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, -1.0f,   0.0f, 0.0f, 1.0f, 1.0f, // East
                -1.0f,  1.0f, -1.0f,   0.0f, 0.0f, 1.0f, 1.0f,
                -1.0f,  1.0f,  1.0f,   0.0f, 0.0f, 1.0f, 1.0f,
                -1.0f, -1.0f,  1.0f,   0.0f, 0.0f, 1.0f, 1.0f,
                 1.0f, -1.0f, -1.0f,   1.0f, 0.5f, 0.0f, 1.0f, // West
                 1.0f,  1.0f, -1.0f,   1.0f, 0.5f, 0.0f, 1.0f,
                 1.0f,  1.0f,  1.0f,   1.0f, 0.5f, 0.0f, 1.0f,
                 1.0f, -1.0f,  1.0f,   1.0f, 0.5f, 0.0f, 1.0f,
                -1.0f, -1.0f, -1.0f,   0.0f, 0.5f, 1.0f, 1.0f, // Bottom
                -1.0f, -1.0f,  1.0f,   0.0f, 0.5f, 1.0f, 1.0f,
                 1.0f, -1.0f,  1.0f,   0.0f, 0.5f, 1.0f, 1.0f,
                 1.0f, -1.0f, -1.0f,   0.0f, 0.5f, 1.0f, 1.0f,
                -1.0f,  1.0f, -1.0f,   1.0f, 0.0f, 0.5f, 1.0f, // Top
                -1.0f,  1.0f,  1.0f,   1.0f, 0.0f, 0.5f, 1.0f,
                 1.0f,  1.0f,  1.0f,   1.0f, 0.0f, 0.5f, 1.0f,
                 1.0f,  1.0f, -1.0f,   1.0f, 0.0f, 0.5f, 1.0f
        };

        vbo = tgfx_buffer_create(&(tgfx_buffer_desc){
                .data = vertices,
                .size = sizeof vertices
        });

        unsigned short const indices[] = {
                 0,  1,  2,   2,  3,  0, // North
                 4,  5,  6,   6,  7,  4, // South
                 8,  9, 10,  10, 11,  8, // East
                12, 13, 14,  14, 15, 12, // West
                16, 17, 18,  18, 19, 16, // Bottom
                20, 21, 22,  22, 23, 20  // Top
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
                .vs.source =
                        "#version 330 core\n"
                        "layout(location = 0) in vec2 aPosition;\n"
                        "layout(location = 1) in vec4 aColor;\n"
                        "out vec4 vColor;\n"
                        "void main(void) {\n"
                        "       gl_Position = vec4(aPosition, 0.0, 1.0);\n"
                        "       vColor = aColor;\n"
                        "}\n",
                .fs.source =
                        "#version 330 core\n"
                        "in vec4 vColor;\n"
                        "out vec4 fColor;\n"
                        "void main(void) {\n"
                        "       fColor = vColor;\n"
                        "}\n",
        });

        pip = tgfx_pipeline_create(&(tgfx_pipeline_desc){
                .layout.attributes = {
                        [0] = { .type = TGFX_VERTEX_TYPE_FLOAT, .count = 2 },
                        [1] = { .type = TGFX_VERTEX_TYPE_FLOAT, .count = 4 },
                },
                .program = prg,
                .index_type = TGFX_INDEX_TYPE_UINT16,
        });
}

void update(float dt) {
        rot[0] += 1.0f * dt;
        rot[1] += 2.0f * dt;

        float4x4 rxm, rym, proj, view, m, vp, mvp;
        float4x4_rotate_x(rxm, rot[0]);
        float4x4_rotate_y(rym, rot[1]);

        float4x4_perspective(proj, 60.0f, tapp_aspect_ratio(), 0.01f, 10.0f);
        float4x4_lookat(view, (float3){0.0f, 1.5f, 6.0f}, (float3){0}, (float3){0.0f, 1.0f, 0.0f});

        float4x4_mul(m, rxm, rym);
        float4x4_mul(vp, proj, view);
        float4x4_mul(mvp, vp, m);

        tgfx_pass_begin(cbo, &(tgfx_pass_desc){0});
                tgfx_program_update(prg, 0, &mvp);
                tgfx_buffer_bind(cbo, vbo);
                tgfx_buffer_bind(cbo, ibo);
                tgfx_pipeline_bind(cbo, pip);
                tgfx_draw(cbo, 36, 0, 0);
        tgfx_pass_end(cbo);
        tgfx_submit(cbo);
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
                .title     = "tapp | Cube",
                .on_init   = init,
                .on_update = update,
                .on_quit   = quit
        };
}
