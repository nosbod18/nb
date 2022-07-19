#include "memory.h"
#include <stdlib.h>
#include <string.h>

void *nbMemoryAlloc(size_t size) {
    return malloc(size);
}

void *nbMemoryZalloc(size_t size) {
    return calloc(1, size);
}

void *nbMemoryRealloc(void *block, size_t size) {
    return realloc(block, size);
}

void nbMemoryFree(void *block) {
    free(block);
}

void nbMemorySet(void *dest, int value, size_t size) {
    memset(dest, value, size);
}

void nbMemoryZero(void *dest, size_t size) {
    memset(dest, 0, size);
}

void nbMemoryMove(void *dest, void const *source, size_t size) {
    memmove(dest, source, size);
}

void nbMemoryCopy(void *dest, void const *source, size_t size) {
    memcpy(dest, source, size);
}
