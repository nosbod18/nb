/* axiom_gfx.h - C/C++ OpenGL wrapper - v0.03 - public domain

========================================================================================================================

	YOU MUST

		#define AXIOM_GFX_IMPL

	in EXACTLY _one_ C or C++ file that includes this header, BEFORE the
	include like this:

		#define AXIOM_GFX_IMPL
		#include "axiom_gfx.h"

	All other files should just #include "axiom_gfx.h" without the #define

========================================================================================================================

LICENSE
	This software is placed under the public domain. See the end of this file
    for the full license.

CREDITS
	Written by Evan Dobson

TODOS
    -

VERSION HISTORY
    0.03  - Project name change
    0.02  - Changed naming style
    0.01  - Initial version
*/

#ifndef AXIOM_GFX_H_
#define AXIOM_GFX_H_

#include <stdbool.h>
#include <stddef.h>  // size_t

typedef enum gfx_buffer_type {
    GFX_BUFFER_TYPE_VERTEX = 0,
    GFX_BUFFER_TYPE_INDEX,
    GFX_BUFFER_TYPE_COMMAND,
} gfx_buffer_type;

typedef enum gfx_buffer_usage {
    GFX_BUFFER_USAGE_STATIC = 0,
    GFX_BUFFER_USAGE_DYNAMIC,
    GFX_BUFFER_USAGE_STREAM,
} gfx_buffer_usage;

typedef enum gfx_uniform_type {
    GFX_UNIFORM_TYPE_INVALID = 0,
    GFX_UNIFORM_TYPE_FLOAT,
    GFX_UNIFORM_TYPE_MATRIX
} gfx_uniform_type;

typedef enum gfx_vertex_type {
    GFX_VERTEX_TYPE_INVALID = 0,
    GFX_VERTEX_TYPE_INT8,
    GFX_VERTEX_TYPE_UINT8,
    GFX_VERTEX_TYPE_INT16,
    GFX_VERTEX_TYPE_UINT16,
    GFX_VERTEX_TYPE_INT32,
    GFX_VERTEX_TYPE_UINT32,
    GFX_VERTEX_TYPE_FLOAT,
} gfx_vertex_type;

typedef enum gfx_index_type {
    GFX_INDEX_TYPE_UINT32 = 0,
    GFX_INDEX_TYPE_UINT16
} gfx_index_type;

typedef enum gfx_pass_action {
    GFX_PASS_ACTION_DEFAULT = 0,
    GFX_PASS_ACTION_CLEAR,
} gfx_pass_action;

typedef struct gfx_buffer gfx_buffer;
typedef struct gfx_image gfx_image;
typedef struct gfx_program gfx_program;
typedef struct gfx_pipeline gfx_pipeline;

typedef struct gfx_buffer_desc {
    void const *data;
    size_t size;
    gfx_buffer_type type;
    gfx_buffer_usage usage;
} gfx_buffer_desc;

typedef struct gfx_shader_desc {
    struct {
        char const *name;
        gfx_uniform_type type;
    } uniforms[16];
    char const *source;
} gfx_shader_desc;

typedef struct gfx_program_desc {
    gfx_shader_desc vs;
    gfx_shader_desc fs;
} gfx_program_desc;

typedef struct gfx_vertex_desc {
    gfx_vertex_type type;
    int count;
    int offset;
    bool normalized;
} gfx_vertex_desc;

typedef struct gfx_pipeline_desc {
    struct {
        gfx_vertex_desc attributes[16];
        int stride;
    } layout;
    gfx_program *program;
    gfx_index_type index_type;
} gfx_pipeline_desc;

typedef struct gfx_pass_desc {
    struct {
        gfx_pass_action action;
        struct { float r, g, b, a; } value;
    } colors[4];
    struct {
        gfx_pass_action action;
        float value;
    } depth;
    struct {
        gfx_pass_action action;
        int value;
    } stencil;
} gfx_pass_desc;


gfx_buffer     *gfx_buffer_alloc    (gfx_buffer_desc const *desc);
void            gfx_buffer_free     (gfx_buffer *buf);
bool            gfx_buffer_set      (gfx_buffer *buf, void const *data, size_t size);
bool            gfx_buffer_push     (gfx_buffer *buf, void const *data, size_t size);

gfx_program    *gfx_program_alloc   (gfx_program_desc const *desc);
void            gfx_program_free    (gfx_program *program);
void            gfx_program_set     (gfx_program *program, size_t index, void const *data);

gfx_pipeline   *gfx_pipeline_alloc  (gfx_pipeline_desc const *desc);
void            gfx_pipeline_free   (gfx_pipeline *pipeline);

void            gfx_pass_begin      (gfx_buffer *cmdbuf, gfx_pass_desc const *desc);
void            gfx_pass_end        (gfx_buffer *cmdbuf);

void            gfx_buffer_bind     (gfx_buffer *cmdbuf, gfx_buffer *buf);
void            gfx_pipeline_bind   (gfx_buffer *cmdbuf, gfx_pipeline *pipeline);

void            gfx_draw            (gfx_buffer *cmdbuf, int count, int start, int numInstances);
void            gfx_submit          (gfx_buffer *cmdbuf);
void            gfx_present         (void);


/***********************************************************************************************************************
************************************************************************************************************************
****                                                                                                               *****
****                                                                                                               *****
****                                                 Implementation                                                *****
****                                                                                                               *****
****                                                                                                               *****
************************************************************************************************************************
***********************************************************************************************************************/


#if defined(AXIOM_GFX_IMPL) || defined(AXIOM_IMPL)
#ifndef AXIOM_GFX_C_
#define AXIOM_GFX_C_

#include <stdbool.h>
#include <assert.h> // assert
#include <stdlib.h> // malloc, free

#if defined(__linux__)
        #include <GL/gl.h>
#elif defined(__APPLE__)
        #include <OpenGL/gl.h>
#endif // __linux__ || __APPLE__

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;

struct gfx_buffer {
    void *data;
    uint id;
    int capacity;
    int size;
    int type;
    int usage;
    int offset;
};

typedef struct gfx__uniform {
    int  loc;
    int  type;
    int  count;
    bool transposed;
} gfx__uniform;

struct gfx_program {
    gfx__uniform uniforms[16];
    uint id;
};

struct gfx_pipeline {
    gfx_pipeline_desc desc;
};

// ======== OpenGL =============================================

#define GFX__GL(x) while (glGetError() != GL_NO_ERROR); x; assert(glGetError() == GL_NO_ERROR)

static int gfx_buffer__type(gfx_buffer_type type) {
    switch (type) {
        case GFX_BUFFER_TYPE_VERTEX:    return GL_ARRAY_BUFFER;
        case GFX_BUFFER_TYPE_INDEX:     return GL_ELEMENT_ARRAY_BUFFER;
        default:                        break;
    }
    return 0;
}

static int gfx_buffer__usage(gfx_buffer_usage usage) {
    switch (usage) {
        case GFX_BUFFER_USAGE_STATIC:   return GL_STATIC_DRAW;
        case GFX_BUFFER_USAGE_DYNAMIC:  return GL_DYNAMIC_DRAW;
        case GFX_BUFFER_USAGE_STREAM:   return GL_STREAM_DRAW;
        default:                        break;
    }
    return 0;
}

static int gfx__uniform_type(gfx_uniform_type type) {
    switch (type) {
        case GFX_UNIFORM_TYPE_FLOAT:    return GL_FLOAT;
        case GFX_UNIFORM_TYPE_MATRIX:   return GL_FLOAT;
        default:                        break;
    }
    return 0;
}

static int gfx_vertex__type(gfx_vertex_type type) {
    switch (type) {
        case GFX_VERTEX_TYPE_INT8:      return GL_BYTE;
        case GFX_VERTEX_TYPE_UINT8:     return GL_UNSIGNED_BYTE;
        case GFX_VERTEX_TYPE_INT16:     return GL_SHORT;
        case GFX_VERTEX_TYPE_UINT16:    return GL_UNSIGNED_SHORT;
        case GFX_VERTEX_TYPE_INT32:     return GL_INT;
        case GFX_VERTEX_TYPE_UINT32:    return GL_UNSIGNED_INT;
        case GFX_VERTEX_TYPE_FLOAT:     return GL_FLOAT;
        default:                        break;
    }
    return 0;
}

static bool gfx_buffer__init(gfx_buffer *buf) {
    GFX__GL(glGenBuffers(1, &buf->id));
    GFX__GL(glBindBuffer(buf->type, buf->id));
    GFX__GL(glBufferData(buf->type, buf->size, buf->data, buf->usage));
    GFX__GL(glBindBuffer(buf->type, 0));
    return true;
}

static void gfx_buffer__deinit(gfx_buffer *buf) {
    GFX__GL(glDeleteBuffers(1, &buf->id));
}

static void gfx_buffer__push(gfx_buffer *buf, void const *data, size_t pos) {
    GFX__GL(glBindBuffer(buf->type, buf->id));
    GFX__GL(glBufferSubData(buf->type, pos, buf->size, data));
    GFX__GL(glBindBuffer(buf->type, 0));
}

static uint gfx__shader_create(char const *src, int type) {
    GFX__GL(uint id = glCreateShader(type));
    GFX__GL(glShaderSource(id, 1, (GLchar const **)&src, NULL));
    GFX__GL(glCompileShader(id));

    int compiled;
    GFX__GL(glGetShaderiv(id, GL_COMPILE_STATUS, &compiled));

    if (compiled == GL_FALSE) {
        char msg[128];
        GFX__GL(glGetShaderInfoLog(id, sizeof msg, NULL, msg));
        printf("[GFX__GL] Failed to compile shader\n%s\n", msg);
        GFX__GL(glDeleteShader(id));
        return 0;
    }

    return id;
}

bool gfx_program__init(gfx_program *program, char const *vss, char const *fss) {
    uint vs = gfx__shader_create(vss, GL_VERTEX_SHADER);
    uint fs = gfx__shader_create(fss, GL_FRAGMENT_SHADER);
    if (!vs || !fs) {
        return false;
    }
    GFX__GL(glAttachShader(program->id, vs));
    GFX__GL(glAttachShader(program->id, fs));
    GFX__GL(glLinkProgram(program->id));
    GFX__GL(glValidateProgram(program->id));
    GFX__GL(glDetachShader(program->id, vs));
    GFX__GL(glDetachShader(program->id, fs));
    return true;
}

void gfx_program__deinit(gfx_program *program) {
    GFX__GL(glDeleteProgram(program->id));
}

void gfx_program__set(gfx_program *program, size_t i, void const *data) {
    GFX__GL(glUseProgram(program->id));

    gfx__uniform uni = program->uniforms[i];
    switch (uni.type) {
        case GFX_UNIFORM_TYPE_FLOAT: {
            switch (uni.count) {
                float const *v = data;
                case 1: GFX__GL(glUniform1f(uni.loc, v[0]));                   break;
                case 2: GFX__GL(glUniform2f(uni.loc, v[0], v[1]));             break;
                case 3: GFX__GL(glUniform3f(uni.loc, v[0], v[1], v[2]));       break;
                case 4: GFX__GL(glUniform4f(uni.loc, v[0], v[1], v[2], v[3])); break;
                default:                                                        break;
            }
        } break;

        case GFX_UNIFORM_TYPE_MATRIX: {
            GFX__GL(glUniformMatrix4fv(uni.loc, 1, uni.transposed, (float const *)data));
        } break;

        default: {
        } break;
    }

    GFX__GL(glUseProgram(0));
}

// =============================================================

gfx_buffer *gfx_buffer_alloc(gfx_buffer_desc const *desc) {
    assert(desc != NULL);

    gfx_buffer *buf = calloc(1, sizeof *buf);
    if (buf == NULL) {
        return NULL;
    }

    buf->data   = desc->data;
    buf->size   = desc->size;
    buf->type   = gfx_buffer__type(desc->type);
    buf->usage  = gfx_buffer__usage(desc->usage);

    if (gfx_buffer__init(buf) == false) {
        gfx_buffer_free(buf);
        return NULL;
    }

    return buf;
}

void gfx_buffer_free(gfx_buffer *buf) {
    assert(buf != NULL);
    gfx_buffer__deinit(buf);
    free(buf);
    memset(buf, 0, sizeof *buf);
}

bool gfx_buffer_set(gfx_buffer *buf, void const *data, size_t size) {
    assert(buf != NULL);

    if (size > buf->capacity) {
        return false;
    }

    buf->size = size;
    gfx_buffer__push(buf, data, 0);
    return true;
}

bool gfx_buffer_push(gfx_buffer *buf, void const *data, size_t size) {
    assert(buf != NULL);

    if (buf->size + size > buf->capacity) {
        return false;
    }

    buf->offset += size;
    buf->size += size;
    gfx_buffer__push(buf, data, buf->offset);
    return true;
}

gfx_program *gfx_program_alloc(gfx_program_desc const *desc) {
    assert(desc);

    gfx_program *program = malloc(sizeof *program);
    if (!program) {
        return NULL;
    }

    if (!gfx_program__init(program, desc->vs.source, desc->fs.source)) {
        gfx_program_free(program);
        return NULL;
    }
    return program;
}

void gfx_program_free(gfx_program *program) {
    gfx_program__deinit(program);
    free(program);
    memset(program, 0, sizeof *program);
}

void gfx_program_set(gfx_program *program, size_t index, void const *data) {
    assert(program);
    assert(data);
    gfx_program__set(program, index, data);
}

gfx_pipeline *gfx_pipeline_alloc(gfx_pipeline_desc const *desc) {
    assert(desc);
    assert(desc->program);

    gfx_pipeline *pipeline = malloc(sizeof *pipeline);
    if (!pipeline) {
        return NULL;
    }

    pipeline->desc = *desc;
    return pipeline;
}

void gfx_pipeline_free(gfx_pipeline *pipeline) {
    free(pipeline);
}

#endif // !AXIOM_GFX_C_
#endif // AXIOM_GFX_IMPL || AXIOM_IMPL
#endif // !AXIOM_GFX_H_

/// ## License
/// This is free and unencumbered software released into the public domain.
/// Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
/// software, either in source code form or as a compiled binary, for any purpose,
/// commercial or non-commercial, and by any means.
///
/// In jurisdictions that recognize copyright laws, the author or authors of this
/// software dedicate any and all copyright interest in the software to the public
/// domain. We make this dedication for the benefit of the public at large and to
/// the detriment of our heirs and successors. We intend this dedication to be an
/// overt act of relinquishment in perpetuity of all present and future rights to
/// this software under copyright law.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
/// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
/// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///
/// For more information, please refer to <http://unlicense.org/>
