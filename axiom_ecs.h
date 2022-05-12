/* axiom_ecs.h - A simple Entity Component System for C/C++ - v0.03 - public domain

========================================================================================================================

	YOU MUST

		#define AXIOM_ECS_IMPL

	in EXACTLY _one_ C or C++ file that includes this header, BEFORE the
	include like this:

		#define AXIOM_ECS_IMPL
		#include "axiom_ecs.h"

	All other files should just #include "axiom_ecs.h" without the #define

========================================================================================================================

LICENSE
	This software is placed under the public domain. See the end of this file
    for the full license.

CREDITS
	Written by Evan Dobson

TODOS
    -

VERSION HISTORY
    0.03  - Project name change
    0.02  - Added arrays, maps, and archetypes
    0.01a - Simplified API
    0.01  - Initial version
*/

#ifndef AXIOM_ECS_H
#define AXIOM_ECS_H

#include <stdbool.h>
#include <stdint.h>  // uint64_t
#include <stddef.h>  // size_t

#ifndef ECS_MAX_TYPES_PER_QUERY
    #define ECS_MAX_TYPES_PER_QUERY 64
#endif

typedef uint64_t ecs_id;

typedef struct ecs_view {
    void   *components[ECS_MAX_TYPES_PER_QUERY];
    ecs_id *entities;
    size_t  count;
} ecs_view;

typedef struct ecs_world ecs_world;

ecs_world  *ecs_alloc                   (void);
void        ecs_free                    (ecs_world *world);
#define     ecs_query(world, ...)       ecs__query(world, (ecs_id []){__VA_ARGS__, 0})
ecs_id      ecs_new                     (ecs_world *world);
void        ecs_del                     (ecs_world *world, ecs_id e);
#define     ecs_set(world, e, c, ...)   ecs_set_size(world, e, c, __VA_ARGS__, sizeof *(__VA_ARGS__))
void        ecs_set_size                (ecs_world *world, ecs_id e, ecs_id c, void const *data, size_t size);
void        ecs_rem                     (ecs_world *world, ecs_id e, ecs_id c);

// ==== Private ===============================================

ecs_view    ecs__query                  (ecs_world *world, ecs_id components[]);


/***********************************************************************************************************************
************************************************************************************************************************
****                                                                                                               *****
****                                                                                                               *****
****                                                 Implementation                                                *****
****                                                                                                               *****
****                                                                                                               *****
************************************************************************************************************************
***********************************************************************************************************************/


#if defined(AXIOM_ECS_IMPL) || defined(AXIOM_IMPL)
#ifndef AXIOM_ECS_C
#define AXIOM_ECS_C

#include <assert.h>
#include <string.h> // memset, memcpy, memcmp, memmove
#include <stdlib.h> // calloc, realloc, free
#include <stdio.h>  // fprintf

typedef struct ecs__pool {
    uint8_t *data;
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

struct ecs_world {
    ecs_id *versions;
    ecs_id *free_ids;
    ecs__archetype *root;
    ecs__type_index *ti;
    ecs__entity_index *ei;
};

#define ecs__advance_until(x, cond)     for (; (cond) == 0; (x)++)
#define ecs__log(...)                   do { fprintf(stderr, "[axiom_ecs.h:%04d] ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); } while (0)

#define ecs_id__idx(i)                  ((uint32_t)(i))
#define ecs_id__ver(i)                  ((uint32_t)((i) >> 32))
#define ecs_id__make(ver, idx)          ((((ecs_id)(ver)) << 32) | (uint32_t)(idx))

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

// Taken straight from axiom_ds.h with a name change

#define ecs__var(x)                      ecs__var_##x##__LINE__##__

#define ecs__buffer_reserve(b, sz)      (ecs__buffer_len(b) + (sz) >= ecs__buffer_cap(b) ? (b) = ecs__buffer__grow(b, ecs__buffer_cap(b) * 2 + (sz)), 0 : 0)
#define ecs__buffer_free(b)             (ecs__buffer__grow(b, 0))
#define ecs__buffer_dup(dst, b)         ((b) ? ecs__buffer_reserve((dst), ecs__buffer_len(b)), memcpy((dst), (b), ecs__buffer_len(b)), 0 : 0)
#define ecs__buffer_cap(b)              ((b) ? ecs__buffer__cap(b) : 0)
#define ecs__buffer_len(b)              ((b) ? ecs__buffer__len(b) : 0)
#define ecs__buffer_clear(b)            ((b) ? ecs__buffer__len(b) = ecs__buffer__pos(b) = 0, 0 : 0)
#define ecs__buffer__head(b)            ((size_t *)(b) - 3)
#define ecs__buffer__cap(b)             (ecs__buffer__head(b)[0])
#define ecs__buffer__len(b)             (ecs__buffer__head(b)[1])
#define ecs__buffer__pos(b)             (ecs__buffer__head(b)[2])

static void *ecs__buffer__grow(void *b, size_t size) {
    if (size == 0) {
        free(b != NULL ? ecs__buffer__head(b) : b);
        return NULL;
    }

    size_t *ptr = NULL;
    size = ecs__npow2(size + sizeof(size_t) * 2);
    if (b != NULL) {
        ptr = realloc(ecs__buffer__head(b), size);
        memset(ptr + ecs__buffer_len(b), 0, size - ecs__buffer_len(b));
    } else {
        ptr = calloc(1, size);
    }
    if (ptr != NULL) {
        *ptr++ = size;
        *ptr++ = ecs__buffer_len(b);
    }
    return (void *)ptr;
}

#define ecs__array_reserve(a, n)        (ecs__buffer_reserve(a, (n) * sizeof *(a)))
#define ecs__array_free(a)              (ecs__buffer_free(a))
#define ecs__array_dup(dst, a)          (ecs__buffer_dup(dst, a))
#define ecs__array_cap(a)               (ecs__buffer_cap(a) / sizeof *(a))
#define ecs__array_len(a)               (ecs__buffer_len(a) / sizeof *(a))
#define ecs__array_insn(a, i, n)        (ecs__array__ensure(a, i), ecs__array_pushn((a), (n)), memmove(&(a)[(i) + (n)], &(a)[(i)], sizeof *(a) * (ecs__array_len(a) - (i) - (n))), &(a)[(i)])
#define ecs__array_ins(a, i, v)         (*ecs__array_insn(a, i, 1) = (v))
#define ecs__array_remn(a, i, n)        (ecs__array_len(a) >= (n) ? ecs__buffer__len(a) -= (n) * sizeof *(a), memmove(&(a)[(i)], &(a)[(i) + (n)], sizeof *(a) * (ecs__array_len(a) - (i) - (n))), 0 : 0)
#define ecs__array_rem(a, i)            (ecs__array_remn(a, i, 1))
#define ecs__array_remswap(a, i)        (ecs__array_len(a) > 0 ? (a)[i] = ecs__array_pop(a), 0 : 0)
#define ecs__array_remval(a, v, eqfn)   do { for (size_t ecs__var(i) = 0; ecs__var(i) < ecs__array_len(a); ecs__var(i)++) { if (eqfn((a)[ecs__var(i)], (v)) == true) { ecs__array_rem(a, ecs__var(i)); break; }}} while (0)
#define ecs__array_pushn(a, n)          (ecs__buffer__len(a) += (n) * sizeof *(a), ecs__buffer__pos(a) += (n) * sizeof *(a), &(a)[ecs__array_len(a) - (n)])
#define ecs__array_push(a, v)           (*ecs__array_pushn(a, 1) = (v))
#define ecs__array_pop(a)               (ecs__buffer__len(a) -= sizeof *(a), (a)[ecs__array_len(a)])
#define ecs__array_clear(a)             (ecs__buffer_clear(a))
#define ecs__array__ensure(a, i)        ((i) > ecs__array_cap(a) ? ecs__array_reserve(a, i), 0 : 0)

typedef struct ecs__map__func_storage {
    uint64_t (*hash)(void const *);
    bool     (*equal)(void const *, void const *);
} ecs__map__func_storage;

#define ecs__map_free(m)                (ecs__array_free(ecs__map__head(m)))
#define ecs__map_len(m)                 ((m) ? ecs__array_len(ecs__map__head(m)) : 0)
#define ecs__map_cap(m)                 ((m) ? ecs__array_cap(ecs__map__head(m)) : 0)
#define ecs__map_load_factor(m)         (ecs__map_cap(m) ? ((float)ecs__map_len(m) / (float)ecs__map_cap(m)) : 1.0f)
#define ecs__map_set_default(m, k, v)   do { ecs__map__ensure(m); ecs__map__default(m).key = (k); ecs__map__default(m).value = (v); } while (0)
#define ecs__map_set_funcs(m, h, e)     do { ecs__map__ensure(m); ecs__map__funcs(m) = (ecs__map__func_storage){ .hash = (h), .equal = (e) }; } while (0)
#define ecs__map_gets(m, k)             ((m)[ecs__map__indexof(m, sizeof *(m), &(k), sizeof (k), ecs__map__keyoff(m), ecs__map_cap(m))])
#define ecs__map_get(m, k)              (ecs__map_gets(m, k).value)
#define ecs__map_getp(m, k)             (&ecs__map_get(m, k))
#define ecs__map_has(m, k)              (ecs__map__indexof(m, sizeof *(m), &(k), sizeof (k), ecs__map__keyoff(m), ecs__map_cap(m)) != -1)
#define ecs__map_set(m, k, v)           do { ecs__map__ensure(m); ecs__map__set(m, k, v); } while (0)
#define ecs__map_rem(m, k)              (ecs__map_gets(m, k) = ecs__map__default(m), ecs__map__len(m)--)
#define ecs__map_clear(m)\
    do {\
        for (size_t ecs__var(i) = 0; ecs__var(i) < ecs__map_cap(m); ecs__var(i)++) {\
            memcpy(&m[ecs__var(i)], &ecs__map__default(m), sizeof *(m));\
        }\
        ecs__array_clear(ecs__map__head(m));\
    } while (0)

#define ecs__map__header_size(m)        (sizeof *(m) + sizeof(ecs__map__func_storage))
#define ecs__map__head(m)               ((char *)(m) - ecs__map__header_size(m))
#define ecs__map__cap(m)                (ecs__buffer__cap(ecs__map__head(m)))
#define ecs__map__len(m)                (ecs__buffer__len(ecs__map__head(m)))
#define ecs__map__default(m)            ((m)[-1])
#define ecs__map__funcs(m)              (*((ecs__map__func_storage *)ecs__map__head(m)))
#define ecs__map__hash(m, k, n)         (ecs__map__funcs(m).hash ? ecs__map__funcs(m).hash(k) : ecs__map__fnv1a(k, n))
#define ecs__map__equal(m, a, b, n)     (ecs__map__funcs(m).equal ? ecs__map__funcs(m).equal(a, b) : memcmp(a, b, n) == 0)
#define ecs__map__keyoff(m)             (((char *)&((m)[0].key)) - (char *)(m))

#define ecs__map__set(m, k, v)\
    do {\
        uint64_t ecs__var(hash) = ecs__map__hash(m, &(k), sizeof (k));\
        size_t ecs__var(i) = ecs__var(hash) & (ecs__map_cap(m) - 1);\
        for (size_t ecs__var(step) = 1, ecs__var(c) = 0; ecs__var(c) < ecs__map_cap(m); ecs__var(c)++) {\
            ecs__var(i) = (ecs__var(i) + ecs__var(step)++) & (ecs__map_cap(m) - 1);\
            if (ecs__map__equal(m, &(m)[ecs__var(i)].key, &(k), sizeof (k)) == 0) {\
                break; /* k already exists in m, update it */\
            } else if (ecs__map__equal(m, &(m)[ecs__var(i)].key, &ecs__map__default(m).key, sizeof (k)) == 0) {\
                ecs__map__len(m)++;\
                break; /* k does not exists in m, insert it */\
            }\
        }\
        memcpy(&(m)[ecs__var(i)].key, &(k), sizeof (k));\
        memcpy(&(m)[ecs__var(i)].value, &(v), sizeof (v));\
    } while (0)

#define ecs__map__ensure(m)\
    do {\
        if (ecs__map_load_factor(m) < 0.7f) {\
            break;\
        }\
        size_t ecs__var(size) = ecs__npow2((ecs__map_cap(m) ? ecs__map_cap(m) : 8) * sizeof *(m)) + ecs__map__header_size(m);\
        struct { char key[sizeof (m)[0].key]; char value[sizeof (m)[0].value]; } *ecs__var(tmp) = ecs__buffer__grow(NULL, ecs__var(size));\
        if ((m) != NULL) {\
            memcpy(ecs__map__head(ecs__var(tmp)), ecs__map__head(m), ecs__map__header_size(ecs__var(tmp)));\
            ecs__map_clear(ecs__var(tmp));\
        }\
        for (size_t ecs__var(i) = 0; ecs__var(i) < ecs__map_cap(m); ecs__var(i)++) {\
            ecs__map__set(ecs__var(tmp), (m)[ecs__var(i)].key, (m)[ecs__var(i)].value);\
        }\
        memcpy(m, ecs__var(tmp), sizeof *(m) * ecs__map_cap(m));\
        ecs__map_free(ecs__var(tmp));\
    } while (0)

static uint64_t ecs__map__fnv1a(void const *key, size_t size) {
    uint64_t hash = 14695981039346656037UL;
    for (uint8_t const *p = key; size; size--, p++) {
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
        if (funcs.equal != NULL ? funcs.equal(key, k) == true : memcmp(key, k, ksize) == 0) {
            return i;
        }
    }
    return -1;
}

static uint64_t ecs__type_hash(void const *key) {
    ecs_id const *type = key;
    uint64_t hash = 5381;
    for (size_t i = 0; i < ecs__array_len(type); i++) {
            hash = ((hash << 5) + hash) ^ type[i];
    }
    return hash;
}

static bool ecs__type_equal(void const *a, void const *b) {
    ecs_id const *at = a;
    ecs_id const *bt = b;
    size_t atn = ecs__array_len(at);
    size_t btn = ecs__array_len(bt);
    size_t n = atn < btn ? atn : btn;
    for (size_t i = 0; i < n; i++) {
        if (at[i] != bt[i]) {
            return false;
        }
    }
    return true;
}

static bool ecs__type_is_subset(ecs_id const *sub, ecs_id const *super) {
    size_t n = ecs__array_len(super);
    size_t m = ecs__array_len(sub);

    if (n < m) {
        return false;
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
            return false;
        }
    }

    return true;
}

static uint64_t ecs__id_hash(void const *key) {
    ecs_id id = *(ecs_id const *)key;
    id = ((id >> 16) ^ id) * 0x45d9f3b;
    id = ((id >> 16) ^ id) * 0x45d9f3b;
    id =  (id >> 16) ^ id;
    return id;
}

static bool ecs__id_equal(void const *a, void const *b) {
    return *(ecs_id const *)a == *(ecs_id const *)b;
}

static void ecs__archetype__connect(ecs__archetype *a, ecs__archetype *b) {
    ecs__array_push(a->ins_edges, b);
    ecs__array_push(b->rem_edges, a);
}

static void ecs__archetype__ins(ecs__archetype *from, ecs__archetype *to) {
    if (ecs__array_len(from->type) < ecs__array_len(to->type) - 1) {
        for (size_t i = 0; i < ecs__array_len(from->ins_edges); i++) {
            ecs__archetype__ins(from->ins_edges[i], to);
        }
    } else if (ecs__type_is_subset(from->type, to->type) == true) {
        ecs__archetype__connect(from, to);
    }
}

static ecs__archetype *ecs__archetype_alloc(ecs_id *type, ecs__type_index *ti) {
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

static ecs__archetype *ecs__archetype_alloc_ins(ecs__archetype *root, ecs__archetype *rem, ecs__type_index *ti, ecs_id *type) {
    ecs__archetype *ins = ecs__archetype_alloc(type, ti);
    ecs__archetype__connect(rem, ins);
    ecs__archetype__ins(root, ins);
    return ins;
}

static void ecs__archetype_free(ecs__archetype *archetype) {
    for (size_t i = 0; i < ecs__array_len(archetype->components); i++) {
        ecs__array_free(archetype->components[i].data);
    }
    ecs__array_free(archetype->components);
    ecs__array_free(archetype->type);
    ecs__array_free(archetype->rem_edges);
    ecs__array_free(archetype->ins_edges);
    ecs__array_free(archetype->entities);
    free(archetype);
}

static size_t ecs__archetype_move(ecs__archetype *rem, ecs__archetype *ins, ecs__entity_index *ei, size_t rem_idx) {
    assert(rem_idx < ecs__array_len(rem->entities) && "Row out of bounds");

    ecs_id e = rem->entities[rem_idx];
    ecs__array_remswap(rem->entities, rem_idx);
    size_t ins_idx = ecs__array_push(ins->entities, e);
    ecs__map_set(ei, e, ((ecs__record){.archetype = ins, .idx = ins_idx}));

    for (size_t i = 0; i < ecs__array_len(rem->type); i++) {
        assert(rem->type[i] >= ins->type[i] && "Elements in type mismatched");

        size_t j = 0;
        ecs__advance_until(j, rem->type[i] == ins->type[j]);

        size_t size = rem->components[i].size;
        memcpy(&ins->components[j].data[size * ins_idx], &rem->components[i].data[size * ins_idx], size);
    }

    return ins_idx;
}


// =============================================================


bool ecs_init(ecs_world *world) {
    ecs__map_set_funcs(world->ti, ecs__type_hash, ecs__type_equal);
    ecs__map_set_funcs(world->ei, ecs__id_hash, ecs__id_equal);
    return true;
}

void ecs_deinit(ecs_world *world) {
    ecs__array_free(world->versions);
    ecs__array_free(world->free_ids);
    ecs__map_free(world->ti);
    ecs__map_free(world->ei);
    memset(world, 0, sizeof *world);
}

ecs_id ecs_new(ecs_world *world) {
    ecs_id index = 0;
    if (ecs__array_len(world->free_ids) != 0) {
        index = ecs__array_pop(world->free_ids);
    } else {
        index = ecs__array_len(world->versions);
        ecs__array_push(world->versions, 1);
    }
    return ecs_id__make(world->versions[index], index);
}

void ecs_del(ecs_world *world, ecs_id e) {
    if (ecs_id__ver(e) != world->versions[ecs_id__idx(e)]) {
        return; // Entity was already deleted
    }
    ecs_id index = ecs_id__idx(e);
    world->versions[index]++;
    ecs__array_push(world->free_ids, index);
}

void ecs__set(ecs_world *world, ecs_id e, ecs_id c, void const *data, size_t size) {
    ecs__record record = ecs__map_get(world->ei, e);
    if (record.archetype == NULL) {
        return; // Unknown entity
    }

    ecs_id *type = NULL;
    ecs__array_dup(type, record.archetype->type);
    size_t cidx = ecs__array_push(type, c);

    // Find the new archetype (create it if it does not exist)
    ecs__archetype **archetype = ecs__map_getp(world->ti, type);
    if (*archetype == NULL) {
        *archetype = ecs__archetype_alloc_ins(world->root, record.archetype, world->ti, type);
        (*archetype)->components[cidx].size = size;
    } else {
        ecs__array_free(type);
    }

    // Move the entity along c's edge in the graph and update its record
    size_t eidx = ecs__archetype_move(record.archetype, *archetype, world->ei, record.idx);
    ecs__map_set(world->ei, e, ((ecs__record){.archetype = *archetype, .idx = eidx}));

    if (data != NULL) {
        uint8_t *carr = record.archetype->components[cidx].data;
        memcpy(&carr[record.idx * size], data, size);
        ecs__buffer__len(carr)++;
    }
}

void ecs_rem(ecs_world *world, ecs_id e, ecs_id c) {
    ecs__record record = ecs__map_get(world->ei, e);
    if (record.archetype == NULL) {
        return; // Unknown entity
    }

    ecs_id *type = NULL;
    ecs__array_dup(type, record.archetype->type);

    #define eq(a, b) ((a) == (b))
    ecs__array_remval(type, c, eq);
    #undef eq

    // Find the new archetype
    ecs__archetype *archetype = ecs__map_get(world->ti, type);
    ecs__array_free(type);
    if (archetype == NULL) {
        return; // Unknown type
    }

    // Move the entity along the component's edge in the graph and update its record
    size_t eidx = ecs__archetype_move(record.archetype, archetype, world->ei, record.idx);
    ecs__map_set(world->ei, e, ((ecs__record){.archetype = archetype, .idx = eidx}));
}

ecs_view ecs__query(ecs_world *world, ecs_id components[]) {
    size_t n = 0;
    ecs_id *cursor = components;
    ecs__advance_until(n, *cursor++ == 0);

    ecs_id *type = NULL;
    memcpy(ecs__array_pushn(type, n), components, n * sizeof *type);

    ecs__archetype *archetype = ecs__map_get(world->ti, type);
    ecs__array_free(type);

    if (archetype != NULL) {
        ecs_view view = {
            .entities = archetype->entities,
            .count = ecs__array_len(archetype->entities)
        };
        for (int i = 0; i < ECS_MAX_TYPES_PER_QUERY && i < ecs__array_len(archetype->components); i++) {
            view.components[i] = archetype->components[i];
        }
        return view;
    }

    return (ecs_view){0}; // Unknown type
}

#endif // !AXIOM_ECS_C
#endif // AXIOM_ECS_IMPL || AXIOM_IMPL
#endif // !AXIOM_ECS_H

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
