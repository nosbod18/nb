#ifndef __tiny_ecs_h__
#define __tiny_ecs_h__

#include <stdint.h> // uint64_t
#include <stdbool.h>

#ifndef TECSAPI
        #ifdef TECS_IMPL_STATIC
                #define TECSAPI static
        #else
                #define TECSAPI extern
        #endif
#endif


typedef uint64_t tecs_entity;

typedef struct tecs_view {
        void **components;
        tecs_entity *entities;
        int count;
} tecs_view;

typedef void (*tecs_system)(tecs_view view, double dt);

typedef struct tecs_world tecs_world;


TECSAPI tecs_world     *tecs_world_create                       (void);
TECSAPI void            tecs_world_delete                       (tecs_world *world);
TECSAPI void            tecs_world_tick                         (tecs_world const *world, double dt);

#define                 tecs_view_get(view, T, index)           ((void *)(((char **)((view).components))[sizeof(T) * (index)]))

TECSAPI tecs_entity     tecs_entity_create                      (tecs_world *world);
TECSAPI void            tecs_entity_delete                      (tecs_world *world, tecs_entity entity);
#define                 tecs_entity_attach(world, e, T, ...)    tecs_entity__attach(world, e, #T, &(T)__VA_ARGS__)
#define                 tecs_entity_detach(world, e, T)         tecs_entity__detach(world, e, #T)

#define                 tecs_component_register(world, T)       tecs_component__register(world, #T, sizeof(T))
#define                 tecs_system_register(world, func, ...)  tecs_system__register(world, func, #__VA_ARGS__)


// ======== Private ============================================

TECSAPI bool            tecs_entity__attach                     (tecs_world *world, tecs_entity entity, char const *component, void *data);
TECSAPI bool            tecs_entity__detach                     (tecs_world *world, tecs_entity entity, char const *component);
TECSAPI void            tecs_component__register                (tecs_world *world, char const *component, int size);
TECSAPI void            tecs_system__register                   (tecs_world *world, tecs_system func, char const *mask);


/*************************************************************************************************************************************************************
**************************************************************************************************************************************************************
****                                                                                                                                                      ****
****                                                                                                                                                      ****
****                                                                    Implementation                                                                    ****
****                                                                                                                                                      ****
****                                                                                                                                                      ****
**************************************************************************************************************************************************************
*************************************************************************************************************************************************************/


#if defined(TECS_IMPL) || defined(TECS_IMPL_STATIC) || defined(TINY_IMPL) || defined(TINY_IMPL_STATIC)
#ifndef __tiny_ecs_c__
#define __tiny_ecs_c__

#include <string.h> // memmove, memset
#include <stdlib.h> // calloc, free


typedef struct tecs__archetype tecs__archetype;

typedef struct tecs__pool {
        void *data;
        int elemsize;
} tecs__pool;

typedef struct tecs__edge {
        tecs__archetype *archetype;
        tecs_entity component;
} tecs__edge;

struct tecs__archetype {
        tecs__pool  *components;
        tecs_entity *entities;
        tecs_entity *type;
        tecs__edge  *ledges;
        tecs__edge  *redges;
};

typedef struct tecs__record {
        tecs__archetype *archetype;
        int row;
} tecs__record;

typedef struct tecs__system {
        tecs__archetype *archetype;
        tecs_system func;
} tecs__system;

typedef struct tecs__entity_index {
        tecs_entity key;
        tecs__record value;
} tecs__entity_index;

typedef struct tecs__system_index {
        char const *key;
        tecs__system value;
} tecs__system_index;

typedef struct tecs__type_index {
        tecs_entity *key;
        tecs__archetype value;
} tecs__type_index;

struct tecs__world {
        tecs__entity_index *entity_index;
        tecs__system_index *system_index;
        tecs__type_index *type_index;
        tecs__archetype *root;
        tecs_entity next_entity;
};


#define tecs__var(x)                    _##x##__LINE__

// TODO: Trim these down to only the necessary ones

#define tecs__array(T)                    T *

#define tecs__array_reserve(a, n)         (tecs__array__ensure(a, n))
#define tecs__array_free(a)               ((a) = tecs__array__realloc(a, 0, 0))
#define tecs__array_free_with(a, func)    (for (int tecs__var(i) = 0; tecs__var(i) < tecs__array_len(a); tecs__var(i)++) { func((a)[tecs__var(i)]); }, tecs__array_free(a))
#define tecs__array_dup(dest, a)          (sizeof *(dest) == sizeof *(a) ? (tecs__array_reserve(dest, tecs__arra_len(a)), memcpy(dest, a, tecs__array_len(a) * sizeof *dest)), 0 : 0)
#define tecs__array_cap(a)                ((a) ? tecs__array__cap(a) : 0)
#define tecs__array_len(a)                ((a) ? tecs__array__len(a) : 0)

#define tecs__array_pushn(a, n)           (tecs__array__ensure(a, n), (n) ? (tecs__array__len(a) += (n), &(a)[tecs__array_len(a) - (n)]) : (a))
#define tecs__array_insn(a, i, n)         (tecs__array_pushn(a, n), memmove(&(a)[(i) + (n)], &a[(i)], sizeof *(a) * (tecs__array_len(a) - (n) - (i))), &(a)[(i)])
#define tecs__array_push(a, v)            (*tecs__array_pushn(a, n) = (v))
#define tecs__array_ins(a, i, v)          (*tecs__array_insn(a, i, 1) = (v))

#define tecs__array_deln(a, i, n)         (tecs__array_len(a) ? (tecs__array__len(a) -= n, memmove(&(a)[(i)], &a[(i) + (n)], sizeof *(a) * (tecs__array__len(a) - (i))), 0) : 0)
#define tecs__array_del(a, i)             (tecs__array_deln(a, i, 1))
#define tecs__array_delswap(a, i)         (tecs__array_len(a) ? ((a)[(i)] = (a)[--tecs__array__len(a)], 0) : 0)
#define tecs__array_pop(a)                (*tecs__array_popn(a, 1))
#define tecs__array_popn(a, n)            (tecs__array_deln(a, tecs__array_len(a) - (n), n), &(a)[tecs__array_len(a) - 1])
#define tecs__array_clear(a)              ((a) ? (tecs__array__len(a) = 0, 0) : 0)

#define tecs__array_foreach(x, a, ...)\
        do {\
                for (T tecs__var(i) = 0; tecs__var(i) < tecs__array_len(a); tecs__var(i)++) {\
                        x = a[tecs__var(i)];\
                        __VA_ARGS__\
                }\
        } while (0)

#define tecs__array__cap(a)               (((int *)(a))[-2])
#define tecs__array__len(a)               (((int *)(a))[-1])
#define tecs__array__ensure(a, n)         (!(a) || tecs__array__len(a) + (n) >= tecs__array__cap(a) ? ((a) = tecs__array__realloc(a, sizeof *a, tecs__array_cap(a) * 2 + (n)), 0) : 0)

TECSAPI void *tecs__array__realloc         (void *a, int asize, int n);


#define tecs__map(K, V)                 struct { K key; V val; }
#define tecs__map_reserve(m, n)         (tecs__array_reserve(tecs__map__head(m), (n) + 2))
#define tecs__map_free(m)               (tecs__array_free(tecs__map__head(m)))
#define tecs__map_len(m)                ((m) ? tecs__map__len(m) : 0)
#define tecs__map_cap(m)                ((m) ? tecs__map__cap(m) : 0)
#define tecs__load_factor(m)            (tecs__map_cap(m) ? ((float)tecs__map_len(m) / (float)tecs__map_cap(m)) : 1.0f)
#define tecs__map_set_default(m, k, v)  (tecs__map__ensure(m), tecs__map__default(m).key = k, tecs__map__default(m).value = v)

#define tecs__map_clear(m)\
        do {\
                for (int tecs__var(i) = 0; tecs__var(i) < tecs__map_cap(m), tecs__var(i)++) {\
                        m[tecs__var(i)] = tecs__map__default(m);\
                }\
                tecs__map__len(m) = 0;
        } while (0)

#define tecs__map_ins(m, k, v)          (tecs__map__ensure(m), tecs__map__ins(m, k, v))
#define tecs__map_del(m, k)             (tecs__map_get(m, k) = tecs__map__default(m))
#define tecs__map_get(m, k)             (tecs__map__temp(m).key = k, tecs__map__get(m, sizeof *m, &tecs__map__temp(m).key, sizeof k), tecs__map__temp(m).value)

#define tecs__map__ensure(m)\
        do {\
                if (tecs__load_factor(m) >= 0.7f) {\
                        void *tecs__var(m_new) = NULL;\
                        tecs__map_reserve(m, tecs__map_cap(m) ? tecs__map_cap(m) * 2 : 2);\
                        tecs__map_set_default(tecs__var(m_new), tecs__map__default(m).key, tecs__map__default(m).value);\
                        tecs__map_clear(tecs__var(m_new));\
                        for (int tecs__var(i) = 0; tecs__var(i) < tecs__map_cap(m); tecs__var(i)++)\
                                tecs__map__ins(tecs__var(m_new), m[tecs__var(i)].key, m[tecs__var(i)].value);\
                        tecs__map_free(m);\
                        (m) = tecs__var(m_new);\
                }\
        } while (0)

#define tecs__map__ins(m, k, v)\
        do {\
                tecs__map__temp(m).key = k;\
                int tecs__var(i) = tecs__map__get(m, sizeof *m, &tecs__map__temp(m).key, sizeof k);\
                if (memcmp(&tecs__map__default(m), tecs__map__temp(m), sizeof *m)) {\
                        /* k was not found in m, insert it */\
                        (m)[tecs__var(i)].key   = k;\
                        (m)[tecs__var(i)].value = v;\
                        tecs__array__len(tecs__map__head(m))++;\
                } else {\
                        /* k was found in m, update its value */\
                        (m)[tecs__var(i)].value = v;\
                }\
        } while (0)

#define tecs__map__cap(m)               (((int *)((m) - 2))[-2])
#define tecs__map__len(m)               (((int *)((m) - 2))[-1])
#define tecs__map__default(m)           ((m)[-2])
#define tecs__map__temp(m)              ((m)[-1])

TECSAPI uint64_t tecs__map__hash        (void const *key, int n);
TECSAPI int tecs__map__get              (void *m, int msize, void *k, int ksize);


#define tecs__pool_get(pool, index) ((void *)((char *)(pool).data + ((index) * (pool).elemsize)))


tecs__archetype *tecs__archetype_create(tecs_entity *type, tecs__type_index *type_index) {
        tecs__archetype *archetype = calloc(1, sizeof *archetype);
        archetype->type = type;
        tecs__map_ins(type_index, type, archetype);
        return archetype;
}

void tecs__archetype_delete(tecs__archetype *archetype) {
        tecs__array_free_with(archetype->components, free);
        tecs__array_free(archetype->entities);
        tecs__array_free(archetype->edges);
        tecs__array_free(archetype->type);
        free(archetype);
}

int tecs__archetype_push(tecs__archetype *archetype, tecs__entity_index *entity_index, tecs_entity e) {
        tecs__map_ins(entity_index, e, (tecs__record){archetype, tecs__array_len(archetype->entities));
        tecs__array_push(archetype->entities, e);
        return tecs__array_len(archetype->entities) - 1;
}

int tecs__archetype_move_right(tecs__archetype *left, tecs__archetype *right, tecs__entity_index *entity_index, int row_left) {
        assert(left_row < tecs__array_len(left->entities));

        tecs_entity removed = left->entities[row_left];
        int row_right = tecs__archetype_ins(right, entity_index, removed);

        for (int i = 0; i < tecs__array_len(left->type); i++) {
                assert(left->type[i] >= right->type[i] && "Elements in type mismatched");

                int j = 0;
                while (left->type[i] != right->type[j]) {
                        j++;
                }

                void *ins_comp = tecs__pool_get(right->components[j], row_right);
                void *del_comp = tecs__pool_get(left->components[i], row_left);
                void *swp_comp = tecs__pool_get(left->components[i], tecs__array_len(left->entities) - 1);

                memcpy(ins_comp, del_comp, left->components[i].size)
                memcpy(del_comp, swp_comp, left->components[i].size)
        }

        return row_right;
}

static inline void tecs__archetype__connect(tecs__archetype *left, tecs__archetype *right, tecs_component component) {
        tecs__array_push(left->redges, (tecs__edge){.archetype = right, .component = component});
        tecs__array_push(right->ledges, (tecs__edge){.archetype = left, .component = component});
}

static void tecs__archetype__ins(tecs__archetype *node, tecs__archetype *ins_node) {
        if (tecs__array_len(node->type) > tecs__array_len(ins_node->type) - 1) {
                return;
        }

        if (tecs__array_len(node->type) < tecs__array_len(ins_node->type) - 1) {
                for (int i = 0; i < tecs__array_len(node->redges); i++) {
                        tecs__archetype__ins(node->redges[i].archetype, ins_node);
                }
                return;
        }

        if (tecs__array_len(node->type) < tecs__array_len(ins_node->type)) {
                return;
        }

        int left = 0;
        int right = 0;
        while (left < tecs__array_len(node->type) && right < tecs__array_len(ins_node->type)) {
                if (node->type[left] > ins_node->type[right]) {
                        return;
                } else if (node->type[left] < ins_node->type[right]) {
                        left++;
                } else {
                        left++;
                        right++;
                }
        }

        if (right != tecs__array_len(ins_node->type)) {
                return;
        }

        int i = 0;
        for (; i < tecs__array_len(ins_node->type) && node->type[i] == ins_node->type[i]; i++) {
        }

        tecs__archetype__connect(new_node, node, node->type[i]);
}

tecs__archetype *tecs__archetype_ins(tecs__archetype *root, tecs__archetype *left, tecs_entity *type, tecs__type_index *type_index, tecs_entity component) {
        tecs__archetype *vertex = tecs__archetype_create(type, type_index);
        tecs__archetype__connect(left, vertex, component);
        tecs__archetype__ins(root, vertex);
        return vertex;
}

static tecs__archetype *tecs__archetype__travins(tecs__archetype *vertex, tecs_entity *type, int n, tecs_entity acc[], int top, tecs__archetype *root, tecs__type_index *type_index) {
        if (!n) {
                assert(memcmp(vertex->type, type, sizeof *type * tecs__array_len(type)));
                return vertex;
        }

        for (int i = 0; i < tecs__array_len(vertex->redges); i++) {
                if (tecs__array_indexof(type, vertex->redges[i].component) != -1) {
                        acc[top] = edge.component;
                        return tecs__archetyep__travins(vertex->redges[i].archetype, type, n - 1, acc, top + 1, root, type_index);
                }
        }

        tecs_entity *new_type = NULL;
        memcpy(tecs__array_pushn(new_type, top), acc, sizeof *acc * top);

        tecs_entity new_component = 0;
        for (int i = 0; i < tecs__array_len(type); i++) {
                if (type[i] != new_type[i]) {
                        new_component = type[i];
                        tecs__array_push(new_type, new_component);
                        acc[top] = new_component;
                        break;
                }
        }

        assert(new_component);

        tecs__archetype *new_vertex = tecs__archetype_ins(root, vertex, new_type, type_index, new_component);
        return tecs__archetype__travins(new_vertex, type, n - 1, acc, top + 1, root, type_index);
}

tecs__archetype *tecs__archetype_travins(tecs__archetype *root, tecs_entity const *type, tecs__type_index *type_index) {
        tecs_entity *acc = alloca(sizeof *acc * tecs__array_len(type));
        return tecs__archetype__travins(root, type, len, acc, 0, root, type_index);
}


tecs_world *tecs_world_create(void) {
        tecs_world *world = calloc(1, sizeof *world);
        tecs_entity *root_type = NULL;
        world->root = tecs__archetype_create(root_type, world->type_index);
        world->next_entity = 1;
        return world;
}

void tecs_world_delete(tecs_world *world) {
        tecs__map_free(world->entity_index);
        tecs__map_free_with(world->system_index, free);
        tecs__map_free_with(world->type_index, free);
        free(world);
}

tecs_entity tecs_entity_create(tecs_world *world) {
        int row = tecs__archetype_ins(world->root, world->entity_index, world->next_entity);
        tecs__map_ins(world->entity_index, world->next_entity, (tecs__record){ .archetype = world->root, .row = row });
        return world->next_entity++;
}

void tecs_entity_delete(tecs_world *world, tecs_entity entity) {
        // TODO
}

void tecs_entity__attach(tecs_world *world, tecs_entity entity, const char *component, void *data) {
        tecs__record *record = tecs__map_get(world->entity_index, entity);

        if (!record) {
                return; // Error: Entity does not exist
        }

        tecs_entity *init_type = record->archetype->type;
        tecs_entity *fini_type = NULL;
        tecs__array_dup(fini_type, init_type);
        tecs__array_push(fini_type, component);
}

void tecs_component__register(tecs_world *world, const char *component, int size) {
        tecs__map_ins(world->component_index, );
}

void tecs_system__register(tecs_world *world, tecs_system func, const char *components) {
        tecs_entity *type = NULL;
        tecs__archetype *archetype = tecs__map_get(world->type_index, type);

        if (!archetype) {
                archetype = tecs__archetype_travins(world->root, type, world->component_index, world->type_index);
        } else {
                tecs__array_free(type);
        }

        tecs__map_ins(world->system_index, components, (tecs__system){ .archetype = archetype, .func = func });
}


#endif // !__tiny_ecs_c__
#endif // TECS_IMPL || TECS_IMPL_STATIC || TINY_IMPL || TINY_IMPL_STATIC
#endif // !__tiny_ecs_h__
