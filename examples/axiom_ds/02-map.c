#define AXIOM_DS_IMPL
#include "axiom_ds.h"
#include <stdio.h>

typedef struct custom_key_t {
    float f;
    char  c;
    int   i;
} custom_key_t;

#define print_map(m)\
    printf("[\"Hello world\"] = %d\n", map_get(map, "Hello world"));\
    printf("[\"Example\"    ] = %d\n", map_get(map, "Example"));\
    printf("[\"Testing\"    ] = %d\n", map_get(map, "Testing"));\
    printf("[\"Not in map\" ] = %d\n", map_get(map, "Not in map"))

int main(void) {
    struct {char const *key; int value; } *map = NULL;
    map_set_default(map, NULL, -1);

    int a = 4, b = 1, c = 100;
    map_set(map, "Hello world", a);
    map_set(map, "Example", b);
    map_set(map, "Testing", c);

    print_map(map);

    map_rem(map, "Hello world");
    map_rem(map, "Testing");

    print_map(map);

    map_free(map);
}
