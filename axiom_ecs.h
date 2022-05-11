#ifndef AXIOM_ECS_H
#define AXIOM_ECS_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t axe_id;

typedef struct axe_view {
    void   **components;
    axe_id  *entities;
    size_t   count;
} axe_view;

typedef struct axe__entity_index axe__entity_index;
typedef struct axe__type_index axe__type_index;
typedef struct axe__archetype axe__archetype;

typedef struct axe_world {
    axe_id *versions;
    axe_id *free_ids;
    axe__archetype *root;
    axe__type_index *ti;
    axe__entity_index *ei;
} axe_world;

bool     axe_init                   (axe_world *world);
void     axe_deinit                 (axe_world *world);
#define  axe_query(world, ...)      axe__query(world, (axe_id []){__VA_ARGS__, 0})
axe_id   axe_create                 (axe_world world);
void     axe_destroy                (axe_world world, axe_id e);
#define  axe_set(world, e, c, ...)  axe_ins(world, e, c, __VA_ARGS__, sizeof *(__VA_ARGS__)) // How to get size if the component is a void *?
void     axe_rem                    (axe_world world, axe_id e, axe_id c);

// ==== Private ================

axe_view axe__query                 (axe_world world, axe_id components[]);
void     axe__set                   (axe_world world, axe_id e, axe_id c, void const *data, size_t size);


/*************************************************************************************************************************************************************
**************************************************************************************************************************************************************
****                                                                                                                                                      ****
****                                                                                                                                                      ****
****                                                                    Implementation                                                                    ****
****                                                                                                                                                      ****
****                                                                                                                                                      ****
**************************************************************************************************************************************************************
*************************************************************************************************************************************************************/


#if defined(AXE_IMPL) || defined(AXIOM_IMPL)
#ifndef AXIOM_ECS_C
#define AXIOM_ECS_C

#include <stdlib.h> // calloc, realloc, free
#include <string.h> // memset, memcpy, memcmp, memmove
#include <stdio.h>  // fprintf

typedef struct axe__pool {
    uint8_t *data;
    size_t csize;
} axe__pool;

typedef struct axe__record {
    axe__archetype *archetype;
    size_t idx;
} axe__record;

struct axe__entity_index {
    axe_id key;
    axe__record value;
};

struct axe__type_index {
    axe_id *key;
    axe__archetype *value;
};

struct axe__archetype {
    axe_id *type;
    axe_id *entities;
    axe__pool *components;
    axe__archetype **rem_edges;
    axe__archetype **ins_edges;
};

// Define the needed axe structures

#define axe__var(x)                     axe__var_##x##__LINE__##__

#define axe__array_reserve(a, n)        (axe__array__ensure(a, 0, n))
#define axe__array_free(a)              ((a) != NULL ? free(axe__array__head(a)), 0 : 0)
#define axe__array_dup(dst, a)          ((a) != NULL ? memcpy(axe__array_pushn(dst, axe__array_len(a)), (a), axe__array_len(a) * sizeof *(a)), 0 : 0)
#define axe__array_cap(a)               ((a) != NULL ? axe__array__cap(a) : 0)
#define axe__array_len(a)               ((a) != NULL ? axe__array__len(a) : 0)
#define axe__array_insn(a, i, n)        (axe__array__ensure(a, i, n), memmove(axe__array_pushn(a, n), &(a)[(i)], sizeof *(a) * (axe__array_len(a) - (n) - (i))), &(a)[(i)])
#define axe__array_ins(a, i, v)         (*axe__array_insn(a, i, 1) = (v))
#define axe__array_remn(a, i, n)        (axe__array_len(a) >= (n) ? axe__array__len(a) -= (n), memmove(&(a)[(i)], &(a)[(i) + (n)], sizeof *(a) * (axe__array_len(a) - (n) - (i))), 0 : 0)
#define axe__array_rem(a, i)            (axe__array_remn(a, i, 1))
#define axe__array_remswap(a, i)        (axe__array_len(a) > 0 ? (a)[(i)] = axe__array_pop(a), 0 : 0)
#define axe__array_remval(a, v, eqfn)   do { axe__array_for(axe__var(i), a) { if (eqfn(a[axe__var(i)], (v)) == true) { axe__array_rem(a, axe__var(i)); break; }}} while (0)
#define axe__array_pushn(a, n)          (axe__array__ensure(a, 0, n), axe__array__len(a) += (n), &(a)[axe__array_len(a) - (n)])
#define axe__array_push(a, v)           (*axe__array_pushn(a, 1) = (v), axe__array_len(a) - 1)
#define axe__array_pop(a)               ((a)[--axe__array__len(a)])
#define axe__array_clear(a)             (axe__array_len(a) > 0 ? axe__array__len(a) = 0, 0 : 0)
#define axe__array_for(i, a)            for (size_t (i) = 0; (i) < axe__array_len(a); (i)++)

#define axe__array__head(a)             ((size_t *)(a) - 2)
#define axe__array__cap(a)              (axe__array__head(a)[0])
#define axe__array__len(a)              (axe__array__head(a)[1])
#define axe__array__ensure(a, i, n)     (axe__array_len(a) + (n) + (i) >= axe__array_cap(a) ? (a) = axe__array__grow(a, sizeof *(a), axe__npow2(axe__array_cap(a) * 2 + (n) + (i))), 0 : 0)

static void *axe__array__grow(void *a, size_t asize, size_t n) {
    size_t *ptr = NULL;
    size_t size = n * asize + sizeof(size_t) * 2;
    if (a != NULL) {
        ptr = realloc(axe__array__head(a), size);
        memset(ptr + axe__array_len(a) * asize, 0, size - axe__array_len(a) * asize);
    } else {
        ptr = calloc(1, size);
    }
    if (ptr != NULL) {
        *ptr++ = n;
        *ptr++ = axe__array_len(a);
    }
    return (void *)ptr;
}

typedef struct axe__map__func_storage {
        uint64_t (*hash)(void const *);
        bool     (*equal)(void const *, void const *);
} axe__map__func_storage;

#define axe__map_free(m)                (axe__array_free(axe__map__head(m)))
#define axe__map_len(m)                 ((m) != NULL ? axe__array_len(axe__map__head(m)) : 0)
#define axe__map_cap(m)                 ((m) != NULL ? axe__array_cap(axe__map__head(m)) : 0)
#define axe__map_load_factor(m)         (axe__map_cap(m) != 0 ? ((float)axe__map_len(m) / (float)axe__map_cap(m)) : 1.0f)
#define axe__map_set_default(m, k, v)   do { axe__map__ensure(m); axe__map__default(m).key = (k); axe__map__default(m).value = (v); } while (0)
#define axe__map_set_funcs(m, h, c)     do { axe__map__ensure(m); axe__map__funcs(m) = (axe__map__func_storage){.hash = (h), .equal = (c)}; } while (0)
#define axe__map_gets(m, k)             ((m)[axe__map__indexof(m, sizeof *(m), &(k), sizeof (k), axe__map__keyoff(m), axe__map_cap(m))])
#define axe__map_get(m, k)              (axe__map_gets(m, k).value)
#define axe__map_getp(m, k)             (&axe__map_get(m, k))
#define axe__map_has(m, k)              (axe__map__indexof(m, sizeof *(m), &(k), sizeof (k), axe__map__keyoff(m), axe__map_cap(m)) != -1)
#define axe__map_set(m, k, v)           do { axe__map__ensure(m); axe__map_ins(m, k, v); } while (0)
#define axe__map_rem(m, k)              (axe__map_gets(m, k) = axe__map__default(m), axe__map__len(m)--)
#define axe__map_clear(m)\
    do {\
        axe__map_for(axe__var(i), m) {\
            memcpy(&m[axe__var(i)], &axe__map__default(m), sizeof *(m));\
        }\
        axe__array_clear(axe__map__head(m));\
    } while (0)

#define axe__map_for(i, m)              for (size_t (i) = 0; (i) < axe__map_cap(m); (i)++)

#define axe__map__header_size(m)        (sizeof *(m) + sizeof(axe__map__func_storage))
#define axe__map__head(m)               ((char *)(m) - axe__map__header_size(m))
#define axe__map__cap(m)                (axe__array__cap(axe__map__head(m)))
#define axe__map__len(m)                (axe__array__len(axe__map__head(m)))
#define axe__map__default(m)            ((m)[-1])
#define axe__map__funcs(m)              (*((axe__map__func_storage *)axe__map__head(m)))
#define axe__map__hash(m, k, n)         (axe__map__funcs(m).hash != NULL ? axe__map__funcs(m).hash(k) : axe__map__fnv1a(k, n))
#define axe__map__equal(m, a, b, n)     (axe__map__funcs(m).equal != NULL ? axe__map__funcs(m).equal(a, b) : memcmp(a, b, n) == 0)
#define axe__map__keyoff(m)             (((char *)&((m)[0].key)) - (char *)(m))

#define axe__map_ins(m, k, v)\
    do {\
        uint64_t axe__var(hash) = axe__map__hash(m, &(k), sizeof (k));\
        int axe__var(mask) = axe__map_cap(m) - 1;\
        int axe__var(i) = axe__var(hash) & axe__var(mask);\
        for (size_t axe__var(step) = 1, axe__var(c) = 0; axe__var(c) < axe__map_cap(m); axe__var(c)++) {\
            axe__var(i) = (axe__var(i) + axe__var(step)++) & axe__var(mask);\
            if (axe__map__equal(m, &(m)[axe__var(i)].key, &(k), sizeof (k)) == 1) {\
                break; /* k already exists in m, update it */\
            } else if (axe__map__equal(m, &(m)[axe__var(i)].key, &axe__map__default(m).key, sizeof (k)) == true) {\
                axe__map__len(m)++;\
                break; /* k does not exists in m, insert it */\
            }\
        }\
        memcpy(&(m)[axe__var(i)].key, &(k), sizeof (k));\
        memcpy(&(m)[axe__var(i)].value, &(v), sizeof (v));\
    } while (0)

#define axe__map__ensure(m)\
    do {\
        if (axe__map_load_factor(m) < 0.7f) {\
            break;\
        }\
        size_t axe__var(size) = axe__npow2((axe__map_cap(m) != 0 ? axe__map_cap(m) : 8) * sizeof *(m)) + axe__map__header_size(m);\
        struct { char key[sizeof (m)[0].key]; char value[sizeof (m)[0].value]; } *axe__var(tmp) = axe__buffer__grow(NULL, axe__var(size));\
        axe__var(tmp) += axe__map__header_size(m);\
        if ((m) != NULL) {\
            memcpy(axe__map__head(axe__var(tmp)), axe__map__head(m), axe__map__header_size(m));\
            axe__map_clear(axe__var(tmp));\
        }\
        axe__map_for(axe__var(i), m) {\
            axe__map_ins(axe__var(tmp), (m)[axe__var(i)].key, (m)[axe__var(i)].value);\
        }\
        memcpy(m, axe__var(tmp), sizeof *(m) * axe__map_cap(m));\
        axe__map_free(axe__var(tmp));\
    } while (0)

static uint64_t axe__map__fnv1a(void const *key, size_t size) {
    uint64_t hash = 14695981039346656037UL;
    for (uint8_t const *p = key; size; size--, p++) {
        hash ^= (uint64_t)(*p);
        hash *= 1099511628211UL;
    }
    return hash;
}

static int axe__map__indexof(void *m, size_t msize, void *k, size_t ksize, size_t koff, size_t cap) {
    axe__map__func_storage funcs = *((axe__map__func_storage *)(msize + sizeof funcs));
    uint64_t hash = funcs.hash != NULL ? funcs.hash(k) : axe__map__fnv1a(k, ksize);
    for (size_t i = hash & (cap - 1), step = 1, c = 0; c < cap; c++, i = (i + step++) & (cap - 1)) {
        void *cur = (char *)m + i * msize;
        void *key = (char *)cur + koff;
        if ((funcs.equal != NULL ? funcs.equal(key, k) : memcmp(key, k, ksize) == 0) == true) {
            return i;
        }
    }
    return -1;
}

// ======== Interal function prototypes ========================

#define                 axe__advance_until(x, cond) for (; (cond) == 0; (x)++)
#define                 axe__log(...)               do { fprintf(stderr, "[axiom_ecs.h:%04d] ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); } while (0)

#define                 axe_id__idx(i)              ((uint32_t)(i))
#define                 axe_id__ver(i)              ((uint32_t)((i) >> 32))
#define                 axe_id__make(ver, idx)      ((((axe_id)(ver)) << 32) | (uint32_t)(idx))

static size_t           axe__npow2                  (size_t x);
static uint64_t         axe__type_hash              (void const *key);
static bool             axe__type_equal             (void const *a, void const *b);
static bool             axe__type_is_subset         (axe_id const *super, axe_id const *sub);

static uint64_t         axe__id_hash                (void const *key);
static bool             axe__id_equal               (void const *a, void const *b);

static axe__archetype *axe__archetype_alloc         (axe_id *type, axe__type_index *ti);
static axe__archetype *axe__archetype_alloc_ins     (axe__archetype *root, axe__archetype *rem, axe__type_index *ti, axe_id *type);
static void             axe__archetype_free         (axe__archetype *archetype);
static size_t           axe__archetype_move         (axe__archetype *from, axe__archetype *to, axe__entity_index *ei, size_t rem_idx);
static void             axe__archetype__ins         (axe__archetype *from, axe__archetype *to);
static void             axe__archetype__connect     (axe__archetype *a, axe__archetype *b);

// =============================================================


bool axe_init(axe_world *world) {
    axe__map_set_funcs(world->ti, axe__type_hash, axe__type_equal);
    axe__map_set_funcs(world->ei, axe__id_hash, axe__id_equal);
    return true;
}

void axe_deinit(axe_world *world) {
    axe__array_free(world->versions);
    axe__array_free(world->free_ids);
    axe__map_free(world->ti);
    axe__map_free(world->ei);
    memset(world, 0, sizeof *world);
}

axe_id axe_create(axe_world world) {
    axe_id index = 0;
    if (axe__array_len(world.free_ids) != 0) {
        index = axe__array_pop(world.free_ids);
    } else {
        index = axe__array_len(world.versions);
        axe__array_push(world.versions, 1);
    }
    return axe_id__make(world.versions[index], index);
}

void axe_destroy(axe_world world, axe_id e) {
    if (axe_id__ver(e) != world.versions[axe_id__idx(e)]) {
        return; // Entity was already destroyed
    }
    axe_id index = axe_id__idx(e);
    world.versions[index]++;
    axe__array_push(world.free_ids, index);
}

void axe__set(axe_world world, axe_id e, axe_id c, void const *data, size_t size) {
    axe__record record = axe__map_get(world.ei, e);
    if (record.archetype == NULL) {
        return; // Unknown entity
    }

    axe_id *type = NULL;
    axe__array_dup(type, record.archetype->type);
    size_t cidx = axe__array_push(type, c);

    // Find the new archetype (create it if it does not exist)
    axe__archetype **archetype = axe__map_getp(world.ti, type);
    if (*archetype == NULL) {
        *archetype = axe__archetype_alloc_ins(world.root, record.archetype, world.ti, type);
        (*archetype)->components[cidx].csize = size;
    } else {
        axe__array_free(type);
    }

    // Move the entity along the component's edge in the graph and update its record
    size_t eidx = axe__archetype_move(record.archetype, *archetype, world.ei, record.idx);
    axe__map_set(world.ei, e, ((axe__record){.archetype = *archetype, .idx = eidx}));

    if (data != NULL) {
        uint8_t *carr = record.archetype->components[cidx].data;
        memcpy(carr[record.idx * size], data, size);
        axe__array__len(carr)++;
    }
}

void axe_rem(axe_world world, axe_id e, axe_id c) {
        axe__record record = axe__map_get(world.ei, e);
        if (record.archetype == NULL) {
            return; // Unknown entity
        }

        axe_id *type = NULL;
        axe__array_dup(type, record.archetype->type);

        #define eq(a, b) ((a) == (b))
        axe__array_remval(type, c, eq);
        #undef eq

        // Find the new archetype
        axe__archetype *archetype = axe__map_get(world.ti, type);
        axe__array_free(type);
        if (archetype == NULL) {
            return; // Unknown type
        }

        // Move the entity along the component's edge in the graph and update its record
        size_t eidx = axe__archetype_move(record.archetype, archetype, world.ei, record.idx);
        axe__map_set(world.ei, e, ((axe__record){.archetype = archetype, .idx = eidx}));
}

axe_view axe__query(axe_world world, axe_id components[]) {
    size_t n = 0;
    axe_id *cursor = components;
    axe__advance_until(n, *cursor++ == 0);

    axe_id *type = NULL;
    memcpy(axe__array_pushn(type, n), components, n * sizeof *type);

    axe__archetype *archetype = axe__map_get(world.ti, type);
    axe__array_free(type);

    return archetype != NULL
        ? (axe_view){.components = archetype->components, .entities = archetype->entities, .count = axe__array_len(archetype->entities)}
        : (axe_view){0}; // Unknown type
}


// ======== Internal function implementation ===================

static size_t axe__npow2(size_t x) {
    x--;
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    x |= sizeof x == 8 ? (x >> 32) : 0;
    return x++;
}

static uint64_t axe__type_hash(void const *key) {
    axe_id const *type = key;
    uint64_t hash = 5381;
    axe__array_for(i, type) {
            hash = ((hash << 5) + hash) ^ type[i];
    }
    return hash;
}

static bool axe__type_equal(void const *a, void const *b) {
    axe_id const *at = a;
    axe_id const *bt = b;
    size_t atn = axe__array_len(at);
    size_t btn = axe__array_len(bt);
    size_t n = atn < btn ? atn : btn;
    for (size_t i = 0; i < n; i++) {
        if (at[i] != bt[i]) {
            return false;
        }
    }
    return true;
}

static bool axe__type_is_subset(axe_id const *sub, axe_id const *super) {
    size_t n = axe__array_len(super);
    size_t m = axe__array_len(sub);

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

static uint64_t axe__id_hash(void const *key) {
    axe_id id = *(axe_id const *)key;
    id = ((id >> 16) ^ id) * 0x45d9f3b;
    id = ((id >> 16) ^ id) * 0x45d9f3b;
    id =  (id >> 16) ^ id;
    return id;
}

static bool axe__id_equal(void const *a, void const *b) {
    return *(axe_id const *)a == *(axe_id const *)b;
}

static axe__archetype *axe__archetype_alloc(axe_id *type, axe__type_index *ti) {
    axe__archetype *archetype = axe__map_get(ti, type);
    if (archetype == NULL) {
        archetype = calloc(1, sizeof *archetype);
        if (archetype != NULL) {
            archetype->type = type;
            axe__map_set(ti, type, archetype);
        }
    }

    return archetype;
}

axe__archetype *axe__archetype_alloc_ins(axe__archetype *root, axe__archetype *rem, axe__type_index *ti, axe_id *type) {
    axe__archetype *ins = axe__archetype_alloc(type, ti);
    axe__archetype__connect(rem, ins);
    axe__archetype__ins(root, ins);
    return ins;
}

static void axe__archetype_free(axe__archetype *archetype) {
    axe__array_for(i, archetype->type) {
            axe__buffer_free(archetype->components[i]);
    }
    axe__array_free(archetype->components);
    axe__array_free(archetype->type);
    axe__array_free(archetype->rem_edges);
    axe__array_free(archetype->ins_edges);
    axe__array_free(archetype->entities);
    free(archetype);
}

static size_t axe__archetype_move(axe__archetype *rem, axe__archetype *ins, axe__entity_index *ei, size_t rem_idx) {
    assert(rem_idx < axe__array_len(rem->entities) && "Row out of bounds");

    axe_id e = rem->entities[rem_idx];
    axe__array_remswap(rem->entities, rem_idx);
    size_t ins_idx = axe__array_push(ins->entities, e);
    axe__map_set(ei, e, ((axe__record){.archetype = ins, .idx = ins_idx}));

    axe__array_for(i, rem->type) {
        assert(rem->type[i] >= ins->type[i] && "Elements in type mismatched");

        int j = 0;
        axe__advance_until(j, rem->type[i] == ins->type[j]);

        size_t      size = rem->components[i].csize;
        uint8_t *rem_com = rem->components[i].data[size * ins_idx];
        uint8_t *ins_com = ins->components[j].data[size * ins_idx];
        memcpy(ins_com, rem_com, size);
    }

    return ins_idx;
}

static void axe__archetype__ins(axe__archetype *from, axe__archetype *to) {
    if (axe__array_len(from->type) < axe__array_len(to->type) - 1) {
        axe__array_for(i, from->ins_edges) {
            axe__archetype__ins(from->ins_edges[i], to);
        }
    } else if (axe__type_is_subset(from->type, to->type) == true) {
        axe__archetype__connect(from, to);
    }
}

static void axe__archetype__connect(axe__archetype *a, axe__archetype *b) {
    axe__array_push(a->ins_edges, b);
    axe__array_push(b->rem_edges, a);
}

#endif // !AXIOM_ECS_C
#endif // AXE_IMPL || AXIOM_IMPL
#endif // !AXIOM_ECS_H

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
