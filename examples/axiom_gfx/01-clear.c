#define AXIOM_APP_IMPL
#define AXIOM_GFX_IMPL
#include "axiom_app.h"
#include "axiom_gfx.h"

gfx_buffer    *cbo;
gfx_pass_desc  pass;

bool init(void) {
    cbo = gfx_buffer_create(&(gfx_buffer_desc){
        .type = GFX_BUFFER_TYPE_COMMAND,
    });

    pass = (gfx_pass_desc){
        .colors[0] = { .action = GFX_PASS_ACTION_CLEAR, .value = { 1.0f, 0.0f, 0.0f, 1.0f }}
    };

    return true;
}

void tick(double dt) {
    float g = pass.colors[0].value.g + 0.01f;
    pass.colors[0].value.g = g > 1.0f ? 0.0f : g;

    gfx_pass_begin(cbo, &pass);
    gfx_pass_end(cbo);
    gfx_submit(cbo);
    gfx_present();
}

void quit(void) {
    gfx_buffer_delete(cbo);
}

app_desc app_main(int argc, char **argv) {
    return (app_desc){
        .on_init = init,
        .on_tick = tick,
        .on_quit = quit
    };
}
