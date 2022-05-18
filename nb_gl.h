/* nb_gl.h - v0.03 - public domain
    An OpenGL wrapper for C/C++

    Table of Contents
    -----------------
    Table of Contents
    Summary
    Usage
    Example
    Documentation
    Version History
    Licence

    Summary
    -------
    TODO

    Usage
    -----
    To use this library, do this in *one* C or C++ file:

        #define NB_GL_IMPLEMENTATION
        #include "nb_gl.h"

    Then include it as normal in all other files.

    Example
    -------
    TODO

    Documentation
    -------------
    TODO

    Version History
    ---------------
    0.03  - Project name change
    0.02  - Changed naming style
    0.01  - Initial version

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

#ifndef _nb_gl_h_
#define _nb_gl_h_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef nbg_usize
    #ifdef nb_usize
        #define nbg_usize nb_usize
    #else
        #include <stddef.h>
        #define nbg_usize size_t
    #endif
#endif

typedef enum nbg_buffer_type {
    NBG_BUFFER_TYPE_VERTEX = 0,
    NBG_BUFFER_TYPE_INDEX,
    NBG_BUFFER_TYPE_COMMAND,
} nbg_buffer_type;

typedef enum nbg_buffer_usage {
    NBG_BUFFER_USAGE_STATIC = 0,
    NBG_BUFFER_USAGE_DYNAMIC,
    NBG_BUFFER_USAGE_STREAM,
} nbg_buffer_usage;

typedef enum nbg_uniform_type {
    NBG_UNIFORM_TYPE_INVALID = 0,
    NBG_UNIFORM_TYPE_FLOAT,
    NBG_UNIFORM_TYPE_MATRIX
} nbg_uniform_type;

typedef enum nbg_vertex_type {
    NBG_VERTEX_TYPE_INVALID = 0,
    NBG_VERTEX_TYPE_INT8,
    NBG_VERTEX_TYPE_UINT8,
    NBG_VERTEX_TYPE_INT16,
    NBG_VERTEX_TYPE_UINT16,
    NBG_VERTEX_TYPE_INT32,
    NBG_VERTEX_TYPE_UINT32,
    NBG_VERTEX_TYPE_FLOAT,
} nbg_vertex_type;

typedef enum nbg_index_type {
    NBG_INDEX_TYPE_UINT32 = 0,
    NBG_INDEX_TYPE_UINT16
} nbg_index_type;

typedef enum nbg_pass_action {
    NBG_PASS_ACTION_DEFAULT = 0,
    NBG_PASS_ACTION_CLEAR,
} nbg_pass_action;

typedef struct nbg_buffer   nbg_buffer;
typedef struct nbg_image    nbg_image;
typedef struct nbg_program  nbg_program;
typedef struct nbg_pipeline nbg_pipeline;

typedef struct nbg_buffer_desc {
    void const *data;
    nbg_usize size;
    nbg_buffer_type type;
    nbg_buffer_usage usage;
} nbg_buffer_desc;

typedef struct nbg_shader_desc {
    struct {
        char const *name;
        nbg_uniform_type type;
    } uniforms[16];
    char const *source;
} nbg_shader_desc;

typedef struct nbg_program_desc {
    nbg_shader_desc vs;
    nbg_shader_desc fs;
} nbg_program_desc;

typedef struct nbg_vertex_desc {
    nbg_vertex_type type;
    int count;
    int offset;
    int normalized;
} nbg_vertex_desc;

typedef struct nbg_pipeline_desc {
    struct {
        nbg_vertex_desc attributes[16];
        int stride;
    } layout;
    nbg_program *program;
    nbg_index_type index_type;
} nbg_pipeline_desc;

typedef struct nbg_pass_desc {
    struct {
        nbg_pass_action action;
        struct { float r, g, b, a; } value;
    } color;
    struct {
        nbg_pass_action action;
        float value;
    } depth;
    struct {
        nbg_pass_action action;
        int value;
    } stencil;
} nbg_pass_desc;

nbg_buffer     *nbg_buffer_create    (nbg_buffer_desc const *desc);
void            nbg_buffer_free     (nbg_buffer *buf);
int             nbg_buffer_set      (nbg_buffer *buf, void const *data, nbg_usize size);
int             nbg_buffer_push     (nbg_buffer *buf, void const *data, nbg_usize size);

nbg_program    *nbg_program_create   (nbg_program_desc const *desc);
void            nbg_program_free    (nbg_program *program);
void            nbg_program_set     (nbg_program *program, nbg_usize index, void const *data);

nbg_pipeline   *nbg_pipeline_create  (nbg_pipeline_desc const *desc);
void            nbg_pipeline_free   (nbg_pipeline *pipeline);

void            nbg_pass_begin      (nbg_buffer *cmdbuf, nbg_pass_desc const *desc);
void            nbg_pass_end        (nbg_buffer *cmdbuf);

void            nbg_buffer_bind     (nbg_buffer *cmdbuf, nbg_buffer *buf);
void            nbg_pipeline_bind   (nbg_buffer *cmdbuf, nbg_pipeline *pipeline);

void            nbg_draw            (nbg_buffer *cmdbuf, int count, int start);
void            nbg_submit          (nbg_buffer *cmdbuf);
void            nbg_present         (void);

#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
************************************************************************************************************************
****                                                                                                               *****
****                                                                                                               *****
****                                                 Implementation                                                *****
****                                                                                                               *****
****                                                                                                               *****
************************************************************************************************************************
***********************************************************************************************************************/

// #if defined(NB_GL_IMPLEMENTATION) || defined(NB_IMPLEMENTATION)
#ifndef _nb_gl_c_
#define _nb_gl_c_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef nbe_assert
    #ifdef nb_assert
        #define nbe_assert nb_assert
    #else
        #include <assert.h>
        #define nbe_assert assert
    #endif
#endif

#ifndef nbe_calloc
    #ifdef nb_calloc
        #define nbe_calloc nb_calloc
    #else
        #include <stdlib.h>
        #define nbe_calloc calloc
    #endif
#endif

#ifndef nbe_free
    #ifdef nb_free
        #define nbe_free nb_free
    #else
        #include <stdlib.h>
        #define nbe_free free
    #endif
#endif

#if defined(__linux__)
        #include <GL/gl.h>
#elif defined(__APPLE__)
        #include <OpenGL/gl.h>
#endif // __linux__ || __APPLE__

typedef struct nbg_buffer {
    nbg_buffer_desc desc;
    unsigned int id;
    int overflowed;
    int capacity;
    int offset;
} nbg_buffer;

typedef struct nbg__uniform {
    int loc;
    int type;
    int count;
    int transposed;
} nbg__uniform;

struct nbg_program {
    nbg__uniform uniforms[16];
    unsigned int id;
};

struct nbg_pipeline {
    nbg_pipeline_desc desc;
};

// ======== OpenGL =============================================

#define NBG__GL(x) while (glGetError() != GL_NO_ERROR); x; nbe_assert(glGetError() == GL_NO_ERROR)

static int nbg_buffer__type(nbg_buffer_type type) {
    switch (type) {
        case NBG_BUFFER_TYPE_VERTEX:    return GL_ARRAY_BUFFER;
        case NBG_BUFFER_TYPE_INDEX:     return GL_ELEMENT_ARRAY_BUFFER;
        default:                        break;
    }
    return 0;
}

static int nbg_buffer__usage(nbg_buffer_usage usage) {
    switch (usage) {
        case NBG_BUFFER_USAGE_STATIC:   return GL_STATIC_DRAW;
        case NBG_BUFFER_USAGE_DYNAMIC:  return GL_DYNAMIC_DRAW;
        case NBG_BUFFER_USAGE_STREAM:   return GL_STREAM_DRAW;
        default:                        break;
    }
    return 0;
}

static int nbg__uniform_type(nbg_uniform_type type) {
    switch (type) {
        case NBG_UNIFORM_TYPE_FLOAT:    return GL_FLOAT;
        case NBG_UNIFORM_TYPE_MATRIX:   return GL_FLOAT;
        default:                        break;
    }
    return 0;
}

static int nbg_vertex__type(nbg_vertex_type type) {
    switch (type) {
        case NBG_VERTEX_TYPE_INT8:      return GL_BYTE;
        case NBG_VERTEX_TYPE_UINT8:     return GL_UNSIGNED_BYTE;
        case NBG_VERTEX_TYPE_INT16:     return GL_SHORT;
        case NBG_VERTEX_TYPE_UINT16:    return GL_UNSIGNED_SHORT;
        case NBG_VERTEX_TYPE_INT32:     return GL_INT;
        case NBG_VERTEX_TYPE_UINT32:    return GL_UNSIGNED_INT;
        case NBG_VERTEX_TYPE_FLOAT:     return GL_FLOAT;
        default:                        break;
    }
    return 0;
}

nbg_buffer *nbg_buffer_create(nbg_buffer_desc const *desc) {
    assert(desc != NULL);

    nbg_buffer *buf = nbe_calloc(1, sizeof(*buf));
    if (buf == NULL) {
        return NULL;
    }

    buf->desc = *desc;
    buf->desc.type  = nbg_buffer__type(desc->type);
    buf->desc.usage = nbg_buffer__usage(desc->usage);

    NBG__GL(glGenBuffers(1, &buf->id));
    NBG__GL(glBindBuffer(buf->desc.type, buf->id));
    NBG__GL(glBufferData(buf->desc.type, buf->desc.size, buf->desc.data, buf->desc.usage));
    NBG__GL(glBindBuffer(buf->desc.type, 0));
    return buf;
}

void nbg_buffer_free(nbg_buffer *buf) {
    assert(buf != NULL);
    NBG__GL(glDeleteBuffers(1, &buf->id));
    memset(buf, 0, sizeof(*buf));
    nbe_free(buf);
}

int nbg_buffer_set(nbg_buffer *buf, void const *data, nbg_usize size) {
    assert(buf != NULL);

    if (size > buf->capacity) {
        return 0;
    }

    NBG__GL(glBindBuffer(buf->desc.type, buf->id));
    NBG__GL(glBufferSubData(buf->desc.type, 0, buf->desc.size, data));
    NBG__GL(glBindBuffer(buf->desc.type, 0));

    buf->desc.size = size;
    return 1;
}

int nbg_buffer_push(nbg_buffer *buf, void const *data, nbg_usize size) {
    assert(buf != NULL);

    if (buf->desc.size + size > buf->capacity) {
        return 0;
    }

    NBG__GL(glBindBuffer(buf->desc.type, buf->id));
    NBG__GL(glBufferSubData(buf->desc.type, buf->offset, buf->desc.size, data));
    NBG__GL(glBindBuffer(buf->desc.type, 0));

    buf->desc.size += size;
    buf->offset += size;
    return 1;
}

static unsigned int nbg__shader_create(char const *src, int type) {
    NBG__GL(unsigned int id = glCreateShader(type));
    NBG__GL(glShaderSource(id, 1, (GLchar const **)&src, NULL));
    NBG__GL(glCompileShader(id));

    int compiled;
    NBG__GL(glGetShaderiv(id, GL_COMPILE_STATUS, &compiled));

    if (compiled == GL_FALSE) {
        char msg[128];
        NBG__GL(glGetShaderInfoLog(id, sizeof(msg), NULL, msg));
        printf("[NBG__GL] Failed to compile shader\n%s\n", msg);
        NBG__GL(glDeleteShader(id));
        return 0;
    }

    return id;
}

nbg_program *nbg_program_create(nbg_program_desc const *desc) {
    assert(desc);

    nbg_program *program = nbe_calloc(1, sizeof(*program));
    if (!program) {
        return NULL;
    }

    unsigned int vs = nbg__shader_create(desc->vs.source, GL_VERTEX_SHADER);
    unsigned int fs = nbg__shader_create(desc->fs.source, GL_FRAGMENT_SHADER);
    if (!vs || !fs) {
        nbg_program_free(program);
        return NULL;
    }

    NBG__GL(program->id = glCreateProgram());
    NBG__GL(glAttachShader(program->id, vs));
    NBG__GL(glAttachShader(program->id, fs));
    NBG__GL(glLinkProgram(program->id));
    NBG__GL(glValidateProgram(program->id));
    NBG__GL(glDetachShader(program->id, vs));
    NBG__GL(glDetachShader(program->id, fs));

    return program;
}

void nbg_program_free(nbg_program *program) {
    NBG__GL(glDeleteProgram(program->id));
    memset(program, 0, sizeof(*program));
    nbe_free(program);
}

void nbg_program_set(nbg_program *program, nbg_usize index, void const *data) {
    assert(program);
    assert(data);

    NBG__GL(glUseProgram(program->id));

    nbg__uniform uni = program->uniforms[index];
    switch (uni.type) {
        case NBG_UNIFORM_TYPE_FLOAT: {
            switch (uni.count) {
                float const *v = data;
                case 1: NBG__GL(glUniform1f(uni.loc, v[0]));                   break;
                case 2: NBG__GL(glUniform2f(uni.loc, v[0], v[1]));             break;
                case 3: NBG__GL(glUniform3f(uni.loc, v[0], v[1], v[2]));       break;
                case 4: NBG__GL(glUniform4f(uni.loc, v[0], v[1], v[2], v[3])); break;
                default:                                                        break;
            }
        } break;

        case NBG_UNIFORM_TYPE_MATRIX: {
            NBG__GL(glUniformMatrix4fv(uni.loc, 1, uni.transposed, (float const *)data));
        } break;

        default: {
        } break;
    }

    NBG__GL(glUseProgram(0));
}

nbg_pipeline *nbg_pipeline_create(nbg_pipeline_desc const *desc) {
    assert(desc);
    assert(desc->program);

    nbg_pipeline *pipeline = nbe_calloc(1, sizeof(*pipeline));
    if (!pipeline) {
        return NULL;
    }

    pipeline->desc = *desc;
    return pipeline;
}

void nbg_pipeline_free(nbg_pipeline *pipeline) {
    nbe_free(pipeline);
}

#ifdef __cplusplus
}
#endif

#endif // !_nb_gl_c_
// #endif // NB_GL_IMPLEMENTATION || NB_IMPLEMENTATION
#endif // !_nb_gl_h_