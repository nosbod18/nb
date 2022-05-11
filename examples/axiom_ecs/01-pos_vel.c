#define AXE_IMPL
#include "axiom_ecs.h"
#include <stdio.h>

typedef struct {
    double x, y;
} position_t, velocity_t;

void move(axe_world world, axe_id cpos, axe_id cvel) {
    axe_view view = axe_query(world, cpos, cvel);
    position_t  *p = view.components[0]; // Same order as passed into axe_query()
    velocity_t  *v = view.components[1];

    for (int i = 0; i < view.count; i++) {
        p[i].x += v[i].x;
        p[i].y += v[i].y;
        printf("entity %llu moved to {.x = %f, .y = %f}\n", view.entities[i], p[i].x, p[i].y);
    }
}

int main(void) {
    axe_world world;
    axe_init(&world);

    axe_id cpos = axe_create(world);
    axe_id cvel = axe_create(world);

    for (int i = 0; i < 8; i++) {
        axe_id e = axe_create(world);
        axe_set(world, e, cpos, &(position_t){1.f * i, 1.f * i});
        axe_set(world, e, cvel, &(velocity_t){1.f * i, 1.f * i});
    }

    // Normally this would be called each frame
    move(world, cpos, cvel);
    move(world, cpos, cvel);
    move(world, cpos, cvel);

    axe_deinit(&world);
}
