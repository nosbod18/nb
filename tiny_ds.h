/// # tiny_ds.h
/// A collection of generic data structures. Since C has no notion of a template and the like, the generic functionality in this library comes from
/// the use of macros, and with macros come no type checking and hard to debug errors. Most of the macros that could cause an error try to do some
/// checking and make sure the structure has enough capacity and everything, but some care is still required.
///
/// Since this is a single header library, the private api will be available to use in the file where `TDS_IMPL` or `TINY_IMPL` is defined.
/// While it is not strictly forbidden to use this internal api, it is dicouraged and the internal functions and macros have been marked as such using
/// two consecutive underscores in their name. If you would like to use them, go ahead, but know that they do not have any of what little checking the public api provides.

#ifndef __tiny_ds_h__
#define __tiny_ds_h__

#include <string.h> // memmove, memcpy
#include <stdint.h> // uint64_t
#include <stddef.h> // size_t

// Useful for defining variables in macros to avoid name collisions
#define         tds__var(x)                     tds__var_##x##__LINE__##__

/// ## Array
/// ```
/// |        array        |
/// +----------+----------+---------+---------+---------+---------+---------+---------+---------+
/// |    -2    |    -1    |    0    |    1    |    2    |    3    |    4    |    5    |   ...   |
/// +----------+----------+---------+---------+---------+---------+---------+---------+---------+
///   capacity    length  ^--- User pointer
/// ```

#define         tds_array_reserve(a, n)         (tds_buffer_reserve(a, (n) * sizeof *(a)))
#define         tds_array_free(a)               ((a) ? free(tds_array__head(a)), 0 : 0)
#define         tds_array_dup(dst, a)           ((a) ? memcpy(tds_array_pushn(dst, tds_array_len(a)), (a), tds_array_len(a) * sizeof *(a)), 0 : 0)
#define         tds_array_cap(a)                ((a) ? tds_array__cap(a) : 0)
#define         tds_array_len(a)                ((a) ? tds_array__len(a) : 0)
#define         tds_array_insn(a, i, n)         (tds_array__ensure(a, i, n), memmove(tds_array_pushn(a, n), &(a)[(i)], sizeof *(a) * (tds_array_len(a) - (n) - (i))), &(a)[(i)])
#define         tds_array_ins(a, i, v)          (*tds_array_insn(a, i, 1) = (v))
#define         tds_array_remn(a, i, n)         (tds_array_len(a) >= (n) ? tds_array__len(a) -= (n) * sizeof *(a), memmove(&(a)[(i)], &(a)[(i) + (n)], sizeof *(a) * (tds_array_len(a) - (n) - (i))), 0 : 0)
#define         tds_array_rem(a, i)             (tds_array_remn(a, i, 1))
#define         tds_array_remswap(a, i)         (tds_array_len(a) ? (a)[(i)] = tds_array_pop(a), 0 : 0)
#define         tds_array_remval(a, v, cmp)     do { tds_array_for(tds__var(i), a) { if (cmp(a[tds__var(i)], (v)) == 0) { tds_array_rem(a, tds__var(i)); break; }}} while (0)
#define         tds_array_pushn(a, n)           (tds_array__ensure(a, 0, n), tds_array__len(a) += (n), &(a)[tds_array_len(a) - (n)])
#define         tds_array_push(a, v)            (*tds_array_pushn(a, 1) = (v), tds_array_len(a) - 1)
#define         tds_array_pop(a)                ((a)[--tds_array__len(a)])
#define         tds_array_clear(a)              (tds_array_len(a) ? tds_array__len(a) = 0, 0 : 0)
#define         tds_array_for(i, a)             for (size_t (i) = 0; (i) < tds_array_len(a); (i)++)
#define         tds_array_foreach(x, a, ...)    tds_array_for(tds__var(i), a) { (x) = (a)[tds__var(i)]; __VA_ARGS__ }

#define         tds_array__head(a)              ((size_t *)(a) - 2)
#define         tds_array__cap(a)               (tds_array__head(a)[0])
#define         tds_array__len(a)               (tds_array__head(a)[1])
#define         tds_array__ensure(a, i, n)      (tds_array_len(a) + (n) + (i) >= tds_array_cap(a) ? (a) = tds_array__grow(a, sizeof *(a), tecs__npow2(tds_array_cap(a) * 2 + (n) + (i))), 0 : 0)
static void    *tds_array__grow                 (void *a, size_t asize, size_t n);

/// ## Map
/// ```
/// |        array        |         map         |
/// +----------+----------+----------+----------+---------+---------+---------+---------+---------+
/// |    -4    |    -3    |    -2    |    -1    |    0    |    1    |    2    |    3    |   ...   |
/// +----------+----------+----------+----------+---------+---------+---------+-------------------+
///   capacity    length    hash/cmp    default ^--- User pointer
/// ```

#define tds_map_free(m)                 (tds_array_free(tds_map__head(m)))
#define tds_map_len(m)                  ((m) ? tds_array_len(tds_map__head(m)) : 0)
#define tds_map_cap(m)                  ((m) ? tds_array_cap(tds_map__head(m)) : 0)
#define tds_map_load_factor(m)          (tds_map_cap(m) ? ((float)tds_map_len(m) / (float)tds_map_cap(m)) : 1.0f)
#define tds_map_set_default(m, k, v)    do { tds_map__ensure(m); tds_map__default(m).key = (k); tds_map__default(m).value = (v); } while (0)
#define tds_map_set_funcs(m, h, c)      do { tds_map__ensure(m); tds_map__funcs(m) = (tds_map__func_storage){ .hash = (h), .cmp = (c) }; } while (0)
#define tds_map_gets(m, k)              ((m)[tds_map__indexof(m, sizeof *(m), &(k), sizeof (k), tds_map__keyoff(m), tds_map_cap(m))])
#define tds_map_get(m, k)               (tds_map_gets(m, k).value)
#define tds_map_getp(m, k)              (&tds_map_get(m, k))
#define tds_map_has(m, k)               (tds_map__indexof(m, sizeof *(m), &(k), sizeof (k), tds_map__keyoff(m), tds_map_cap(m)) != -1)
#define tds_map_set(m, k, v)            do { tds_map__ensure(m); tds_map__ins(m, k, v); } while (0)
#define tds_map_rem(m, k)               (tds_map_gets(m, k) = tds_map__default(m), tds_map__len(m)--)
#define tds_map_clear(m)\
                do {\
                        for (size_t tds__var(i) = 0; tds__var(i) < tds_map_cap(m); tds__var(i)++) {\
                                memcpy(&m[tds__var(i)], &tds_map__default(m), sizeof *(m));\
                        }\
                        tds_array_clear(tds_map__head(m));\
                } while (0)

#define tds_map_for(i, m)               for (size_t (i) = 0; (i) < tds_map_cap(m); (i)++)
#define tds_map_foreach(x, m, ...)      tds_map_for(tds__var(i), m) { if (tds_map__cmp(m, &(m)[tds__var(i)], &tds_map__default(m), sizeof *(m)) == 0) { (x) = (m)[tds__var(i)]; __VA_ARGS__ }}

typedef struct tds_map__func_storage {
        uint64_t (*hash)(void const *);
        int      (*cmp)(void const *, void const *);
} tds_map__func_storage;

#define tds_map__header_size(m)         (sizeof *(m) + sizeof(tds_map__func_storage))
#define tds_map__head(m)                ((char *)(m) - tds_map__header_size(m))
#define tds_map__cap(m)                 (tds_array__cap(tds_map__head(m)))
#define tds_map__len(m)                 (tds_array__len(tds_map__head(m)))
#define tds_map__default(m)             ((m)[-1])
#define tds_map__funcs(m)               (*((tds_map__func_storage *)tds_map__head(m)))
#define tds_map__hash(m, k, n)          (tds_map__funcs(m).hash ? tds_map__funcs(m).hash(k) : tds_map__fnv1a(k, n))
#define tds_map__cmp(m, a, b, n)        (tds_map__funcs(m).cmp ? tds_map__funcs(m).cmp(a, b) : memcmp(a, b, n))
#define tds_map__keyoff(m)              (((char *)&((m)[0].key)) - (char *)(m))
#define tds_map__ins(m, k, v)\
                do {\
                        uint64_t tds__var(hash) = tds_map__hash(m, &(k), sizeof (k));\
                        int tds__var(i) = tds__var(hash) & (tds_map_cap(m) - 1);\
                        for (size_t tds__var(step) = 1, tds__var(c) = 0; tds__var(c) < tds_map_cap(m); tds__var(c)++) {\
                                tds__var(i) = (tds__var(i) + tds__var(step)++) & (tds_map_cap(m) - 1);\
                                if (tds_map__cmp(m, &(m)[tds__var(i)].key, &(k), sizeof (k)) == 0) {\
                                        break; /* k already exists in m, update it */\
                                } else if (tds_map__cmp(m, &(m)[tds__var(i)].key, &tds_map__default(m).key, sizeof (k)) == 0) {\
                                        tds_map__len(m)++;\
                                        break; /* k does not exists in m, insert it */\
                                }\
                        }\
                        memcpy(&(m)[tds__var(i)].key, &(k), sizeof (k));\
                        memcpy(&(m)[tds__var(i)].value, &(v), sizeof (v));\
                } while (0)

#define tds_map__ensure(m)\
                do {\
                        if (tds_map_load_factor(m) < 0.7f) {\
                                break;\
                        }\
                        size_t tds__var(size) = tecs__npow2((tds_map_cap(m) ? tds_map_cap(m) : 8) * sizeof *(m)) + tds_map__header_size(m);\
                        struct { char key[sizeof (m)[0].key]; char value[sizeof (m)[0].value]; } *tds__var(tmp) = tds_buffer__grow(NULL, tds__var(size));\
                        if ((m) != NULL) {\
                                memcpy(tds_map__head(tds__var(tmp)), tds_map__head(m), tds_map__header_size(tds__var(tmp)));\
                                tds_map_clear(tds__var(tmp));\
                        }\
                        for (size_t tds__var(i) = 0; tds__var(i) < tds_map_cap(m); tds__var(i)++) {\
                                tds_map__ins(tds__var(tmp), (m)[tds__var(i)].key, (m)[tds__var(i)].value);\
                        }\
                        memcpy(m, tds__var(tmp), sizeof *(m) * tds_map_cap(m));\
                        tds_map_free(tds__var(tmp));\
                } while (0)

static uint64_t tds_map__fnv1a                  (void const *key, size_t size);
static int      tds_map__indexof                (void *m, size_t msize, void *k, size_t ksize, size_t koff, size_t cap);

/// ## Sparse Set

#define         tds_sset(T)                     struct { T tmp; tds_array(int) sparse; tds_array(T) dense; }
#define         tds_sset_reserve(s, n)          (tds_array_reserve((s).sparse, n), tds_array_reserve((s).dense))
#define         tds_sset_free(s)                (tds_array_free((s).sparse), tds_array_free((s).dense))
#define         tds_sset_cap(s)                 (tds_array_cap((s).dense))
#define         tds_sset_len(s)                 (tds_array_len((s).dense))
#define         tds_sset_clear(s)               (tds_array_clear((s).sparse), tds_array_clear((s).dense))
#define         tds_sset_get(s, i)              ((s).dense[(s).sparse[(i) % tds_array_len((s).sparse)]])
#define         tds_sset_ins(s, v)              ((s).tmp = v, tds_sset__ins((s).dense, (s).sparse, &(s).tmp, sizeof *((s).dense)))
#define         tds_sset_rem(s, i)\
                do {\
                        if (tds_sset_len(s) == 1) {\
                                tds_sset_clear(s);\
                        } else if ((i) < tds_array_len((s).sparse) && (s).sparse[(i)] != -1) {\
                                for (int tds__var(j) = 0; tds__var(j) < tds_array_len((s).sparse); tds__var(j)++) {\
                                        if ((s).sparse[tds__var(j)] == tds_array_len((s).dense) - 1) {\
                                                tds_array_remswap((s).dense, (s).sparse[(i)]); /* remete data */\
                                                (s).sparse[tds__var(j)] = (s).sparse[(i)]; /* Swap handles */\
                                                (s).sparse[(i)] = -1; /* Invalidate remeted handle */\
                                                tds_array__len((s).sparse)--;\
                                        }\
                                }\
                        }\
                } while (0)

#define         tds_sset_foreach(x, s, ...)     tds_array_foreach(x, (s).dense, __VA_ARGS__)
#define         tds_sset_foreachp(x, s, ...)    tds_array_foreachp(x, (s).dense, __VA_ARGS__)

int             tds_sset__ins                   (void *dense, int *sparse, void *v, int vsize);


/// ## Sparse Map

#define         tds_smap(K, V)                  struct { int tmp; struct { K key; int value; } map; tds_sset(V) sset; }
#define         tds_smap_reserve(s, n)          (tds_map_reserve((s).map, n), tds_sset_reserve((s).sset, n))
#define         tds_smap_free(s)                (tds_map_free((s).map), tds_sset_free((s).sset))
#define         tds_smap_cap(s)                 (tds_sset_cap((s).sset))
#define         tds_smap_len(s)                 (tds_sset_len((s).sset))
#define         tds_smap_clear(s)               (tds_map_clear((s).map), tds_sset_clear((s).sset))

#define         tds_smap_get(s, k)              (tds_sset_get((s).sset, tds_map_get((s).map, k)))
#define         tds_smap_set(s, k, v)           ((s).tmp = tds_sset_ins((s).sset, v), tds_map_set((s).map, k, (s).tmp), (s).tmp)
#define         tds_smap_rem(s, k)              (tds_sset_rem((s).sset, tds_map_get((s).map, k)), tds_map_rem((s).map, k))

#define         tds_smap_foreach(x, s, ...)     tds_sset_foreach(x, (s).sset, __VA_ARGS__)
#define         tds_smap_foreachp(x, s, ...)    tds_sset_foreachp(x, (s).sset, __VA_ARGS__)


/************************************************************************************************************************************************************
*************************************************************************************************************************************************************
****                                                                                                                                                     ****
****                                                                                                                                                     ****
****                                                                   Implementation                                                                    ****
****                                                                                                                                                     ****
****                                                                                                                                                     ****
*************************************************************************************************************************************************************
************************************************************************************************************************************************************/


#if defined(TDS_IMPL) || defined(TINY_IMPL)
#ifndef __tiny_ds_c__
#define __tiny_ds_c__

#include <stdlib.h> // calloc, realloc, free
#include <stdint.h> // uint64_t


static void *tds_array__grow(void *a, size_t asize, size_t n) {
        size_t *ptr = NULL;
        size_t size = n * asize + sizeof n * 2;
        if (a != NULL) {
                ptr = realloc(tds_array__head(a), size);
                memset(ptr + tds_array_len(a) * asize, 0, size - tds_array_len(a) * asize);
        } else {
                ptr = calloc(1, n * asize);
        }
        if (ptr != NULL) {
                *ptr++ = n;
                *ptr++ = tds_array_len(a);
        }
        return (void *)ptr;
}

static uint64_t tds_map__fnv1a(void const *key, size_t size) {
        uint64_t hash = 14695981039346656037UL;
        for (uint8_t const *p = key; size; size--, p++) {
                hash ^= (uint64_t)(*p);
                hash *= 1099511628211UL;
        }
        return hash;
}

static int tds_map__indexof(void *m, size_t msize, void *k, size_t ksize, size_t koff, size_t cap) {
        // tds_map__hash and tds_map__cmp cannot be used here because m is a void *, which cannot be dereferenced like it would've been in tds_map__head
        tds_map__func_storage funcs = *((tds_map__func_storage *)(msize + sizeof funcs));
        uint64_t hash = funcs.hash ? funcs.hash(k) : tds_map__fnv1a(k, ksize);
        for (size_t i = hash & (cap - 1), step = 1, c = 0; c < cap; c++, i = (i + step++) & (cap - 1)) {
                void *cur = (char *)m + i * msize;
                void *key = (char *)cur + koff;
                if ((funcs.cmp ? funcs.cmp(key, k) : memcmp(key, k, ksize)) == 0) {
                        return i;
                }
        }
        return -1;
}


int tds_sset__ins(void *dense, int *sparse, void *v, int vsize) {
        int i = 0;
        for (; i < tds_array_len(sparse); i++) {
                if (sparse[i] == -1)
                        break;
        }

        tds_buffer__ensure(dense, vsize);
        memcpy(&((char *)dense)[tds_array_len(dense) * vsize], v, vsize); // TODO: implement some sort of tds_array_pushbytes?
        sparse[i] = tds_array_len(dense);

        tds_array__len(dense)++;
        tds_array__len(sparse)++;
        return i;
}

#endif // !__tiny_ds_c__
#endif // TDS_IMPLEMENTATION || TINY_IMPLEMENTATION
#endif // !__tiny_ds_h__


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