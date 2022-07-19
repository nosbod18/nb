#include "array.h"
#include "memory.h"
#include <stdint.h>

static uint64_t nextPowerOf2(uint64_t x) {
#ifdef __GNUC__
    return x == 1 ? 1 : 1 << ((sizeof x) * 8 - __builtin_clzl(x - 1));
#else
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    return x++;
#endif
}

void *_nbArrayGrow(void *a, int n, int stride) {
    int m = nextPowerOf2(n);
    int size = m * stride + sizeof(int) * 2;
    int *ptr = nbMemoryRealloc(a ? &_nbArrayGetCapacity(a) : 0, size);
    if (ptr) {
        nbMemoryZero(ptr + nbArrayGetLength(a) * stride, size - nbArrayGetLength(a) * stride);
        *ptr++ = m;
        *ptr++ = nbArrayGetLength(a);
    }
    return (void *)ptr;
}

