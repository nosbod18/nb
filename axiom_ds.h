/* axiom_ds.h - Generic data structures for C/C++ - v0.08 - public domain

========================================================================================================================

	YOU MUST

		#define AXIOM_DS_IMPL

	in EXACTLY _one_ C or C++ file that includes this header, BEFORE the
	include like this:

		#define AXIOM_DS_IMPL
		#include "axiom_ds.h"

	All other files should just #include "axiom_ds.h" without the #define

========================================================================================================================

LICENSE
	This software is placed under the public domain. See the end of this file
    for the full license.

CREDITS
	Written by Evan Dobson

TODOS
    -

VERSION HISTORY
    0.08  - Project name change
    0.07  - tds_sset and tds_smap implementation
    0.06  - Started documentation
    0.05  - Expanded tds_array and tds_map
    0.04  - tds_map start
    0.03  - Changed naming style
    0.02  - Basics of tds_array
    0.01  - Initial version
*/

#ifndef AXIOM_DS_H_
#define AXIOM_DS_H_

#include <stdbool.h>
#include <string.h> // memmove, memcpy
#include <stddef.h> // size_t
#include <stdint.h> // uint64_t

// Useful for defining variables in macros to avoid name collisions
#define var__(x)                     x##__LINE__##__

/// ## Buffer
/// ```
/// |             bytebuf             |
/// +----------+----------+----------+---------+---------+---------+---------+---------+---------+
/// |    -3    |    -2    |    -1    |    0    |    1    |    2    |    3    |    4    |   ...   |
/// +----------+----------+----------+---------+---------+---------+---------+---------+---------+
///   capacity    length    position ^--- User pointer
/// ```

typedef uint8_t byte;

#define bytebuf_reserve(b, sz)          (bytebuf_len(b) + (sz) >= bytebuf_cap(b) ? (b) = bytebuf__grow(b, bytebuf_cap(b) * 2 + (sz)), 0 : 0)
#define bytebuf_free(b)                 (bytebuf__grow(b, 0))
#define bytebuf_dup(dst, b)             ((b) ? bytebuf_reserve((dst), bytebuf_len(b)), memcpy((dst), (b), bytebuf_len(b)), 0 : 0)
#define bytebuf_cap(b)                  ((b) ? bytebuf__cap(b) : 0)
#define bytebuf_len(b)                  ((b) ? bytebuf__len(b) : 0)
#define bytebuf_pos(b)                  ((b) ? bytebuf__pos(b) : 0)
#define bytebuf_readn(b, T, n)          (bytebuf__pos(b) += (n) * sizeof(T), (T *)&(b)[bytebuf_pos(b)])
#define bytebuf_read(b, T)              (bytebuf_readn((b), (T), 1))
#define bytebuf_writen(b, T, vptr, n)   (bytebuf_reserve((b), (n) * sizeof(T)), bytebuf__len(b) += (n) * sizeof(T), memcpy(bytebuf_readn(b, T, n), (vptr), (n) * sizeof(T)))
#define bytebuf_write(b, T, v)          (bytebuf_writen((b), (T), &(v), 1))
#define bytebuf_clear(b)                ((b) ? bytebuf__len(b) = bytebuf__pos(b) = 0, 0 : 0)

#define bytebuf__head(b)                ((size_t *)(b) - 3)
#define bytebuf__cap(b)                 (bytebuf__head(b)[0])
#define bytebuf__len(b)                 (bytebuf__head(b)[1])
#define bytebuf__pos(b)                 (bytebuf__head(b)[2])
void   *bytebuf__grow                   (void *b, size_t size);

/// ## Array
/// Exactly the same as `bytebuf`

#define array_reserve(a, n)             (bytebuf_reserve(a, (n) * sizeof *(a)))
#define array_free(a)                   (bytebuf_free(a))
#define array_dup(dst, a)               (bytebuf_dup(dst, a))
#define array_cap(a)                    (bytebuf_cap(a) / sizeof *(a))
#define array_len(a)                    (bytebuf_len(a) / sizeof *(a))
#define array_insn(a, i, n)             (array__ensure(a, i), array_pushn((a), (n)), memmove(&(a)[(i) + (n)], &(a)[(i)], sizeof *(a) * (array_len(a) - (i) - (n))), &(a)[(i)])
#define array_ins(a, i, v)              (*array_insn(a, i, 1) = (v))
#define array_remn(a, i, n)             (array_len(a) >= (n) ? bytebuf__len(a) -= (n) * sizeof *(a), memmove(&(a)[(i)], &(a)[(i) + (n)], sizeof *(a) * (array_len(a) - (i) - (n))), 0 : 0)
#define array_rem(a, i)                 (array_remn(a, i, 1))
#define array_remswap(a, i)             (array_len(a) > 0 ? (a)[i] = array_pop(a), 0 : 0)
#define array_pushn(a, n)               (bytebuf__len(a) += (n) * sizeof *(a), bytebuf__pos(a) += (n) * sizeof *(a), &(a)[array_len(a) - (n)])
#define array_push(a, v)                (*array_pushn(a, 1) = (v))
#define array_pop(a)                    (bytebuf__len(a) -= sizeof *(a), (a)[array_len(a)])
#define array_clear(a)                  (bytebuf_clear(a))

#define array__ensure(a, i)             ((i) > array_cap(a) ? array_reserve(a, i), 0 : 0)

/// ## Map
/// ```
/// |             bytebuf            |         map         |
/// +----------+----------+----------+----------+----------+---------+---------+---------+---------+
/// |    -5    |    -4    |    -3    |    -2    |    -1    |    0    |    1    |    2    |   ...   |
/// +----------+----------+----------+----------+----------+---------+---------+-------------------+
///   capacity    length    position  hash/equal  default  ^--- User pointer
/// ```

typedef struct map__func_storage {
    uint64_t (*hash)(void const *);
    bool     (*equal)(void const *, void const *);
} map__func_storage;

#define map_free(m)                 (array_free(map__head(m)))
#define map_len(m)                  ((m) ? array_len(map__head(m)) : 0)
#define map_cap(m)                  ((m) ? array_cap(map__head(m)) : 0)
#define map_load_factor(m)          (map_cap(m) ? ((float)map_len(m) / (float)map_cap(m)) : 1.0f)
#define map_set_default(m, k, v)    do { map__ensure(m); map__default(m).key = (k); map__default(m).value = (v); } while (0)
#define map_set_funcs(m, h, e)      do { map__ensure(m); map__funcs(m) = (map__func_storage){ .hash = (h), .equal = (e) }; } while (0)
#define map_gets(m, k)              ((m)[map__indexof(m, sizeof *(m), &(k), sizeof (k), map__keyoff(m), map_cap(m))])
#define map_get(m, k)               (map_gets(m, k).value)
#define map_getp(m, k)              (&map_get(m, k))
#define map_has(m, k)               (map__indexof(m, sizeof *(m), &(k), sizeof (k), map__keyoff(m), map_cap(m)) != -1)
#define map_set(m, k, v)            do { map__ensure(m); map__set(m, k, v); } while (0)
#define map_rem(m, k)               (map_gets(m, k) = map__default(m), map__len(m)--)
#define map_clear(m)\
    do {\
        for (size_t var__(i) = 0; var__(i) < map_cap(m); var__(i)++) {\
            memcpy(&m[var__(i)], &map__default(m), sizeof *(m));\
        }\
        array_clear(map__head(m));\
    } while (0)

#define map__header_size(m)         (sizeof *(m) + sizeof(map__func_storage))
#define map__head(m)                ((char *)(m) - map__header_size(m))
#define map__cap(m)                 (bytebuf__cap(map__head(m)))
#define map__len(m)                 (bytebuf__len(map__head(m)))
#define map__default(m)             ((m)[-1])
#define map__funcs(m)               (*((map__func_storage *)map__head(m)))
#define map__hash(m, k, n)          (map__funcs(m).hash ? map__funcs(m).hash(k) : map__fnv1a(k, n))
#define map__equal(m, a, b, n)      (map__funcs(m).equal ? map__funcs(m).equal(a, b) : memcmp(a, b, n) == 0)
#define map__keyoff(m)              (((char *)&((m)[0].key)) - (char *)(m))

#define map__set(m, k, v)\
    do {\
        uint64_t var__(hash) = map__hash(m, &(k), sizeof (k));\
        size_t var__(i) = var__(hash) & (map_cap(m) - 1);\
        for (size_t var__(step) = 1, var__(c) = 0; var__(c) < map_cap(m); var__(c)++) {\
            var__(i) = (var__(i) + var__(step)++) & (map_cap(m) - 1);\
            if (map__equal(m, &(m)[var__(i)].key, &(k), sizeof (k)) == 0) {\
                break; /* k already exists in m, update it */\
            } else if (map__equal(m, &(m)[var__(i)].key, &map__default(m).key, sizeof (k)) == 0) {\
                map__len(m)++;\
                break; /* k does not exists in m, insert it */\
            }\
        }\
        memcpy(&(m)[var__(i)].key, &(k), sizeof (k));\
        memcpy(&(m)[var__(i)].value, &(v), sizeof (v));\
    } while (0)

#define map__ensure(m)\
    do {\
        if (map_load_factor(m) < 0.7f) {\
            break;\
        }\
        size_t var__(size) = _npow2((map_cap(m) ? map_cap(m) : 8) * sizeof *(m)) + map__header_size(m);\
        struct { char key[sizeof (m)[0].key]; char value[sizeof (m)[0].value]; } *var__(tmp) = bytebuf__grow(NULL, var__(size));\
        if ((m) != NULL) {\
            memcpy(map__head(var__(tmp)), map__head(m), map__header_size(var__(tmp)));\
            map_clear(var__(tmp));\
        }\
        for (size_t var__(i) = 0; var__(i) < map_cap(m); var__(i)++) {\
            map__set(var__(tmp), (m)[var__(i)].key, (m)[var__(i)].value);\
        }\
        memcpy(m, var__(tmp), sizeof *(m) * map_cap(m));\
        map_free(var__(tmp));\
    } while (0)

uint64_t map__fnv1a                 (void const *key, size_t size);
int      map__indexof               (void *m, size_t msize, void *k, size_t ksize, size_t koff, size_t cap);

/// ## Sparse Set

#define sset(T)                     struct { array(int) sparse; array(T) dense; }
#define sset_reserve(s, n)          (array_reserve((s).sparse, n), array_reserve((s).dense))
#define sset_free(s)                (array_free((s).sparse), array_free((s).dense))
#define sset_cap(s)                 (array_cap((s).dense))
#define sset_len(s)                 (array_len((s).dense))
#define sset_get(s, i)              ((s).dense[(s).sparse[(i) % array_len((s).sparse)]])
#define sset_push(s, v)             (sset__push(&(s).dense, (s).sparse, &(v), sizeof (v)))
#define sset_rem(s, i)\
    do {\
        if (sset_len(s) == 1) {\
            sset_clear(s);\
        } else if ((i) < array_len((s).sparse) && (s).sparse[(i)] != -1) {\
            for (size_t var__(j) = 0; var__(j) < array_len((s).sparse); var__(j)++) {\
                if ((s).sparse[var__(j)] == array_len((s).dense) - 1) {\
                    array_remswap((s).dense, (s).sparse[(i)]);\
                    (s).sparse[var__(j)] = (s).sparse[(i)];\
                    (s).sparse[(i)] = -1;\
                    bytebuf__len((s).sparse) -= sizeof *((s).dense);\
                }\
            }\
        }\
    } while (0)
#define sset_clear(s)               (array_clear((s).sparse), array_clear((s).dense))

size_t  sset__push                  (void **dense, int *sparse, void *v, size_t vsize);

/// ## Sparse Map

#define smap(K, V)                  struct { size_t tmp; struct { K key; size_t value; } map; sset(V) sset; }
#define smap_reserve(s, n)          (sset_reserve((s).sset, n))
#define smap_free(s)                (map_free((s).map), sset_free((s).sset))
#define smap_cap(s)                 (sset_cap((s).sset))
#define smap_len(s)                 (sset_len((s).sset))
#define smap_get(s, k)              (sset_get((s).sset, map_get((s).map, k)))
#define smap_set(s, k, v)           ((s).tmp = sset_push((s).sset, v), map_set((s).map, k, (s).tmp), (s).tmp)
#define smap_rem(s, k)              (sset_rem((s).sset, map_get((s).map, k)), map_rem((s).map, k))
#define smap_clear(s)               (map_clear((s).map), sset_clear((s).sset))


/***********************************************************************************************************************
************************************************************************************************************************
****                                                                                                                ****
****                                                                                                                ****
****                                                 Implementation                                                 ****
****                                                                                                                ****
****                                                                                                                ****
************************************************************************************************************************
***********************************************************************************************************************/


#if defined(AXIOM_DS_IMPL) || defined(AXIOM_IMPL)
#ifndef AXIOM_DS_C_
#define AXIOM_DS_C_

#include <stdlib.h> // calloc, realloc, free
#include <stdint.h> // uint64_t

static uint64_t _npow2(uint64_t x) {
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

void *bytebuf__grow(void *b, size_t size) {
    if (size == 0) {
        free(b ? bytebuf__head(b) : b);
        return NULL;
    }

    size_t *ptr = NULL;
    size = _npow2(size + sizeof(size_t) * 2);
    if (b != NULL) {
        ptr = realloc(bytebuf__head(b), size);
        memset(ptr + bytebuf_len(b), 0, size - bytebuf_len(b));
    } else {
        ptr = calloc(1, size);
    }
    if (ptr != NULL) {
        *ptr++ = size;
        *ptr++ = bytebuf_len(b);
    }
    return (void *)ptr;
}

uint64_t map__fnv1a(void const *key, size_t size) {
    uint64_t hash = 14695981039346656037UL;
    for (uint8_t const *p = key; size; size--, p++) {
        hash ^= (uint64_t)(*p);
        hash *= 1099511628211UL;
    }
    return hash;
}

int map__indexof(void *m, size_t msize, void *k, size_t ksize, size_t koff, size_t cap) {
    // map__hash and map__equal cannot be used here because m is a void *, which cannot be dereferenced like it would've been in map__head
    map__func_storage funcs = *((map__func_storage *)(msize + sizeof funcs));
    uint64_t hash = funcs.hash ? funcs.hash(k) : map__fnv1a(k, ksize);
    for (size_t i = hash & (cap - 1), step = 1, c = 0; c < cap; c++, i = (i + step++) & (cap - 1)) {
        void *cur = (char *)m + i * msize;
        void *key = (char *)cur + koff;
        if (funcs.equal != NULL ? funcs.equal(key, k) == true : memcmp(key, k, ksize) == 0) {
            return i;
        }
    }
    return -1;
}

size_t sset__push(void **dense, int *sparse, void *v, size_t vsize) {
    size_t i = 0;
    for (; i < array_len(sparse); i++) {
        if (sparse[i] == -1)
            break;
    }
    bytebuf_reserve(*dense, vsize);
    sparse[i] = bytebuf_len(*dense) / vsize;
    bytebuf_writen(*(char **)dense, char, v, vsize);
    bytebuf__len(sparse) += vsize;
    return i;
}

#endif // !AXIOM_DS_C_
#endif // AXIOM_DS_IMPL || AXIOM_IMPL
#endif // !AXIOM_DS_H_

/// ## License
/// This is free and unencumbered software released into the public domain.
/// Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
/// software, either in source code form or as a compiled binary, for any purpose,
/// commercial or non-commercial, and by any means.
///
/// In jurisdictions that recognize copyright laws, the author or authors of this
/// software dedicate any and all copyright interest in the software to the public
/// domain. We make this dedication for the benefit of the public at large and to
/// the detriment of our heirs and successors. We intend this dedication to be an
/// overt act of relinquishment in perpetuity of all present and future rights to
/// this software under copyright law.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
/// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
/// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///
/// For more information, please refer to <http://unlicense.org/>
