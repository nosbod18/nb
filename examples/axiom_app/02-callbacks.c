#define AXIOM_APP_IMPL
#include "axiom_app.h"
#include <stdio.h>

bool init(void) {
    printf("Hello App!\n");
    return true;
}

void event(app_event const *event) {
    printf("Event type: %d at %f.2 seconds into program execution\n", event->type, event->time);
}

void tick(double dt) {
    // This is going to be a lot...
    printf("FPS: %.2f\n", 1.0 / dt);
}

void quit(void) {
    printf("Shutting down...\n");
}

app_desc app_main(int arc, char **argv) {
    return (app_desc){
        .on_init  = init,
        .on_event = event,
        .on_tick  = tick,
        .on_quit  = quit,
    };
}
