#ifndef __tiny_ds_h__
#define __tiny_ds_h__

#include <stdio.h>  // realloc, free
#include <string.h> // memmove
#include <stddef.h> // size_t


// ======== General ============================================

// ---- Public -----------------


// ---- Private ----------------

#define tds__JoinImpl(x, y) x##y
#define tds__Join(x, y) tds__JoinImpl(x, y)

size_t tds__NextPow2(size_t x);

// ======== Array ==============================================

// ---- Public -----------------

#ifndef tds_ARRAY_INIT_LENGTH
        #define tds_ARRAY_INIT_LENGTH 16
#endif

#define tds_ArrayInit(a)                (a = NULL, tds__ArrayRealloc(&tds__ArrayHeader(a), tds_ARRAY_INIT_LENGTH, sizeof *a))
#define tds_ArrayFree(a)                (tds__ArrayRealloc(&tds__ArrayHeader(a), 0, 0), a = NULL)
#define tds_ArrayCapacity(a)            (tds__ArrayHeader(a)->capacity)
#define tds_ArrayLength(a)              (tds__ArrayHeader(a)->length)
#define tds_ArrayClear(a)               (tds__ArrayHeader(a)->length = 0)
#define tds_ArrayReserve(a, n)          (tds__ArrayHeader(a)->length < n ? (tds__ArrayRealloc(&tds__ArrayHeader(a), n, sizeof *a), 0) : 0)
#define tds_ArrayPut(a, i, val)         (tds__CheckArray(a, 1), memmove(a + (i) + 1, a + (i), (tds__ArrayHeader(a)->length - (i)) * sizeof *a), tds__ArrayHeader(a)->length++, a[i] = val)
#define tds_ArrayDel(a, i)              (tds__CheckArray(a, 0), memmove(a + (i), a + (i) + 1, (tds__ArrayHeader(a)->length - (i)) * sizeof *a), tds__ArrayHeader(a)->length--)
#define tds_ArrayDelSwap(a, i)          (tds__CheckArray(a, 0), a[i] = a[--tds__ArrayHeader(a)->length])
#define tds_ArrayPush(a, val)           (tds__CheckArray(a, 1), a[tds__ArrayHeader(a)->length++] = val)
#define tds_ArrayPop(a)                 (tds__CheckArray(a, 0), a[--tds__ArrayHeader(a)->length])

#define tds_ArrayForeach(x, a, ...)\
        do {\
                for (int tds__Join(_i, __LINE__) = 0; tds__Join(_i, __LINE__) < tds_ArrayLength(a); tds__Join(_i, __LINE__)++) {\
                        x = a[tds__Join(_i, __LINE__)];\
                        __VA_ARGS__\
                }\
        } while (0)

// ---- Private ----------------

typedef struct tds__Header {
        void   *data; // Suplementary data, not the actual data of the structure
        size_t  length;
        size_t  capacity;
} tds__Header;

#define tds__ArrayHeader(a) ((tds__Header *)a - 1)

#define tds__CheckArray(a, n)\
        (a == NULL\
                ? (tds__ArrayRealloc(&tds__ArrayHeader(a), tds_ARRAY_INIT_LENGTH, sizeof *a), 0)\
                : tds_ArrayLength(a) + (n) >= tds_ArrayCapacity(a)\
                        ? (tds__ArrayRealloc(&tds__ArrayHeader(a), tds__NextPow2(tds_ArrayLength(a) << 1 + (n)), sizeof *a), 0)\
                        : tds_ArrayLength(a) <= tds_ArrayCapacity(a) >> 2\
                                ? (tds__ArrayRealloc(&tds__ArrayHeader(a), tds__NextPow2(tds_ArrayCapacity(a) >> 1), sizeof *a), 0)\
                                : 0)

void tds__ArrayRealloc(tds__Header **a, size_t n, size_t asize);

// ======== Map ================================================

// ---- Public -----------------

#ifndef tds_MAP_INIT_LENGTH
        #define tds_MAP_INIT_LENGTH 16
#endif

#define tds_MapInit(m)                  (m = NULL, tds__MapRealloc(&m, tds_MAP_INIT_LENGTH, sizeof *m))
#define tds_MapFree(m)                  (tds__MapRealloc(&tds__MapHeader(m), 0, 0), m = NULL)
#define tds_MapLength(m)                (tds_ArrayLength(m))
#define tds_MapCapacity(m)              (tds_ArrayCapacity(m))
#define tds_MapClear(m)                 (tds_ArrayClear(m))
#define tds_MapReserve(m, n)            (tds_MapCapacity(m) < n ? (tds__MapRealloc(&tds__MapHeader(m), n, sizeof *m), 0) : 0)
#define tds_MapPut(m, k, v)             (tds__MapPut(&tds__MapHeader(m), ))

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

void tds__ArrayRealloc(tds__Header **a, size_t n, size_t sz) {
        size_t size = n && sz ? n * sz + sizeof(tds__Header);
        tds__Header *ptr = realloc(a ? tds__ArrayHeader(a) : NULL, size);
        if (ptr) {
                ptr->capacity = size;
                ptr->length   = a ? (*a)->length : 0;
                *a = ptr;
        }
}

#endif // !__tiny_ds_c__
#endif // tds_IMPLEMENTATION
#endif // !__tiny_ds_h__
