#define GL_SILENCE_DEPRECATION
#include "buffer.h"
#include "../core/array.h"
#include <OpenGL/gl3.h>

typedef struct Buffer {
    unsigned type;
    unsigned usage;
    unsigned size;
    unsigned version;
} Buffer;

static Buffer *gBuffers = NULL;

static unsigned translateBufferType(NbBufferType type) {
    switch (type) {
        case NbBufferType_Vertex:   return GL_ARRAY_BUFFER;
        case NbBufferType_Index:    return GL_ELEMENT_ARRAY_BUFFER;
    }
    return 0;
}

static unsigned translateBufferUsage(NbBufferUsage usage) {
    switch (usage) {
        case NbBufferUsage_Static:  return GL_STATIC_DRAW;
        case NbBufferUsage_Dynamic: return GL_DYNAMIC_DRAW;
        case NbBufferUsage_Stream:  return GL_STREAM_DRAW;
    }
    return 0;
}

NbBuffer NbBufferCreate(NbBufferDesc const *desc) {
    Buffer glbuffer = {
        .type = translateBufferType(desc->type),
        .usage = translateBufferUsage(desc->usage)
    };

    NbBuffer buffer = {0};
    glGenBuffers(1, &buffer.id);
    glBindBuffer(glbuffer.type, buffer.id);
    glBufferData(glbuffer.type, desc->size, desc->data, glbuffer.usage);
    glBindBuffer(glbuffer.type, 0);

    nbArrayReserve(gBuffers, buffer.id);
    buffer.version = gBuffers[buffer.id].version;
    gBuffers[buffer.id] = glbuffer;

    return buffer;
}

void NbBufferDelete(NbBuffer buffer) {
    if (buffer.version != gBuffers[buffer.id].version)
        return;

    glDeleteBuffers(1, &buffer.id);
    gBuffers[buffer.id].version++;
}

void NbBufferSetData(NbBuffer buffer, void *const data) {
    Buffer glbuffer = gBuffers[buffer.id];

    if (buffer.version != glbuffer.version)
        return;

    if (glbuffer.usage != GL_DYNAMIC_DRAW)
        return;

    glBindBuffer(glbuffer.type, buffer.id);
    glBufferSubData(glbuffer.type, 0, glbuffer.size, data);
    glBindBuffer(glbuffer.type, 0);
}

