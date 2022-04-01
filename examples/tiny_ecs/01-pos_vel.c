#define TECS_IMPL
#include "tiny_ecs.h"
#include <stdio.h>

typedef struct {
        double x, y;
} position_t, velocity_t;

void move(tecs_world world, tecs_id cpos, tecs_id cvel) {
        tecs_view view = tecs_query(world, cpos, cvel);
        position_t  *p = view.components[0]; // Same order as passed into tecs_query()
        velocity_t  *v = view.components[1];

        for (int i = 0; i < view.count; i++) {
                p[i].x += v[i].x;
                p[i].y += v[i].y;
                printf("entity %llu moved to {.x = %f, .y = %f}\n", view.entities[i], p[i].x, p[i].y);
        }
}

int main(void) {
        tecs_world world;
        tecs_init(&world);

        tecs_id cpos = tecs_create(world);
        tecs_id cvel = tecs_create(world);

        for (int i = 0; i < 8; i++) {
                tecs_id e = tecs_create(world);
                tecs_set(world, e, cpos, &(position_t){1.f * i, 1.f * i});
                tecs_set(world, e, cvel, &(velocity_t){1.f * i, 1.f * i});
        }

        // Normally this would be called each frame
        move(world, cpos, cvel);
        move(world, cpos, cvel);
        move(world, cpos, cvel);

        tecs_deinit(&world);
}