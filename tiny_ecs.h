#ifndef __tiny_ecs_h__
#define __tiny_ecs_h__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t tecs_id;

typedef struct tecs_view {
        void    **components;
        tecs_id  *entities;
        size_t    count;
} tecs_view;

typedef struct tecs__entity_index tecs__entity_index;
typedef struct tecs__type_index tecs__type_index;
typedef struct tecs__archetype tecs__archetype;

typedef struct tecs_world {
        tecs_id *versions;
        tecs_id *free_ids;
        tecs__archetype *root;
        tecs__type_index *ti;
        tecs__entity_index *ei;
} tecs_world;

bool            tecs_init                       (tecs_world *world);
void            tecs_deinit                     (tecs_world *world);
#define         tecs_query(world, ...)          tecs__query(world, (tecs_id []){__VA_ARGS__, 0})
tecs_id         tecs_create                     (tecs_world world);
void            tecs_destroy                    (tecs_world world, tecs_id e);
#define         tecs_set(world, e, c, ...)      tecs_ins(world, e, c, __VA_ARGS__, sizeof __VA_ARGS__)
void            tecs_rem                        (tecs_world world, tecs_id e, tecs_id c);

// ==== Private ================

tecs_view       tecs__query                     (tecs_world world, tecs_id components[]);
void            tecs__set                       (tecs_world world, tecs_id e, tecs_id c, void const *data, size_t size);


/*************************************************************************************************************************************************************
**************************************************************************************************************************************************************
****                                                                                                                                                      ****
****                                                                                                                                                      ****
****                                                                    Implementation                                                                    ****
****                                                                                                                                                      ****
****                                                                                                                                                      ****
**************************************************************************************************************************************************************
*************************************************************************************************************************************************************/


#if defined(TECS_IMPL) || defined(TINY_IMPL)
#ifndef __tiny_ecs_c__
#define __tiny_ecs_c__

#include <stdlib.h> // calloc, realloc, free
#include <string.h> // memset, memcpy, memcmp, memmove
#include <stdio.h>  // fprintf

typedef struct tecs__pool {
        uint8_t *data;
        size_t csize;
} tecs__pool;

typedef struct tecs__record {
        tecs__archetype *archetype;
        size_t idx;
} tecs__record;

struct tecs__entity_index {
        tecs_id key;
        tecs__record value;
};

struct tecs__type_index {
        tecs_id *key;
        tecs__archetype *value;
};

struct tecs__archetype {
        tecs_id *type;
        tecs_id *entities;
        tecs__pool *components;
        tecs__archetype **rem_edges;
        tecs__archetype **ins_edges;
};

// Define the needed tds structures if they have not been already
#ifndef __tiny_ds_h__

#define tds__var(x)                     tds__var_##x##__LINE__##__

/// ## Array
/// ```
/// |        array        |
/// +----------+----------+---------+---------+---------+---------+---------+---------+---------+
/// |    -2    |    -1    |    0    |    1    |    2    |    3    |    4    |    5    |   ...   |
/// +----------+----------+---------+---------+---------+---------+---------+---------+---------+
///   capacity    length  ^--- User pointer
/// ```

#define tds_array_reserve(a, n)         (tds_array__ensure(a, 0, n))
#define tds_array_free(a)               ((a) != NULL ? free(tds_array__head(a)), 0 : 0)
#define tds_array_dup(dst, a)           ((a) != NULL ? memcpy(tds_array_pushn(dst, tds_array_len(a)), (a), tds_array_len(a) * sizeof *(a)), 0 : 0)
#define tds_array_cap(a)                ((a) != NULL ? tds_array__cap(a) : 0)
#define tds_array_len(a)                ((a) != NULL ? tds_array__len(a) : 0)
#define tds_array_insn(a, i, n)         (tds_array__ensure(a, i, n), memmove(tds_array_pushn(a, n), &(a)[(i)], sizeof *(a) * (tds_array_len(a) - (n) - (i))), &(a)[(i)])
#define tds_array_ins(a, i, v)          (*tds_array_insn(a, i, 1) = (v))
#define tds_array_remn(a, i, n)         (tds_array_len(a) >= (n) ? tds_array__len(a) -= (n), memmove(&(a)[(i)], &(a)[(i) + (n)], sizeof *(a) * (tds_array_len(a) - (n) - (i))), 0 : 0)
#define tds_array_rem(a, i)             (tds_array_remn(a, i, 1))
#define tds_array_remswap(a, i)         (tds_array_len(a) > 0 ? (a)[(i)] = tds_array_pop(a), 0 : 0)
#define tds_array_remval(a, v, eqfn)    do { tds_array_for(tds__var(i), a) { if (eqfn(a[tds__var(i)], (v)) == true) { tds_array_rem(a, tds__var(i)); break; }}} while (0)
#define tds_array_pushn(a, n)           (tds_array__ensure(a, 0, n), tds_array__len(a) += (n), &(a)[tds_array_len(a) - (n)])
#define tds_array_push(a, v)            (*tds_array_pushn(a, 1) = (v), tds_array_len(a) - 1)
#define tds_array_pop(a)                ((a)[--tds_array__len(a)])
#define tds_array_clear(a)              (tds_array_len(a) > 0 ? tds_array__len(a) = 0, 0 : 0)

#define tds_array_for(i, a)             for (size_t (i) = 0; (i) < tds_array_len(a); (i)++)

#define tds_array__head(a)              ((size_t *)(a) - 2)
#define tds_array__cap(a)               (tds_array__head(a)[0])
#define tds_array__len(a)               (tds_array__head(a)[1])
#define tds_array__ensure(a, i, n)      (tds_array_len(a) + (n) + (i) >= tds_array_cap(a) ? (a) = tds_array__grow(a, sizeof *(a), tecs__npow2(tds_array_cap(a) * 2 + (n) + (i))), 0 : 0)

static void *tds_array__grow(void *a, size_t asize, size_t n) {
        size_t *ptr = NULL;
        size_t size = n * asize + sizeof(size_t) * 2;
        if (a != NULL) {
                ptr = realloc(tds_array__head(a), size);
                memset(ptr + tds_array_len(a) * asize, 0, size - tds_array_len(a) * asize);
        } else {
                ptr = calloc(1, size);
        }
        if (ptr != NULL) {
                *ptr++ = n;
                *ptr++ = tds_array_len(a);
        }
        return (void *)ptr;
}

/// ## Map
/// ```
/// |        array        |         map         |
/// +----------+----------+----------+----------+---------+---------+---------+---------+---------+
/// |    -4    |    -3    |    -2    |    -1    |    0    |    1    |    2    |    3    |   ...   |
/// +----------+----------+----------+----------+---------+---------+---------+-------------------+
///   capacity    length   hash/equal   default ^--- User pointer
/// ```

typedef struct tds_map__func_storage {
        uint64_t (*hash)(void const *);
        bool     (*equal)(void const *, void const *);
} tds_map__func_storage;

#define tds_map_free(m)                 (tds_array_free(tds_map__head(m)))
#define tds_map_len(m)                  ((m) != NULL ? tds_array_len(tds_map__head(m)) : 0)
#define tds_map_cap(m)                  ((m) != NULL ? tds_array_cap(tds_map__head(m)) : 0)
#define tds_map_load_factor(m)          (tds_map_cap(m) != 0 ? ((float)tds_map_len(m) / (float)tds_map_cap(m)) : 1.0f)
#define tds_map_set_default(m, k, v)    do { tds_map__ensure(m); tds_map__default(m).key = (k); tds_map__default(m).value = (v); } while (0)
#define tds_map_set_funcs(m, h, c)      do { tds_map__ensure(m); tds_map__funcs(m) = (tds_map__func_storage){.hash = (h), .equal = (c)}; } while (0)
#define tds_map_gets(m, k)              ((m)[tds_map__indexof(m, sizeof *(m), &(k), sizeof (k), tds_map__keyoff(m), tds_map_cap(m))])
#define tds_map_get(m, k)               (tds_map_gets(m, k).value)
#define tds_map_getp(m, k)              (&tds_map_get(m, k))
#define tds_map_has(m, k)               (tds_map__indexof(m, sizeof *(m), &(k), sizeof (k), tds_map__keyoff(m), tds_map_cap(m)) != -1)
#define tds_map_set(m, k, v)            do { tds_map__ensure(m); tds_map_ins(m, k, v); } while (0)
#define tds_map_rem(m, k)               (tds_map_gets(m, k) = tds_map__default(m), tds_map__len(m)--)
#define tds_map_clear(m)\
                do {\
                        tds_map_for(tds__var(i), m) {\
                                memcpy(&m[tds__var(i)], &tds_map__default(m), sizeof *(m));\
                        }\
                        tds_array_clear(tds_map__head(m));\
                } while (0)

#define tds_map_for(i, m)               for (size_t (i) = 0; (i) < tds_map_cap(m); (i)++)

#define tds_map__header_size(m)         (sizeof *(m) + sizeof(tds_map__func_storage))
#define tds_map__head(m)                ((char *)(m) - tds_map__header_size(m))
#define tds_map__cap(m)                 (tds_array__cap(tds_map__head(m)))
#define tds_map__len(m)                 (tds_array__len(tds_map__head(m)))
#define tds_map__default(m)             ((m)[-1])
#define tds_map__funcs(m)               (*((tds_map__func_storage *)tds_map__head(m)))
#define tds_map__hash(m, k, n)          (tds_map__funcs(m).hash != NULL ? tds_map__funcs(m).hash(k) : tds_map__fnv1a(k, n))
#define tds_map__equal(m, a, b, n)      (tds_map__funcs(m).equal != NULL ? tds_map__funcs(m).equal(a, b) : memcmp(a, b, n) == 0)
#define tds_map__keyoff(m)              (((char *)&((m)[0].key)) - (char *)(m))

#define tds_map_ins(m, k, v)\
                do {\
                        uint64_t tds__var(hash) = tds_map__hash(m, &(k), sizeof (k));\
                        int tds__var(mask) = tds_map_cap(m) - 1;\
                        int tds__var(i) = tds__var(hash) & tds__var(mask);\
                        for (size_t tds__var(step) = 1, tds__var(c) = 0; tds__var(c) < tds_map_cap(m); tds__var(c)++) {\
                                tds__var(i) = (tds__var(i) + tds__var(step)++) & tds__var(mask);\
                                if (tds_map__equal(m, &(m)[tds__var(i)].key, &(k), sizeof (k)) == 1) {\
                                        break; /* k already exists in m, update it */\
                                } else if (tds_map__equal(m, &(m)[tds__var(i)].key, &tds_map__default(m).key, sizeof (k)) == true) {\
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
                        size_t tds__var(size) = tecs__npow2((tds_map_cap(m) != 0 ? tds_map_cap(m) : 8) * sizeof *(m)) + tds_map__header_size(m);\
                        struct { char key[sizeof (m)[0].key]; char value[sizeof (m)[0].value]; } *tds__var(tmp) = tds_buffer__grow(NULL, tds__var(size));\
                        tds__var(tmp) += tds_map__header_size(m);\
                        if ((m) != NULL) {\
                                memcpy(tds_map__head(tds__var(tmp)), tds_map__head(m), tds_map__header_size(m));\
                                tds_map_clear(tds__var(tmp));\
                        }\
                        tds_map_for(tds__var(i), m) {\
                                tds_map_ins(tds__var(tmp), (m)[tds__var(i)].key, (m)[tds__var(i)].value);\
                        }\
                        memcpy(m, tds__var(tmp), sizeof *(m) * tds_map_cap(m));\
                        tds_map_free(tds__var(tmp));\
                } while (0)

static uint64_t tds_map__fnv1a(void const *key, size_t size) {
        uint64_t hash = 14695981039346656037UL;
        for (uint8_t const *p = key; size; size--, p++) {
                hash ^= (uint64_t)(*p);
                hash *= 1099511628211UL;
        }
        return hash;
}

static int tds_map__indexof(void *m, size_t msize, void *k, size_t ksize, size_t koff, size_t cap) {
        // tds_map__hash and tds_map__equal cannot be used here because m is a void *, which cannot be dereferenced like it would've been in tds_map__head
        tds_map__func_storage funcs = *((tds_map__func_storage *)(msize + sizeof funcs));
        uint64_t hash = funcs.hash != NULL ? funcs.hash(k) : tds_map__fnv1a(k, ksize);
        for (size_t i = hash & (cap - 1), step = 1, c = 0; c < cap; c++, i = (i + step++) & (cap - 1)) {
                void *cur = (char *)m + i * msize;
                void *key = (char *)cur + koff;
                if ((funcs.equal != NULL ? funcs.equal(key, k) : memcmp(key, k, ksize) == 0) == true) {
                        return i;
                }
        }
        return -1;
}

#endif // !__tiny_ds_h__

// ======== Interal function prototypes ========================

#define                 tecs__advance_until(x, cond)    for (; (cond) == 0; (x)++)
#define                 tecs__log(...)                  do { fprintf(stderr, "[tiny_ecs.h:%04d] ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); } while (0)

#define                 tecs_id__idx(i)                 ((uint32_t)(i))
#define                 tecs_id__ver(i)                 ((uint32_t)((i) >> 32))
#define                 tecs_id__make(ver, idx)         ((((tecs_id)(ver)) << 32) | (uint32_t)(idx))

static size_t           tecs__npow2                     (size_t x);
static uint64_t         tecs__type_hash                 (void const *key);
static bool             tecs__type_equal                  (void const *a, void const *b);
static bool             tecs__type_is_subset          (tecs_id const *super, tecs_id const *sub);

static uint64_t         tecs__id_hash                   (void const *key);
static bool             tecs__id_equal                    (void const *a, void const *b);

static tecs__archetype *tecs__archetype_alloc           (tecs_id *type, tecs__type_index *ti);
static tecs__archetype *tecs__archetype_alloc_ins       (tecs__archetype *root, tecs__archetype *rem, tecs__type_index *ti, tecs_id *type);
static void             tecs__archetype_free            (tecs__archetype *archetype);
static size_t           tecs__archetype_move            (tecs__archetype *from, tecs__archetype *to, tecs__entity_index *ei, size_t rem_idx);
static void             tecs__archetype__ins            (tecs__archetype *from, tecs__archetype *to);
static void             tecs__archetype__connect        (tecs__archetype *a, tecs__archetype *b);

// =============================================================


bool tecs_init(tecs_world *world) {
        tds_map_set_funcs(world->ti, tecs__type_hash, tecs__type_equal);
        tds_map_set_funcs(world->ei, tecs__id_hash, tecs__id_equal);
        return true;
}

void tecs_deinit(tecs_world *world) {
        tds_array_free(world->versions);
        tds_array_free(world->free_ids);
        tds_map_free(world->ti);
        tds_map_free(world->ei);
        memset(world, 0, sizeof *world);
}

tecs_id tecs_create(tecs_world world) {
        tecs_id index = 0;
        if (tds_array_len(world.free_ids) != 0) {
                index = tds_array_pop(world.free_ids);
        } else {
                index = tds_array_len(world.versions);
                tds_array_push(world.versions, 1);
        }
        return tecs_id__make(world.versions[index], index);
}

void tecs_destroy(tecs_world world, tecs_id e) {
        if (tecs_id__ver(e) != world.versions[tecs_id__idx(e)]) {
                return; // Entity was already destroyed
        }
        tecs_id index = tecs_id__idx(e);
        world.versions[index]++;
        tds_array_push(world.free_ids, index);
}

void tecs__set(tecs_world world, tecs_id e, tecs_id c, void const *data, size_t size) {
        tecs__record record = tds_map_get(world.ei, e);
        if (record.archetype == NULL) {
                return; // Unknown entity
        }

        tecs_id *type = NULL;
        tds_array_dup(type, record.archetype->type);
        size_t cidx = tds_array_push(type, c);

        // Find the new archetype (create it if it does not exist)
        tecs__archetype **archetype = tds_map_getp(world.ti, type);
        if (*archetype == NULL) {
                *archetype = tecs__archetype_alloc_ins(world.root, record.archetype, world.ti, type);
                (*archetype)->components[cidx].csize = size;
        } else {
                tds_array_free(type);
        }

        // Move the entity along the component's edge in the graph and update its record
        size_t eidx = tecs__archetype_move(record.archetype, *archetype, world.ei, record.idx);
        tds_map_set(world.ei, e, ((tecs__record){.archetype = *archetype, .idx = eidx}));

        if (data != NULL) {
                uint8_t *carr = record.archetype->components[cidx].data;
                memcpy(carr[record.idx * size], data, size);
                tds_array__len(carr)++;
        }
}

void tecs_rem(tecs_world world, tecs_id e, tecs_id c) {
        tecs__record record = tds_map_get(world.ei, e);
        if (record.archetype == NULL) {
                return; // Unknown entity
        }

        tecs_id *type = NULL;
        tds_array_dup(type, record.archetype->type);

        #define eq(a, b) ((a) == (b))
        tds_array_remval(type, c, eq);
        #undef eq

        // Find the new archetype
        tecs__archetype *archetype = tds_map_get(world.ti, type);
        tds_array_free(type);
        if (archetype == NULL) {
                return; // Unknown type
        }

        // Move the entity along the component's edge in the graph and update its record
        size_t eidx = tecs__archetype_move(record.archetype, archetype, world.ei, record.idx);
        tds_map_set(world.ei, e, ((tecs__record){.archetype = archetype, .idx = eidx}));
}

tecs_view tecs__query(tecs_world world, tecs_id components[]) {
        size_t n = 0;
        tecs_id *cursor = components;
        tecs__advance_until(n, *cursor++ == 0);

        tecs_id *type = NULL;
        memcpy(tds_array_pushn(type, n), components, n * sizeof *type);

        tecs__archetype *archetype = tds_map_get(world.ti, type);
        tds_array_free(type);

        return archetype != NULL
                ? (tecs_view){.components = archetype->components, .entities = archetype->entities, .count = tds_array_len(archetype->entities)}
                : (tecs_view){0}; // Unknown type
}


// ======== Internal function implementation ===================

static size_t tecs__npow2(size_t x) {
        x--;
        x |= (x >> 1);
        x |= (x >> 2);
        x |= (x >> 4);
        x |= (x >> 8);
        x |= (x >> 16);
        x |= sizeof x == 8 ? (x >> 32) : 0;
        return x++;
}

static uint64_t tecs__type_hash(void const *key) {
        tecs_id const *type = key;
        uint64_t hash = 5381;
        tds_array_for(i, type) {
                hash = ((hash << 5) + hash) ^ type[i];
        }
        return hash;
}

static bool tecs__type_equal(void const *a, void const *b) {
        tecs_id const *at = a;
        tecs_id const *bt = b;
        size_t atn = tds_array_len(at);
        size_t btn = tds_array_len(bt);
        size_t n = atn < btn ? atn : btn;
        for (size_t i = 0; i < n; i++) {
                if (at[i] != bt[i]) {
                        return false;
                }
        }
        return true;
}

static bool tecs__type_is_subset(tecs_id const *sub, tecs_id const *super) {
        size_t n = tds_array_len(super);
        size_t m = tds_array_len(sub);

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

static uint64_t tecs__id_hash(void const *key) {
        tecs_id id = *(tecs_id const *)key;
        id = ((id >> 16) ^ id) * 0x45d9f3b;
        id = ((id >> 16) ^ id) * 0x45d9f3b;
        id =  (id >> 16) ^ id;
        return id;
}

static bool tecs__id_equal(void const *a, void const *b) {
        return *(tecs_id const *)a == *(tecs_id const *)b;
}

static tecs__archetype *tecs__archetype_alloc(tecs_id *type, tecs__type_index *ti) {
        tecs__archetype *archetype = tds_map_get(ti, type);
        if (archetype == NULL) {
                archetype = calloc(1, sizeof *archetype);
                if (archetype != NULL) {
                        archetype->type = type;
                        tds_map_set(ti, type, archetype);
                }
        }

        return archetype;
}

tecs__archetype *tecs__archetype_alloc_ins(tecs__archetype *root, tecs__archetype *rem, tecs__type_index *ti, tecs_id *type) {
        tecs__archetype *ins = tecs__archetype_alloc(type, ti);
        tecs__archetype__connect(rem, ins);
        tecs__archetype__ins(root, ins);
        return ins;
}

static void tecs__archetype_free(tecs__archetype *archetype) {
        tds_array_for(i, archetype->type) {
                tds_buffer_free(archetype->components[i]);
        }
        tds_array_free(archetype->components);
        tds_array_free(archetype->type);
        tds_array_free(archetype->rem_edges);
        tds_array_free(archetype->ins_edges);
        tds_array_free(archetype->entities);
        free(archetype);
}

static size_t tecs__archetype_move(tecs__archetype *rem, tecs__archetype *ins, tecs__entity_index *ei, size_t rem_idx) {
        assert(rem_idx < tds_array_len(rem->entities) && "Row out of bounds");

        tecs_id e = rem->entities[rem_idx];
        tds_array_remswap(rem->entities, rem_idx);
        size_t ins_idx = tds_array_push(ins->entities, e);
        tds_map_set(ei, e, ((tecs__record){.archetype = ins, .idx = ins_idx}));

        tds_array_for(i, rem->type) {
                assert(rem->type[i] >= ins->type[i] && "Elements in type mismatched");

                int j = 0;
                tecs__advance_until(j, rem->type[i] == ins->type[j]);

                size_t      size = rem->components[i].csize;
                uint8_t *rem_com = rem->components[i].data[size * ins_idx];
                uint8_t *ins_com = ins->components[j].data[size * ins_idx];
                memcpy(ins_com, rem_com, size);
        }

        return ins_idx;
}

static void tecs__archetype__ins(tecs__archetype *from, tecs__archetype *to) {
        if (tds_array_len(from->type) < tds_array_len(to->type) - 1) {
                tds_array_for(i, from->ins_edges) {
                        tecs__archetype__ins(from->ins_edges[i], to);
                }
        } else if (tecs__type_is_subset(from->type, to->type) == true) {
                tecs__archetype__connect(from, to);
        }
}

static void tecs__archetype__connect(tecs__archetype *a, tecs__archetype *b) {
        tds_array_push(a->ins_edges, b);
        tds_array_push(b->rem_edges, a);
}


#endif // !__tiny_ecs_c__
#endif // TECS_IMPL || TINY_IMPL
#endif // !__tiny_ecs_h__

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
