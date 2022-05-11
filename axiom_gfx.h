#ifndef AXIOM_GFX_H_
#define AXIOM_GFX_H_

#include <stdbool.h> // bool
#include <stddef.h>  // size_t

#ifdef __cplusplus
extern "C" {
#endif

typedef enum axg_buffer_type {
    AXG_BUFFER_TYPE_VERTEX = 0,
    AXG_BUFFER_TYPE_INDEX,
    AXG_BUFFER_TYPE_COMMAND,
} axg_buffer_type;

typedef enum axg_buffer_usage {
    AXG_BUFFER_USAGE_STATIC = 0,
    AXG_BUFFER_USAGE_DYNAMIC,
    AXG_BUFFER_USAGE_STREAM,
} axg_buffer_usage;

typedef enum axg_uniform_type {
    AXG_UNIFORM_TYPE_INVALID = 0,
    AXG_UNIFORM_TYPE_FLOAT,
    AXG_UNIFORM_TYPE_MATRIX
} axg_uniform_type;

typedef enum axg_vertex_type {
    AXG_VERTEX_TYPE_INVALID = 0,
    AXG_VERTEX_TYPE_INT8,
    AXG_VERTEX_TYPE_UINT8,
    AXG_VERTEX_TYPE_INT16,
    AXG_VERTEX_TYPE_UINT16,
    AXG_VERTEX_TYPE_INT32,
    AXG_VERTEX_TYPE_UINT32,
    AXG_VERTEX_TYPE_FLOAT,
} axg_vertex_type;

typedef enum axg_index_type {
    AXG_INDEX_TYPE_UINT32 = 0,
    AXG_INDEX_TYPE_UINT16
} axg_index_type;

typedef enum axg_pass_action {
    AXG_PASS_ACTION_DEFAULT = 0,
    AXG_PASS_ACTION_CLEAR,
} axg_pass_action;

typedef struct axg_buffer axg_buffer;
typedef struct axg_image axg_image;
typedef struct axg_program axg_program;
typedef struct axg_pipeline axg_pipeline;

typedef struct axg_buffer_desc {
    void const *data;
    size_t size;
    axg_buffer_type type;
    axg_buffer_usage usage;
} axg_buffer_desc;

typedef struct axg_shader_desc {
    struct {
        char const *name;
        axg_uniform_type type;
    } uniforms[16];
    char const *source;
} axg_shader_desc;

typedef struct axg_program_desc {
    axg_shader_desc vs;
    axg_shader_desc fs;
} axg_program_desc;

typedef struct axg_vertex_desc {
    axg_vertex_type type;
    int count;
    int offset;
    bool normalized;
} axg_vertex_desc;

typedef struct axg_pipeline_desc {
    struct {
        axg_vertex_desc attributes[16];
        int stride;
    } layout;
    axg_program *program;
    axg_index_type index_type;
} axg_pipeline_desc;

typedef struct axg_pass_desc {
    struct {
        axg_pass_action action;
        struct { float r, g, b, a; } value;
    } colors[4];
    struct {
        axg_pass_action action;
        float value;
    } depth;
    struct {
        axg_pass_action action;
        int value;
    } stencil;
} axg_pass_desc;


axg_buffer     *axg_buffer_alloc    (axg_buffer_desc const *desc);
void            axg_buffer_free     (axg_buffer *buf);
bool            axg_buffer_set      (axg_buffer *buf, void const *data, size_t size);
bool            axg_buffer_push     (axg_buffer *buf, void const *data, size_t size);

axg_program    *axg_program_alloc   (axg_program_desc const *desc);
void            axg_program_free    (axg_program *program);
void            axg_program_set     (axg_program *program, size_t index, void const *data);

axg_pipeline   *axg_pipeline_alloc  (axg_pipeline_desc const *desc);
void            axg_pipeline_free   (axg_pipeline *pipeline);

// Commands

void            axg_pass_begin      (axg_buffer *cmdbuf, axg_pass_desc const *desc);
void            axg_pass_end        (axg_buffer *cmdbuf);

void            axg_buffer_bind     (axg_buffer *cmdbuf, axg_buffer *buf);
void            axg_pipeline_bind   (axg_buffer *cmdbuf, axg_pipeline *pipeline);

void            axg_draw            (axg_buffer *cmdbuf, int count, int start, int numInstances);
void            axg_submit          (axg_buffer *cmdbuf);
void            axg_present         (void);

#ifdef __cplusplus
}
#endif


/*************************************************************************************************************************************************************
**************************************************************************************************************************************************************
****                                                                                                                                                      ****
****                                                                                                                                                      ****
****                                                                    Implementation                                                                    ****
****                                                                                                                                                      ****
****                                                                                                                                                      ****
**************************************************************************************************************************************************************
*************************************************************************************************************************************************************/


#if defined(AXG_IMPL) || defined(AXIOM_IMPL)
#ifndef AXIOM_GFX_C_
#define AXIOM_GFX_C_

#include <stdlib.h> // malloc, free
#include <assert.h> // assert
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__linux__)
        #include <GL/gl.h>
#elif defined(__APPLE__)
        #include <OpenGL/gl.h>
#endif // __linux__ || __APPLE__

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;

struct axg_buffer {
    void *data;
    uint id;
    int capacity;
    int size;
    int type;
    int usage;
    int offset;
};

typedef struct axg__uniform {
    int  loc;
    int  type;
    int  count;
    bool transposed;
} axg__uniform;

struct axg_program {
    axg__uniform uniforms[16];
    uint id;
};

struct axg_pipeline {
    axg_pipeline_desc desc;
};

// ======== OpenGL =============================================

#define AXG__GL(x) while (glGetError() != GL_NO_ERROR); x; assert(glGetError() == GL_NO_ERROR)

static int axg_buffer__type(axg_buffer_type type) {
    switch (type) {
        case AXG_BUFFER_TYPE_VERTEX:    return GL_ARRAY_BUFFER;
        case AXG_BUFFER_TYPE_INDEX:     return GL_ELEMENT_ARRAY_BUFFER;
        default:                        break;
    }
    return 0;
}

static int axg_buffer__usage(axg_buffer_usage usage) {
    switch (usage) {
        case AXG_BUFFER_USAGE_STATIC:   return GL_STATIC_DRAW;
        case AXG_BUFFER_USAGE_DYNAMIC:  return GL_DYNAMIC_DRAW;
        case AXG_BUFFER_USAGE_STREAM:   return GL_STREAM_DRAW;
        default:                        break;
    }
    return 0;
}

static int axg__uniform_type(axg_uniform_type type) {
    switch (type) {
        case AXG_UNIFORM_TYPE_FLOAT:    return GL_FLOAT;
        case AXG_UNIFORM_TYPE_MATRIX:   return GL_FLOAT;
        default:                        break;
    }
    return 0;
}

static int axg_vertex__type(axg_vertex_type type) {
    switch (type) {
        case AXG_VERTEX_TYPE_INT8:      return GL_BYTE;
        case AXG_VERTEX_TYPE_UINT8:     return GL_UNSIGNED_BYTE;
        case AXG_VERTEX_TYPE_INT16:     return GL_SHORT;
        case AXG_VERTEX_TYPE_UINT16:    return GL_UNSIGNED_SHORT;
        case AXG_VERTEX_TYPE_INT32:     return GL_INT;
        case AXG_VERTEX_TYPE_UINT32:    return GL_UNSIGNED_INT;
        case AXG_VERTEX_TYPE_FLOAT:     return GL_FLOAT;
        default:                        break;
    }
    return 0;
}

static bool axg_buffer__init(axg_buffer *buf) {
    AXG__GL(glGenBuffers(1, &buf->id));
    AXG__GL(glBindBuffer(buf->type, buf->id));
    AXG__GL(glBufferData(buf->type, buf->size, buf->data, buf->usage));
    AXG__GL(glBindBuffer(buf->type, 0));
    return true;
}

static void axg_buffer__deinit(axg_buffer *buf) {
    AXG__GL(glDeleteBuffers(1, &buf->id));
}

static void axg_buffer__push(axg_buffer *buf, void const *data, size_t pos) {
    AXG__GL(glBindBuffer(buf->type, buf->id));
    AXG__GL(glBufferSubData(buf->type, pos, buf->size, data));
    AXG__GL(glBindBuffer(buf->type, 0));
}

static uint axg__shader_create(char const *src, int type) {
    AXG__GL(uint id = glCreateShader(type));
    AXG__GL(glShaderSource(id, 1, (GLchar const **)&src, NULL));
    AXG__GL(glCompileShader(id));

    int compiled;
    AXG__GL(glGetShaderiv(id, GL_COMPILE_STATUS, &compiled));

    if (compiled == GL_FALSE) {
        char msg[128];
        AXG__GL(glGetShaderInfoLog(id, sizeof msg, NULL, msg));
        printf("[AXG__GL] Failed to compile shader\n%s\n", msg);
        AXG__GL(glDeleteShader(id));
        return 0;
    }

    return id;
}

bool axg_program__init(axg_program *program, char const *vss, char const *fss) {
    uint vs = axg__shader_create(vss, GL_VERTEX_SHADER);
    uint fs = axg__shader_create(fss, GL_FRAGMENT_SHADER);
    if (!vs || !fs) {
        return false;
    }
    AXG__GL(glAttachShader(program->id, vs));
    AXG__GL(glAttachShader(program->id, fs));
    AXG__GL(glLinkProgram(program->id));
    AXG__GL(glValidateProgram(program->id));
    AXG__GL(glDetachShader(program->id, vs));
    AXG__GL(glDetachShader(program->id, fs));
    return true;
}

void axg_program__deinit(axg_program *program) {
    AXG__GL(glDeleteProgram(program->id));
}

void axg_program__set(axg_program *program, size_t i, void const *data) {
    AXG__GL(glUseProgram(program->id));

    axg__uniform uni = program->uniforms[i];
    switch (uni.type) {
        case AXG_UNIFORM_TYPE_FLOAT: {
            switch (uni.count) {
                float const *v = data;
                case 1: AXG__GL(glUniform1f(uni.loc, v[0]));                   break;
                case 2: AXG__GL(glUniform2f(uni.loc, v[0], v[1]));             break;
                case 3: AXG__GL(glUniform3f(uni.loc, v[0], v[1], v[2]));       break;
                case 4: AXG__GL(glUniform4f(uni.loc, v[0], v[1], v[2], v[3])); break;
                default:                                                        break;
            }
        } break;

        case AXG_UNIFORM_TYPE_MATRIX: {
            AXG__GL(glUniformMatrix4fv(uni.loc, 1, uni.transposed, (float const *)data));
        } break;

        default: {
        } break;
    }

    AXG__GL(glUseProgram(0));
}

// =============================================================

axg_buffer *axg_buffer_alloc(axg_buffer_desc const *desc) {
    assert(desc != NULL);

    axg_buffer *buf = calloc(1, sizeof *buf);
    if (buf == NULL) {
        return NULL;
    }

    buf->data   = desc->data;
    buf->size   = desc->size;
    buf->type   = axg_buffer__type(desc->type);
    buf->usage  = axg_buffer__usage(desc->usage);

    if (axg_buffer__init(buf) == false) {
        axg_buffer_free(buf);
        return NULL;
    }

    return buf;
}

void axg_buffer_free(axg_buffer *buf) {
    assert(buf != NULL);
    axg_buffer__deinit(buf);
    free(buf);
    memset(buf, 0, sizeof *buf);
}

bool axg_buffer_set(axg_buffer *buf, void const *data, size_t size) {
    assert(buf != NULL);

    if (size > buf->capacity) {
        return false;
    }

    buf->size = size;
    axg_buffer__push(buf, data, 0);
    return true;
}

bool axg_buffer_push(axg_buffer *buf, void const *data, size_t size) {
    assert(buf != NULL);

    if (buf->size + size > buf->capacity) {
        return false;
    }

    buf->offset += size;
    buf->size += size;
    axg_buffer__push(buf, data, buf->offset);
    return true;
}

axg_program *axg_program_alloc(axg_program_desc const *desc) {
    assert(desc);

    axg_program *program = malloc(sizeof *program);
    if (!program) {
        return NULL;
    }

    if (!axg_program__init(program, desc->vs.source, desc->fs.source)) {
        axg_program_free(program);
        return NULL;
    }
    return program;
}

void axg_program_free(axg_program *program) {
    axg_program__deinit(program);
    free(program);
    memset(program, 0, sizeof *program);
}

void axg_program_set(axg_program *program, size_t index, void const *data) {
    assert(program);
    assert(data);
    axg_program__set(program, index, data);
}

axg_pipeline *axg_pipeline_alloc(axg_pipeline_desc const *desc) {
    assert(desc);
    assert(desc->program);

    axg_pipeline *pipeline = malloc(sizeof *pipeline);
    if (!pipeline) {
        return NULL;
    }

    pipeline->desc = *desc;
    return pipeline;
}

void axg_pipeline_free(axg_pipeline *pipeline) {
    free(pipeline);
}


#ifdef __cplusplus
}
#endif

#endif // !AXIOM_GFX_C_
#endif // AXG_IMPL || AXIOM_IMPL
#endif // !AXIOM_GFX_H_


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
