#ifndef __tiny_gfx_h__
#define __tiny_gfx_h__

#include <stdbool.h>

typedef enum tgfx_buffer_type {
        TGFX_BUFFER_TYPE_VERTEX = 0,
        TGFX_BUFFER_TYPE_INDEX,
        TGFX_BUFFER_TYPE_COMMAND,
} tgfx_buffer_type;

typedef enum tgfx_buffer_usage {
        TGFX_BUFFER_USAGE_STATIC = 0,
        TGFX_BUFFER_USAGE_DYNAMIC,
        TGFX_BUFFER_USAGE_STREAM,
} tgfx_buffer_usage;

typedef enum tgfx_uniform_type {
        TGFX_UNIFORM_TYPE_INVALID = 0,
        TGFX_UNIFORM_TYPE_FLOAT,
        TGFX_UNIFORM_TYPE_MATRIX
} tgfx_uniform_type;

typedef enum tgfx_vertex_type {
        TGFX_VERTEX_TYPE_INVALID = 0,
        TGFX_VERTEX_TYPE_INT8,
        TGFX_VERTEX_TYPE_UINT8,
        TGFX_VERTEX_TYPE_INT16,
        TGFX_VERTEX_TYPE_UINT16,
        TGFX_VERTEX_TYPE_INT32,
        TGFX_VERTEX_TYPE_UINT32,
        TGFX_VERTEX_TYPE_FLOAT,
} tgfx_vertex_type;

typedef enum tgfx_index_type {
        TGFX_INDEX_TYPE_UINT32 = 0,
        TGFX_INDEX_TYPE_UINT16
} tgfx_index_type;

typedef enum tgfx_pass_action {
        TGFX_PASS_ACTION_DEFAULT = 0,
        TGFX_PASS_ACTION_CLEAR,
} tgfx_pass_action;


typedef struct tgfx_buffer      tgfx_buffer;
typedef struct tgfx_image       tgfx_image;
typedef struct tgfx_program     tgfx_program;
typedef struct tgfx_pipeline    tgfx_pipeline;

typedef struct tgfx_buffer_desc {
        void const *data;
        int size;
        tgfx_buffer_type type;
        tgfx_buffer_usage usage;
} tgfx_buffer_desc;

typedef struct tgfx_shader_desc {
        struct {
                char const *name;
                tgfx_uniform_type type;
        } uniforms[16];
        char const *source;
} tgfx_shader_desc;

typedef struct tgfx_program_desc {
        tgfx_shader_desc vs;
        tgfx_shader_desc fs;
} tgfx_program_desc;

typedef struct tgfx_vertex_desc {
        tgfx_vertex_type type;
        int count;
        int offset;
        bool normalized;
} tgfx_vertex_desc;

typedef struct tgfx_pipeline_desc {
        struct {
                tgfx_vertex_desc attributes[16];
                int stride;
        } layout;
        tgfx_program *program;
        tgfx_index_type index_type;
} tgfx_pipeline_desc;

typedef struct tgfx_pass_desc {
        struct {
                tgfx_pass_action action;
                struct { float r, g, b, a; } value;
        } colors[4];
        struct {
                tgfx_pass_action action;
                float value;
        } depth;
        struct {
                tgfx_pass_action action;
                int value;
        } stencil;
} tgfx_pass_desc;


tgfx_buffer    *tgfx_buffer_create      (tgfx_buffer_desc const *desc);
void            tgfx_buffer_delete      (tgfx_buffer *buffer);
bool            tgfx_buffer_update      (tgfx_buffer *buffer, void const *data, int size);
bool            tgfx_buffer_append      (tgfx_buffer *buffer, void const *data, int size);

tgfx_program   *tgfx_program_create     (tgfx_program_desc const *desc);
void            tgfx_program_delete     (tgfx_program *program);
void            tgfx_program_update     (tgfx_program *program, int index, void const *data);

tgfx_pipeline  *tgfx_pipeline_create    (tgfx_pipeline_desc const *desc);
void            tgfx_pipeline_delete    (tgfx_pipeline *pipeline);

// Commands

void            tgfx_pass_begin         (tgfx_buffer *command, tgfx_pass_desc const *desc);
void            tgfx_pass_end           (tgfx_buffer *command);

void            tgfx_buffer_bind        (tgfx_buffer *command, tgfx_buffer *buffer);
void            tgfx_pipeline_bind      (tgfx_buffer *command, tgfx_pipeline *pipeline);

void            tgfx_draw               (tgfx_buffer *command, int count, int start, int numInstances);
void            tgfx_submit             (tgfx_buffer *command);


/***********************************************************************************************************************************************************
************************************************************************************************************************************************************
****                                                                                                                                                    ****
****                                                                                                                                                    ****
****                                                                   Implementation                                                                   ****
****                                                                                                                                                    ****
****                                                                                                                                                    ****
************************************************************************************************************************************************************
***********************************************************************************************************************************************************/


#if defined(TGFX_IMPL) || defined(TINY_IMPL)
#ifndef __tiny_gfx_c__
#define __tiny_gfx_c__

#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <assert.h>

#ifndef uchar
        #define uchar   unsigned char
        #define ushort  unsigned short
        #define uint    unsigned int
        #define ulong   unsigned long
#endif


struct tgfx_buffer {
        void *data;
        uint id;
        int capacity;
        int size;
        int type;
        int offset;
};

struct tgfx_pipeline {
        tgfx_pipeline_desc desc;
};

typedef struct tgfx_uniform {
        int  loc;
        int  type;
        int  count;
        bool transposed;
} tgfx_uniform;

static int tgfx__gl_buffer_type(tgfx_buffer_type type) {
        switch (type) {
                case TGFX_BUFFER_TYPE_VERTEX:   return TGFX__GL_ARRAY_BUFFER;
                case TGFX_BUFFER_TYPE_INDEX:    return TGFX__GL_ELEMENT_ARRAY_BUFFER;
                default                         break;
        }
        return 0;
}

static int tgfx__gl_buffer_usage(tgfx_buffer_usage usage) {
        switch (usage) {
                case TGFX_BUFFER_USAGE_STATIC:  return TGFX__GL_STATIC_DRAW;
                case TGFX_BUFFER_USAGE_DYNAMIC: return TGFX__GL_DYNAMIC_DRAW;
                case TGFX_BUFFER_USAGE_STREAM:  return TGFX__GL_STREAM_DRAW;
                default:                        break;
        }
        return 0;
}

static int tgfx__gl_uniform_type(tgfx_uniform_type type) {
        switch (type) {
                case TGFX_UNIFORM_TYPE_FLOAT:   return TGFX__GL_FLOAT;
                case TGFX_UNIFORM_TYPE_MATRIX:  return TGFX__GL_FLOAT;
                default:                        break;
        }
        return 0;
}

static int tgfx__gl_vertex_type(tgfx_vertex_type type) {
        switch (type) {
                case TGFX_VERTEX_TYPE_INT8:     return TGFX__GL_BYTE;
                case TGFX_VERTEX_TYPE_UINT8:    return TGFX__GL_UNSIGNED_BYTE;
                case TGFX_VERTEX_TYPE_INT16:    return TGFX__GL_SHORT;
                case TGFX_VERTEX_TYPE_UINT16:   return TGFX__GL_UNSIGNED_SHORT;
                case TGFX_VERTEX_TYPE_INT32:    return TGFX__GL_INT;
                case TGFX_VERTEX_TYPE_UINT32:   return TGFX__GL_UNSIGNED_INT;
                case TGFX_VERTEX_TYPE_FLOAT:    return TGFX__GL_FLOAT;
                default:                        break;
        }
        return 0;
}


tgfx_buffer *tgfx_buffer_create(tgfx_buffer_desc const *desc) {
        assert(desc);

        tgfx_buffer *buffer = malloc(1, sizeof *buffer);
        if (!buffer) {
                return NULL;
        }

        buffer->data   = desc->data;
        buffer->size   = desc->size;
        buffer->type   = tgfx__gl_buffer_type(desc->type);
        buffer->useage = tgfx__gl_buffer_usage(desc->useage);

        TGFX__GL(glGenBuffers(1, &buffer->id));
        TGFX__GL(glBindBuffer(buffer->type, buffer->id));
        TGFX__GL(glBufferData(buffer->type, buffer->size, buffer->data, buffer->usage));
        TGFX__GL(glBindBuffer(buffer->type, 0));
        return buffer;
}

void tgfx_buffer_delete(tgfx_buffer *buffer) {
        assert(buffer);
        TGFX__GL(glDeleteBuffers(1, &buffer->id));
        free(buffer);
}


bool tgfx_buffer_update(tgfx_buffer *buffer, void const *data, int size) {
        assert(buffer);

        if (size > buffer->capacity) {
                return false;
        }

        TGFX__GL(glBindBuffer(buffer->type, buffer->id));
        TGFX__GL(glBufferSubData(buffer->type, 0, size, data));
        TGFX__GL(glBindBuffer(buffer->type, 0));
        buffer->size = size;
        return true;

}

bool tgfx_buffer_append(tgfx_buffer *buffer, void const *data, int size) {
        assert(buffer);

        if (buffer->size + size > buffer->capacity) {
                return false;
        }

        TGFX__GL(glBindBuffer(buffer->type, buffer->id));
        TGFX__GL(glBufferSubData(buffer->type, buffer->offset, size, data));
        TGFX__GL(glBindBuffer(buffer->type, 0));
        buffer->offset += size;
        return true;
}

static uint tgfx__gl_shader_create(char const *src, int type) {
        TGFX__GL(uint id = glCreateShader(type));
        TGFX__GL(glShaderSource(id, 1, (TGFX__GLchar const **)&src, NULL));
        TGFX__GL(glCompileShader(id));

        int compiled;
        TGFX__GL(glGetShaderiv(id, TGFX__GL_COMPILE_STATUS, &compiled));

        if (compiled == TGFX__GL_FALSE) {
                char msg[128];
                TGFX__GL(glGetShaderInfoLog(id, sizeof msg, NULL, msg));
                printf("[TGFX__GL] Failed to compile shader\n%s\n", msg);
                TGFX__GL(glDeleteShader(id));
                return 0;
        }

        return id;
}

tgfx_program *tgfx_program_create(tgfx_program_desc const *desc) {
        assert(desc);

        uint vs = tgfx__gl_shader_create(desc->vs.source, TGFX__GL_VERTEX_SHADER);
        uint fs = tgfx__gl_shader_create(desc->fs.source, TGFX__GL_FRAGMENT_SHADER);

        if (!vs || !fs) {
                return NULL;
        }

        tgfx_program *program = malloc(sizeof *program);
        if (!program) {
                return NULL;
        }

        TGFX__GL(glAttachShader(program->id, vs));
        TGFX__GL(glAttachShader(program->id, fs));
        TGFX__GL(glLinkProgram(program->id));
        TGFX__GL(glValidateProgram(program->id));
        TGFX__GL(glDetachShader(program->id, vs));
        TGFX__GL(glDetachShader(program->id, fs));
        return program;
}

void tgfx_program_delete(tgfx_program *program) {
        TGFX__GL(glDeleteProgram(program->id));
        free(program);
}

void tgfx_program_update(tgfx_program *program, int index, void const *data) {
        assert(program);
        assert(data);

        TGFX__GL(glUseProgram(program->id));

        tgfx_uniform uni = program->uniforms[index];
        switch (uni.type) {
                case TGFX_UNIFORM_TYPE_FLOAT: {
                        switch (uni.count) {
                                float const *v = data;
                                case 1: TGFX__GL(glUniform1f(uni.loc, v[0]));                   break;
                                case 2: TGFX__GL(glUniform2f(uni.loc, v[0], v[1]));             break;
                                case 3: TGFX__GL(glUniform3f(uni.loc, v[0], v[1], v[2]));       break;
                                case 4: TGFX__GL(glUniform4f(uni.loc, v[0], v[1], v[2], v[3])); break;
                                default:                                                        break;
                        }
                } break;

                case TGFX_UNIFORM_TYPE_MATRIX: {
                        TGFX__GL(glUniformMatrix4fv(uni.loc, 1, uni.transposed, (float const *)data));
                } break;

                default: {
                } break;
        }

        TGFX__GL(glUseProgram(0));
}

tgfx_pipeline *tgfx_pipeline_create(tgfx_pipeline_desc const *desc) {
        assert(desc);
        assert(desc->program);

        tgfx_pipeline *pipeline = malloc(sizeof *pipeline);
        if (!pipeline) {
                return NULL;
        }

        pipeline->desc = *desc;
        return pipeline;
}

void tgfx_pipeline_delete(tgfx_pipeline *pipeline) {
        free(pipeline);
}


#endif // !__tiny_gfx_c__
#endif // TGFX_IMPLEMENTATION || TINY_IMPLEMENTATION
#endif // !__tiny_gfx_h__


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
