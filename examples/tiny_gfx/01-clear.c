#define TAPP_IMPL
#define TGFX_IMPL
#include "tiny_app.h"
#include "tiny_gfx.h"

tgfx_buffer    *cbo;
tgfx_pass_desc  pass;

bool init(void) {
        cbo = tgfx_buffer_create(&(tgfx_buffer_desc){
                .type = TGFX_BUFFER_TYPE_COMMAND,
        });

        pass = (tgfx_pass_desc){
                .colors[0] = { .action = TGFX_PASS_ACTION_CLEAR, .value = { 1.0f, 0.0f, 0.0f, 1.0f }}
        };

        return true;
}

void tick(double dt) {
        float g = pass.colors[0].value.g + 0.01f;
        pass.colors[0].value.g = g > 1.0f ? 0.0f : g;

        tgfx_pass_begin(cbo, &pass);
        tgfx_pass_end(cbo);
        tgfx_submit(cbo);
}

void quit(void) {
        tgfx_buffer_delete(cbo);
}

tapp_desc tapp_main(int argc, char **argv) {
        return (tapp_desc){
                .on_init = init,
                .on_tick = tick,
                .on_quit = quit
        };
}
