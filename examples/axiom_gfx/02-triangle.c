#define AXIOM_APP_IMPL
#define AXIOM_GFX_IMPL
#include "axiom_app.h"
#include "axiom_gfx.h"

gfx_buffer   *vbo;
gfx_buffer   *cbo;
gfx_program  *prg;
gfx_pipeline *pip;

bool init(void) {
    float const vertices[] = {
         0.0f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
    };

    vbo = gfx_buffer_create(&(gfx_buffer_desc){
        .data = vertices,
        .size = sizeof vertices,
    });

    cbo = gfx_buffer_create(&(gfx_buffer_desc){
        .type = GFX_BUFFER_TYPE_COMMAND
    });

    prg = gfx_program_create(&(gfx_program_desc){
        .vs.source =
            "#version 330 core\n"
            "layout(location = 0) in vec2 a_pos;\n"
            "layout(location = 1) in vec4 a_color;\n"
            "out vec4 v_color;\n"
            "void main(void) {\n"
            "       gl_Position = vec4(a_pos, 0.0, 1.0);\n"
            "       v_color = a_color;\n"
            "}\n",
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
            [0] = { .type = GFX_VERTEX_TYPE_FLOAT, .count = 2 },
            [1] = { .type = GFX_VERTEX_TYPE_FLOAT, .count = 4 },
        },
        .program = prg,
    });

    return true;
}

void tick(double dt) {
    gfx_pass_begin(cbo, &(gfx_pass_desc){0});
        gfx_buffer_bind(cbo, vbo);
        gfx_pipeline_bind(cbo, pip);
        gfx_draw(cbo, 3, 0, 0);
    gfx_pass_end(cbo);
    gfx_submit(cbo);
    gfx_present();
}

void quit(void) {
    gfx_buffer_delete(vbo);
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
