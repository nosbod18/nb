/* nb_ds.h - v0.10 - public domain
    Generic data structures in C/C++

    Table of Contents
    -----------------
    Table of Contents
    Summary
    Usage
    Example
    Documentation
    Version History
    Licence

    Summary
    -------
    TODO

    Usage
    -----
    To use this library, do this in *one* C or C++ file:

        #define NB_DS_IMPLEMENTATION
        #include "nb_ds.h"

    Then include it as normal in all other files.

    Example
    -------
    TODO

    Documentation
    -------------
    TODO

    Version History
    ---------------
    0.10  - Removed nb_sset and nb_smap
    0.09  - Project name change
    0.08  - tds_buffer implementation
    0.07  - tds_sset and tds_smap implementation
    0.06  - Started documentation
    0.05  - Expanded tds_array and tds_map
    0.04  - tds_map start
    0.03  - Changed naming style
    0.02  - Basics of tds_array
    0.01  - Initial version

    License
    -------
    This is free and unencumbered software released into the public domain.
    Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
    software, either in source code form or as a compiled binary, for any purpose,
    commercial or non-commercial, and by any means.

    In jurisdictions that recognize copyright laws, the author or authors of this
    software dedicate any and all copyright interest in the software to the public
    domain. We make this dedication for the benefit of the public at large and to
    the detriment of our heirs and successors. We intend this dedication to be an
    overt act of relinquishment in perpetuity of all present and future rights to
    this software under copyright law.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
    ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

    For more information, please refer to <http://unlicense.org/>
*/

#ifndef _nb_ds_h_
#define _nb_ds_h_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef nbd_u64
    #ifdef nb_u64
        #define nbd_u64 nb_u64
    #else
        #include <stdint.h>
        #define nbd_u64 uint64_t
    #endif
#endif

#ifndef nbd_usize
    #ifdef nb_usize
        #define nbd_usize nb_usize
    #else
        #include <stddef.h>
        #define nbd_usize size_t
    #endif
#endif

#ifndef nbd_memmove
    #ifdef nb_memmove
        #define nbd_memmove nb_memmove
    #else
        #include <string.h>
        #define nbd_memmove memmove
    #endif
#endif

#ifndef nbd_memcpy
    #ifdef nb_memcpy
        #define nbd_memcpy nb_memcpy
    #else
        #include <string.h>
        #define nbd_memcpy memcpy
    #endif
#endif

// Useful for defining variables in macros to avoid name collisions
#define nbd__var_impl(x) nbd__var_##x##__LINE__
#define nbd__var(x)      nbd__var_impl(x)

// nbd_buf layout
// +----------+----------+----------+---------+---------+---------+---------+
// |    -3    |    -2    |    -1    |    0    |    1    |    2    |   ...   |
// +----------+----------+----------+---------+---------+---------+---------+
//   capacity    length    position ^--- User pointer

#define nbd_buf_reserve(b, sz)          (nbd_buf_len(b) + (sz) >= nbd_buf_cap(b) ? (b) = nbd_buf__grow(b, nbd_buf_cap(b) * 2 + (sz)), 0 : 0)
#define nbd_buf_free(b)                 (nbd_buf__grow(b, 0))
#define nbd_buf_dup(dst, b)             ((b) ? nbd_buf_reserve((dst), nbd_buf_len(b)), nbd_memcpy((dst), (b), nbd_buf_len(b)), 0 : 0)
#define nbd_buf_cap(b)                  ((b) ? nbd_buf__cap(b) : 0)
#define nbd_buf_len(b)                  ((b) ? nbd_buf__len(b) : 0)
#define nbd_buf_pos(b)                  ((b) ? nbd_buf__pos(b) : 0)
#define nbd_buf_readn(b, T, n)          (nbd_buf__pos(b) += (n) * sizeof(T), (T *)&(b)[nbd_buf_pos(b)])
#define nbd_buf_read(b, T)              (nbd_buf_readn((b), (T), 1))
#define nbd_buf_writen(b, T, vptr, n)   (nbd_buf_reserve((b), (n) * sizeof(T)), nbd_buf__len(b) += (n) * sizeof(T), nbd_memcpy(nbd_buf_readn(b, T, n), (vptr), (n) * sizeof(T)))
#define nbd_buf_write(b, T, v)          (nbd_buf_writen((b), (T), &(v), 1))
#define nbd_buf_clear(b)                ((b) ? nbd_buf__len(b) = nbd_buf__pos(b) = 0, 0 : 0)

#define nbd_buf__head(b)                ((nbd_usize *)(b) - 3)
#define nbd_buf__cap(b)                 (nbd_buf__head(b)[0])
#define nbd_buf__len(b)                 (nbd_buf__head(b)[1])
#define nbd_buf__pos(b)                 (nbd_buf__head(b)[2])

void   *nbd_buf__grow                   (void *b, nbd_usize size);


// nbd_arr (same as nbd_buf)
// +----------+----------+----------+---------+---------+---------+---------+
// |    -3    |    -2    |    -1    |    0    |    1    |    2    |   ...   |
// +----------+----------+----------+---------+---------+---------+---------+
//   capacity    length    position ^--- User pointer

#define nbd_arr_reserve(a, n)           (nbd_buf_reserve(a, (n) * sizeof *(a)))
#define nbd_arr_free(a)                 (nbd_buf_free(a))
#define nbd_arr_dup(dst, a)             (nbd_buf_dup(dst, a))
#define nbd_arr_cap(a)                  (nbd_buf_cap(a) / sizeof *(a))
#define nbd_arr_len(a)                  (nbd_buf_len(a) / sizeof *(a))
#define nbd_arr_insn(a, i, n)           (nbd_arr_reserve(a, (i) + (n)), nbd_arr_pushn((a), (n)), nbd_memmove(&(a)[(i) + (n)], &(a)[(i)], sizeof *(a) * (nbd_arr_len(a) - (i) - (n))), &(a)[(i)])
#define nbd_arr_ins(a, i, v)            (*nbd_arr_insn(a, i, 1) = (v))
#define nbd_arr_remn(a, i, n)           (nbd_arr_len(a) >= (n) ? nbd_buf__len(a) -= (n) * sizeof *(a), nbd_memmove(&(a)[(i)], &(a)[(i) + (n)], sizeof *(a) * (nbd_arr_len(a) - (i) - (n))), 0 : 0)
#define nbd_arr_rem(a, i)               (nbd_arr_remn(a, i, 1))
#define nbd_arr_remswap(a, i)           (nbd_arr_len(a) > 0 ? (a)[i] = nbd_arr_pop(a), 0 : 0)
#define nbd_arr_pushn(a, n)             (nbd_buf__len(a) += (n) * sizeof *(a), nbd_buf__pos(a) += (n) * sizeof *(a), &(a)[nbd_arr_len(a) - (n)])
#define nbd_arr_push(a, v)              (*nbd_arr_pushn(a, 1) = (v))
#define nbd_arr_pop(a)                  (nbd_buf__len(a) -= sizeof *(a), (a)[nbd_arr_len(a)])
#define nbd_arr_clear(a)                (nbd_buf_clear(a))


// nbd_map
// +----------+----------+----------+----------+----------+---------+---------+---------+---------+
// |    -5    |    -4    |    -3    |    -2    |    -1    |    0    |    1    |    2    |   ...   |
// +----------+----------+----------+----------+----------+---------+---------+-------------------+
//   capacity    length    position     funcs     default ^--- User pointer

#define nbd_map_free(m)                 (nbd_arr_free(nbd_map__head(m)))
#define nbd_map_len(m)                  ((m) ? nbd_arr_len(nbd_map__head(m)) : 0)
#define nbd_map_cap(m)                  ((m) ? nbd_arr_cap(nbd_map__head(m)) : 0)
#define nbd_map_load_factor(m)          (nbd_map_cap(m) ? ((float)nbd_map_len(m) / (float)nbd_map_cap(m)) : 1.0f)
#define nbd_map_set_default(m, k, v)    do { nbd_map__ensure(m); nbd_map__default(m).key = (k); nbd_map__default(m).value = (v); } while (0)
#define nbd_map_set_funcs(m, h, e)      do { nbd_map__ensure(m); nbd_map__funcs(m) = (nbd_map__func_storage){ .hash = (h), .equal = (e) }; } while (0)
#define nbd_map_gets(m, k)              ((m)[nbd_map__indexof(m, sizeof *(m), &(k), sizeof (k), nbd_map__keyoff(m), nbd_map_cap(m))])
#define nbd_map_get(m, k)               (nbd_map_gets(m, k).value)
#define nbd_map_getp(m, k)              (&nbd_map_get(m, k))
#define nbd_map_has(m, k)               (nbd_map__indexof(m, sizeof *(m), &(k), sizeof (k), nbd_map__keyoff(m), nbd_map_cap(m)) != -1)
#define nbd_map_set(m, k, v)            do { nbd_map__ensure(m); nbd_map__set(m, k, v); } while (0)
#define nbd_map_rem(m, k)               (nbd_map_gets(m, k) = nbd_map__default(m), nbd_map__len(m)--)

#define nbd_map_clear(m) do {\
    for (nbd_usize nbd__var(i) = 0; nbd__var(i) < nbd_map_cap(m); nbd__var(i)++) {\
        nbd_memcpy(&m[nbd__var(i)], &nbd_map__default(m), sizeof *(m));\
    }\
    nbd_arr_clear(nbd_map__head(m));\
} while (0)

typedef struct nbd_map__func_storage {
    nbd_u64 (*hash)(void const *);
    int      (*equal)(void const *, void const *);
} nbd_map__func_storage;

#define nbd_map__header_size(m)         (sizeof *(m) + sizeof(nbd_map__func_storage))
#define nbd_map__head(m)                ((char *)(m) - nbd_map__header_size(m))
#define nbd_map__cap(m)                 (nbd_buf__cap(nbd_map__head(m)))
#define nbd_map__len(m)                 (nbd_buf__len(nbd_map__head(m)))
#define nbd_map__default(m)             ((m)[-1])
#define nbd_map__funcs(m)               (*((nbd_map__func_storage *)nbd_map__head(m)))
#define nbd_map__hash(m, k, n)          (nbd_map__funcs(m).hash ? nbd_map__funcs(m).hash(k) : nbd_map__fnv1a(k, n))
#define nbd_map__equal(m, a, b, n)      (nbd_map__funcs(m).equal ? nbd_map__funcs(m).equal(a, b) : memcmp(a, b, n) == 0)
#define nbd_map__keyoff(m)              (((char *)&((m)[0].key)) - (char *)(m))

#define nbd_map__set(m, k, v) do {\
        nbd_u64 nbd__var(hash) = nbd_map__hash(m, &(k), sizeof (k));\
        nbd_usize nbd__var(i) = nbd__var(hash) & (nbd_map_cap(m) - 1);\
        for (nbd_usize nbd__var(step) = 1, nbd__var(c) = 0; nbd__var(c) < nbd_map_cap(m); nbd__var(c)++) {\
            nbd__var(i) = (nbd__var(i) + nbd__var(step)++) & (nbd_map_cap(m) - 1);\
            if (nbd_map__equal(m, &(m)[nbd__var(i)].key, &(k), sizeof (k)) == 0) {\
                break; /* k already exists in m, update it */\
            } else if (nbd_map__equal(m, &(m)[nbd__var(i)].key, &nbd_map__default(m).key, sizeof (k)) == 0) {\
                nbd_map__len(m)++;\
                break; /* k does not exists in m, insert it */\
            }\
        }\
        nbd_memcpy(&(m)[nbd__var(i)].key, &(k), sizeof (k));\
        nbd_memcpy(&(m)[nbd__var(i)].value, &(v), sizeof (v));\
    } while (0)

#define nbd_map__ensure(m) do {\
        if (nbd_map_load_factor(m) < 0.7f) {\
            break;\
        }\
        nbd_usize nbd__var(size) = nbd_npow2((nbd_map_cap(m) ? nbd_map_cap(m) : 8) * sizeof *(m)) + nbd_map__header_size(m);\
        struct { char key[sizeof (m)[0].key]; char value[sizeof (m)[0].value]; } *nbd__var(tmp) = nbd_buf__grow(NULL, nbd__var(size));\
        if ((m) != NULL) {\
            nbd_memcpy(nbd_map__head(nbd__var(tmp)), nbd_map__head(m), nbd_map__header_size(nbd__var(tmp)));\
            nbd_map_clear(nbd__var(tmp));\
        }\
        for (nbd_usize nbd__var(i) = 0; nbd__var(i) < nbd_map_cap(m); nbd__var(i)++) {\
            nbd_map__set(nbd__var(tmp), (m)[nbd__var(i)].key, (m)[nbd__var(i)].value);\
        }\
        nbd_memcpy(m, nbd__var(tmp), sizeof *(m) * nbd_map_cap(m));\
        nbd_map_free(nbd__var(tmp));\
    } while (0)

nbd_u64 nbd_map__fnv1a                  (void const *key, nbd_usize size);
int     nbd_map__indexof                (void *m, nbd_usize msize, void *k, nbd_usize ksize, nbd_usize koff, nbd_usize cap);

#ifdef __cplusplus
}
#endif

/**********************************************************************************************************************
***********************************************************************************************************************
****                                                                                                               ****
****                                                                                                               ****
****                                                 Implementation                                                ****
****                                                                                                               ****
****                                                                                                               ****
***********************************************************************************************************************
**********************************************************************************************************************/


#if defined(NB_DS_IMPLEMENTATION) || defined(NB_IMPLEMENTATION)
#ifndef _nb_ds_c_
#define _nb_ds_c_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef nbd_calloc
    #include <stdlib.h>
    #define nbd_calloc calloc
#endif

#ifndef nbd_realloc
    #include <stdlib.h>
    #define nbd_realloc realloc
#endif

#ifndef nbd_free
    #include <stdlib.h>
    #define nbd_free free
#endif


static nbd_u64 nbd_npow2(nbd_u64 x) {
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

void *nbd_buf__grow(void *b, nbd_usize size) {
    if (size == 0) {
        nbd_free(b ? nbd_buf__head(b) : b);
        return NULL;
    }

    nbd_usize *ptr = NULL;
    size = nbd_npow2(size + sizeof(nbd_usize) * 2);

    if (b != NULL) {
        ptr = nbd_realloc(nbd_buf__head(b), size);
        memset(ptr + nbd_buf_len(b), 0, size - nbd_buf_len(b));
    } else {
        ptr = nbd_calloc(1, size);
    }

    if (ptr != NULL) {
        *ptr++ = size;
        *ptr++ = nbd_buf_len(b);
    }

    return (void *)ptr;
}

nbd_u64 nbd_map__fnv1a(void const *key, nbd_usize size) {
    nbd_u64 hash = 14695981039346656037UL;
    for (uint8_t const *p = key; size; size--, p++) {
        hash ^= (nbd_u64)(*p);
        hash *= 1099511628211UL;
    }
    return hash;
}

int nbd_map__indexof(void *m, nbd_usize msize, void *k, nbd_usize ksize, nbd_usize koff, nbd_usize cap) {
    // nbd_map__hash and nbd_map__equal cannot be used here because m is a void *, which cannot be dereferenced like it would've been in nbd_map__head
    nbd_map__func_storage funcs = *((nbd_map__func_storage *)(msize + sizeof funcs));
    nbd_u64 hash = funcs.hash ? funcs.hash(k) : nbd_map__fnv1a(k, ksize);
    for (nbd_usize i = hash & (cap - 1), step = 1, c = 0; c < cap; c++, i = (i + step++) & (cap - 1)) {
        void *cur = (char *)m + i * msize;
        void *key = (char *)cur + koff;
        if (funcs.equal != NULL ? funcs.equal(key, k) == 1 : memcmp(key, k, ksize) == 0) {
            return i;
        }
    }
    return -1;
}

#ifdef __cplusplus
}
#endif

#endif // !_nb_ds_c_
#endif // NB_DS_IMPLEMENTATION || NB_IMPLEMENTATION
#endif // !_nb_ds_h_
