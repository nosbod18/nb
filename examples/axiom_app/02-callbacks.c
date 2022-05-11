#define AXA_IMPL
#include "axiom_app.h"
#include <stdio.h>

bool init(void) {
    return true;
}

void event(axa_event const *event) {
    axa_log("Event type: %s", axa_event_type_string(event->type));
}

void tick(double dt) {
    axa_log("FPS: %.2f", 1.0 / dt);
}

void quit(void) {
}

axa_desc axa_main(int arc, char **argv) {
    return (axa_desc){
        .on_init  = init,
        .on_event = event,
        .on_tick  = tick,
        .on_quit  = quit,
    };
}
