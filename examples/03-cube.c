#define TINY_IMPLEMENTATION
#include "../tiny_app.h"
#include "../tiny_gfx.h"
#include "../tiny_math.h"

tgfx_buffer   *cbo;
tgfx_buffer   *vbo;
tgfx_buffer   *ibo;
tgfx_program  *prg;
tgfx_pipeline *pip;
tm_vec2        rot;

void init(void) {
        cbo = tgfx_buffer_create(&(tgfx_buffer_desc){
                .type = TGFX_BUFFER_TYPE_COMMAND,
        });

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
        });
}

bool event(tapp_event event) {
        return !(event.type == TAPP_EVENT_KEYUP && event.key.sym == TAPP_KEY_ESCAPE);
}

void update(float dt) {
        rot.x += 1.0f * dt;
        rot.y += 2.0f * dt;

        tm_mat4 rxm   = tm_rotate((tm_vec3){1.0f, 0.0f, 0.0f}, rot.x);
        tm_mat4 rym   = tm_rotate((tm_vec3){0.0f, 1.0f, 0.0f}, rot.y);
        tm_mat4 proj  = tm_perspective(60.0f, tapp_aspect_ratio(), 0.01f, 10.0f);
        tm_mat4 view  = tm_lookat((tm_vec3){0.0f, 1.5f, 6.0f}, (tm_vec3){0}, (tm_vec3){0.0f, 1.0f, 0.0f});
        tm_mat4 m     = tm_mat4_mul(rxm, rym);
        tm_mat4 vp    = tm_mat4_mul(proj, view);
        tm_mat4 mvp   = tm_mat4_mul(vp, m);

        tgfx_begin_pass(cbo, &(tgfx_PassDesc){0});
                tgfx_program_update(prg, 0, &mvp);
                tgfx_buffer_bind(cbo, vbo);
                tgfx_buffer_bind(cbo, ibo);
                tgfx_pipeline_bind(cbo, pip);
                tgfx_draw(cbo, 3, 0);
        tgfx_end_pass(cbo);

        tgfx_submit(cbo);
}

void quit(void) {
        tgfx_buffer_delete(cbo);
        tgfx_buffer_delete(vbo);
        tgfx_buffer_delete(ibo);
        tgfx_program_delete(prg);
        tgfx_pipeline_delete(pip);
}

tapp_desc tapp_main(int argc, char **argv) {
        return (tapp_desc){
                .window.title   = "tapp | Cube",
                .on_init        = init,
                .on_event       = event,
                .on_update      = update,
                .on_quit        = quit
        };
}
