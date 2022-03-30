#define TAPP_IMPL
#define TECS_IMPL
#include "tiny_app.h"
#include "tiny_ecs.h"
#include <stdio.h>

typedef struct {
        double x, y;
} position_t, velocity_t;

tecs_world world;
tecs_id cpos, cvel;

/*

void move(double dt) {
        world.query([&](position_t &p, velocity_t const &v) {
                p.x += v.x * dt;
                p.y += v.y * dt;
        });
}

*/

void move(double dt) {
        tecs_view view = tecs_query(&world, 2, cpos, cvel);
        position_t  *p = view.columns[0];
        velocity_t  *v = view.columns[1];

        for (int i = 0; i < view.count; i++) {
                p[i].x += v[i].x * dt;
                p[i].y += v[i].y * dt;
                printf("entity %llu moved to {.x = %f, .y = %f}\n", view.entities[i], p[i].x, p[i].y);
        }
}

bool init(void) {
        if (!tecs_init(&world, 8, 2))
                return false;

        cpos = tecs_register(&world, sizeof(position_t), 8);
        cvel = tecs_register(&world, sizeof(velocity_t), 8);

        for (int i = 0; i < 8; i++) {
                tecs_id e = tecs_new(&world);
                tecs_add(&world, e, cpos, &(position_t){1.f * i, 1.f * i});
                tecs_add(&world, e, cvel, &(velocity_t){1.f * i, 1.f * i});
        }

        return true;
}

void tick(double dt) {
        move(dt);
}

void quit(void) {
        tecs_fini(&world);
}

tapp_desc tapp_main(int argc, char **argv) {
        return (tapp_desc){
                .on_init = init,
                .on_tick = tick,
                .on_quit = quit
        };
}
