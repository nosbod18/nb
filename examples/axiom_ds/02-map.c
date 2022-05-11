#define AXD_IMPL
#include "axiom_ds.h"
#include <stdio.h>

typedef struct custom_key_t {
    float f;
    char  c;
    int   i;
} custom_key_t;

#define print_map(m)\
    printf("[\"Hello world\"] = %d\n", axd_map_get(map, "Hello world"));\
    printf("[\"Example\"    ] = %d\n", axd_map_get(map, "Example"));\
    printf("[\"Testing\"    ] = %d\n", axd_map_get(map, "Testing"));\
    printf("[\"Not in map\" ] = %d\n", axd_map_get(map, "Not in map"))

int main(void) {
    struct {char const *key; int value; } *map = NULL;
    axd_map_set_default(map, NULL, -1);

    axd_map_ins(map, "Hello world", 4);
    axd_map_ins(map, "Example", 1);
    axd_map_ins(map, "Testing", 100);

    print_map(map);

    axd_map_rem(map, "Hello world");
    axd_map_rem(map, "Testing");

    print_map(map);

    axd_map_foreachp(int *x, map, {
        *x++;
    });

    print_map(map);

    axd_map_free(map);
}
