#ifndef __tiny_ecs_h__
#define __tiny_ecs_h__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t                tecs_id;
typedef struct tecs_world       tecs_world;

#define TECS_SYSTEM_MAX_COMPONENT_TYPES 32
typedef struct tecs_view {
        void    *columns[TECS_SYSTEM_MAX_COMPONENT_TYPES];
        tecs_id *entities;
        int      count;
} tecs_view;


tecs_world     *tecs_alloc      (tecs_id max_entities, tecs_id max_components);
void            tecs_free       (tecs_world *world);
tecs_id         tecs_register   (tecs_world *world, size_t size, size_t cap);
tecs_view       tecs_query      (tecs_world *world, int n, ...);
tecs_id         tecs_new        (tecs_world *world);
void            tecs_del        (tecs_world *world, tecs_id *e);
void            tecs_add        (tecs_world *world, tecs_id e, tecs_id c, void *data);
void            tecs_rem        (tecs_world *world, tecs_id e, tecs_id c);


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

#include <string.h>
#include <stdarg.h>

#if defined(__GNUC__)
        #define tecs__alignof(T) (size_t)__alignof__(T)
#elif defined(_MSC_VER)
        #define tecs__alignof(T) (size_t)__alignof(T)
#else
        #define tecs__alignof(T) ((size_t)&((struct { char c; T d; } *)0)->d)
#endif

typedef struct tecs_sset {
        tecs_id        *sparse;
        tecs_id        *dense;
        size_t          cap;
        size_t          len;
} tecs_sset;

typedef struct tecs_pool {
        tecs_sset       sset;
        uint8_t        *data;
        size_t          size;
} tecs_pool;

struct tecs_world {
        tecs_sset       component_index;
        tecs_pool      *components;
        tecs_id        *entities;
        size_t          count;
};

#define tecs__idx(e)            ((uint32_t)(e))
#define tecs__gen(e)            ((uint32_t)((e) >> 32))
#define tecs__id(idx, gen)      (((tecs_id)(gen)) << 32 | (tecs_id)(idx))

static bool  tecs__sset_init    (tecs_sset *ss, size_t cap);
static void  tecs__sset_deinit  (tecs_sset *ss);
static void  tecs__sset_clear   (tecs_sset *ss);
static void  tecs__sset_add     (tecs_sset *ss, tecs_id e);
static void  tecs__sset_rem     (tecs_sset *ss, tecs_id e);
static bool  tecs__sset_has     (tecs_sset  ss, tecs_id e);

static bool  tecs__pool_init    (tecs_pool *p, size_t cap, size_t size);
static void  tecs__pool_deinit  (tecs_pool *p);
static void  tecs__pool_clear   (tecs_pool *p);
static void  tecs__pool_add     (tecs_pool *p, tecs_id e, void *data);
static void *tecs__pool_get     (tecs_pool  p, tecs_id e);
static void  tecs__pool_rem     (tecs_pool *p, tecs_id e);
static bool  tecs__pool_has     (tecs_pool  p, tecs_id e);


tecs_world *tecs_alloc(tecs_id num_entities, tecs_id num_components) {
        tecs_world *world = malloc(sizeof *world);
        if (!world) {
                return NULL;
        }

        world->entities   = malloc(sizeof *world->entities * num_entities);
        world->components = malloc(sizeof *world->components * num_components);

        if (!world->entities || !world->components) {
                tecs_free(world);
                return false;
        }

        tecs__sset_init(&world->component_index, num_components);

        while (--num_entities) {
                world->entities[num_entities] = num_entities;
        }

        world->count = 0;
        return true;
}

void tecs_free(tecs_world *world) {
        for (int i = 0; i < world->component_index.len; i++) {
                tecs__pool_deinit(&world->components[i]);
        }

        tecs__sset_deinit(&world->component_index);

        free(world->entities);
        free(world->components);
        free(world);
        memset(world, 0, sizeof *world);
}

tecs_id tecs_register(tecs_world *world, size_t size, size_t cap) {
        tecs_id c = tecs_new(world);
        tecs__sset_add(world->component_index, c);
        tecs__pool_init(&world->components[world->component_index.sparse[c]], cap, size);
        return c;
}

tecs_view tecs_query(tecs_world *world, int n, ...) {
        tecs_view view = {.count = INT_MAX};

        va_list ap;
        va_start(ap, n);

        for (int i = 0; i < n; i++) {
                tecs_pool p = world->components[world->component_index.sparse[va_arg(ap, tecs_id)]];
                view.columns[i] = (void *)p.data;
                view.count = view.count < p.sset.len ? view.count : p.sset.len;
                // TODO: Entities
        }

        va_end(ap);
        return view;
}

tecs_id tecs_new(tecs_world *world) {
        return world->entities[world->num_entities++];
}

void tecs_del(tecs_world *world, tecs_id *e) {
        world->entities[--world->num_entities] = tecs__id(tecs__gen(*e) + 1, tecs__idx(*e));
        *e = 0;
        // TODO: Remove components and stuff
}

void tecs_add(tecs_world *world, tecs_id e, tecs_id c, void *data) {
        tecs__pool_add(world->components[c], tecs__idx(e), data);
}

void tecs_rem(tecs_world *world, tecs_id e, tecs_id c) {
        tecs__sset_rem(world->components[c], tecs__idx(e));
}



static bool tecs__sset_init(tecs_sset *ss, size_t cap) {
        memset(ss, 0, sizeof *ss);
        ss->dense  = malloc(sizeof *ss->dense * cap);
        ss->sparse = malloc(sizeof *ss->sparse * cap);
        if (!ss->dense || !ss->sparse) {
                tecs__sset_deinit(ss);
                return false;
        }
        ss->cap = cap;
        return true;
}

static void tecs__sset_deinit(tecs_sset *ss) {
        free(ss->dense);
        free(ss->sparse);
        memset(ss, 0, sizeof *ss);
}

static void tecs__sset_clear(tecs_sset *ss) {
        ss->len = 0;
}

static void tecs__sset_add(tecs_sset *ss, tecs_id e) {
        if (tecs__sset_has(*ss, e)) {
                return;
        }
        ss->dense[ss->len] = e;
        ss->sparse[e]     = ss->len;
        ss->len++;
}

static void tecs__sset_rem(tecs_sset *ss, tecs_id e) {
        if (!tecs__sset_has(*ss, e)) {
                return;
        }
        ss->len--;
        ss->dense[ss->sparse[e]]      = ss->dense[ss->len];
        ss->sparse[ss->dense[ss->len]] = ss->sparse[e];
}

static bool tecs__sset_has(tecs_sset ss, tecs_id e) {
        return ss.sparse[e] < ss.len && ss.dense[ss.sparse[e]] == e;
}

static bool tecs__pool_init(tecs_pool *p, size_t cap, size_t size) {
        memset(p, 0, sizeof *p);

        if (!tecs__sset_init(&p->sset, cap)) {
                return false;
        }

        p->data = malloc(size * cap);
        if (!p->data) {
                tecs__pool_deinit(p);
                return false;
        }

        p->size = size;
        return true;
}

static void tecs__pool_deinit(tecs_pool *p) {
        tecs__sset_deinit(&p->sset);
        free(p->data);
        memset(p, 0, sizeof *p);
}

static void tecs__pool_clear(tecs_pool *p) {
        tecs__sset_clear(&p->sset);
}

static void tecs__pool_add(tecs_pool *p, tecs_id e, void *data) {
        if (tecs__pool_has(*p, e)) {
                return;
        }

        memcpy(&p->data[p->size * p->sset.len], data, p->size);
        tecs__sset_add(&p->sset, e);
}

static void *tecs__pool_get(tecs_pool p, tecs_id e) {
        return tecs__pool_has(p, e) ? (void *)&p.data[p.sset.sparse[e] * p.size] : NULL;
}

static void tecs__pool_rem(tecs_pool *p, tecs_id e) {
        tecs__sset_rem(&p->sset, e);
        memcpy(&p->data[p->sset.sparse[e] * p->size], &p->data[p->ss.len * p->size], p->size);
}

static bool tecs__pool_has(tecs_pool p, tecs_id e) {
        tecs__sset_has(p.sset, e);
}

#endif // !__tiny_ecs_c__
#endif // TECS_IMPL || TINY_IMPL
#endif // !__tiny_ecs_h__
