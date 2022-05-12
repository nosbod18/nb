#define AXIOM_DS_IMPL
#include "axiom_ds.h"
#include <stddef.h> // size_t
#include <stdio.h>  // printf

void print_array(int *array) {
    printf("array = [ ");
    for (size_t i = 0; i < array_len(array); i++) {
        printf("%d ", array[i]);
    };
    printf("]\n");
}

int main(void) {
    int *array = NULL;

    for (int i = 0; i < 10; i++) {
        array_push(array, i);
    }

    print_array(array);

    array_ins(array, 3, 1);
    array_ins(array, 3, 2);
    array_ins(array, 3, 3);
    array_ins(array, 3, 4);

    print_array(array);

    array_clear(array);

    print_array(array);

    int *ptr = array_pushn(array, 32);
    for (int i = 0; i < 32; i++) {
        ptr[i] = i;
    }

    array_rem(array, 8);
    array_remswap(array, 0);

    array_push(array, 1);
    array_push(array, 2);
    array_push(array, 3);

    print_array(array);

    array_free(array);
}
