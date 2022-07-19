#pragma once
#include <stddef.h>

void   *nbMemoryAlloc   (size_t size);
void   *nbMemoryZalloc  (size_t size);
void   *nbMemoryRealloc (void *block, size_t size);
void    nbMemoryFree    (void *block);

void    nbMemorySet     (void *dest, int value, size_t size);
void    nbMemoryZero    (void *dest, size_t size);
void    nbMemoryMove    (void *dest, void const *source, size_t size);
void    nbMemoryCopy    (void *dest, void const *source, size_t size);

