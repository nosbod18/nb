/* ecs.h - v0.04 - public domain
    A minimal Entity Component System in C/C++

    Table of Contents
    -----------------
    Table of Contents
    Summary
    Usage
    Example
    Documentation
    Licence

    Summary
    -------
    TODO

    Usage
    -----
    To use this library, do

        #define ECS_IMPLEMENTATION
        #include "ecs.h"

    in *one* C or C++ file to create the implementation.
    Then include it as normal in all other files.

    Example
    -------
    typedef struct { float x, y; } vec2;

    void move(ecs_id cpos, ecs_id cvel) {
        ecs_view view = ecs_query(cpos, cvel);
        vec2 *p = view.components[0];
        vec2 *v = view.components[1];

        for (size_t i = 0; i < view.count; i++) {
            p[i].x += v[i].x;
            p[i].y += v[i].y;
        }
    }

    int main(void) {
        if (ecs_init() != 0) {
            return -1;
        }

        ecs_id cpos = ecs_new();
        ecs_id cvel = ecs_new();

        for (int i = 0; i < 8; i++) {
            ecs_id e = ecs_new();
            ecs_add(e, cpos, &(vec2){1.f * i, 1.f * i});
            ecs_add(e, cvel, &(vec2){1.f * i, 1.f * i});
        }

        move(cpos, cvel);
        move(cpos, cvel);
        move(cpos, cvel);

        ecs_exit();
    }

    Documentation
    -------------
    TODO

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

#pragma once
#include <stdint.h> // uint64_t
#include <stddef.h> // size_t

typedef uint64_t ecs_id;

typedef struct ecs_view {
    void  **components;
    ecs_id *entities;
    size_t  count;
} ecs_view;

int         ecs_init            (void);
void        ecs_exit            (void);
#define     ecs_query(...)      ecs_query_arr((ecs_id []){__VA_ARGS__, 0})
ecs_view    ecs_query_arr       (ecs_id *components);

ecs_id      ecs_new             (void);
void        ecs_del             (ecs_id entity);
#define     ecs_set(e, c, ...)  ecs_set_size(e, c, __VA_ARGS__, sizeof *(__VA_ARGS__))
void        ecs_set_size        (ecs_id entity, ecs_id component, void const *data, size_t size);
void        ecs_rem             (ecs_id entity, ecs_id component);

/***********************************************************************************************************************
************************************************************************************************************************
****                                                                                                               *****
****                                                                                                               *****
****                                                 Implementation                                                *****
****                                                                                                               *****
****                                                                                                               *****
************************************************************************************************************************
***********************************************************************************************************************/


#if defined(ECS_IMPLEMENTATION) || defined(IMPLEMENTATION)

#ifndef ecs_memmove
    #ifdef memmove
        #define ecs_memmove memmove
    #else
        #include <string.h>
        #define ecs_memmove memmove
    #endif
#endif

#ifndef ecs_memcpy
    #ifdef memcpy
        #define ecs_memcpy memcpy
    #else
        #include <string.h>
        #define ecs_memcpy memcpy
    #endif
#endif

#ifndef ecs_memset
    #ifdef memset
        #define ecs_memset memset
    #else
        #include <string.h>
        #define ecs_memset memset
    #endif
#endif

#ifndef ecs_memcmp
    #ifdef memcmp
        #define ecs_memcmp memcmp
    #else
        #include <string.h>
        #define ecs_memcmp memcmp
    #endif
#endif

#ifndef ecs_calloc
    #ifdef calloc
        #define ecs_calloc calloc
    #else
        #include <stdlib.h>
        #define ecs_calloc calloc
    #endif
#endif

#ifndef ecs_realloc
    #ifdef realloc
        #define ecs_realloc realloc
    #else
        #include <stdlib.h>
        #define ecs_realloc realloc
    #endif
#endif

#ifndef ecs_free
    #ifdef free
        #define ecs_free free
    #else
        #include <stdlib.h>
        #define ecs_free free
    #endif
#endif

#ifndef NULL
    #define NULL ((void *)0)
#endif

typedef struct ecs__pool {
    char *data;
    size_t size;
} ecs__pool;

typedef struct ecs__archetype {
    ecs_id *type;
    ecs_id *entities;
    ecs__pool *components;
    struct ecs__archetype **rem_edges;
    struct ecs__archetype **ins_edges;
} ecs__archetype;

typedef struct ecs__record {
    ecs__archetype *archetype;
    size_t idx;
} ecs__record;

typedef struct ecs__entity_index {
    ecs_id key;
    ecs__record value;
} ecs__entity_index;

typedef struct ecs__type_index {
    ecs_id *key;
    ecs__archetype *value;
} ecs__type_index;


static struct {
    ecs_id *versions;
    ecs_id *free_ids;
    ecs__archetype *root;
    ecs__type_index *ti;
    ecs__entity_index *ei;
} _ecs = {0};


#define ecs_id__idx(i)                  ((i) & 0xFFFFFFFF)
#define ecs_id__ver(i)                  (((i) >> 32) & 0xFFFFFFFF)
#define ecs_id__make(ver, idx)          ((((ecs_id)(ver)) << 32) | ((idx) & 0xFFFFFFFF))

// Taken straight from stl.h with a few changes

#define ecs__var_impl(x)            ecs__var_##x##__LINE__
#define ecs__var(x)                 ecs__var_impl(x)

#define ecs__arr_reserve(a, n)      (ecs__arr_len(a) + (n) >= ecs__arr_cap(a) ? ecs__arr__grow(&(a), sizeof *(a) * (ecs__arr_cap(a) * 2 + (n))), 0 : 0)
#define ecs__arr_free(a)            (ecs__arr__grow(a, 0))
#define ecs__arr_dup(dst, a)        ((a) ? ecs__arr_reserve((dst), ecs__arr_len(a)), ecs_memcpy((dst), (a), ecs__arr_len(a)), 0 : 0)
#define ecs__arr_cap(a)             ((a) ? ecs__arr__cap(a) : 0)
#define ecs__arr_len(a)             ((a) ? ecs__arr__len(a) : 0)
#define ecs__arr_end(a)             ((a) ? (a) + ecs__arr_len(a) : (a))
#define ecs__arr_insn(a, i, n)      (ecs__arr_reserve(a, (i) + (n)), ecs__arr_pushn((a), (n)), ecs_memmove(&(a)[(i) + (n)], &(a)[(i)], sizeof *(a) * (ecs__arr_len(a) - (i) - (n))), &(a)[(i)])
#define ecs__arr_ins(a, i, v)       (*ecs__arr_insn(a, i, 1) = (v))
#define ecs__arr_remn(a, i, n)      (ecs__arr_len(a) >= (n) ? ecs__arr__len(a) -= (n) * sizeof *(a), ecs_memmove(&(a)[(i)], &(a)[(i) + (n)], sizeof *(a) * (ecs__arr_len(a) - (i) - (n))), 0 : 0)
#define ecs__arr_rem(a, i)          (ecs__arr_remn(a, i, 1))
#define ecs__arr_remswap(a, i)      (ecs__arr_len(a) > 0 ? (a)[i] = ecs__arr_pop(a), 0 : 0)
#define ecs__arr_remval(a, v, cmp)  do { for (int ecs__var(i) = 0; ecs__var(i) < ecs__arr_len(a); ecs__var(i)++) { if (cmp((a)[ecs__var(i)], (v)) == 0) { ecs__arr_rem(a, ecs__var(i)); break; }}} while (0)
#define ecs__arr_pushn(a, n)        (ecs__arr_reserve(a, n), ecs__arr__len(a) += (n), &(a)[ecs__arr_len(a) - (n)])
#define ecs__arr_push(a, v)         (*ecs__arr_pushn(a, 1) = (v))
#define ecs__arr_pop(a)             ((a)[ecs__arr__len(a)--])
#define ecs__arr_clear(a)           ((a) ? ecs__arr__len(a) = 0, 0 : 0)
#define ecs__arr__hdr(a)            ((int *)(a) - 2)
#define ecs__arr__cap(a)            (ecs__arr__hdr(a)[0])
#define ecs__arr__len(a)            (ecs__arr__hdr(a)[1])

static uint64_t ecs__npow2(uint64_t x) {
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

static void ecs__arr__grow(void **a, size_t size) {
    if (a == NULL) {
        return;
    } else if (size == 0 && *a != NULL) {
        ecs_free(*a);
        *a = NULL;
    } else {
        size_t *ptr = NULL;
        size = ecs__npow2(size + sizeof(size_t) * 2);
        if (*a != NULL) {
            ptr = ecs_realloc(ecs__arr__head(*a), size);
            nbd_memset(ptr + ecs__arr_len(*a), 0, size - ecs__arr_len(*a));
        } else {
            ptr = ecs_calloc(1, size);
        }
        if (ptr != NULL) {
            *ptr++ = size;
            *ptr++ = ecs__arr_len(*a);
        }
        *a = (void *)ptr;
    }
}

typedef struct ecs__map__func_storage {
    uint64_t (*hash)(void const *);
    int     (*cmp)(void const *, void const *);
} ecs__map__func_storage;

#define ecs__map_free(m)                (ecs__arr_free(ecs__map__hdr(m)))
#define ecs__map_len(m)                 ((m) ? ecs__arr_len(ecs__map__hdr(m)) : 0)
#define ecs__map_cap(m)                 ((m) ? ecs__arr_cap(ecs__map__hdr(m)) : 0)
#define ecs__map_load_factor(m)         (ecs__map_cap(m) ? ((float)ecs__map_len(m) / (float)ecs__map_cap(m)) : 1.0f)
#define ecs__map_set_default(m, k, v)   do { ecs__map__ensure(m); ecs__map__default(m).key = (k); ecs__map__default(m).value = (v); } while (0)
#define ecs__map_set_funcs(m, h, c)     do { ecs__map__ensure(m); ecs__map__funcs(m) = (ecs__map__func_storage){ .hash = (h), .cmp = (c) }; } while (0)
#define ecs__map_gets(m, k)             ((m)[ecs__map__indexof(m, sizeof *(m), &(k), sizeof (k), ecs__map__keyoff(m), ecs__map_cap(m))])
#define ecs__map_get(m, k)              (ecs__map_gets(m, k).value)
#define ecs__map_getp(m, k)             (&ecs__map_get(m, k))
#define ecs__map_has(m, k)              (ecs__map__indexof(m, sizeof *(m), &(k), sizeof (k), ecs__map__keyoff(m), ecs__map_cap(m)) != -1)
#define ecs__map_set(m, k, v)           do { ecs__map__ensure(m); ecs__map__set(m, k, v); } while (0)
#define ecs__map_rem(m, k)              (ecs__map_gets(m, k) = ecs__map__default(m), ecs__map__len(m)--)

#define ecs__map_clear(m) do {\
    for (size_t ecs__var(i) = 0; ecs__var(i) < ecs__map_cap(m); ecs__var(i)++) {\
        ecs_memcpy(&m[ecs__var(i)], &ecs__map__default(m), sizeof *(m));\
    }\
    ecs__arr_clear(ecs__map__hdr(m));\
} while (0)

#define ecs__map__hdr_size(m)           (sizeof *(m) + sizeof(ecs__map__func_storage))
#define ecs__map__hdr(m)                ((char *)(m) - ecs__map__hdr_size(m))
#define ecs__map__cap(m)                (ecs__arr__cap(ecs__map__hdr(m)))
#define ecs__map__len(m)                (ecs__arr__len(ecs__map__hdr(m)))
#define ecs__map__default(m)            ((m)[-1])
#define ecs__map__funcs(m)              (*((ecs__map__func_storage *)ecs__map__hdr(m)))
#define ecs__map__hash(m, k, n)         (ecs__map__funcs(m).hash ? ecs__map__funcs(m).hash(k) : ecs__map__fnv1a(k, n))
#define ecs__map__cmp(m, a, b, n)       ((ecs__map__funcs(m).cmp ? ecs__map__funcs(m).cmp(a, b) : ecs_memcmp(a, b, n)) == 0)
#define ecs__map__keyoff(m)             (((char *)&((m)[0].key)) - (char *)(m))

#define ecs__map__set(m, k, v) do {\
    uint64_t ecs__var(hash) = ecs__map__hash(m, &(k), sizeof (k));\
    size_t ecs__var(i) = ecs__var(hash) & (ecs__map_cap(m) - 1);\
    for (size_t ecs__var(step) = 1, ecs__var(c) = 0; ecs__var(c) < ecs__map_cap(m); ecs__var(c)++) {\
        ecs__var(i) = (ecs__var(i) + ecs__var(step)++) & (ecs__map_cap(m) - 1);\
        if (ecs__map__cmp(m, &(m)[ecs__var(i)].key, &(k), sizeof (k)) == 0) {\
            break; /* k already exists in m, update it */\
        } else if (ecs__map__cmp(m, &(m)[ecs__var(i)].key, &ecs__map__default(m).key, sizeof (k)) == 0) {\
            ecs__map__len(m)++;\
            break; /* k does not exists in m, insert it */\
        }\
    }\
    ecs_memcpy(&(m)[ecs__var(i)].key, &(k), sizeof (k));\
    ecs_memcpy(&(m)[ecs__var(i)].value, &(v), sizeof (v));\
} while (0)

#define ecs__map__ensure(m) do {\
        if (ecs__map_load_factor(m) < 0.7f) {\
            break;\
        }\
        size_t ecs__var(size) = ecs__npow2((ecs__map_cap(m) ? ecs__map_cap(m) : 8) * sizeof *(m)) + ecs__map__hdr_size(m);\
        struct { char key[sizeof (m)[0].key]; char value[sizeof (m)[0].value]; } *ecs__var(tmp) = NULL;\
        ecs__arr__grow((void **)&ecs__var(tmp), ecs__var(size));\
        if ((m) != NULL) {\
            ecs_memcpy(ecs__map__hdr(ecs__var(tmp)), ecs__map__hdr(m), ecs__map__hdr_size(ecs__var(tmp)));\
            ecs__map_clear(ecs__var(tmp));\
        }\
        for (size_t ecs__var(i) = 0; ecs__var(i) < ecs__map_cap(m); ecs__var(i)++) {\
            ecs__map__set(ecs__var(tmp), (m)[ecs__var(i)].key, (m)[ecs__var(i)].value);\
        }\
        ecs_memcpy(m, ecs__var(tmp), sizeof *(m) * ecs__map_cap(m));\
        ecs__map_free(ecs__var(tmp));\
    } while (0)

static uint64_t ecs__map__fnv1a(void const *key, size_t size) {
    uint64_t hash = 14695981039346656037UL;
    for (char const *p = key; size; size--, p++) {
        hash ^= (uint64_t)(*p);
        hash *= 1099511628211UL;
    }
    return hash;
}

static int ecs__map__indexof(void *m, size_t msize, void *k, size_t ksize, size_t koff, size_t cap) {
    ecs__map__func_storage funcs = *((ecs__map__func_storage *)(msize + sizeof funcs));
    uint64_t hash = funcs.hash != NULL ? funcs.hash(k) : ecs__map__fnv1a(k, ksize);
    for (size_t i = hash & (cap - 1), step = 1, c = 0; c < cap; c++, i = (i + step++) & (cap - 1)) {
        void *cur = (char *)m + i * msize;
        void *key = (char *)cur + koff;
        if ((funcs.cmp != NULL ? funcs.cmp(key, k) : ecs_memcmp(key, k, ksize)) == 0) {
            return i;
        }
    }
    return -1;
}

static uint64_t ecs__type_hash(void const *key) {
    ecs_id const *type = key;
    uint64_t hash = 5381;
    for (size_t i = 0; i < ecs__arr_len(type); i++) {
            hash = ((hash << 5) + hash) ^ type[i];
    }
    return hash;
}

static int ecs__type_cmp(void const *a, void const *b) {
    ecs_id const *at = a;
    ecs_id const *bt = b;
    size_t n = ecs__arr_len(at) < ecs__arr_len(bt) ? ecs__arr_len(at) : ecs__arr_len(bt);
    for (size_t i = 0; i < n; i++) {
        if (at[i] != bt[i]) {
            return at[i] - bt[i];
        }
    }
    return 0;
}

static int ecs__type_is_subset(ecs_id const *sub, ecs_id const *super) {
    size_t n = ecs__arr_len(super);
    size_t m = ecs__arr_len(sub);

    if (n < m) {
        return 0;
    }

    // O(n^2), but the arrays are small enough that it's shouldn't be an issue
    // If this turns out to be a bottleneck I'll find a different solution
    for (size_t i = 0, j = 0; i < n; i++) {
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

static uint64_t ecs__id_hash(void const *key) {
    ecs_id id = *(ecs_id const *)key;
    id = ((id >> 16) ^ id) * 0x45d9f3b;
    id = ((id >> 16) ^ id) * 0x45d9f3b;
    id =  (id >> 16) ^ id;
    return id;
}

static int ecs__id_cmp(void const *a, void const *b) {
    return *(ecs_id const *)a - *(ecs_id const *)b;
}

static void ecs__archetype__connect(ecs__archetype *a, ecs__archetype *b) {
    ecs__arr_push(a->ins_edges, b);
    ecs__arr_push(b->rem_edges, a);
}

static void ecs__archetype__ins(ecs__archetype *from, ecs__archetype *to) {
    if (ecs__arr_len(from->type) < ecs__arr_len(to->type) - 1) {
        for (size_t i = 0; i < ecs__arr_len(from->ins_edges); i++) {
            ecs__archetype__ins(from->ins_edges[i], to);
        }
    } else if (ecs__type_is_subset(from->type, to->type) == 1) {
        ecs__archetype__connect(from, to);
    }
}

static ecs__archetype *ecs__archetype_create(ecs_id *type, ecs__type_index *ti) {
    ecs__archetype *archetype = ecs__map_get(ti, type);
    if (archetype == NULL) {
        archetype = calloc(1, sizeof *archetype);
        if (archetype != NULL) {
            archetype->type = type;
            ecs__map_set(ti, type, archetype);
        }
    }

    return archetype;
}

static ecs__archetype *ecs__archetype_create_ins(ecs__archetype *root, ecs__archetype *rem, ecs__type_index *ti, ecs_id *type) {
    ecs__archetype *ins = ecs__archetype_create(type, ti);
    ecs__archetype__connect(rem, ins);
    ecs__archetype__ins(root, ins);
    return ins;
}

static void ecs__archetype_free(ecs__archetype *archetype) {
    for (size_t i = 0; i < ecs__arr_len(archetype->components); i++) {
        ecs__arr_free(archetype->components[i].data);
    }
    ecs__arr_free(archetype->components);
    ecs__arr_free(archetype->type);
    ecs__arr_free(archetype->rem_edges);
    ecs__arr_free(archetype->ins_edges);
    ecs__arr_free(archetype->entities);
    free(archetype);
}

static size_t ecs__archetype_move(ecs__archetype *rem, ecs__archetype *ins, ecs__entity_index *ei, size_t rem_idx) {
    assert(rem_idx < ecs__arr_len(rem->entities) && "Row out of bounds");

    ecs_id e = rem->entities[rem_idx];
    ecs__arr_remswap(rem->entities, rem_idx);
    size_t ins_idx = ecs__arr_push(ins->entities, e);
    ecs__map_set(ei, e, ((ecs__record){.archetype = ins, .idx = ins_idx}));

    for (size_t i = 0; i < ecs__arr_len(rem->type); i++) {
        assert(rem->type[i] >= ins->type[i] && "Elements in type mismatched");

        size_t j = 0;
        while (rem->type[i] != ins->type[j]) {
            j++;
        }

        size_t size = rem->components[i].size;
        ecs_memcpy(&ins->components[j].data[size * ins_idx], &rem->components[i].data[size * ins_idx], size);
    }

    return ins_idx;
}


// =============================================================


int ecs_init(void) {
    ecs__map_set_funcs(_ecs.ti, ecs__type_hash, ecs__type_cmp);
    ecs__map_set_funcs(_ecs.ei, ecs__id_hash, ecs__id_cmp);
    return 0;
}

void ecs_exit(void) {
    ecs__arr_free(_ecs.versions);
    ecs__arr_free(_ecs.free_ids);
    ecs__map_free(_ecs.ti);
    ecs__map_free(_ecs.ei);
    nbd_memset(&_ecs, 0, sizeof(_ecs));
}

ecs_id ecs_new(void) {
    ecs_id index = 0;
    if (ecs__arr_len(_ecs.free_ids) != 0) {
        index = ecs__arr_pop(_ecs.free_ids);
    } else {
        index = ecs__arr_len(_ecs.versions);
        ecs__arr_push(_ecs.versions, 1);
    }
    return ecs_id__make(_ecs.versions[index], index);
}

void ecs_del(ecs_id e) {
    if (ecs_id__ver(e) != _ecs.versions[ecs_id__idx(e)]) {
        return; // Entity was already deleted
    }
    ecs_id index = ecs_id__idx(e);
    _ecs.versions[index]++;
    ecs__arr_push(_ecs.free_ids, index);
}

void ecs_set_size(ecs_id e, ecs_id c, void const *data, size_t size) {
    ecs__record record = ecs__map_get(_ecs.ei, e);
    if (record.archetype == NULL) {
        return; // Unknown entity
    }

    ecs_id *type = NULL;
    ecs__arr_dup(type, record.archetype->type);
    size_t cidx = ecs__arr_push(type, c);

    // Find the new archetype (create it if it does not exist)
    ecs__archetype **archetype = ecs__map_getp(_ecs.ti, type);
    if (*archetype == NULL) {
        *archetype = ecs__archetype_create_ins(_ecs.root, record.archetype, _ecs.ti, type);
        (*archetype)->components[cidx].size = size;
    } else {
        ecs__arr_free(type);
    }

    // Move the entity along c's edge in the graph and update its record
    size_t eidx = ecs__archetype_move(record.archetype, *archetype, _ecs.ei, record.idx);
    ecs__map_set(_ecs.ei, e, ((ecs__record){.archetype = *archetype, .idx = eidx}));

    if (data != NULL) {
        char *carr = record.archetype->components[cidx].data;
        ecs_memcpy(&carr[record.idx * size], data, size);
        ecs__arr__len(carr)++;
    }
}

void ecs_rem(ecs_id e, ecs_id c) {
    ecs__record record = ecs__map_get(_ecs.ei, e);
    if (record.archetype == NULL) {
        return; // Unknown entity
    }

    ecs_id *type = NULL;
    ecs__arr_dup(type, record.archetype->type);

    #define eq(a, b) ((a) == (b))
    ecs__arr_remval(type, c, eq);
    #undef eq

    // Find the new archetype
    ecs__archetype *archetype = ecs__map_get(_ecs.ti, type);
    ecs__arr_free(type);
    if (archetype == NULL) {
        return; // Unknown type
    }

    // Move the entity along the component's edge in the graph and update its record
    size_t eidx = ecs__archetype_move(record.archetype, archetype, _ecs.ei, record.idx);
    ecs__map_set(_ecs.ei, e, ((ecs__record){.archetype = archetype, .idx = eidx}));
}

ecs_view ecs_query_arr(ecs_id components[]) {
    size_t n = 0;
    ecs_id *cursor = components;
    while (*cursor++ != 0) {
        n++;
    }

    ecs_id *type = NULL;
    ecs_memcpy(ecs__arr_pushn(type, n), components, n * sizeof *type);

    ecs__archetype *archetype = ecs__map_get(_ecs.ti, type);
    ecs__arr_free(type);

    // TODO

    return (ecs_view){0}; // Unknown type
}

#endif // ECS_IMPL_IMPLEMENTATION || IMPL_IMPLEMENTATION
