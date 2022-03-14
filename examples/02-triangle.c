#define TINY_APP_IMPL
#define TINY_GFX_IMPL
#include "../tiny_app.h"
#include "../tiny_gfx.h"

tgfx_buffer   *vbo = NULL;
tgfx_buffer   *cbo = NULL;
tgfx_program  *prg = NULL;
tgfx_pipeline *pip = NULL;

void init(void) {
        float const vertices[] = {
                 0.0f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f,
                 0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
                -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
        };

        vbo = tgfx_buffer_create(&(tgfx_buffer_desc){
                .data = vertices,
                .size = sizeof vertices,
        });

        cbo = tgfx_buffer_create(&(tgfx_buffer_desc){
                .type = TGFX_BUFFER_TYPE_COMMAND
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

void update(float dt) {
        tgfx_pass_begin(cbo, &(tgfx_pass_desc){0});
                tgfx_buffer_bind(cbo, vbo);
                tgfx_pipeline_bind(cbo, pip);
                tgfx_draw(cbo, 3, 0, 0);
        tgfx_pass_end(cbo);
        tgfx_submit(cbo);
}

void quit(void) {
        tgfx_buffer_delete(cbo);
        tgfx_buffer_delete(vbo);
        tgfx_program_delete(prg);
        tgfx_pipeline_delete(pip);
}

tapp_desc tapp_main(int argc, char **argv) {
        return (tapp_desc){
                .title     = "tapp | Triangle",
                .on_init   = init,
                .on_update = update,
                .on_quit   = quit
        };
}
