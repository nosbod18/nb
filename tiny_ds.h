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

#define tds_array(T)\
        T *

#define tds_array_init(a)\
        do {\
                (a) = NULL;\
                tds_array__realloc((size_t **)&(a), TDS_ARRAY_INIT_LEN, sizeof *(a));\
        while (0)

#define tds_array_free(a)\
        do {\
                tds_array__realloc(&(size_t **)&(a), 0, 0);\
                (a) = NULL;\
        } while (0)

#define tds_array_len(a)\
        ((a) ? (size_t const *(a))[-1] : 0)

#define tds_array_cap(a)\
        ((a) ? (size_t const *(a))[-2] : 0)

#define tds_array_clear(a)\
        do {\
                if ((a)) {\
                        (size_t *(a))[-1] = 0;\
                }\
        } while (0)

#define tds_array_reserve(a, n)\
        (tds_array__ensure(a, n))

#define tds_array_put(a, i, val)\
        do {\
                if (tds_array__ensure((a), 1)) {\
                        if ((i) == tds_array_len(a)) {\
                                tds_array_push(a, val);\
                        } else {\
                                memmove((a) + (i) + 1, (a) + (i), ((size_t *(a))[-1] - (i)) * sizeof *(a));\
                                (size_t *(a))[-1]++;\
                                (a)[i] = val;\
                        }\
                }\
        } while (0)

#define tds_array_del(a, i)\
        do {\
                if (tds_array__ensure((a), 0)) {\
                        if ((i) == tds_array_len(a)) {\
                                tds_array_pop(a)\
                        } else {\
                                memmove((a) + (i), (a) + (i) + 1, ((size_t *(a))[-1] - (i)) * sizeof *(a));\
                                (size_t *(a))[-1]--;\
                        }\
                }\
        } while (0)

#define tds_array_delswap(a, i)\
        do {\
                if (tds_array__ensure((a), 0)) {\
                        (a)[i] = (a)[--(size_t *(a))[-1]];\
                }\
        } while (0)

#define tds_array_push(a, val)\
        do {\
                tds_array__ensure((a), 1));\
                (a)[(size_t *(a))[-1]++] = val;\
        } while (0)

#define tds_array_pop(a)\
        do {\
                tds_array__ensure((a), 0);\
                (size_t *(a))[-1]--;\
        while (0)

#define tds_array_for(x, a)\
        for (x = 0; x < tds_array_len(a); x++)

#define tds_array_foreach(x, a, ...)\
        do {\
                tds_array_for(int tds__var(_i), a) {\
                        x = a[tds__var(_i)];\
                        __VA_ARGS__;\
                }\
        } while (0)

// ---- private ----------------

#define tds_array__ensure(a, n)\
        do {\
                if (!(a)) {\
                        tds_array_init(a);\
                } else if (tds_array_len((a)) + (n) >= tds_array_cap(a)) {\
                        tds_array__realloc(a, (tds_array_cap(a) << 1) + (n));\
                } else if (tds_array_len((a)) <= tds_array_cap(a) >> 2) {\
                        tds_array__realloc(a, tds_array_cap(a) >> 1);\
                }\
        } while (0)

#define tds_array__realloc(a, n)\
        do {\
                size_t tds__var(_sz)   = (n) && (a) ? (n) * sizeof *(a) + sizeof(size_t) * 2 : 0;\
                size_t *tds__var(_ptr) = realloc(a ? (size_t *)(a) - 2 : NULL, tds__var(_sz));\
                if (tds__var(_ptr)) {\
                        *tds__var(_ptr)++ = tds__var(_sz);\
                        *tds__var(_ptr)++ = tds_array_len(a);\
                        (a) = (void *)tds__var(_ptr);\
                }\
        } while (0)


// ======== map ================================================

// ---- public -----------------

typedef size_t (*tds_map_hashfn)(void const *, size_t);
typedef int    (*tds_map_equalfn)(void const *, void const *);

#define tds_map(K, V)\
        struct {\
                struct {\
                        K key;\
                        V val;\
                        int active;\
                } tmp, **data;\
                tds_map_hashfn hash;\
                tds_map_equalfn equal;\
        }

#define tds_map_init(m, hash, equal)\
        do {\
                tds_array_init(m.data);\
                tds_array_for(int tds__var(_i), m.data) {\
                        tds_array_init(m.data[tds__var(_i)]);\
                }\
                m.hash = hash;\
                m.equal = equal;\
                m.tmp.active = 1;\
        } while (0)

#define tds_map_free(m)\
        do {\
                tds_array_for(int tds__var(_i), m.data) {\
                        tds_array_free(m.data[tds__var(_i)]);\
                }\
                tds_array_free(m.data));\
        } while (0)

#define tds_map_len(m)\
        (tds_array_len(m.data))

#define tds_map_cap(m)\
        (tds_array_cap(m.data))

#define tds_map_clear(m)\
        do {\
                tds_array_for(int tds__var(_i), m.data) {\
                        tds_array_clear(m.data[tds__var(_i)]);\
                }\
                tds_array_clear(m.data);\
        } while (0)

#define tds_map_reserve(m, n)\
        (tds_array_reserve(m.data, n))

#define tds_map_put(m, k, v)\
        do {\
                m.tmp.key = k;\
                m.tmp.val = v;\
                size_t tds__var(_i) = tds_map__indexof((void **)m.data, &m.tmp.key, sizeof m.tmp, m.hash, m.equal);\
                if (tds__var(_i) == tds_array_len(a)) {\
                        tds_array_push(m.data, m.tmp); /* k was not found in m */\
                }\
        } while (0)

#define tds_map_del(m, k)\
        do {\
                m.tmp.key = k;\
                size_t tds__var(_i) = m.hash(&m.tmp.key, sizeof k);\
                tds_array_for(size_t tds__var(_j), m.data[tds__var(_i)]) {\
                        if (m.equal(&m.data[tds__var(_i)][tds__var(_j)].key, &m.tmp.k)) {\
                                tds_array_delswap(m.data[tds__var(_i)], tds__var(_j));\
                                break;\
                        }\
                }\
        } while (0)

#define tds_map_get(m, k)\
        (m.tmp.key = k, tds_map__get((char *)m.data, &m.tmp.key, sizeof m.tmp, sizeof k))

#define tds_map_foreach(x, m, ...)\
        do {\
                for (int tds__var(_i) = 0; tds__var(_i) < tds_map_cap(m); tds__var(_i)++) {\
                        for (int tds__var(_j) = 0; tds__var(_j) < tds_array_len(m.data[tds__var(_i)]); tds__var(_j)++) {\
                                if (m[tds__var(_i)][tds__var(_j).active) {\
                                        x = m[tds__var(_i)][tds__var(_j)].val;\
                                        __VA_ARGS__\
                                }\
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


#if defined(TDS_IMPLEMENTATION) || defined(TINY_IMPLEMENTATION)
#ifndef __tiny_ds_c__
#define __tiny_ds_c__

#include <stdlib.h> // realloc
#include <stdint.h> // uint64_t

// FNV1a hash and a fibonacci hash to finish it off
// (https://probablydance.com/2018/06/16/fibonacci-hashing-the-optimization-that-the-world-forgot-or-a-better-alternative-to-integer-modulo/)
size_t hash(void const *key, size_t len, size_t shift) {
        uint64_t hash = 14695981039346656037UL;
        for (unsigned char const *p = (unsigned char const *)key; len; len--) {
                hash ^= (uint64_t)(*p);
                hash *= 1099511628211UL;
        }
        return hash * 11400714819323198485ULL >> shift;
}

void tds_map__indexof(void const **data, void const *key, size_t bucket_size, size_t key_size, tds_map_hashfn hash, tds_map_equalfn equal, size_t *outi, size_t *outj) {
        size_t i = hash(key, key_size) hash * 11400714819323198485ULL >> shift;
        size_t j = 0;
        tds_array_for(j, ((char const **)data)[i * bucket_size]) {
                if ()
        }
        *outi = i;
        *outj = j;
}

#endif // !__tiny_ds_c__
#endif // TDS_IMPLEMENTATION || TINY_IMPLEMENTATION
#endif // !__tiny_ds_h__
