#define TAPP_IMPL
#define TECS_IMPL
#include "../tiny_app.h"
#include "../tiny_ecs.h"

#include <stdio.h>

typedef struct {
        float x, y;
} position_t, velocity_t;

tecs_world *world;

void move(tecs_view view, double dt) {
        position_t *p = tecs_view_get(view, position_t, 0);
        velocity_t *v = tecs_view_get(view, velocity_t, 1);

        for (int i = 0; i < view.count; i++) {
                p[i].x += v[i].x * dt;
                p[i].y += v[i].y * dt;
                printf("entity %lu moved to {.x = %f, .y = %f}\n", view.entities[i], p[i].x, p[i].y);
        }
}

bool init(void) {
        world = tecs_world_create();
        tecs_component_register(world, position_t);
        tecs_component_register(world, velocity_t);
        tecs_system_register(world, move, position_t, velocity_t);

        for (int i = 0; i < 8; i++) {
                tecs_entity e = tecs_entity_create(world);
                tecs_entity_attach(world, e, position_t, {1.f * i, 1.f * i});
                tecs_entity_attach(world, e, velocity_t, {1.f * i, 1.f * i});
        }

        return true;
}

void tick(double dt) {
        tecs_world_tick(world, dt);
}

void quit(void) {
        tecs_world_delete(world);
}

tapp_desc tapp_main(int argc, char **argv) {
        return (tapp_desc){
                .window.title = "tapp | Entity Component System",
                .on_init      = init,
                .on_tick      = tick,
                .on_quit      = quit
        };
}
