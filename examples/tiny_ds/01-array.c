#define TDS_IMPL
#include "tiny_ds.h"
#include <stdio.h> // printf

void print_array(int *array) {
        printf("array = [ ");
        tds_array_foreach(int x, array, {
                printf("%d ", x);
        });
        printf("]\n");
}

int main(void) {
        int *array = NULL;

        for (int i = 0; i < 10; i++) {
                tds_array_push(array, i);
        }

        print_array(array);

        tds_array_ins(array, 3, 1);
        tds_array_ins(array, 3, 2);
        tds_array_ins(array, 3, 3);
        tds_array_ins(array, 3, 4);

        print_array(array);

        tds_array_clear(array);

        print_array(array);

        int *ptr = tds_array_pushn(array, 32);
        for (int i = 0; i < 32; i++) {
                ptr[i] = i;
        }

        tds_array_del(array, 8);
        tds_array_delswap(array, 0);

        int *other = NULL;
        tds_array_dup(other, array);

        print_array(other);

        int x = tds_array_pop(other);
        printf("x = %d\n", x);

        tds_array_free(array);
        tds_array_push(array, 1);
        tds_array_push(array, 2);
        tds_array_push(array, 3);

        print_array(array);

        tds_array_free(array);
        tds_array_free(other);
}
