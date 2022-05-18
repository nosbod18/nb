/* nb_ds.h - v0.04 - public domain
    A minimal Entity Component System in C/C++

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

        #define NB_ECS_IMPLEMENTATION
        #include "nb_ecs.h"

    Then include it as normal in all other files.

    Example
    -------
    typedef struct {
        float x, y;
    } position, velocity;

    void move(nbe_id cpos, nbe_id cvel) {
        nbe_view view = nbe_query(cpos, cvel);
        position *p = view.components[0];
        velocity *v = view.components[1];

        for (size_t i = 0; i < view.count; i++) {
            p[i].x += v[i].x;
            p[i].y += v[i].y;
        }
    }

    int main(void) {
        if (nbe_init() != 0) {
            return -1;
        }

        nbe_id cpos = nbe_new();
        nbe_id cvel = nbe_new();

        for (int i = 0; i < 8; i++) {
            nbe_id e = nbe_new();
            nbe_add(e, cpos, &(position){1.f * i, 1.f * i});
            nbe_add(e, cvel, &(velocity){1.f * i, 1.f * i});
        }

        move(cpos, cvel);
        move(cpos, cvel);
        move(cpos, cvel);

        nbe_exit();
    }

    Documentation
    -------------
    TODO

    Version History
    ---------------
    0.04  - Started documentation
    0.03  - Project name change
    0.02  - Added arrays, maps, and archetypes
    0.01a - Simplified API
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

#ifndef _nb_ecs_h_
#define _nb_ecs_h_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef nbe_u64
    #ifdef nb_u64
        #define nbe_u64 nb_u64
    #else
        #include <stdint.h>
        #define nbe_u64 uint64_t
    #endif
#endif

#ifndef nbe_usize
    #ifdef nb_usize
        #define nbe_usize nb_usize
    #else
        #include <stddef.h>
        #define nbe_usize size_t
    #endif
#endif

typedef nbe_u64 nbe_id;

typedef struct nbe_view {
    void      **components;
    nbe_id     *entities;
    nbe_usize   count;
} nbe_view;

int         nbe_init            (void);
void        nbe_exit            (void);
#define     nbe_query(...)      nbe_query((nbe_id []){__VA_ARGS__, 0})
nbe_view    nbe_query_arr       (nbe_id *components);

nbe_id      nbe_new             (void);
void        nbe_del             (nbe_id entity);
#define     nbe_set(e, c, ...)  nbe_set_size(e, c, __VA_ARGS__, sizeof *(__VA_ARGS__))
void        nbe_set_size        (nbe_id entity, nbe_id component, void const *data, nbe_usize size);
void        nbe_rem             (nbe_id entity, nbe_id component);

#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
************************************************************************************************************************
****                                                                                                               *****
****                                                                                                               *****
****                                                 Implementation                                                *****
****                                                                                                               *****
****                                                                                                               *****
************************************************************************************************************************
***********************************************************************************************************************/


#if defined(NB_ECS_IMPLEMENTATION) || defined(NB_IMPLEMENTATION)
#ifndef _nb_ecs_c_
#define _nb_ecs_c_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef nbe_memmove
    #ifdef nb_memmove
        #define nbe_memmove nb_memmove
    #else
        #include <string.h>
        #define nbe_memmove memmove
    #endif
#endif

#ifndef nbe_memcpy
    #ifdef nb_memcpy
        #define nbe_memcpy nb_memcpy
    #else
        #include <string.h>
        #define nbe_memcpy memcpy
    #endif
#endif

#ifndef nbe_memset
    #ifdef nb_memset
        #define nbe_memset nb_memset
    #else
        #include <string.h>
        #define nbe_memset memset
    #endif
#endif

#ifndef nbe_memcmp
    #ifdef nb_memcmp
        #define nbe_memcmp nb_memcmp
    #else
        #include <string.h>
        #define nbe_memcmp memcmp
    #endif
#endif

#ifndef nbe_calloc
    #ifdef nb_calloc
        #define nbe_calloc nb_calloc
    #else
        #include <stdlib.h>
        #define nbe_calloc calloc
    #endif
#endif

#ifndef nbe_realloc
    #ifdef nb_realloc
        #define nbe_realloc nb_realloc
    #else
        #include <stdlib.h>
        #define nbe_realloc realloc
    #endif
#endif

#ifndef nbe_free
    #ifdef nb_free
        #define nbe_free nb_free
    #else
        #include <stdlib.h>
        #define nbe_free free
    #endif
#endif

#ifndef NULL
    #define NULL ((void *)0)
#endif

typedef struct nbe__pool {
    char *data;
    nbe_usize size;
} nbe__pool;

typedef struct nbe__archetype {
    nbe_id *type;
    nbe_id *entities;
    nbe__pool *components;
    struct nbe__archetype **rem_edges;
    struct nbe__archetype **ins_edges;
} nbe__archetype;

typedef struct nbe__record {
    nbe__archetype *archetype;
    nbe_usize idx;
} nbe__record;

typedef struct nbe__entity_index {
    nbe_id key;
    nbe__record value;
} nbe__entity_index;

typedef struct nbe__type_index {
    nbe_id *key;
    nbe__archetype *value;
} nbe__type_index;


static struct {
    nbe_id *versions;
    nbe_id *free_ids;
    nbe__archetype *root;
    nbe__type_index *ti;
    nbe__entity_index *ei;
} _nbe = {0};


#define nbe_id__idx(i)                  ((i) & 0xFFFFFFFF)
#define nbe_id__ver(i)                  (((i) >> 32) & 0xFFFFFFFF)
#define nbe_id__make(ver, idx)          ((((nbe_id)(ver)) << 32) | ((idx) & 0xFFFFFFFF))

// Taken straight from nb_ds.h with a few changes

#define nbe__var_impl(x)            nbe__var_##x##__LINE__
#define nbe__var(x)                 nbe__var_impl(x)

#define nbe__arr_reserve(a, n)      (nbe__arr_len(a) + (n) >= nbe__arr_cap(a) ? nbe__arr__grow(&(a), sizeof *(a) * (nbe__arr_cap(a) * 2 + (n))), 0 : 0)
#define nbe__arr_free(a)            (nbe__arr__grow(a, 0))
#define nbe__arr_dup(dst, a)        ((a) ? nbe__arr_reserve((dst), nbe__arr_len(a)), nbe_memcpy((dst), (a), nbe__arr_len(a)), 0 : 0)
#define nbe__arr_cap(a)             ((a) ? nbe__arr__cap(a) : 0)
#define nbe__arr_len(a)             ((a) ? nbe__arr__len(a) : 0)
#define nbe__arr_end(a)             ((a) ? (a) + nbe__arr_len(a) : (a))
#define nbe__arr_insn(a, i, n)      (nbe__arr_reserve(a, (i) + (n)), nbe__arr_pushn((a), (n)), nbe_memmove(&(a)[(i) + (n)], &(a)[(i)], sizeof *(a) * (nbe__arr_len(a) - (i) - (n))), &(a)[(i)])
#define nbe__arr_ins(a, i, v)       (*nbe__arr_insn(a, i, 1) = (v))
#define nbe__arr_remn(a, i, n)      (nbe__arr_len(a) >= (n) ? nbe__arr__len(a) -= (n) * sizeof *(a), nbe_memmove(&(a)[(i)], &(a)[(i) + (n)], sizeof *(a) * (nbe__arr_len(a) - (i) - (n))), 0 : 0)
#define nbe__arr_rem(a, i)          (nbe__arr_remn(a, i, 1))
#define nbe__arr_remswap(a, i)      (nbe__arr_len(a) > 0 ? (a)[i] = nbe__arr_pop(a), 0 : 0)
#define nbe__arr_remval(a, v, eq)   do { for (int nbe__var(i) = 0; nbe__var(i) < nbe__arr_len(a); nbe__var(i)++) { if (eq((a)[nbe__var(i)], (v)) == 1) { nbe__arr_rem(a, nbe__var(i)); break; }}} while (0)
#define nbe__arr_pushn(a, n)        (nbe__arr_reserve(a, n), nbe__arr__len(a) += (n), &(a)[nbe__arr_len(a) - (n)])
#define nbe__arr_push(a, v)         (*nbe__arr_pushn(a, 1) = (v))
#define nbe__arr_pop(a)             ((a)[nbe__arr__len(a)--])
#define nbe__arr_clear(a)           ((a) ? nbe__arr__len(a) = 0, 0 : 0)
#define nbe__arr__hdr(a)            ((int *)(a) - 2)
#define nbe__arr__cap(a)            (nbe__arr__hdr(a)[0])
#define nbe__arr__len(a)            (nbe__arr__hdr(a)[1])

static nbe_u64 nbe__npow2(nbe_u64 x) {
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

static void nbe__arr__grow(void **a, nbe_usize size) {
    if (a == NULL) {
        return;
    } else if (size == 0) {
        nbe_free(*a != NULL ? nbe__arr__head(*a) : *a);
        *a = NULL;
    } else {
        nbe_usize *ptr = NULL;
        size = nbe__npow2(size + sizeof(nbe_usize) * 2);
        if (*a != NULL) {
            ptr = nbe_realloc(nbe__arr__head(*a), size);
            nbd_memset(ptr + nbe__arr_len(*a), 0, size - nbe__arr_len(*a));
        } else {
            ptr = nbe_calloc(1, size);
        }
        if (ptr != NULL) {
            *ptr++ = size;
            *ptr++ = nbe__arr_len(*a);
        }
        *a = (void *)ptr;
    }
}

typedef struct nbe__map__func_storage {
    nbe_u64 (*hash)(void const *);
    int     (*cmp)(void const *, void const *);
} nbe__map__func_storage;

#define nbe__map_free(m)                (nbe__arr_free(nbe__map__head(m)))
#define nbe__map_len(m)                 ((m) ? nbe__arr_len(nbe__map__head(m)) : 0)
#define nbe__map_cap(m)                 ((m) ? nbe__arr_cap(nbe__map__head(m)) : 0)
#define nbe__map_load_factor(m)         (nbe__map_cap(m) ? ((float)nbe__map_len(m) / (float)nbe__map_cap(m)) : 1.0f)
#define nbe__map_set_default(m, k, v)   do { nbe__map__ensure(m); nbe__map__default(m).key = (k); nbe__map__default(m).value = (v); } while (0)
#define nbe__map_set_funcs(m, h, c)     do { nbe__map__ensure(m); nbe__map__funcs(m) = (nbe__map__func_storage){ .hash = (h), .cmp = (c) }; } while (0)
#define nbe__map_gets(m, k)             ((m)[nbe__map__indexof(m, sizeof *(m), &(k), sizeof (k), nbe__map__keyoff(m), nbe__map_cap(m))])
#define nbe__map_get(m, k)              (nbe__map_gets(m, k).value)
#define nbe__map_getp(m, k)             (&nbe__map_get(m, k))
#define nbe__map_has(m, k)              (nbe__map__indexof(m, sizeof *(m), &(k), sizeof (k), nbe__map__keyoff(m), nbe__map_cap(m)) != -1)
#define nbe__map_set(m, k, v)           do { nbe__map__ensure(m); nbe__map__set(m, k, v); } while (0)
#define nbe__map_rem(m, k)              (nbe__map_gets(m, k) = nbe__map__default(m), nbe__map__len(m)--)

#define nbe__map_clear(m) do {\
    for (nbe_usize nbe__var(i) = 0; nbe__var(i) < nbe__map_cap(m); nbe__var(i)++) {\
        nbe_memcpy(&m[nbe__var(i)], &nbe__map__default(m), sizeof *(m));\
    }\
    nbe__arr_clear(nbe__map__head(m));\
} while (0)

#define nbe__map__header_size(m)        (sizeof *(m) + sizeof(nbe__map__func_storage))
#define nbe__map__head(m)               ((char *)(m) - nbe__map__header_size(m))
#define nbe__map__cap(m)                (nbe__arr__cap(nbe__map__head(m)))
#define nbe__map__len(m)                (nbe__arr__len(nbe__map__head(m)))
#define nbe__map__default(m)            ((m)[-1])
#define nbe__map__funcs(m)              (*((nbe__map__func_storage *)nbe__map__head(m)))
#define nbe__map__hash(m, k, n)         (nbe__map__funcs(m).hash ? nbe__map__funcs(m).hash(k) : nbe__map__fnv1a(k, n))
#define nbe__map__cmp(m, a, b, n)       ((nbe__map__funcs(m).cmp ? nbe__map__funcs(m).cmp(a, b) : nbe_memcmp(a, b, n)) == 0)
#define nbe__map__keyoff(m)             (((char *)&((m)[0].key)) - (char *)(m))

#define nbe__map__set(m, k, v) do {\
    nbe_u64 nbe__var(hash) = nbe__map__hash(m, &(k), sizeof (k));\
    nbe_usize nbe__var(i) = nbe__var(hash) & (nbe__map_cap(m) - 1);\
    for (nbe_usize nbe__var(step) = 1, nbe__var(c) = 0; nbe__var(c) < nbe__map_cap(m); nbe__var(c)++) {\
        nbe__var(i) = (nbe__var(i) + nbe__var(step)++) & (nbe__map_cap(m) - 1);\
        if (nbe__map__cmp(m, &(m)[nbe__var(i)].key, &(k), sizeof (k)) == 0) {\
            break; /* k already exists in m, update it */\
        } else if (nbe__map__cmp(m, &(m)[nbe__var(i)].key, &nbe__map__default(m).key, sizeof (k)) == 0) {\
            nbe__map__len(m)++;\
            break; /* k does not exists in m, insert it */\
        }\
    }\
    nbe_memcpy(&(m)[nbe__var(i)].key, &(k), sizeof (k));\
    nbe_memcpy(&(m)[nbe__var(i)].value, &(v), sizeof (v));\
} while (0)

#define nbe__map__ensure(m) do {\
        if (nbe__map_load_factor(m) < 0.7f) {\
            break;\
        }\
        nbe_usize nbe__var(size) = nbe__npow2((nbe__map_cap(m) ? nbe__map_cap(m) : 8) * sizeof *(m)) + nbe__map__header_size(m);\
        struct { char key[sizeof (m)[0].key]; char value[sizeof (m)[0].value]; } *nbe__var(tmp) = nbe__arr__grow(NULL, nbe__var(size));\
        if ((m) != NULL) {\
            nbe_memcpy(nbe__map__head(nbe__var(tmp)), nbe__map__head(m), nbe__map__header_size(nbe__var(tmp)));\
            nbe__map_clear(nbe__var(tmp));\
        }\
        for (nbe_usize nbe__var(i) = 0; nbe__var(i) < nbe__map_cap(m); nbe__var(i)++) {\
            nbe__map__set(nbe__var(tmp), (m)[nbe__var(i)].key, (m)[nbe__var(i)].value);\
        }\
        nbe_memcpy(m, nbe__var(tmp), sizeof *(m) * nbe__map_cap(m));\
        nbe__map_free(nbe__var(tmp));\
    } while (0)

static nbe_u64 nbe__map__fnv1a(void const *key, nbe_usize size) {
    nbe_u64 hash = 14695981039346656037UL;
    for (char const *p = key; size; size--, p++) {
        hash ^= (nbe_u64)(*p);
        hash *= 1099511628211UL;
    }
    return hash;
}

static int nbe__map__indexof(void *m, nbe_usize msize, void *k, nbe_usize ksize, nbe_usize koff, nbe_usize cap) {
    nbe__map__func_storage funcs = *((nbe__map__func_storage *)(msize + sizeof funcs));
    nbe_u64 hash = funcs.hash != NULL ? funcs.hash(k) : nbe__map__fnv1a(k, ksize);
    for (nbe_usize i = hash & (cap - 1), step = 1, c = 0; c < cap; c++, i = (i + step++) & (cap - 1)) {
        void *cur = (char *)m + i * msize;
        void *key = (char *)cur + koff;
        if ((funcs.cmp != NULL ? funcs.cmp(key, k) : nbe_memcmp(key, k, ksize)) == 0) {
            return i;
        }
    }
    return -1;
}

static nbe_u64 nbe__type_hash(void const *key) {
    nbe_id const *type = key;
    nbe_u64 hash = 5381;
    for (nbe_usize i = 0; i < nbe__arr_len(type); i++) {
            hash = ((hash << 5) + hash) ^ type[i];
    }
    return hash;
}

static int nbe__type_cmp(void const *a, void const *b) {
    nbe_id const *at = a;
    nbe_id const *bt = b;
    nbe_usize atn = nbe__arr_len(at);
    nbe_usize btn = nbe__arr_len(bt);
    nbe_usize n = atn < btn ? atn : btn;
    for (nbe_usize i = 0; i < n; i++) {
        if (at[i] != bt[i]) {
            return at[i] - bt[i];
        }
    }
    return 0;
}

static int nbe__type_is_subset(nbe_id const *sub, nbe_id const *super) {
    nbe_usize n = nbe__arr_len(super);
    nbe_usize m = nbe__arr_len(sub);

    if (n < m) {
        return 0;
    }

    // O(n^2), but the arrays are small enough that it's shouldn't be an issue
    // If this turns out to be a bottleneck I'll find a different solution
    for (nbe_usize i = 0, j = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (sub[i] == super[j]) {
                break;
            }
        }

        if (j == m) {
            return 0;
        }
    }

    return 1;
}

static nbe_u64 nbe__id_hash(void const *key) {
    nbe_id id = *(nbe_id const *)key;
    id = ((id >> 16) ^ id) * 0x45d9f3b;
    id = ((id >> 16) ^ id) * 0x45d9f3b;
    id =  (id >> 16) ^ id;
    return id;
}

static int nbe__id_cmp(void const *a, void const *b) {
    return *(nbe_id const *)a - *(nbe_id const *)b;
}

static void nbe__archetype__connect(nbe__archetype *a, nbe__archetype *b) {
    nbe__arr_push(a->ins_edges, b);
    nbe__arr_push(b->rem_edges, a);
}

static void nbe__archetype__ins(nbe__archetype *from, nbe__archetype *to) {
    if (nbe__arr_len(from->type) < nbe__arr_len(to->type) - 1) {
        for (nbe_usize i = 0; i < nbe__arr_len(from->ins_edges); i++) {
            nbe__archetype__ins(from->ins_edges[i], to);
        }
    } else if (nbe__type_is_subset(from->type, to->type) == 1) {
        nbe__archetype__connect(from, to);
    }
}

static nbe__archetype *nbe__archetype_create(nbe_id *type, nbe__type_index *ti) {
    nbe__archetype *archetype = nbe__map_get(ti, type);
    if (archetype == NULL) {
        archetype = calloc(1, sizeof *archetype);
        if (archetype != NULL) {
            archetype->type = type;
            nbe__map_set(ti, type, archetype);
        }
    }

    return archetype;
}

static nbe__archetype *nbe__archetype_create_ins(nbe__archetype *root, nbe__archetype *rem, nbe__type_index *ti, nbe_id *type) {
    nbe__archetype *ins = nbe__archetype_create(type, ti);
    nbe__archetype__connect(rem, ins);
    nbe__archetype__ins(root, ins);
    return ins;
}

static void nbe__archetype_free(nbe__archetype *archetype) {
    for (nbe_usize i = 0; i < nbe__arr_len(archetype->components); i++) {
        nbe__arr_free(archetype->components[i].data);
    }
    nbe__arr_free(archetype->components);
    nbe__arr_free(archetype->type);
    nbe__arr_free(archetype->rem_edges);
    nbe__arr_free(archetype->ins_edges);
    nbe__arr_free(archetype->entities);
    free(archetype);
}

static nbe_usize nbe__archetype_move(nbe__archetype *rem, nbe__archetype *ins, nbe__entity_index *ei, nbe_usize rem_idx) {
    assert(rem_idx < nbe__arr_len(rem->entities) && "Row out of bounds");

    nbe_id e = rem->entities[rem_idx];
    nbe__arr_remswap(rem->entities, rem_idx);
    nbe_usize ins_idx = nbe__arr_push(ins->entities, e);
    nbe__map_set(ei, e, ((nbe__record){.archetype = ins, .idx = ins_idx}));

    for (nbe_usize i = 0; i < nbe__arr_len(rem->type); i++) {
        assert(rem->type[i] >= ins->type[i] && "Elements in type mismatched");

        nbe_usize j = 0;
        while (rem->type[i] != ins->type[j]) {
            j++;
        }

        nbe_usize size = rem->components[i].size;
        nbe_memcpy(&ins->components[j].data[size * ins_idx], &rem->components[i].data[size * ins_idx], size);
    }

    return ins_idx;
}


// =============================================================


int nbe_init(void) {
    nbe__map_set_funcs(_nbe.ti, nbe__type_hash, nbe__type_cmp);
    nbe__map_set_funcs(_nbe.ei, nbe__id_hash, nbe__id_cmp);
    return 0;
}

void nbe_exit(void) {
    nbe__arr_free(_nbe.versions);
    nbe__arr_free(_nbe.free_ids);
    nbe__map_free(_nbe.ti);
    nbe__map_free(_nbe.ei);
    nbd_memset(&_nbe, 0, sizeof(_nbe));
}

nbe_id nbe_new(void) {
    nbe_id index = 0;
    if (nbe__arr_len(_nbe.free_ids) != 0) {
        index = nbe__arr_pop(_nbe.free_ids);
    } else {
        index = nbe__arr_len(_nbe.versions);
        nbe__arr_push(_nbe.versions, 1);
    }
    return nbe_id__make(_nbe.versions[index], index);
}

void nbe_del(nbe_id e) {
    if (nbe_id__ver(e) != _nbe.versions[nbe_id__idx(e)]) {
        return; // Entity was already deleted
    }
    nbe_id index = nbe_id__idx(e);
    _nbe.versions[index]++;
    nbe__arr_push(_nbe.free_ids, index);
}

void nbe_set_size(nbe_id e, nbe_id c, void const *data, nbe_usize size) {
    nbe__record record = nbe__map_get(_nbe.ei, e);
    if (record.archetype == NULL) {
        return; // Unknown entity
    }

    nbe_id *type = NULL;
    nbe__arr_dup(type, record.archetype->type);
    nbe_usize cidx = nbe__arr_push(type, c);

    // Find the new archetype (create it if it does not exist)
    nbe__archetype **archetype = nbe__map_getp(_nbe.ti, type);
    if (*archetype == NULL) {
        *archetype = nbe__archetype_create_ins(_nbe.root, record.archetype, _nbe.ti, type);
        (*archetype)->components[cidx].size = size;
    } else {
        nbe__arr_free(type);
    }

    // Move the entity along c's edge in the graph and update its record
    nbe_usize eidx = nbe__archetype_move(record.archetype, *archetype, _nbe.ei, record.idx);
    nbe__map_set(_nbe.ei, e, ((nbe__record){.archetype = *archetype, .idx = eidx}));

    if (data != NULL) {
        char *carr = record.archetype->components[cidx].data;
        nbe_memcpy(&carr[record.idx * size], data, size);
        nbe__arr__len(carr)++;
    }
}

void nbe_rem(nbe_id e, nbe_id c) {
    nbe__record record = nbe__map_get(_nbe.ei, e);
    if (record.archetype == NULL) {
        return; // Unknown entity
    }

    nbe_id *type = NULL;
    nbe__arr_dup(type, record.archetype->type);

    #define eq(a, b) ((a) == (b))
    nbe__arr_remval(type, c, eq);
    #undef eq

    // Find the new archetype
    nbe__archetype *archetype = nbe__map_get(_nbe.ti, type);
    nbe__arr_free(type);
    if (archetype == NULL) {
        return; // Unknown type
    }

    // Move the entity along the component's edge in the graph and update its record
    nbe_usize eidx = nbe__archetype_move(record.archetype, archetype, _nbe.ei, record.idx);
    nbe__map_set(_nbe.ei, e, ((nbe__record){.archetype = archetype, .idx = eidx}));
}

nbe_view nbe_query_arr(nbe_id components[]) {
    nbe_usize n = 0;
    nbe_id *cursor = components;
    while (*cursor++ != 0) {
        n++;
    }

    nbe_id *type = NULL;
    nbe_memcpy(nbe__arr_pushn(type, n), components, n * sizeof *type);

    nbe__archetype *archetype = nbe__map_get(_nbe.ti, type);
    nbe__arr_free(type);

    // TODO

    return (nbe_view){0}; // Unknown type
}

#ifdef __cplusplus
}
#endif

#endif // !_nb_ecs_c_
#endif // NB_ECS_IMPL_IMPLEMENTATION || NB_IMPL_IMPLEMENTATION
#endif // !_nb_ecs_h_
