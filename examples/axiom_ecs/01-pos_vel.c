#define AXIOM_ECS_IMPL
#include "axiom_ecs.h"
#include <stdio.h>

typedef struct {
    double x, y;
} position_t, velocity_t;

void move(ecs_world *world, ecs_id cpos, ecs_id cvel) {
    ecs_view view = ecs_query(world, cpos, cvel);
    position_t *p = view.components[0]; // Same order as passed into ecs_query()
    velocity_t *v = view.components[1]; // TODO: Find a better way to access these?

    for (size_t i = 0; i < view.count; i++) {
        p[i].x += v[i].x;
        p[i].y += v[i].y;
        printf("entity %llu moved to {.x = %f, .y = %f}\n", view.entities[i], p[i].x, p[i].y);
    }
}

int main(void) {
    ecs_world *world = ecs_alloc();

    ecs_id cpos = ecs_create(world);
    ecs_id cvel = ecs_create(world);

    for (int i = 0; i < 8; i++) {
        ecs_id e = ecs_create(world);
        ecs_set(world, e, cpos, &(position_t){1.f * i, 1.f * i});
        ecs_set(world, e, cvel, &(velocity_t){1.f * i, 1.f * i});
    }

    // Normally this would be called each frame
    move(world, cpos, cvel);
    move(world, cpos, cvel);
    move(world, cpos, cvel);

    ecs_free(world);
}
