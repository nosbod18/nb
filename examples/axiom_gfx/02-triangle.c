#define AXA_IMPL
#define AXG_IMPL
#include "axiom_app.h"
#include "axiom_gfx.h"

axg_buffer   *vbo;
axg_buffer   *cbo;
axg_program  *prg;
axg_pipeline *pip;

bool init(void) {
    float const vertices[] = {
         0.0f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
    };

    vbo = axg_buffer_create(&(axg_buffer_desc){
        .data = vertices,
        .size = sizeof vertices,
    });

    cbo = axg_buffer_create(&(axg_buffer_desc){
        .type = AXG_BUFFER_TYPE_COMMAND
    });

    prg = axg_program_create(&(axg_program_desc){
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

    pip = axg_pipeline_create(&(axg_pipeline_desc){
        .layout.attributes = {
            [0] = { .type = AXG_VERTEX_TYPE_FLOAT, .count = 2 },
            [1] = { .type = AXG_VERTEX_TYPE_FLOAT, .count = 4 },
        },
        .program = prg,
    });

    return true;
}

void tick(double dt) {
    axg_pass_begin(cbo, &(axg_pass_desc){0});
        axg_buffer_bind(cbo, vbo);
        axg_pipeline_bind(cbo, pip);
        axg_draw(cbo, 3, 0, 0);
    axg_pass_end(cbo);
    axg_submit(cbo);
    axg_present();
}

void quit(void) {
    axg_buffer_delete(vbo);
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
