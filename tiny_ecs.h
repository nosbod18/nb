#ifndef __tiny_ecs_h__
#define __tiny_ecs_h__

#include <stdint.h>
#include <stddef.h>


typedef uint64_t tecs_id;

typedef struct tecs_view {
        void   **components;
        tecs_id *entities;
        int      count;
} tecs_view;

typedef struct tecs_world tecs_world;


tecs_world     *tecs_alloc                      (void);
void            tecs_free                       (tecs_world *world);
#define         tecs_query(world, ...)          tecs__query(world, (tecs_id []){__VA_ARGS__, 0})
tecs_id         tecs_create                     (tecs_world *world);
void            tecs_destroy                    (tecs_world *world, tecs_id e);
#define         tecs_set(world, e, c, ...)      tecs__ins(world, e, c, __VA_ARGS__, sizeof __VA_ARGS__)
void            tecs_rem                        (tecs_world *world, tecs_id e, tecs_id c);

// ======== Private ============================================

tecs_view       tecs__query                     (tecs_world *world, tecs_id components[]);
void            tecs__set                       (tecs_world *world, tecs_id e, tecs_id c, void const *data, size_t size);


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

#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct tecs__archetype tecs__archetype;

typedef struct tecs__edge {
        tecs__archetype *archetype;
        tecs_id component;
} tecs__edge;

typedef struct tecs__pool {
        uint8_t *data;
        size_t itemsize;
} tecs__pool;

struct tecs__archetype {
        tecs_id *type;
        tecs_id *entities;
        tecs__pool *components;
        tecs__edge *rem;
        tecs__edge *ins;
};

typedef struct tecs__record {
        tecs__archetype *archetype;
        size_t row;
} tecs__record;

typedef struct tecs__entity_index {
        tecs_id key;
        tecs__record value;
} tecs__entity_index;

typedef struct tecs__type_index {
        tecs_id *key;
        tecs__archetype *value;
} tecs__type_index;

struct tecs_world {
        tecs_id *versions;
        tecs_id *free_ids;
        tecs__archetype *root;
        tecs__type_index *ti;
        tecs__entity_index *ei;
};


#define tecs_id__idx(e)                 ((uint32_t)(e))
#define tecs_id__ver(e)                 ((uint32_t)((e) >> 32))
#define tecs_id__make(ver, idx)         ((((tecs_id)(ver)) << 32) | (uint32_t)(idx))

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

#define tds_array_reserve(a, n)         (tds_buffer_reserve(a, (n) * sizeof *(a)))
#define tds_array_free(a)               ((a) ? free(tds_array__head(a)), 0 : 0)
#define tds_array_dup(dst, a)           ((a) ? memcpy(tds_array_pushn(dst, tds_array_len(a)), (a), tds_array_len(a) * sizeof *(a)), 0 : 0)
#define tds_array_cap(a)                ((a) ? tds_array__cap(a) : 0)
#define tds_array_len(a)                ((a) ? tds_array__len(a) : 0)
#define tds_array_insn(a, i, n)         (tds_array__ensure(a, i, n), memmove(tds_array_pushn(a, n), &(a)[(i)], sizeof *(a) * (tds_array_len(a) - (n) - (i))), &(a)[(i)])
#define tds_array_ins(a, i, v)          (*tds_array_insn(a, i, 1) = (v))
#define tds_array_remn(a, i, n)         (tds_array_len(a) >= (n) ? tds_array__len(a) -= (n) * sizeof *(a), memmove(&(a)[(i)], &(a)[(i) + (n)], sizeof *(a) * (tds_array_len(a) - (n) - (i))), 0 : 0)
#define tds_array_rem(a, i)             (tds_array_remn(a, i, 1))
#define tds_array_remswap(a, i)         (tds_array_len(a) ? (a)[(i)] = tds_array_pop(a), 0 : 0)
#define tds_array_remval(a, v, cmp)     do { for (size_t tds__var(i) = 0; tds__var(i) < tds_array_len(a); tds__var(i)++) { if (cmp(a[tds__var(i)], (v)) == 0) { tds_array_rem(a, tds__var(i)); break; }}} while (0)
#define tds_array_pushn(a, n)           (tds_array__ensure(a, 0, n), tds_array__len(a) += (n), &(a)[tds_array_len(a) - (n)])
#define tds_array_push(a, v)            (*tds_array_pushn(a, 1) = (v), tds_array_len(a) - 1)
#define tds_array_pop(a)                ((a)[--tds_array__len(a)])
#define tds_array_clear(a)              (tds_array_len(a) ? tds_array__len(a) = 0, 0 : 0)

#define tds_array__head(a)              ((size_t *)(a) - 2)
#define tds_array__cap(a)               (tds_array__head(a)[0])
#define tds_array__len(a)               (tds_array__head(a)[1])
#define tds_array__ensure(a, i, n)      (tds_array_len(a) + (n) + (i) >= tds_array_cap(a) ? (a) = tds_array__grow(a, sizeof *(a), tecs__npow2(tds_array_cap(a) * 2 + (n) + (i))), 0 : 0)

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
                        int tds__var(mask) = tds_map_cap(m) - 1;\
                        int tds__var(i) = tds__var(hash) & tds__var(mask);\
                        for (size_t tds__var(step) = 1, tds__var(c) = 0; tds__var(c) < tds_map_cap(m); tds__var(c)++) {\
                                tds__var(i) = (tds__var(i) + tds__var(step)++) & tds__var(mask);\
                                if (tds_map__cmp(m, &(m)[tds__var(i)].key, &(k), sizeof (k)) == 1) {\
                                        break; /* k already exists in m, update it */\
                                } else if (tds_map__cmp(m, &(m)[tds__var(i)].key, &tds_map__default(m).key, sizeof (k)) == 1) {\
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

#endif // !__tiny_ds_h__

// ======== Interal function prototypes ========================

#define                 tecs__advance_until(x, cond)    for (; (cond) == 0; (x)++)

static size_t           tecs__npow2                     (size_t x);
static uint64_t         tecs__type_hash                 (void const *key);
static int              tecs__type_cmp                  (void const *a, void const *b);
static int              tecs__type_superset             (tecs_id const *super, tecs_id const *sub);

static uint64_t         tecs__id_hash                   (void const *key);
static int              tecs__id_cmp                    (void const *a, void const *b);

static tecs__archetype *tecs__archetype_alloc           (tecs_id *type, tecs__type_index *ti);
static tecs__archetype *tecs__archetype_alloc_ins       (tecs__archetype *root, tecs__archetype *rem, tecs_id *type, tecs_id c, tecs__type_index *ti);
static void             tecs__archetype_free            (tecs__archetype *archetype);
static size_t           tecs__archetype_push            (tecs__archetype *archetype, tecs__entity_index *ei, tecs_id e);
static size_t           tecs__archetype_move            (tecs__archetype *rem, tecs__archetype *ins, tecs__entity_index *ei, size_t rem_row);
static void             tecs__archetype__connect        (tecs__archetype *rem, tecs__archetype *ins, tecs_id c);
static void             tecs__archetype__ins            (tecs__archetype *rem, tecs__archetype *ins);

// =============================================================


tecs_world *tecs_alloc(void) {
        tecs_world *world = calloc(1, sizeof *world);
        tds_map_set_funcs(world->ti, tecs__type_hash, tecs__type_cmp);
        tds_map_set_funcs(world->ei, tecs__id_hash, tecs__id_cmp);
        return world;
}

void tecs_deinit(tecs_world *world) {
        tds_array_free(world->versions);
        tds_array_free(world->free_ids);
        tds_map_free(world->ti);
        tds_map_free(world->ei);
        free(world);
        memset(world, 0, sizeof *world);
}

tecs_id tecs_create(tecs_world *world) {
        tecs_id index = 0;
        if (tds_array_len(world->free_ids) != 0) {
                index = tds_array_pop(world->free_ids);
        } else {
                index = tds_array_len(world->versions);
                tds_array_push(world->versions, 1);
        }
        return tecs_id__make(world->versions[index], index);
}

void tecs_destroy(tecs_world *world, tecs_id e) {
        if (tecs_id__ver(e) != world->versions[tecs_id__idx(e)])
                return; // Entity was already destroyed
        tecs_id index = tecs_id__idx(e);
        world->versions[index]++;
        tds_array_push(world->free_ids, index);
}

void tecs__set(tecs_world *world, tecs_id e, tecs_id c, void const *data, size_t size) {
        tecs__record record = tds_map_get(world->ei, e);
        assert(record.archetype && record.row && "Unknown entity");

        tecs_id *type = NULL;
        tds_array_dup(type, record.archetype->type);
        size_t cidx = tds_array_push(type, c);

        // Find the new archetype (create it if it does not exist)
        tecs__archetype **archetype = tds_map_getp(world->ti, type);
        if (*archetype == NULL) {
                *archetype = tecs__archetype_alloc_ins(world->root, record.archetype, type, c, world->ti);
                (*archetype)->components[cidx].itemsize = size;
        } else {
                tds_array_free(type);
        }

        // Move the entity along the component's edge in the graph and update its record
        size_t new_row = tecs__archetype_move(record.archetype, *archetype, world->ei, record.row);
        tds_map_set(world->ei, e, ((tecs__record){.archetype = *archetype, .row = new_row}));

        if (data != NULL) {
                // Do I really want to insert here? Or should it just be a memcpy
                uint8_t *slot = tds_array_insn(record.archetype->components[cidx].data, record.row * size, size);
                memcpy(slot, data, size);
        }
}

void tecs_rem(tecs_world *world, tecs_id e, tecs_id c) {
        tecs__record record = tds_map_get(world->ei, e);
        assert(record.archetype && record.row && "Unknown entity");

        tecs_id *type = NULL;
        tds_array_dup(type, record.archetype->type);

        #define cmp(a, b) ((a) - (b))
        tds_array_remval(type, c, cmp);
        #undef cmp

        // Find the new archetype
        tecs__archetype *archetype = tds_map_get(world->ti, type);
        assert(archetype != NULL && "Unknown type");
        tds_array_free(type);

        // Move the entity along the component's edge in the graph and update its record
        size_t new_row = tecs__archetype_move(record.archetype, archetype, world->ei, record.row);
        tds_map_set(world->ei, e, ((tecs__record){.archetype = archetype, .row = new_row}));
}

tecs_view tecs__query(tecs_world *world, tecs_id components[]) {
        size_t n = 0;
        tecs_id *cursor = components;
        tecs__advance_until(n, *cursor++ == 0);

        tecs_id *type = NULL;
        memcpy(tds_array_pushn(type, n), components, n * sizeof *type);

        tecs__archetype *archetype = tds_map_get(world->ti, type);
        assert(archetype != NULL && "The requested type does not exist");
        tds_array_free(type);

        return (tecs_view){
                .components = archetype->components,
                .entities = archetype->entities,
                .count = tds_array_len(archetype->entities)
        };
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
        for (size_t i = 0; i < tds_array_len(type); i++) {
                hash = ((hash << 5) + hash) ^ type[i];
        }
        return hash;
}

static int tecs__type_cmp(void const *a, void const *b) {
        tecs_id const *at = a;
        tecs_id const *bt = b;
        size_t atn = tds_array_len(at);
        size_t btn = tds_array_len(bt);
        size_t n = atn < btn ? atn : btn;
        for (size_t i = 0; i < n; i++) {
                int x = at[i] - bt[i];
                if (x) {
                        return x;
                }
        }
        return 0;
}

static int tecs__type_superset(tecs_id const *super, tecs_id const *sub) {
        if (tds_array_len(super) < tds_array_len(sub)) {
                return 1;
        }

        size_t left = 0;
        size_t right = 0;
        while (left < tds_array_len(super) && right < tds_array_len(sub)) {
                if (super[left] < sub[right]) {
                        left++;
                } else if (super[left] == sub[right]) {
                        left++;
                        right++;
                } else {
                        return 1;
                }
        }

        return right != tds_array_len(sub);
}

static uint64_t tecs__id_hash(void const *key) {
        tecs_id id = *(tecs_id const *)key;
        id = ((id >> 16) ^ id) * 0x45d9f3b;
        id = ((id >> 16) ^ id) * 0x45d9f3b;
        id =  (id >> 16) ^ id;
        return id;
}

static int tecs__id_equal(void const *a, void const *b) {
        return *(tecs_id const *)a == *(tecs_id const *)b;
}

static tecs__archetype *tecs__archetype_alloc(tecs_id *type, tecs__type_index *ti) {
        tecs__archetype *archetype = tds_map_get(ti, type);
        if (archetype != NULL) {
                return archetype;
        }

        archetype = calloc(1, sizeof *archetype);
        if (archetype == NULL) {
                return NULL;
        }

        archetype->type = type;
        tds_map_set(ti, type, archetype);
        return archetype;
}

tecs__archetype *tecs__archetype_alloc_ins(tecs__archetype *root, tecs__archetype *rem, tecs_id *type, tecs_id c, tecs__type_index *ti) {
        tecs__archetype *ins = tecs__archetype_alloc(type, ti);
        tecs__archetype__ins(root, ins);
        return ins;
}

static void tecs__archetype_free(tecs__archetype *archetype) {
        for (size_t i = 0; i < tds_array_len(archetype->type); i++) {
                tds_buffer_free(archetype->components[i]);
        }
        tds_array_free(archetype->components);
        tds_array_free(archetype->type);
        tds_array_free(archetype->rem);
        tds_array_free(archetype->ins);
        tds_array_free(archetype->entities);
        free(archetype);
}

static size_t tecs__archetype_push(tecs__archetype *archetype, tecs__entity_index *ei, tecs_id e) {
        size_t row = tds_array_push(archetype->entities, e);
        tds_map_set(ei, e, ((tecs__record){.archetype = archetype, .row = row}));
        return row;
}

static size_t tecs__archetype_move(tecs__archetype *rem, tecs__archetype *ins, tecs__entity_index *ei, size_t rem_row) {
        assert(rem_row < tds_array_len(rem->entities) && "Row out of bounds");

        tecs_id removed = rem->entities[rem_row]; // Get the id that will be moved
        tds_array_remswap(rem->entities, rem_row); // Delete the id from the old archetype
        size_t ins_row = tecs__archetype_push(ins, ei, removed); // Insert the id into the new archetype

        for (size_t i = 0; i < tds_array_len(rem->type); i++) {
                assert(rem->type[i] >= ins->type[i] && "Elements in type mismatched");

                int j = 0;
                tecs__advance_until(j, rem->type[i] == ins->type[j]); // Find the component's index

                size_t      size = rem->components[i].itemsize; // Component type size
                uint8_t *rem_com = rem->components[i].data[size * ins_row]; // Component to move
                uint8_t *ins_com = ins->components[j].data[size * ins_row]; // Slot to move component into
                memcpy(ins_com, rem_com, size);
        }

        return ins_row;
}

static void tecs__archetype__connect(tecs__archetype *rem, tecs__archetype *ins, tecs_id c) {
        tds_array_push(rem->ins, ((tecs__edge){.archetype = ins, .component = c}));
        tds_array_push(ins->rem, ((tecs__edge){.archetype = rem, .component = c}));
}

static void tecs__archetype__ins(tecs__archetype *rem, tecs__archetype *ins) {
        if (tds_array_len(rem->type) > tds_array_len(ins->type) - 1) {
                return;
        }

        if (tds_array_len(rem->type) < tds_array_len(ins->type) - 1) {
                for (size_t i = 0; i < tds_array_len(rem->ins); i++) {
                        tecs__archetype__ins(rem->ins[i].archetype, ins);
                }
                return;
        }

        if (tecs__type_superset(rem, ins) != 0) {
                return;
        }

        size_t i = 0;
        tecs__advance_until(i, i == tds_array_len(ins->type) || rem->type[i] != ins->type[i]);
        tecs__archetype__connect(rem, ins, rem->type[i]);
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