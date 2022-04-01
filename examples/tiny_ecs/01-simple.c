#define TAPP_IMPL
#define TECS_IMPL
#include "../../tiny_app.h"
#include "../../tiny_ecs.h"
#include <stdio.h>

typedef struct {
        double x, y;
} position_t, velocity_t;

tecs_world *world;
tecs_id cpos, cvel;

void move(double dt) {
        tecs_view view = tecs_query(world, cpos, cvel);
        position_t  *p = view.components[0];
        velocity_t  *v = view.components[1];

        for (int i = 0; i < view.count; i++) {
                p[i].x += v[i].x * dt;
                p[i].y += v[i].y * dt;
                printf("entity %llu moved to {.x = %f, .y = %f}\n", view.entities[i], p[i].x, p[i].y);
        }
}

int init(void) {
        if (!(world = tecs_alloc()))
                return 0;

        cpos = tecs_create(world);
        cvel = tecs_create(world);

        for (int i = 0; i < 8; i++) {
                tecs_id e = tecs_create(world);
                tecs_set(world, e, cpos, &(position_t){1.f * i, 1.f * i});
                tecs_set(world, e, cvel, &(velocity_t){1.f * i, 1.f * i});
        }

        return 1;
}

void tick(double dt) {
        move(dt);
}

void quit(void) {
        tecs_free(world);
}

tapp_desc tapp_main(int argc, char **argv) {
        return (tapp_desc){
                .on_init = init,
                .on_tick = tick,
                .on_quit = quit
        };
}
