#pragma once
#include "memory.h"

#define NbArray(T)\
    T *

#define nbArrayFree(a)\
    ((a) ? free(&_nbArrayGetCapacity(a)), 0 : 0)

#define nbArrayGetLength(a)\
    ((a) ? _nbArrayGetLength(a) : 0)

#define nbArrayGetCapacity(a)\
    ((a) ? _nbArrayGetCapacity(a) : 0)

#define nbArrayClear(a)\
    ((a) ? _nbArrayGetLength(a) = 0, 0 : 0)

#define nbArrayReserve(a, n)\
    (nbArrayGetLength(a) + (n) >= nbArrayGetCapacity(a)\
        ? *((void **)&(a)) = _nbArrayGrow(a, nbArrayGetCapacity(a) * 2 + (n), sizeof *(a)), 0\
        : 0)

#define nbArrayPushN(a, n)\
    (nbArrayReserve(a, nbArrayGetLength(a) + (n)),\
        _nbArrayGetLength(a) += (n),\
        &(a)[nbArrayGetLength(a) - (n)])

#define nbArrayPopN(a, n)\
    (_nbArrayGetLength(a) -= (n),\
        &(a)[nbArrayGetLength(a)])

#define nbArrayInsertN(a, i, n)\
    (nbMemoryMove(nbArrayPushN(a, (i) + (n)), &(a)[i], sizeof *(a) * (nbArrayGetLength(a) - (i) - (n))),\
        &(a)[i])

#define nbArrayRemoveN(a, i, n)\
    (_nbArrayGetLength(a) -= (n),\
        nbMemoryMove(&(a)[i], &(a)[(i) + (n)], sizeof *(a) * (nbArrayGetLength(a) - (i) - (n))))

#define nbArrayPush(a, x)\
    (*nbArrayPushN(a, 1) = x)

#define nbArrayPop(a)\
    (*nbArrayPopN(a, 1))

#define nbArrayInsert(a, i, x)\
    (*nbArrayInsertN(a, i, 1) = x)

#define nbArrayRemove(a, i)\
    (nbArrayRemoveN(a, i, 1))

#define nbArrayRemoveSwap(a, i)\
    ((a)[i] = nbArrayPop(a))

#define nbArrayFor(i, a)\
    for (int (i) = 0; (i) < nbArrayGetLength(a); (i)++)

#define nbArrayForeach(it, a, ...) do {\
    nbArrayFor(_i__, a) {\
        it = (a)[_i__];\
        __VA_ARGS__\
    }\
} while (0)

#define nbArrayForeachP(it, a, ...) do {\
    nbArrayFor(_i__, a) {\
        it = &(a)[_i__];\
        __VA_ARGS__\
    }\
} while (0)


#define _nbArrayGetLength(a)\
    (((int *)(a))[-1])

#define _nbArrayGetCapacity(a)\
    (((int *)(a))[-2])

void *_nbArrayGrow(void *a, int n, int stride);

