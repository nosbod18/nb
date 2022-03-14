/// # tiny_ds.h
/// A collection of generic data structures

#ifndef __tiny_ds_h__
#define __tiny_ds_h__

#include <string.h> // memmove
#include <stddef.h> // size_t


// ======== General ============================================

#define tds__var(x) _##x##__LINE__


/// ## Array
///
/// #### Description
/// The array is the base of all `tiny_ds.h` structures. A simple "stretchy buffer" implementation, it keeps track of its current capacity
/// and number of elements so it knows when to allocate more space once it gets full. Internally, the array actually looks like this:
///
///      capacity  length
///     +--------+--------+-------+-------+-------+-------+
///     |   -2   |   -1   |   0   |   1   |   2   |  ...  |
///     +--------+--------+-------+-------+-------+-------+
///                        \
///                          User pointer
///
/// The array API functions are all macros, and with macros come no type checking and hard to debug errors, but they are the only way to do
/// type-agnostic implementations in C. The user will just have to be careful with what they pass as arguments to these macros. Most of
/// them try to do some checking to see if the passed in array is `NULL` to avoid segmentation faults, but some care is still required.
///
/// ### Creating / Freeing
/// There is no `init` or `create` macro for an array, because the macros for insertion check to see if `a` is `NULL` and allocate space if it is.
/// `tds_array_reserve` can be used to set an initial capacity if needed.
///
/// ```c
/// // Define a array of type int like this
/// int *array = NULL;
///
/// // Reserve 32 spaces in the array
/// tds_array_reserve(array, 32);
///
/// // Free the array when it's no longer needed
/// tds_array_free(array);
/// ```
///
/// #### Macros
/// ```c
/// void tds_array_reserve(T *a, int n)
/// void tds_array_free(T *a);
/// ```
///
/// ### Inserting / Deleting
/// Inserting an element into an array takes a few steps. First, if required, uninitialized elements are allocated at the end of the array
/// with `tds_array_pushn`. Then, the rest of the elements are shifted down using `tds_array_insn` to make room for the new element. Finally,
/// the element is inserted at the specified index with `tds_array_ins`. Data can be inserted using any of these steps. For example, multiple
/// elements can be appended to an array at once like this:
/// ```c
/// int *array = NULL;
/// int to_insert[5] = {1, 2, 3, 4, 5};
///
/// int *ptr = tds_array_pushn(array, 5);
/// for (int i = 0; i < 5; i++)
///         ptr[i] = to_insert[i];
/// // or memcpy(ptr, to_insert, sizeof to_insert);
/// ```
/// `tds_array_del{n}` deletes elements in an array the way an `std::vector` does in C++, shifting the other elements down and overwriting the
/// deleted element with the one from the next index. This keeps the array tightly packed with no gaps and keeps the order. `tds_array_delswap`
/// deletes an element by swapping it with the last element in the array then popping the last element off the array, similar to the "swap and pop" idiom
/// in C++. This allows an element to be deleted in O(1) time, but changes the order of the array. `tds_array_delswap` is much faster than
/// `tds_array_del` and should probably be used, unless the array's order needs to be maintained.
/// ```c
/// // Building off of the insertion example above
/// tds_array_del(array, 3);
/// tds_array_deln(array, 2, 4);
///
/// int last = tds_array_pop(array); // last == 0
/// int len = tds_array_len(array); // len == 0
/// tds_array_free(array);
/// ```
///
/// #### Macros
/// ```c
/// // Inserting
/// T    *tds_array_insn(T *a, int index, int n);
/// void  tds_array_ins(T *a, int index);
/// T    *tds_array_pushn(T *a, int n);
/// void  tds_array_push(T *a);
///
/// // Deleting
/// void  tds_array_deln(T *a, int index, int n);
/// void  tds_array_del(T *a, int index);
/// void  tds_array_delswap(T *a, int index);
/// T    *tds_array_popn(t *a, int n);
/// T     tds_array_pop(T *a);
/// void  tds_array_clear(T *a);
/// ```
///
/// ### Accessing / Iterating
/// Since the array is just a normal C array, access into it happens as it would with any other array.
/// ```c
/// float *array = NULL;
/// tds_array_push(array, 5.0f);
/// tds_array_push(array, 10.0f);
///
/// float x = array[1]; // x == 10.0f
/// ```
///
/// Array elements can also be set like a normal array.
/// ```c
/// array[1] = 15.0f;
/// ```
///
/// Looping through an array can be done with a regular for loop by testing against `tds_array_len(array)`, or by using the `tds_array_foreach` macro.
/// ```c
/// // Normal for loop
/// for (size_t i = 0; i < tds_array_len(array); i++) {
///         printf("%d\n", array[i]);
/// }
///
/// // Notice how the curly brackets are inside the macro as a parameter
/// tds_array_foreach(int i, array, {
///         printf("%d\n", i);
/// });
///
/// // The curly brackets are not required
/// tds_array_foreach(int i, array,
///         printf("%d\n", i);
/// );
///
/// // The "iterator" can be any type
/// tds_array_foreach(my_custom_type c, array, {
///         print_my_custom_type(c);
/// });
/// ```
///
/// #### Macros
/// ```c
/// T *tds_begin(T *a);
/// T *tds_end(T *a);
///
/// tds_array_foreach(T it, T *array, ...);
/// ```

#define tds_array_reserve(a, n)         (tds_array_cap(a) < (n) ? ((a) = tds_array__grow(a, n), 0) : 0)
#define tds_array_free(a)               ((a) = tds_array__realloc(a, 0, 0))
#define tds_array_cap(a)                ((a) ? tds_array__cap(a) : 0)
#define tds_array_len(a)                ((a) ? tds_array__len(a) : 0)

#define tds_array_pushn(a, n)           (tds_array__grow(a, n), (n) ? (tds_array__len(a) += (n), &(a)[tds_array_len(a) - (n)]) : (a))
#define tds_array_insn(a, i, n)         (tds_array_pushn(a, n), memmove(&(a)[(i) + (n)], &a[(i)], sizeof *(a) * (tds_array_len(a) - (n) - (i))), &(a)[(i)])
#define tds_array_push(a, v)            (*tds_array_pushn(a, n) = (v))
#define tds_array_ins(a, i, v)          (*tds_array_insn(a, i, 1) = (v))

#define tds_array_deln(a, i, n)         (tds_array_len(a) ? (tds_array__len(a) -= n, memmove(&(a)[(i)], &a[(i) + (n)], sizeof *(a) * (tds_array__len(a) - (i))), 0) : 0)
#define tds_array_del(a, i)             (tds_array_deln(a, i, 1))
#define tds_array_delswap(a, i)         (tds_array_len(a) ? ((a)[(i)] = (a)[--tds_array__len(a)], 0) : 0)
#define tds_array_pop(a)                (*tds_array_popn(a, 1))
#define tds_array_popn(a, n)            (tds_array_deln(a, tds_array_len(a) - (n), n), &(a)[tds_array_len(a) - 1])
#define tds_array_clear(a)              ((a) ? (tds_array__len(a) = 0, 0) : 0)

#define tds_array_begin(a)              (a)
#define tds_array_end(a)                ((a) + tds_array_len(a))

#define tds_array_foreach(x, a, ...)\
        do {\
                for (size_t tds__var(i) = 0; tds__var(i) < tds_array_len(a); tds__var(i)++) {\
                        x = a[tds__var(i)];\
                        __VA_ARGS__\
                }\
        } while (0)

#define tds_array__cap(a)               ((size_t *(a))[-2])
#define tds_array__len(a)               ((size_t *(a))[-1])
#define tds_array__grow(a, n)           (!(a) || tds_array__len(a) >= tds_array__cap(a) ? ((a) = tds_array__realloc(a, sizeof *a, n), 0) : 0)
void   *tds_array__realloc              (void *a, size_t asize, size_t n);


/// ## Map
///
/// #### Description
/// A generic hashmap implementation. A hashmap is really a specialized array, where the array type is a struct that has a key and value field.
/// Since a hashmap is an array, it stores the capacity and length before the returned pointer, along with 2 other pieces of data. An element is used
/// to represent the "default" or "empty" value to test against when determining whether a bucket is open. The other element is used as a temporary
/// element to store the key and value so the address of the key can be taken even if it's not an rvalue.
///
///      capacity  length   default   temp
///     +--------+--------+--------+--------+-------+-------+-------+
///     |   -4   |   -3   |   -2   |   -1   |   0   |   1   |  ...  |
///     +--------+--------+--------+--------+-------+-------+-------+
///                                         \
///                                           User pointer

// ---- public -----------------

#define tds_map__head(m)                ((m) - 2)
#define tds_map__default(m)             (tds_map__head(m)[0])
#define tds_map__temp(m)                (tds_map__head(m)[1])

#define tds_map_reserve(m, n)           (tds_array_reserve(tds_map__head(m), n + 1))
#define tds_map_free(m)                 (tds_array_free(tds_map__head(m)))
#define tds_map_len(m)                  ((m) ? tds_array_len(tds_map__head(m)) : 0)
#define tds_map_cap(m)                  ((m) ? tds_array_cap(tds_map__head(m)) : 0)
#define tds_map_default(m, k, v)        ((m) ? ((m)[-1].key = k, (m)[-1].val = v, 0) : 0)

#define tds_map_ins(m, k, v)\
        do {\
                /* Double the size of m if it is more than 65% full */\
                if (tds_map_load_factor(m) >= 0.65f) {\
                        size_t tds__var(ocap) = tds_map_cap(m);\
                        tds_array_reserve(m, tds__var(ocap) ? tds__var(ocap) * 2 : 2);\
                        memset(m + tds__var(ocap), 0, sizeof *m * (tds_map_cap(m) - tds__var(ocap)));\
                }\
                tds_map__head(m)[1].key = k;\
                tds_map__head(m)[1].val = v;\
                size_t tds__var(hash) = tds_map__hash(&m->tmp.k, sizeof k);\
                size_t tds__var(i) = tds__var(hash) % tds_map_cap(m);\
                while (tds__var(hash) != tds_map__hash(&m[tds__var(i)].key, sizeof k) && m[tds__var(i)].active) {\
                        tds__var(j) = (tds__var(j) + 1) % tds_map_cap(m);\
                }\
                m[tds__var(i)] = m->tmp;\
        } while (0)

#define tds_map_del(m, k)\
        do {\
                m->tmp.key = k;\
                size_t tds__var(i) = m->hash(&m->tmp.key, sizeof k);\
                tds_array_for(size_t tds__var(j), m[tds__var(i)]) {\
                        if (m->equal(&m[tds__var(i)][tds__var(j)].key, &m->tmp.k)) {\
                                tds_array_delswap(m[tds__var(i)], tds__var(j));\
                                break;\
                        }\
                }\
        } while (0)

#define tds_map_get(m, k)\
        (m->tmp.key = k, tds_map__get((char *)m, &m->tmp.key, sizeof m->tmp, sizeof k))

#define tds_map_clear(m)\
        do {\
                for (size_t tds__var(i) = 0; tds__var(i) < tds_array_len(m), tds__var(i)++) {\
                        tds_array_clear(m[tds__var(i)]);\
                }\
                tds_array_clear(m);\
        } while (0)

#define tds_map_foreach(x, m, ...)\
        do {\
                if (!m || !m) {\
                        break;\
                }\
                for (int tds__var(i) = 0; tds__var(i) < tds_map_cap(m); tds__var(i)++) {\
                        if (m[tds__var(i)].active) {\
                                x = m[tds__var(i)].val;\
                                __VA_ARGS__\
                        }\
                }\
        } while (0)


// ======== Queue ==============================================

#define tds_queue_reserve(q, n) tds_array_reserve(q)
#define tds_queue_free(q)       tds_array_free(q)
#define tds_queue_len(q)        tds_array_len(q)
#define tds_queue_cap(q)        tds_array_cap(q)


/************************************************************************************************************************************************************
*************************************************************************************************************************************************************
****                                                                                                                                                     ****
****                                                                                                                                                     ****
****                                                                   Implementation                                                                    ****
****                                                                                                                                                     ****
****                                                                                                                                                     ****
*************************************************************************************************************************************************************
************************************************************************************************************************************************************/


#if defined(TDS_IMPLEMENTATION) || defined(TINY_IMPLEMENTATION)
#ifndef __tiny_ds_c__
#define __tiny_ds_c__

#include <stdlib.h> // realloc
#include <stdint.h> // uint64_t

void *tds_array__realloc(void *a, size_t asize, size_t n)
        if (!a && !n) {
                return NULL;
        }

        size_t size = n ? n * asize + sizeof(size_t) * 2 : 0;
        size_t *ptr = realloc(a ? (size_t *)(a) - 2 : NULL, size);
        if (ptr) {
                *ptr++ = size;
                *ptr++ = tds_array_len(a);
        }
        return (void *)ptr;
}

// FNV1a hash
size_t tds_map__hash(void const *key, size_t n) {
        uint64_t hash = 14695981039346656037UL;
        for (unsigned char const *p = (unsigned char const *)key; n; n--) {
                hash ^= (uint64_t)(*p);
                hash *= 1099511628211UL;
        }
        return hash;
}

size_t tds_map__indexof(void **data, void *key, size_t ksize, size_t vsize) {
        size_t stride = ksize + vsize + sizeof(int);
        size_t hash = tds_map__hash(key, ksize);

        for (size_t i = hash % cap, c = 0; c < tds_array_cap(*data); c++, j = ((j + 1) % cap)) {
                void *k = ((char *)(*data) + i * stride);
                int active = *(int *)((char *)(*data) + i * stride + ksize + vsize);
                if (memcmp(k, key, key_len) == 0 && hash == tds_map__hash(k, ksize) && active) {
                        return i;
                }
        }
}


#endif // !__tiny_ds_c__
#endif // TDS_IMPLEMENTATION || TINY_IMPLEMENTATION
#endif // !__tiny_ds_h__


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
