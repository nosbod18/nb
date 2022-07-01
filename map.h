#pragma once
#include <string.h>
#include <stdint.h>

// map layout
// +------+------+------+------+-----+-----+-----+-----+
// |  -4  |  -3  |  -2  |  -1  |  0  |  1  |  2  |  3  |
// +------+------+------+------+-----+-----+-----+-----+
//   cap    len    tmp    def  ^-- User pointer

#define map(T)          T *
#define map_free(m)     (*((void **)&(m)) = map__grow(m, 0, 0))
#define map_len(m)      ((m) ? map__len(m) : 0)
#define map_cap(m)      ((m) ? map__cap(m) : 0)
#define map_geti(m, k)  (map__tmp(m).key = (k), map__index(m, sizeof *(m), &map__tmp(m).key, sizeof map__tmp(m).key, offsetof(*(m), key), map_cap(m)))
#define map_gets(m, k)  ((m)[map_geti(m, k)])
#define map_get(m, k)   (map_gets(m, k).value)
#define map_del(m, k)   (memcpy(&map_gets(m, k), &map__def(m), sizeof *(m)), map__len(m)--)

#define map_put(m, k, v) do {\
    map__tmp(m).key = (k);\
    int _i__ = map__hash(&map__tmp(m).key, sizeof map__tmp(m).key) & (map_cap(m) - 1);\
    for (int _step__ = 0;;_i__ = (_i__ + ++_step__) & (map_cap(m) - 1)) {\
        if (memcmp(&(m)[_i__].key, &map__tmp(m).key, sizeof map__tmp(m).key) == 0) {\
            break;\
        } else if (memcmp(&(m)[_i__].key, &map__def(m).key, sizeof map__def(m).key) == 0) {\
            (m)[_i__].key = k;\
            map__len(m)++;\
            break;\
        }\
    }\
    (m)[_i__].value = v;\
} while (0)

#define map_foreach(it, m, ...) do {\
    for (int _i__ = 0; _i__ < map_cap(m); _i__++) {\
        if (memcmp(&(m)[_i__], &map__def(m), sizeof *(m)) != 0) {\
            it = &(m)[_i__];\
            __VA_ARGS__\
        }\
    }\
} while (0)

#define map__ensure(m) do {\
    if (map_len(m) < map_cap(m) * 0.75f)\
        break;\
    char *_tmp__ = map__grow(m, map_cap(m) << 1, sizeof *(m));\
    for (int _i__ = 0; _i__ < map_cap(m); _i__++) {\
        map__tmp(m).key = (k);\
        int _j__ = map__hash(&map__tmp(m).key, sizeof map__tmp(m).key) & (map_cap(m) - 1);\
        for (;;_j__ = (_j__ + _c__) & (map_cap(m) - 1)) {\
            if (memcmp(&(m)[_j__].key, &map__tmp(m).key, sizeof map__tmp(m).key) == 0) {\
                break;\
            } else if (memcmp(&(m)[_j__].key, &map__def(m).key, sizeof map__def(m).key) == 0) {\
                (m)[_j__].key = k;\
                map__len(m)++;\
                break;\
            }\
        }\
        (m)[_j__].value = v;\
    }

} while (0)

#define  map__def(m)    ((m)[-1])
#define  map__tmp(m)    ((m)[-2])
#define  map__len(m)    (((int *)((m) - 2))[-1])
#define  map__cap(m)    (((int *)((m) - 2))[-2])

//
// IMPLEMENTATION
//

// fnv1a
static inline uint64_t map__hash(void *key, int size) {
    uint64_t hash = 14695981039346656037UL;
    for (uint8_t *p = key; size > 0; size--, p++) {
        hash ^= (uint64_t)(*p);
        hash *= 1099511628211UL;
    }
    return hash;
}

static inline int map__index(void *m, int stride, void *key, int ksize, int koff, int cap) {
    uint64_t hash = map__hash(key, ksize);
    for (int i = hash & (cap - 1), step = 1, c = 0; c < cap; c++, i = (i + ++step) & (cap - 1)) {
        char *cur = (char *)m + i * stride;
        if (memcmp(key, cur + koff, ksize) == 0)
            return i;
    }
    return -1;
}

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

static inline void *map__grow(void *v, int n, int stride) {
    int m = _npow2(n);
    int size = m * stride + sizeof(int) * 2 + stride * 2;
    int *ptr = realloc(v ? &map__cap(v) : NULL, size);
    if (ptr != NULL) {
        memset(ptr + map_len(v) * stride, 0, size - map_len(v) * stride);
        *ptr++ = m;
        *ptr++ = map_len(v);
    }
    return (void *)((char *)ptr + stride * 2);
}

#undef _npow2
