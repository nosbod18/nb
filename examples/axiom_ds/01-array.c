#define AXD_IMPL
#include "axiom_ds.h"
#include <stdio.h> // printf

void print_array(int *array) {
    printf("array = [ ");
    axd_array_foreach(int x, array, {
        printf("%d ", x);
    });
    printf("]\n");
}

int main(void) {
    int *array = NULL;

    for (int i = 0; i < 10; i++) {
        axd_array_push(array, i);
    }

    print_array(array);

    axd_array_ins(array, 3, 1);
    axd_array_ins(array, 3, 2);
    axd_array_ins(array, 3, 3);
    axd_array_ins(array, 3, 4);

    print_array(array);

    axd_array_clear(array);

    print_array(array);

    int *ptr = axd_array_pushn(array, 32);
    for (int i = 0; i < 32; i++) {
        ptr[i] = i;
    }

    axd_array_rem(array, 8);
    axd_array_remswap(array, 0);

    axd_array_free(array);
    axd_array_push(array, 1);
    axd_array_push(array, 2);
    axd_array_push(array, 3);

    print_array(array);

    axd_array_free(array);
}
