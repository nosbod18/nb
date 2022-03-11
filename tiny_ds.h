#ifndef __tiny_ds_h__
#define __tiny_ds_h__

#include <string.h> // memmove, memcpy, memcmp
#include <stddef.h> // size_t


// ======== General ============================================

// ---- public -----------------


// ---- private ----------------

#define tds__join_impl(x, y) x##y
#define tds__join(x, y) tds__join_impl(x, y)
#define tds__var(x) tds__join(x, __LINE__)

// ======== array ==============================================

// ---- public -----------------

#ifndef TDS_ARRAY_INIT_LEN
        #define TDS_ARRAY_INIT_LEN 16
#endif

#define tds_array(T)                    T *
#define tds_array_init(a)               ((a) = NULL, tds_array__realloc((size_t **)&(a), TDS_ARRAY_INIT_LEN, sizeof *(a)))
#define tds_array_free(a)               (tds_array__realloc(&(size_t **)&(a), 0, 0), (a) = NULL)
#define tds_array_cap(a)                ((a) ?  (size_t *(a))[-1] : 0)
#define tds_array_len(a)                ((a) ?  (size_t *(a))[-2] : 0)
#define tds_array_clear(a)              ((a) ? ((size_t *(a))[-1] = 0, 0) : 0)
#define tds_array_reserve(a, n)         (tds_array__check((a), n))
#define tds_array_put(a, i, val)        (tds_array__check((a), 1) ? (memmove((a) + (i) + 1, (a) + (i), ((size_t *(a))[-1] - (i)) * sizeof *(a)), (size_t *(a))[-1]++, (a)[i] = val, 0) : 0)
#define tds_array_del(a, i)             (tds_array__check((a), 0) ? (memmove((a) + (i), (a) + (i) + 1, ((size_t *(a))[-1] - (i)) * sizeof *(a)), (size_t *(a))[-1]--, 0) : 0)
#define tds_array_delswap(a, i)         (tds_array__check((a), 0) ? ((a)[i] = (a)[--(size_t *(a))[-1]], 0) : 0)
#define tds_array_push(a, val)          (tds_array__check((a), 1) ? ((a)[(size_t *(a))[-1]++] = val, 0) : 0)
#define tds_array_pop(a)                (tds_array__check((a), 0) ? ((a)[--(size_t *(a))[-1]], 0) : 0)

#define tds_array_foreach(x, a, ...)\
        do {\
                for (int tds__var(_i) = 0; tds__var(_i) < tds_array_len((a)); tds__var(_i)++) {\
                        x = (a)[tds__var(_i)];\
                        __VA_ARGS__\
                }\
        } while (0)

// ---- private ----------------

#define tds_array__check(a, n)\
        ((a) == NULL\
                ? tds_array__realloc(&(size_t **)&(a), TDS_ARRAY_INIT_LEN, sizeof *(a))\
                : tds_array_len((a)) + (n) >= tds_array_cap((a))\
                        ? tds_array__realloc(&(size_t **)&(a), tds_array_len((a)) << 1 + (n), sizeof *(a))\
                        : tds_array_len((a)) <= tds_array_cap((a)) >> 2\
                                ? tds_array__realloc(&(size_t **)&(a), tds_array_cap((a)) >> 1, sizeof *(a))\
                                : 1)

int tds_array__realloc(size_t **a, size_t n, size_t asize);

// ======== map ================================================

// ---- public -----------------

#define tds_map(K, V)                   struct { struct { K key; V val; int active; } tmp, *data; }
#define tds_map_init(m)                 (tds_array_init(m.data))
#define tds_map_free(m)                 (tds_array_free(m.data))
#define tds_map_len(m)                  (tds_array_len(m.data))
#define tds_map_cap(m)                  (tds_array_cap(m.data))
#define tds_map_clear(m)                (tds_array_clear(m.data))
#define tds_map_reserve(m, n)           (tds_array_reserve(m.data, n))

#define tds_map_put(m, k, v)\
        do {\
                m.tmp.key = k;\
                m.tmp.val = v;\
                size_t _i = tds_map__hash((void *)&m.tmp.key, sizeof k, tds_map_cap(m));\
                while (m.data[_i].active && memcmp(&m.tmp.key, &m.data[_i].key, sizeof k)) {\
                        _i = (_i + 1) % tds_map_cap(m);\
                }\
                memcpy(&m.data[_i], &m.tmp, sizeof m.tmp);\
        } while (0)

#define tds_map_del(m, k)\
        do {\
                m.tmp.key = k;\
                m.tmp.val = v;\
                size_t _i = tds_map__hash((void *)&m.tmp.key, sizeof k, tds_map_cap(m));\
                while (memcmp(&m.tmp.key, &m.data[_i].key, sizeof k)) {\
                        _i = (_i + 1) % tds_map_cap(m);\
                }\
                m.data[_i].active = 0;\
        } while (0)

#define tds_map_get(m, k)\
        (m.tmp.key = k, tds_map__get((char *)m.data, m.tmp.key, sizeof m.tmp.key, sizeof m.tmp.val))

#define tds_map_foreach(x, m, ...)\
        do {\
                for (int tds__var(_i) = 0; tds__var(_i) < tds_map_cap(m); tds__var(_i)++) {\
                        if (m[tds__var(_i)].active) {\
                                x = m[tds__var(_i)].val;\
                                __VA_ARGS__\
                        }\
                }\
        } while (0)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                                                                                     ////
////                                                                                                                                                     ////
////                                                                   Implementation                                                                    ////
////                                                                                                                                                     ////
////                                                                                                                                                     ////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef TDS_IMPLEMENTATION
#ifndef __tiny_ds_c__
#define __tiny_ds_c__

#include <stdlib.h> // realloc
#include <stdint.h> // uint64_t

int tds_array__realloc(size_t **(a), size_t n, size_t sz) {
        size_t size = n && sz ? n * sz + sizeof(size_t) * 2;
        size_t *ptr = realloc(*(a), size);
        if (ptr) {
                *ptr++ = size;
                *ptr++ = tds_array_len(*a);
                *a = ptr;
                return 1;
        }
        return 0;
}

size_t tds_map__hash(void const *key, size_t len, size_t shift)
        uint64_t hash = 14695981039346656037UL;
        for (unsigned char const *p = (unsigned char const *)key; len; len--) {
                hash ^= (uint64_t)(*p);
                hash *= 1099511628211UL;
        }
        return hash * 11400714819323198485ULL >> shift;
}

#endif // !__tiny_ds_c__
#endif // TDS_IMPLEMENTATION
#endif // !__tiny_ds_h__
