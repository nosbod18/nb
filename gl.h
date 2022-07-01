/* gl.h - v0.03 - public domain
    An OpenGL wrapper for C/C++

    Table of Contents
    -----------------
    Table of Contents
    Summary
    Usage
    Example
    Documentation
    Licence

    Summary
    -------
    TODO

    Usage
    -----
    To use this library, do this in *one* C or C++ file:

        #define GL_IMPLEMENTATION
        #include "gl.h"

    Then include it as normal in all other files.

    Example
    -------
    TODO

    Documentation
    -------------
    TODO

    License
    -------
    This is free and unencumbered software released into the public domain.
    Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
    software, either in source code form or as a compiled binary, for any purpose,
    commercial or non-commercial, and by any means.

    In jurisdictions that recognize copyright laws, the author or authors of this
    software dedicate any and all copyright interest in the software to the public
    domain. We make this dedication for the benefit of the public at large and to
    the detriment of our heirs and successors. We intend this dedication to be an
    overt act of relinquishment in perpetuity of all present and future rights to
    this software under copyright law.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
    ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

    For more information, please refer to <http://unlicense.org/>
*/

#pragma once
#include <stddef.h> // size_t

typedef enum ngl_buffer_type {
    NGL_BUFFER_TYPE_VERTEX = 0,
    NGL_BUFFER_TYPE_INDEX,
    NGL_BUFFER_TYPE_COMMAND,
} ngl_buffer_type;

typedef enum ngl_buffer_usage {
    NGL_BUFFER_USAGE_STATIC = 0,
    NGL_BUFFER_USAGE_DYNAMIC,
    NGL_BUFFER_USAGE_STREAM,
} ngl_buffer_usage;

typedef enum ngl_uniform_type {
    NGL_UNIFORM_TYPE_INVALID = 0,
    NGL_UNIFORM_TYPE_FLOAT,
    NGL_UNIFORM_TYPE_MATRIX
} ngl_uniform_type;

typedef enum ngl_vertex_type {
    NGL_VERTEX_TYPE_INVALID = 0,
    NGL_VERTEX_TYPE_INT8,
    NGL_VERTEX_TYPE_UINT8,
    NGL_VERTEX_TYPE_INT16,
    NGL_VERTEX_TYPE_UINT16,
    NGL_VERTEX_TYPE_INT32,
    NGL_VERTEX_TYPE_UINT32,
    NGL_VERTEX_TYPE_FLOAT,
} ngl_vertex_type;

typedef enum ngl_index_type {
    NGL_INDEX_TYPE_UINT32 = 0,
    NGL_INDEX_TYPE_UINT16
} ngl_index_type;

typedef enum ngl_pass_action {
    NGL_PASS_ACTION_DEFAULT = 0,
    NGL_PASS_ACTION_CLEAR,
} ngl_pass_action;

typedef struct ngl_buffer   ngl_buffer;
typedef struct ngl_image    ngl_image;
typedef struct ngl_program  ngl_program;
typedef struct ngl_pipeline ngl_pipeline;

typedef struct ngl_buffer_desc {
    void const *data;
    size_t size;
    ngl_buffer_type type;
    ngl_buffer_usage usage;
} ngl_buffer_desc;

typedef struct ngl_shader_desc {
    struct {
        char const *name;
        ngl_uniform_type type;
    } uniforms[16];
    char const *source;
} ngl_shader_desc;

typedef struct ngl_program_desc {
    ngl_shader_desc vs;
    ngl_shader_desc fs;
} ngl_program_desc;

typedef struct ngl_vertex_desc {
    ngl_vertex_type type;
    int count;
    int offset;
    int normalized;
} ngl_vertex_desc;

typedef struct ngl_pipeline_desc {
    struct {
        ngl_vertex_desc attributes[16];
        int stride;
    } layout;
    ngl_program *program;
    ngl_index_type index_type;
} ngl_pipeline_desc;

typedef struct ngl_pass_desc {
    struct {
        ngl_pass_action action;
        struct { float r, g, b, a; } value;
    } color;
    struct {
        ngl_pass_action action;
        float value;
    } depth;
    struct {
        ngl_pass_action action;
        int value;
    } stencil;
} ngl_pass_desc;

ngl_buffer     *ngl_buffer_create       (ngl_buffer_desc const *desc);
void            ngl_buffer_destroy      (ngl_buffer *buf);
int             ngl_buffer_set          (ngl_buffer *buf, void const *data, size_t size);
int             ngl_buffer_push         (ngl_buffer *buf, void const *data, size_t size);

ngl_program    *ngl_program_create      (ngl_program_desc const *desc);
void            ngl_program_destroy     (ngl_program *program);
void            ngl_program_set         (ngl_program *program, size_t index, void const *data);

ngl_pipeline   *ngl_pipeline_create     (ngl_pipeline_desc const *desc);
void            ngl_pipeline_destroy    (ngl_pipeline *pipeline);

void            ngl_pass_begin          (ngl_buffer *cmdbuf, ngl_pass_desc const *desc);
void            ngl_pass_end            (ngl_buffer *cmdbuf);

void            ngl_buffer_bind         (ngl_buffer *cmdbuf, ngl_buffer *buf);
void            ngl_pipeline_bind       (ngl_buffer *cmdbuf, ngl_pipeline *pipeline);

void            ngl_draw                (ngl_buffer *cmdbuf, int count, int start);
void            ngl_submit              (ngl_buffer *cmdbuf);
void            ngl_present             (void);

/***********************************************************************************************************************
************************************************************************************************************************
****                                                                                                               *****
****                                                                                                               *****
****                                                 Implementation                                                *****
****                                                                                                               *****
****                                                                                                               *****
************************************************************************************************************************
***********************************************************************************************************************/

#if defined(GL_IMPLEMENTATION) || defined(IMPLEMENTATION)

#ifndef ngl_assert
    #ifdef assert
        #define ngl_assert assert
    #else
        #include <assert.h>
        #define ngl_assert assert
    #endif
#endif

#ifndef ngl_calloc
    #include <stdlib.h>
    #define ngl_calloc calloc
#endif

#ifndef ngl_free
    #include <stdlib.h>
    #define ngl_free free
#endif

#if defined(__linux__)
        #include <GL/gl.h>
#elif defined(__APPLE__)
        #include <OpenGL/gl.h>
#endif // __linux__ || __APPLE__

typedef struct ngl_buffer {
    ngl_buffer_desc desc;
    unsigned int id;
    int overflowed;
    int capacity;
    int offset;
} ngl_buffer;

typedef struct ngl__uniform {
    int loc;
    int type;
    int count;
    int transposed;
} ngl__uniform;

struct ngl_program {
    ngl__uniform uniforms[16];
    unsigned int id;
};

struct ngl_pipeline {
    ngl_pipeline_desc desc;
};

// ======== OpenGL =============================================

#define NGL__CALL(x) while (glGetError() != GL_NO_ERROR); x; ngl_assert(glGetError() == GL_NO_ERROR)

static int ngl_buffer__type(ngl_buffer_type type) {
    switch (type) {
        case NGL_BUFFER_TYPE_VERTEX:    return GL_ARRAY_BUFFER;
        case NGL_BUFFER_TYPE_INDEX:     return GL_ELEMENT_ARRAY_BUFFER;
        default:                        break;
    }
    return 0;
}

static int ngl_buffer__usage(ngl_buffer_usage usage) {
    switch (usage) {
        case NGL_BUFFER_USAGE_STATIC:   return GL_STATIC_DRAW;
        case NGL_BUFFER_USAGE_DYNAMIC:  return GL_DYNAMIC_DRAW;
        case NGL_BUFFER_USAGE_STREAM:   return GL_STREAM_DRAW;
        default:                        break;
    }
    return 0;
}

static int ngl__uniform_type(ngl_uniform_type type) {
    switch (type) {
        case NGL_UNIFORM_TYPE_FLOAT:    return GL_FLOAT;
        case NGL_UNIFORM_TYPE_MATRIX:   return GL_FLOAT;
        default:                        break;
    }
    return 0;
}

static int ngl_vertex__type(ngl_vertex_type type) {
    switch (type) {
        case NGL_VERTEX_TYPE_INT8:      return GL_BYTE;
        case NGL_VERTEX_TYPE_UINT8:     return GL_UNSIGNED_BYTE;
        case NGL_VERTEX_TYPE_INT16:     return GL_SHORT;
        case NGL_VERTEX_TYPE_UINT16:    return GL_UNSIGNED_SHORT;
        case NGL_VERTEX_TYPE_INT32:     return GL_INT;
        case NGL_VERTEX_TYPE_UINT32:    return GL_UNSIGNED_INT;
        case NGL_VERTEX_TYPE_FLOAT:     return GL_FLOAT;
        default:                        break;
    }
    return 0;
}

ngl_buffer *ngl_buffer_create(ngl_buffer_desc const *desc) {
    assert(desc != NULL);

    ngl_buffer *buf = ngl_calloc(1, sizeof(*buf));
    if (buf == NULL) {
        return NULL;
    }

    buf->desc = *desc;
    buf->desc.type  = ngl_buffer__type(desc->type);
    buf->desc.usage = ngl_buffer__usage(desc->usage);

    NGL__CALL(glGenBuffers(1, &buf->id));
    NGL__CALL(glBindBuffer(buf->desc.type, buf->id));
    NGL__CALL(glBufferData(buf->desc.type, buf->desc.size, buf->desc.data, buf->desc.usage));
    NGL__CALL(glBindBuffer(buf->desc.type, 0));
    return buf;
}

void ngl_buffer_free(ngl_buffer *buf) {
    assert(buf != NULL);
    NGL__CALL(glDeleteBuffers(1, &buf->id));
    memset(buf, 0, sizeof(*buf));
    ngl_free(buf);
}

int ngl_buffer_set(ngl_buffer *buf, void const *data, size_t size) {
    assert(buf != NULL);

    if (size > buf->capacity) {
        return 0;
    }

    NGL__CALL(glBindBuffer(buf->desc.type, buf->id));
    NGL__CALL(glBufferSubData(buf->desc.type, 0, buf->desc.size, data));
    NGL__CALL(glBindBuffer(buf->desc.type, 0));

    buf->desc.size = size;
    return 1;
}

int ngl_buffer_push(ngl_buffer *buf, void const *data, size_t size) {
    assert(buf != NULL);

    if (buf->desc.size + size > buf->capacity) {
        return 0;
    }

    NGL__CALL(glBindBuffer(buf->desc.type, buf->id));
    NGL__CALL(glBufferSubData(buf->desc.type, buf->offset, buf->desc.size, data));
    NGL__CALL(glBindBuffer(buf->desc.type, 0));

    buf->desc.size += size;
    buf->offset += size;
    return 1;
}

static unsigned int ngl__shader_create(char const *src, int type) {
    NGL__CALL(unsigned int id = glCreateShader(type));
    NGL__CALL(glShaderSource(id, 1, (GLchar const **)&src, NULL));
    NGL__CALL(glCompileShader(id));

    int compiled;
    NGL__CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &compiled));

    if (compiled == GL_FALSE) {
        char msg[128];
        NGL__CALL(glGetShaderInfoLog(id, sizeof(msg), NULL, msg));
        printf("[NGL__CALL] Failed to compile shader\n%s\n", msg);
        NGL__CALL(glDeleteShader(id));
        return 0;
    }

    return id;
}

ngl_program *ngl_program_create(ngl_program_desc const *desc) {
    assert(desc);

    ngl_program *program = ngl_calloc(1, sizeof(*program));
    if (!program) {
        return NULL;
    }

    unsigned int vs = ngl__shader_create(desc->vs.source, GL_VERTEX_SHADER);
    unsigned int fs = ngl__shader_create(desc->fs.source, GL_FRAGMENT_SHADER);
    if (!vs || !fs) {
        ngl_program_free(program);
        return NULL;
    }

    NGL__CALL(program->id = glCreateProgram());
    NGL__CALL(glAttachShader(program->id, vs));
    NGL__CALL(glAttachShader(program->id, fs));
    NGL__CALL(glLinkProgram(program->id));
    NGL__CALL(glValidateProgram(program->id));
    NGL__CALL(glDetachShader(program->id, vs));
    NGL__CALL(glDetachShader(program->id, fs));

    return program;
}

void ngl_program_free(ngl_program *program) {
    NGL__CALL(glDeleteProgram(program->id));
    memset(program, 0, sizeof(*program));
    ngl_free(program);
}

void ngl_program_set(ngl_program *program, size_t index, void const *data) {
    assert(program);
    assert(data);

    NGL__CALL(glUseProgram(program->id));

    ngl__uniform uni = program->uniforms[index];
    switch (uni.type) {
        case NGL_UNIFORM_TYPE_FLOAT: {
            switch (uni.count) {
                float const *v = data;
                case 1: NGL__CALL(glUniform1f(uni.loc, v[0]));                   break;
                case 2: NGL__CALL(glUniform2f(uni.loc, v[0], v[1]));             break;
                case 3: NGL__CALL(glUniform3f(uni.loc, v[0], v[1], v[2]));       break;
                case 4: NGL__CALL(glUniform4f(uni.loc, v[0], v[1], v[2], v[3])); break;
                default:                                                         break;
            }
        } break;

        case NGL_UNIFORM_TYPE_MATRIX: {
            NGL__CALL(glUniformMatrix4fv(uni.loc, 1, uni.transposed, (float const *)data));
        } break;

        default: {
        } break;
    }

    NGL__CALL(glUseProgram(0));
}

ngl_pipeline *ngl_pipeline_create(ngl_pipeline_desc const *desc) {
    assert(desc);
    assert(desc->program);

    ngl_pipeline *pipeline = ngl_calloc(1, sizeof(*pipeline));
    if (!pipeline) {
        return NULL;
    }

    pipeline->desc = *desc;
    return pipeline;
}

void ngl_pipeline_free(ngl_pipeline *pipeline) {
    ngl_free(pipeline);
}

#undef NGL__CALL
#endif // GL_IMPLEMENTATION || IMPLEMENTATION
