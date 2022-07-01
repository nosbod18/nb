#pragma once
#include <string.h> // memmove, memcpy
#include <stdlib.h> // realloc, free

// vec layout
// +------+------+-----+-----+-----+-----+
// |  -2  |  -1  |  0  |  1  |  2  |  3  |
// +------+------+-----+-----+-----+-----+
//   cap    len  ^-- User pointer

#define vec(T)                    T *
#define vec_free(v)               ((v) ? free(&vec__cap(v)), 0 : 0)
#define vec_len(v)                ((v) ? vec__len(v) : 0)
#define vec_cap(v)                ((v) ? vec__cap(v) : 0)
#define vec_clear(v)              ((v) ? vec__len(v) = 0, 0 : 0)
#define vec_reserve(v, n)         (vec_len(v) + (n) >= vec_cap(v) ? *((void **)&(v)) = vec__grow(v, vec_cap(v) * 2 + (n), sizeof *(v)), 0 : 0)
#define vec_pushn(v, n)           (vec_reserve(v, vec_len(v) + (n)), vec__len(v) += (n), &(v)[vec_len(v) - (n)])
#define vec_popn(v, n)            (vec__len(v) -= (n), &(v)[vec_len(v)])
#define vec_putn(v, i, n)         (memmove(vec_pushn(v, (i) + (n)), &(v)[i], sizeof *(v) * (vec_len(v) - (i) - (n)), &(v)[i])
#define vec_deln(v, i, n)         (vec__len(v) -= (n), memmove(&(v)[i], &(v)[(i) + (n)], sizeof *(v) * (vec_len(v) - (i) - (n))))
#define vec_push(v, x)            (*vec_pushn(v, 1) = x)
#define vec_pop(v)                (*vec_popn(v, 1))
#define vec_put(v, i, x)          (*vec_putn(v, i, 1) = x)
#define vec_del(v, i)             (vec_deln(v, i, 1))
#define vec_delswap(v, i)         ((v)[i] = vec_pop(v))
#define vec_for(i, v)             for (int (i) = 0; (i) < vec_len(v); (i)++)
#define vec_foreach(it, v, ...)   do { vec_for(_i__, v) { it = &(v)[_i__]; __VA_ARGS__ }} while (0)

#define vec__len(v)               (((int *)(v))[-1])
#define vec__cap(v)               (((int *)(v))[-2])

//
// IMPLEMENTATION
//

#ifdef __GNUC__
    #define _npow2(x) (x == 1 ? 1 : 1 << ((sizeof x) * 8 - __builtin_clzl(x - 1)))
#else
    #define _npow2(x)\
        (x--,\
         x |= x >> 1,\
         x |= x >> 2,\
         x |= x >> 4,\
         x |= x >> 8,\
         x |= x >> 16,\
         x |= (sizeof x) == 8 ? x >> 32 : 0,\
         x++)
#endif

static inline void *vec__grow(void *v, int n, int stride) {
    int m = _npow2(n);
    int size = m * stride + sizeof(int) * 2;
    int *ptr = realloc(v ? &vec__cap(v) : NULL, size);
    if (ptr != NULL) {
        memset(ptr + vec_len(v) * stride, 0, size - vec_len(v) * stride);
        *ptr++ = m;
        *ptr++ = vec_len(v);
    }
    return (void *)ptr;
}

#undef _npow2
