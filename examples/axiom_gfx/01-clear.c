#define AXA_IMPL
#define AXG_IMPL
#include "axiom_app.h"
#include "axiom_gfx.h"

axg_buffer    *cbo;
axg_pass_desc  pass;

bool init(void) {
    cbo = axg_buffer_create(&(axg_buffer_desc){
        .type = AXG_BUFFER_TYPE_COMMAND,
    });

    pass = (axg_pass_desc){
        .colors[0] = { .action = AXG_PASS_ACTION_CLEAR, .value = { 1.0f, 0.0f, 0.0f, 1.0f }}
    };

    return true;
}

void tick(double dt) {
    float g = pass.colors[0].value.g + 0.01f;
    pass.colors[0].value.g = g > 1.0f ? 0.0f : g;

    axg_pass_begin(cbo, &pass);
    axg_pass_end(cbo);
    axg_submit(cbo);
    axg_present();
}

void quit(void) {
    axg_buffer_delete(cbo);
}

axa_desc axa_main(int argc, char **argv) {
    return (axa_desc){
        .on_init = init,
        .on_tick = tick,
        .on_quit = quit
    };
}
