#ifndef __tiny_gfx_h__
#define __tiny_gfx_h__

#include <stdbool.h>

typedef enum tgfx_BufferType {
        tgfx_BufferType_Vertex = 0,
        tgfx_BufferType_Index,
        tgfx_BufferType_Command,
} tgfx_BufferType;

typedef enum tgfx_BufferUsage {
        tgfx_BufferUsage_Static = 0,
        tgfx_BufferUsage_Dynamic,
        tgfx_BufferUsage_Stream,
} tgfx_BufferUsage;

typedef enum tgfx_UniformType {
        tgfx_UniformType_Invalid = 0,
        tgfx_UniformType_Float,
        tgfx_UniformType_Matrix
} tgfx_UniformType;

typedef enum tgfx_VertexType {
        tgfx_VertexType_Invalid = 0,
        tgfx_VertexType_Int8,
        tgfx_VertexType_Uint8,
        tgfx_VertexType_Int16,
        tgfx_VertexType_Uint16,
        tgfx_VertexType_Int32,
        tgfx_VertexType_Uint32,
        tgfx_VertexType_Float,
} tgfx_VertexType;

typedef enum tgfx_PassAction {
        tgfx_PassAction_Default = 0,
        tgfx_PassAction_Clear,
} tgfx_PassAction;


typedef struct tgfx_Buffer      tgfx_Buffer;
typedef struct tgfx_Image       tgfx_Image;
typedef struct tgfx_Program     tgfx_Program;
typedef struct tgfx_Pipeline    tgfx_Pipeline;

typedef struct tgfx_Bindings {
        tgfx_Buffer *vertexBuffers[16];
        tgfx_Buffer *indexBuffer;
} tgfx_Bindings;

typedef struct tgfx_BufferDesc {
        void const *data;
        int size;
        tgfx_BufferType type;
        tgfx_BufferUsage usage;
} tgfx_BufferDesc;

typedef struct tgfx_ShaderDesc {
        struct {
                char const *name;
                tgfx_UniformType type;
        } uniforms[16];
        char const *source;
} tgfx_ShaderDesc;

typedef struct tgfx_ProgramDesc {
        tgfx_ShaderDesc vs;
        tgfx_ShaderDesc fs;
} tgfx_ProgramDesc;

typedef struct tgfx_VertexDesc {
        tgfx_VertexType type;
        int count;
        int offset;
        bool normalized;
} tgfx_VertexDesc;

typedef struct tgfx_PipelineDesc {
        struct {
                tgfx_VertexDesc attributes[16];
                int stride;
        } layout;
        tgfx_Program *program;
} tgfx_PipelineDesc;

typedef struct tgfx_PassDesc {
        struct {
                tgfx_PassAction action;
                struct { float r, g, b, a; } value;
        } colors[4];
        struct {
                tgfx_PassAction action;
                float value;
        } depth;
        struct {
                tgfx_PassAction action;
                int value;
        } stencil;
} tgfx_PassDesc;


tgfx_Buffer    *tgfx_CreateBuffer       (tgfx_BufferDesc const *desc);
void            tgfx_DeleteBuffer       (tgfx_Buffer *buffer);
bool            tgfx_UpdateBuffer       (tgfx_Buffer *buffer, void const *data, int size);
bool            tgfx_AppendBuffer       (tgfx_Buffer *buffer, void const *data, int size);

tgfx_Program   *tgfx_CreateProgram      (tgfx_ProgramDesc const *desc);
void            tgfx_DeleteProgram      (tgfx_Program *program);
void            tgfx_UpdateProgram      (tgfx_Program *program, int index, void const *data);

tgfx_Pipeline  *tgfx_CreatePipeline     (tgfx_PipelineDesc const *desc);
void            tgfx_DeletePipeline     (tgfx_Pipeline *pipeline);

void            tgfx_BeginPass          (tgfx_Buffer *cmd, tgfx_PassDesc const *desc);
void            tgfx_EndPass            (tgfx_Buffer *cmd);

void            tgfx_UsePipeline        (tgfx_Buffer *cmd, tgfx_Pipeline *pipeline);
void            tgfx_UseBindings        (tgfx_Buffer *cmd, tgfx_Bindings bindings);

void            tgfx_Draw               (tgfx_Buffer *cmd, int numVertices, int start);
void            tgfx_DrawIndexed        (tgfx_Buffer *cmd, int numIndices, int start);
void            tgfx_DrawInstanced      (tgfx_Buffer *cmd, int numIndices, int start, int numInstances);

void            tgfx_SubmitCommands     (tgfx_Buffer *cmd);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                                                                                    ////
////                                                                                                                                                    ////
////                                                                   Implementation                                                                   ////
////                                                                                                                                                    ////
////                                                                                                                                                    ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef tgfx_IMPLEMENTATION
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


struct tgfx_Buffer {
        void *data;
        uint id;
        int capacity;
        int size;
        int type;
        int offset;
};

typedef struct tgfx_Uniform {
        int  loc;
        int  type;
        int  count;
        bool transposed;
} tgfx_Uniform;


static int tgfx__GetBufferTypeAsGL(tgfx_BufferType type) {
        switch (type) {
                case tgfx_BufferType_Vertex:    return GL_ARRAY_BUFFER;
                case tgfx_BufferType_Index:     return GL_ELEMENT_ARRAY_BUFFER;
                case tgfx_BufferType_Command:   return GL_COMMAND_BUFFER;
                default                         break;
        }
        return 0;
}

static int tgfx__GetBufferUsageAsGL(tgfx_BufferUsage usage) {
        switch (usage) {
                case tgfx_BufferUsage_Static:   return GL_STATIC_DRAW;
                case tgfx_BufferUsage_Dynamic:  return GL_DYNAMIC_DRAW;
                case tgfx_BufferUsage_Stream:   return GL_STREAM_DRAW;
                default:                        break;
        }
        return 0;
}

static int tgfx__GetUniformTypeAsGL(tgfx_UniformType type) {
        switch (type) {
                case tgfx_UniformType_Float:    return GL_FLOAT;
                case tgfx_UniformType_Matrix:   return GL_FLOAT;
                default:                        break;
        }
        return 0;
}

static int tgfx__GetVertexTypeAsGL(tgfx_VertexType type) {
        switch (type) {
                case tgfx_VertexType_Int8:      return GL_BYTE;
                case tgfx_VertexType_Uint8:     return GL_UNSIGNED_BYTE;
                case tgfx_VertexType_Int16:     return GL_SHORT;
                case tgfx_VertexType_Uint16:    return GL_UNSIGNED_SHORT;
                case tgfx_VertexType_Int32:     return GL_INT;
                case tgfx_VertexType_Uint32:    return GL_UNSIGNED_INT;
                case tgfx_VertexType_Float:     return GL_FLOAT;
                default:                        break;
        }
        return 0;
}


tgfx_Buffer *tgfx_CreateBuffer(tgfx_BufferDesc const *desc) {
        assert(desc);

        tgfx_Buffer *buffer = malloc(1, sizeof *buffer);
        if (!buffer) {
                return NULL;
        }

        buffer->data   = desc->data;
        buffer->size   = desc->size;
        buffer->type   = tgfx__GetBufferTypeAsGL(desc->type);
        buffer->useage = tgfx__GetBufferUsageAsGL(desc->useage);

        GL(glGenBuffers(1, &buffer->id));
        GL(glBindBuffer(buffer->type, buffer->id));
        GL(glBufferData(buffer->type, buffer->size, buffer->data, buffer->usage));
        GL(glBindBuffer(buffer->type, 0));
        return buffer;
}

void tgfx_DeleteBuffer(tgfx_Buffer *buffer) {
        assert(buffer);
        GL(glDeleteBuffers(1, &buffer->id));
        free(buffer);
}


bool tgfx_UpdateBuffer(tgfx_Buffer *buffer, void const *data, int size) {
        assert(buffer);

        if (size > buffer->capacity) {
                return false;
        }

        GL(glBindBuffer(buffer->type, buffer->id));
        GL(glBufferSubData(buffer->type, 0, size, data));
        GL(glBindBuffer(buffer->type, 0));
        buffer->size = size;
        return true;

}

bool tgfx_AppendBuffer(tgfx_Buffer *buffer, void const *data, int size) {
        assert(buffer);

        if (buffer->size + size > buffer->capacity) {
                return false;
        }

        GL(glBindBuffer(buffer->type, buffer->id));
        GL(glBufferSubData(buffer->type, buffer->offset, size, data));
        GL(glBindBuffer(buffer->type, 0));
        buffer->offset += size;
        return true;
}

uint tgfx_CreateShader(char const *src, int type) {
        GL(uint id = glCreateShader(type));
        GL(glShaderSource(id, 1, (GLchar const **)&src, NULL));
        GL(glCompileShader(id));

        int compiled;
        GL(glGetShaderiv(id, GL_COMPILE_STATUS, &compiled));

        if (compiled == GL_FALSE) {
                char msg[128];
                GL(glGetShaderInfoLog(id, sizeof msg, NULL, msg));
                printf("[GL] Failed to compile shader\n%s", msg);
                GL(glDeleteShader(id));
                return 0;
        }

        return id;
}

tgfx_Program *tgfx_CreateProgram(tgfx_ProgramDesc const *desc) {
        assert(desc);

        uint vs = tgfx_CreateShader(desc->vs.source, GL_VERTEX_SHADER);
        uint fs = tgfx_CreateShader(desc->fs.source, GL_FRAGMENT_SHADER);

        if (!vs || !fs) {
                return NULL;
        }

        tgfx_Program *program = malloc(sizeof *program);
        if (!program) {
                return NULL;
        }

        GL(glAttachShader(program->id, vs));
        GL(glAttachShader(program->id, fs));
        GL(glLinkProgram(program->id));
        GL(glValidateProgram(program->id));
        GL(glDetachShader(program->id, vs));
        GL(glDetachShader(program->id, fs));

        return program;
}

void tgfx_DeleteProgram(tgfx_Program *program) {
        GL(glDeleteProgram(program->id));
        free(program);
}

void tgfx_UpdateProgram(tgfx_Program *program, int index, void const *data) {
        assert(program);
        asssert(data);

        GL(glUseProgram(program->id));

        tgfx_Uniform uni = program->uniforms[index];
        switch (uni.type) {
                case tgfx_UniformType_Float: {
                        switch (uni.count) {
                                float const *v = data;
                                case 1: GL(glUniform1f(uni.loc, v[0]));                   break;
                                case 2: GL(glUniform2f(uni.loc, v[0], v[1]));             break;
                                case 3: GL(glUniform3f(uni.loc, v[0], v[1], v[2]));       break;
                                case 4: GL(glUniform4f(uni.loc, v[0], v[1], v[2], v[3])); break;
                                default:                                                  break;
                        }
                } break;

                case tgfx_UniformType_Matrix: {
                        GL(glUniformMatrix4fv(uni.loc, 1, uni.transposed, (float const *)data));
                } break;

                default: {
                } break;
        }

        GL(glUseProgram(0));
}

tgfx_Pipeline *tgfx_CreatePipeline(tgfx_PipelineDesc const *desc) {
        assert(desc);
        assert(desc->program);

        tgfx_Pipeline *pipeline = malloc(sizeof *pipeline);
        if (!pipeline) {
                return NULL;
        }

        memcpy(&pipeline->layout, &desc->layout, sizeof pipline->layout);
        pipeline->program = desc->program;

        return pipeline;
}

void tgfx_DeletePipeline(tgfx_Pipeline *pipeline) {
        free(pipeline);
}


#endif // !__tiny_gfx_c__
#endif // tgfx_IMPLEMENTATION
#endif // !__tiny_gfx_h__
