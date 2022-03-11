#ifndef __tiny_ds_h__
#define __tiny_ds_h__

#include <string.h> // memmove
#include <stddef.h> // size_t


// ======== General ============================================

// ---- Public -----------------


// ---- Private ----------------

typedef struct tds__Header {
        void      *data; // Suplementary data, not the actual data of the structure
        size_t     length;
        size_t     capacity;
        ptrdiff_t  temp;
} tds__Header;

#define tds__GetHeader(a) ((tds__Header *)a - 1)

#define tds__JoinImpl(x, y) x##y
#define tds__Join(x, y) tds__JoinImpl(x, y)

// ======== Array ==============================================

// ---- Public -----------------

#ifndef tds_ARRAY_INIT_LENGTH
        #define tds_ARRAY_INIT_LENGTH 16
#endif

#define tds_Array(T)                    T *
#define tds_Array_Init(a)               (a = NULL, tds_Array__Realloc(&tds__GetHeader(a), tds_ARRAY_INIT_LENGTH, sizeof *a))
#define tds_Array_Free(a)               (tds_Array__Realloc(&tds__GetHeader(a), 0, 0), a = NULL)
#define tds_Array_Capacity(a)           (a ? tds__GetHeader(a)->capacity : 0)
#define tds_Array_Length(a)             (a ? tds__GetHeader(a)->length : 0)
#define tds_Array_Clear(a)              (a ? (tds__GetHeader(a)->length = 0, 0) : 0)
#define tds_Array_Reserve(a, n)         (tds_Array__Check(a, n))
#define tds_Array_Put(a, i, val)        (tds_Array__Check(a, 1) ? (memmove(a + (i) + 1, a + (i), (tds__GetHeader(a)->length - (i)) * sizeof *a), tds__GetHeader(a)->length++, a[i] = val, 0) : 0)
#define tds_Array_Del(a, i)             (tds_Array__Check(a, 0) ? (memmove(a + (i), a + (i) + 1, (tds__GetHeader(a)->length - (i)) * sizeof *a), tds__GetHeader(a)->length--), 0) : 0)
#define tds_Array_DelSwap(a, i)         (tds_Array__Check(a, 0) ? (a[i] = a[--tds__GetHeader(a)->length], 0) : 0)
#define tds_Array_Push(a, val)          (tds_Array__Check(a, 1) ? (a[tds__GetHeader(a)->length++] = val, 0) : 0)
#define tds_Array_Pop(a)                (tds_Array__Check(a, 0) ? (a[--tds__GetHeader(a)->length]), 0 : 0)

#define tds_Array_Foreach(x, a, ...)\
        do {\
                for (int tds__Join(_i, __LINE__) = 0; tds__Join(_i, __LINE__) < tds_Array_Length(a); tds__Join(_i, __LINE__)++) {\
                        x = a[tds__Join(_i, __LINE__)];\
                        __VA_ARGS__\
                }\
        } while (0)

// ---- Private ----------------

#define tds_Array__Check(a, n)\
        (a == NULL\
                ? tds_Array__Realloc(&tds__GetHeader(a), tds_ARRAY_INIT_LENGTH, sizeof *a)\
                : tds_Array_Length(a) + (n) >= tds_Array_Capacity(a)\
                        ? tds_Array__Realloc(&tds__GetHeader(a), tds_Array_Length(a) << 1 + (n), sizeof *a)\
                        : tds_Array_Length(a) <= tds_Array_Capacity(a) >> 2\
                                ? tds_Array__Realloc(&tds__GetHeader(a), tds_Array_Capacity(a) >> 1, sizeof *a)\
                                : 1)

void tds_Array__Realloc(tds__Header **a, size_t n, size_t asize);

// ======== Map ================================================

// ---- Public -----------------

#ifndef tds_MAP_INIT_LENGTH
        #define tds_MAP_INIT_LENGTH 16
#endif

#define tds_Map(K, V)                   struct { struct { K key; V val; int active; } tmp, *data; }
#define tds_Map_Init(m)                 (tds_Array_Init(m.data))
#define tds_Map_Free(m)                 (tds_Array_Free(m.data))
#define tds_Map_Length(m)               (tds_Array_Length(m.data))
#define tds_Map_Capacity(m)             (tds_Array_Capacity(m.data))
#define tds_Map_Clear(m)                (tds_Array_Clear(m.data))
#define tds_Map_Reserve(m, n)           (tds_Array_Reserve(m.data, n))

#define tds_Map_Put(m, k, v)            (m.tmp.key = k, m.tmp.val = v,  tds_Map__Put((char *)m.data, m.tmp.k, sizeof m.tmp.k, m.tmp.v, sizeof m.tmp.v))
#define tds_Map_Del(m, k)               (m.tmp.key = k, tds_Map__Del((char *)m.data, m.tmp.k, sizeof m.tmp.k, sizeof m.tmp.v))
#define tds_Map_Get(m, k)               (m.tmp.key = k, tds_Map__Del((char *)m.data, m.tmp.k, sizeof m.tmp.k, sizeof m.tmp.v))

#define tds_Map_Foreach(x, m, ...)\
        do {\
                for (int tds__Join(_i, __LINE__) = 0; tds__Join(_i, __LINE__) < tds_Map_Capacity(m); tds__Join(_i, __LINE__)++) {\
                        if (m[tds__Join(_i, __LINE__)].active) {\
                                x = m[tds__Join(_i, __LINE__)].val;\
                                __VA_ARGS__\
                        }\
                }\
        } while (0)

/*

size_t i = tds_Map__Hash(&m.tmp.k, sizeof m.tmp.k, tds_Array_Capacity(m.data));
while (m.data.active) {
        
}j

m.data[i].key = k;
m.data[i].val = v;
m.data[i].active = 1

*/

// ---- Private ----------------

size_t  tds_Map__Hash                   (void const *key, size_t keySize, size_t shift);
size_t  tds_Map__Put                    (char *data, void const *key, size_t keySize, void const *val, size_t valSize);
void    tds_Map__Del                    (char *data, void const *key, size_t keySize, size_t valSize);
void   *tds_Map__Get                    (char *data, void const *key, size_t keySize, size_t valSize);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                                                                                     ////
////                                                                                                                                                     ////
////                                                                   Implementation                                                                    ////
////                                                                                                                                                     ////
////                                                                                                                                                     ////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef tds_IMPLEMENTATION
#ifndef __tiny_ds_c__
#define __tiny_ds_c__

#include <stdlib.h> // realloc
#include <stdint.h> // uint64_t

size_t tds__NextPow2(size_t x) {
        x--;
        x |= x >>  1;
        x |= x >>  2;
        x |= x >>  4;
        x |= x >>  8;
        x |= x >> 16;
        x++;
        return x;
}

int tds_Array__Realloc(tds__Header **a, size_t n, size_t sz) {
        size_t size = n && sz ? n * sz + sizeof(tds__Header);
        tds__Header *ptr = realloc(a ? tds__GetHeader(a) : NULL, size);
        if (ptr) {
                ptr->capacity = size;
                ptr->length   = a ? (*a)->length : 0;
                *a = ptr;
                return 1;
        }
        return 0;
}

size_t tds_Map__Hash(void const *key, size_t len, size_t shift) {
        uint64_t hash = 14695981039346656037UL;
        for (char const *p = key; len; len--) {
                hash ^= (uint64_t)(unsigned char)(*p);
                hash *= 1099511628211UL;
        }
        return hash * 11400714819323198485ULL >> shift;
}

#endif // !__tiny_ds_c__
#endif // tds_IMPLEMENTATION
#endif // !__tiny_ds_h__
