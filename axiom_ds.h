#ifndef AXIOM_DS_H_
#define AXIOM_DS_H_

#include <string.h> // memmove, memcpy
#include <stdint.h> // uint64_t
#include <stddef.h> // size_t
#include <stdlib.h> // free

// Useful for defining variables in macros to avoid name collisions
#define         axd__var(x)                     axd__var_##x##__LINE__##__

/// ## Buffer
/// ```
/// |             buffer             |
/// +----------+----------+----------+---------+---------+---------+---------+---------+---------+
/// |    -3    |    -2    |    -1    |    0    |    1    |    2    |    3    |    4    |   ...   |
/// +----------+----------+----------+---------+---------+---------+---------+---------+---------+
///   capacity    length    position ^--- User pointer
/// ```

typedef uint8_t axd_byte;

#define axd_buffer_reserve(b, sz)       (axd_buffer_len(b) + (sz) >= axd_buffer_cap(b) ? (b) = axd_buffer__grow(b, axd_buffer_cap(b) * 2 + (sz)), 0 : 0)
#define axd_buffer_free(b)              ((b) != NULL ? free(axd_buffer__head(b)), 0 : 0)
#define axd_buffer_dup(dst, b)          ((b) != NULL ? axd_buffer_reserve((dst), axd_buffer_len(b)), memcpy((dst), (b), axd_buffer_len(b)), 0 : 0)
#define axd_buffer_cap(b)               ((b) != NULL ? axd_buffer__cap(b) : 0)
#define axd_buffer_len(b)               ((b) != NULL ? axd_buffer__len(b) : 0)
#define axd_buffer_pos(b)               ((b) != NULL ? axd_buffer__pos(b) : 0)
#define axd_buffer_readn(b, T, n)       (axd_buffer__pos(b) += (n) * sizeof(T), *(T *)&(b)[axd_buffer_pos(b)])
#define axd_buffer_read(b, T)           (axd_buffer_readn((b), (T), 1))
#define axd_buffer_writen(b, T, vptr, n)(axd_buffer_reserve((b), (n) * sizeof(T)), axd_buffer__len(b) += (n) * sizeof(T), memcpy(axd_buffer_readn((b), (T), (n)), (vptr), (n) * sizeof *(T))
#define axd_buffer_write(b, T, v)       (axd_buffer_writen((b), (T), &(v), 1))
#define axd_buffer_clear(b)             ((b) != NULL ? axd_buffer__len(b) = axd_buffer__pos(b) = 0, 0 : 0)

#define axd_buffer__head(b)             ((size_t *)(b) - 3)
#define axd_buffer__cap(b)              (axd_buffer__head(b)[0])
#define axd_buffer__len(b)              (axd_buffer__head(b)[1])
#define axd_buffer__pos(b)              (axd_buffer__head(b)[2])
void   *axd_buffer__grow                (void *b, size_t size);

/// ## Array
/// Exactly the same as `axd_buffer`

#define axd_array_reserve(a, n)         (axd_buffer_reserve(a, (n) * sizeof *(a)))
#define axd_array_free(a)               (axd_buffer_free(a))
#define axd_array_dup(dst, a)           (axd_buffer_dup((dst), (a)))
#define axd_array_cap(a)                (axd_buffer_cap(a) / sizeof *(a))
#define axd_array_len(a)                (axd_buffer_len(a) / sizeof *(a))
#define axd_array_insn(a, i, v, n)      (axd_array__ensure((a), (i)), axd_array_pushn((a), (n)), memmove(&(a)[(i) + (n)], &(a)[(i)], sizeof *(a) * (axd_array_len(a) - (i) - (n))))
#define axd_array_ins(a, i, v)          (*axd_array_insn((a), (i), 1) = (v))
#define axd_array_remn(a, i, n)         (axd_array_len(a) >= (n) ? axd_buffer__len(a) -= (n) * sizeof *(a), memmove(&(a)[(i)], &(a)[(i) + (n)], sizeof *(a) * (axd_array_len(a) - (i) - (n))), 0 : 0)
#define axd_array_rem(a, i)             (axd_array_remn((a), (i), 1))
#define axd_array_remswap(a, i)         (axd_array_len(a) > 0 ? (a)[(i)] = axd_array_pop(a), 0 : 0)
#define axd_array_remval(a, v, eqfn)    do { axd_array_for(axd__var(i), (a)) { if (eqfn(a[axd__var(i)], (v)) == 0) { axd_array_rem((a), axd__var(i)); break; }}} while (0)
#define axd_array_pushn(a, vptr, n)     (axd_array_reserve((a), (n)), axd_buffer_writen(a, char, vptr, (n) * sizeof *(a)))
#define axd_array_push(a, v)            (axd_array_pushn((a), &(v), 1))
#define axd_array_pop(a)                (axd_buffer__len(a) -= sizeof *(a), (a)[axd_array_len(a)])
#define axd_array_clear(a)              (axd_buffer_clear(a))
#define axd_array_for(i, a)             for (size_t (i) = 0; (i) < axd_array_len(a); (i)++)
#define axd_array_foreach(x, a, ...)    axd_array_for(axd__var(i), a) { x = (a)[axd__var(i)]; __VA_ARGS__ }

#define axd_array__ensure(a, i)         ((i) > axd_array_cap(a) ? axd_array_reserve(a, i), 0 : 0)

/// ## Map
/// ```
/// |             buffer             |         map         |
/// +----------+----------+----------+----------+----------+---------+---------+---------+---------+
/// |    -5    |    -4    |    -3    |    -2    |    -1    |    0    |    1    |    2    |   ...   |
/// +----------+----------+----------+----------+----------+---------+---------+-------------------+
///   capacity    length    position   hash/cmp    default ^--- User pointer
/// ```

typedef struct axd_map__func_storage {
        uint64_t (*hash)(void const *);
        int      (*cmp)(void const *, void const *);
} axd_map__func_storage;

#define axd_map_free(m)                 (axd_array_free(axd_map__head(m)))
#define axd_map_len(m)                  ((m) ? axd_array_len(axd_map__head(m)) : 0)
#define axd_map_cap(m)                  ((m) ? axd_array_cap(axd_map__head(m)) : 0)
#define axd_map_load_factor(m)          (axd_map_cap(m) ? ((float)axd_map_len(m) / (float)axd_map_cap(m)) : 1.0f)
#define axd_map_set_default(m, k, v)    do { axd_map__ensure(m); axd_map__default(m).key = (k); axd_map__default(m).value = (v); } while (0)
#define axd_map_set_funcs(m, h, c)      do { axd_map__ensure(m); axd_map__funcs(m) = (axd_map__func_storage){ .hash = (h), .cmp = (c) }; } while (0)
#define axd_map_gets(m, k)              ((m)[axd_map__indexof(m, sizeof *(m), &(k), sizeof (k), axd_map__keyoff(m), axd_map_cap(m))])
#define axd_map_get(m, k)               (axd_map_gets(m, k).value)
#define axd_map_getp(m, k)              (&axd_map_get(m, k))
#define axd_map_has(m, k)               (axd_map__indexof(m, sizeof *(m), &(k), sizeof (k), axd_map__keyoff(m), axd_map_cap(m)) != -1)
#define axd_map_set(m, k, v)            do { axd_map__ensure(m); axd_map__ins(m, k, v); } while (0)
#define axd_map_rem(m, k)               (axd_map_gets(m, k) = axd_map__default(m), axd_map__len(m)--)
#define axd_map_clear(m)\
                do {\
                        axd_map_for(axd__var(i), m) {\
                                memcpy(&m[axd__var(i)], &axd_map__default(m), sizeof *(m));\
                        }\
                        axd_array_clear(axd_map__head(m));\
                } while (0)

#define axd_map_for(i, m)               for (size_t (i) = 0; (i) < axd_map_cap(m); (i)++)
#define axd_map_foreach(x, m, ...)      axd_map_for(axd__var(i), m) { if (axd_map__cmp(m, &(m)[axd__var(i)], &axd_map__default(m), sizeof *(m)) == 0) { (x) = (m)[axd__var(i)]; __VA_ARGS__ }}

#define axd_map__header_size(m)         (sizeof *(m) + sizeof(axd_map__func_storage))
#define axd_map__head(m)                ((char *)(m) - axd_map__header_size(m))
#define axd_map__cap(m)                 (axd_buffer__cap(axd_map__head(m)))
#define axd_map__len(m)                 (axd_buffer__len(axd_map__head(m)))
#define axd_map__default(m)             ((m)[-1])
#define axd_map__funcs(m)               (*((axd_map__func_storage *)axd_map__head(m)))
#define axd_map__hash(m, k, n)          (axd_map__funcs(m).hash ? axd_map__funcs(m).hash(k) : axd_map__fnv1a(k, n))
#define axd_map__cmp(m, a, b, n)        (axd_map__funcs(m).cmp ? axd_map__funcs(m).cmp(a, b) : memcmp(a, b, n))
#define axd_map__keyoff(m)              (((char *)&((m)[0].key)) - (char *)(m))
#define axd_map__ins(m, k, v)\
    do {\
        uint64_t axd__var(hash) = axd_map__hash(m, &(k), sizeof (k));\
        int axd__var(i) = axd__var(hash) & (axd_map_cap(m) - 1);\
        for (size_t axd__var(step) = 1, axd__var(c) = 0; axd__var(c) < axd_map_cap(m); axd__var(c)++) {\
            axd__var(i) = (axd__var(i) + axd__var(step)++) & (axd_map_cap(m) - 1);\
            if (axd_map__cmp(m, &(m)[axd__var(i)].key, &(k), sizeof (k)) == 0) {\
                break; /* k already exists in m, update it */\
            } else if (axd_map__cmp(m, &(m)[axd__var(i)].key, &axd_map__default(m).key, sizeof (k)) == 0) {\
                axd_map__len(m)++;\
                break; /* k does not exists in m, insert it */\
            }\
        }\
        memcpy(&(m)[axd__var(i)].key, &(k), sizeof (k));\
        memcpy(&(m)[axd__var(i)].value, &(v), sizeof (v));\
    } while (0)

#define axd_map__ensure(m)\
    do {\
        if (axd_map_load_factor(m) < 0.7f) {\
            break;\
        }\
        size_t axd__var(size) = axe__npow2((axd_map_cap(m) ? axd_map_cap(m) : 8) * sizeof *(m)) + axd_map__header_size(m);\
        struct { char key[sizeof (m)[0].key]; char value[sizeof (m)[0].value]; } *axd__var(tmp) = axd_buffer__grow(NULL, axd__var(size));\
        if ((m) != NULL) {\
            memcpy(axd_map__head(axd__var(tmp)), axd_map__head(m), axd_map__header_size(axd__var(tmp)));\
            axd_map_clear(axd__var(tmp));\
        }\
        axd_map_for(axd__var(i), m) {\
            axd_map__ins(axd__var(tmp), (m)[axd__var(i)].key, (m)[axd__var(i)].value);\
        }\
        memcpy(m, axd__var(tmp), sizeof *(m) * axd_map_cap(m));\
        axd_map_free(axd__var(tmp));\
    } while (0)

uint64_t axd_map__fnv1a                 (void const *key, size_t size);
int      axd_map__indexof               (void *m, size_t msize, void *k, size_t ksize, size_t koff, size_t cap);

/// ## Sparse Set

#define axd_sset(T)                     struct { axd_array(ssize_t) sparse; axd_array(T) dense; }
#define axd_sset_reserve(s, n)          (axd_array_reserve((s).sparse, n), axd_array_reserve((s).dense))
#define axd_sset_free(s)                (axd_array_free((s).sparse), axd_array_free((s).dense))
#define axd_sset_cap(s)                 (axd_array_cap((s).dense))
#define axd_sset_len(s)                 (axd_array_len((s).dense))
#define axd_sset_get(s, i)              ((s).dense[(s).sparse[(i) % axd_array_len((s).sparse)]])
#define axd_sset_push(s, v)             (axd_sset__push(&(s).dense, (s).sparse, &(v), sizeof (v)))
#define axd_sset_rem(s, i)\
    do {\
        if (axd_sset_len(s) == 1) {\
            axd_sset_clear(s);\
        } else if ((i) < axd_array_len((s).sparse) && (s).sparse[(i)] != -1) {\
            for (int axd__var(j) = 0; axd__var(j) < axd_array_len((s).sparse); axd__var(j)++) {\
                if ((s).sparse[axd__var(j)] == axd_array_len((s).dense) - 1) {\
                    axd_array_remswap((s).dense, (s).sparse[(i)]);\
                    (s).sparse[axd__var(j)] = (s).sparse[(i)];\
                    (s).sparse[(i)] = -1;\
                    axd_buffer__len((s).sparse) -= sizeof *((s).dense);\
                }\
            }\
        }\
    } while (0)
#define axd_sset_clear(s)               (axd_array_clear((s).sparse), axd_array_clear((s).dense))

#define axd_sset_foreach(x, s, ...)     axd_array_foreach(x, (s).dense, __VA_ARGS__)
#define axd_sset_foreachp(x, s, ...)    axd_array_foreachp(x, (s).dense, __VA_ARGS__)

size_t  axd_sset__push                  (void **dense, ssize_t *sparse, void *v, size_t vsize);

/// ## Sparse Map

#define axd_smap(K, V)                  struct { size_t tmp; struct { K key; ssize_t value; } map; axd_sset(V) sset; }
#define axd_smap_reserve(s, n)          (axd_sset_reserve((s).sset, n))
#define axd_smap_free(s)                (axd_map_free((s).map), axd_sset_free((s).sset))
#define axd_smap_cap(s)                 (axd_sset_cap((s).sset))
#define axd_smap_len(s)                 (axd_sset_len((s).sset))
#define axd_smap_get(s, k)              (axd_sset_get((s).sset, axd_map_get((s).map, k)))
#define axd_smap_set(s, k, v)           ((s).tmp = axd_sset_push((s).sset, v), axd_map_set((s).map, k, (s).tmp), (s).tmp)
#define axd_smap_rem(s, k)              (axd_sset_rem((s).sset, axd_map_get((s).map, k)), axd_map_rem((s).map, k))
#define axd_smap_clear(s)               (axd_map_clear((s).map), axd_sset_clear((s).sset))
#define axd_smap_foreach(x, s, ...)     axd_sset_foreach(x, (s).sset, __VA_ARGS__)
#define axd_smap_foreachp(x, s, ...)    axd_sset_foreachp(x, (s).sset, __VA_ARGS__)


/************************************************************************************************************************************************************
*************************************************************************************************************************************************************
****                                                                                                                                                     ****
****                                                                                                                                                     ****
****                                                                   Implementation                                                                    ****
****                                                                                                                                                     ****
****                                                                                                                                                     ****
*************************************************************************************************************************************************************
************************************************************************************************************************************************************/


#if defined(AXD_IMPL) || defined(AXIOM_IMPL)
#ifndef AXIOM_DS_C_
#define AXIOM_DS_C_

#include <stdlib.h> // calloc, realloc, free
#include <stdint.h> // uint64_t

static uint64_t axd__npow2(uint64_t x) {
#ifdef __GNUC__
    return x == 1 ? 1 : 1 << (64 - __builtin_clzl(x - 1));
#else
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    return x;
#endif
}

void *axd_buffer__grow(void *b, size_t size) {
    size_t *ptr = NULL;
    size = axd__npow2(size + sizeof(size_t) * 2);
    if (b != NULL) {
        ptr = realloc(axd_buffer__head(b), size);
        memset(ptr + axd_buffer_len(b), 0, size - axd_buffer_len(b));
    } else {
        ptr = calloc(1, size);
    }
    if (ptr != NULL) {
        *ptr++ = size;
        *ptr++ = axd_buffer_len(b);
    }
    return (void *)ptr;
}

uint64_t axd_map__fnv1a(void const *key, size_t size) {
    uint64_t hash = 14695981039346656037UL;
    for (uint8_t const *p = key; size; size--, p++) {
        hash ^= (uint64_t)(*p);
        hash *= 1099511628211UL;
    }
    return hash;
}

int axd_map__indexof(void *m, size_t msize, void *k, size_t ksize, size_t koff, size_t cap) {
    // axd_map__hash and axd_map__cmp cannot be used here because m is a void *, which cannot be dereferenced like it would've been in axd_map__head
    axd_map__func_storage funcs = *((axd_map__func_storage *)(msize + sizeof funcs));
    uint64_t hash = funcs.hash ? funcs.hash(k) : axd_map__fnv1a(k, ksize);
    for (size_t i = hash & (cap - 1), step = 1, c = 0; c < cap; c++, i = (i + step++) & (cap - 1)) {
        void *cur = (char *)m + i * msize;
        void *key = (char *)cur + koff;
        if ((funcs.cmp ? funcs.cmp(key, k) : memcmp(key, k, ksize)) == 0) {
            return i;
        }
    }
    return -1;
}

size_t axd_sset__push(void **dense, ssize_t *sparse, void *v, size_t vsize) {
    size_t i = 0;
    for (; i < axd_array_len(sparse); i++) {
        if (sparse[i] == -1)
            break;
    }
    axd_buffer_reserve(*dense, vsize);
    sparse[i] = axd_buffer_len(*dense) / vsize;
    axd_buffer_writen(*(char **)dense, char, v, vsize);
    axd_buffer__len(sparse) += vsize;
    return i;
}

#endif // !AXIOM_DS_C_
#endif // AXD_IMPL || AXIOM_IMPL
#endif // !AXIOM_DS_H_


/// ## License
/// This software is available under 2 licenses -- choose whichever you prefer.
///
/// #### ALTERNATIVE A - MIT License
/// Copyright (c) 2022 Evan Dobson
/// Permission is hereby granted, free of charge, to any person obtaining a copy of
/// this software and associated documentation files (the "Software"), to deal in
/// the Software without restriction, including without limitation the rights to
/// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
/// of the Software, and to permit persons to whom the Software is furnished to do
/// so, subject to the following conditions:
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.
///
/// #### ALTERNATIVE B - Public Domain (www.unlicense.org)
/// This is free and unencumbered software released into the public domain.
/// Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
/// software, either in source code form or as a compiled binary, for any purpose,
/// commercial or non-commercial, and by any means.
/// In jurisdictions that recognize copyright laws, the author or authors of this
/// software dedicate any and all copyright interest in the software to the public
/// domain. We make this dedication for the benefit of the public at large and to
/// the detriment of our heirs and successors. We intend this dedication to be an
/// overt act of relinquishment in perpetuity of all present and future rights to
/// this software under copyright law.
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
/// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
/// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
