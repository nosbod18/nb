#pragma once
#include <stddef.h>

typedef enum NbBufferType {
    NbBufferType_Vertex,
    NbBufferType_Index,
} NbBufferType;

typedef enum NbBufferUsage {
    NbBufferUsage_Static,
    NbBufferUsage_Dynamic,
    NbBufferUsage_Stream,
} NbBufferUsage;

typedef struct NbBufferDesc {
    void *data;
    size_t size;
    NbBufferType type;
    NbBufferUsage usage;
} NbBufferDesc;

typedef struct NbBuffer {
    unsigned id;
    unsigned version;
} NbBuffer;


NbBuffer    NbBufferCreate      (NbBufferDesc const *desc);
void        NbBufferDelete      (NbBuffer buffer);
void        NbBufferSetData     (NbBuffer buffer, void *const data);

