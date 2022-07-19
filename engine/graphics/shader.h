#pragma once

typedef enum NbShaderStage {
    NbShaderStage_Vertex,
    NbShaderStage_Fragment,
} NbShaderStage;

typedef struct NbShaderDesc {
    const char* label;
    const char* entry;
    const char* source;
    NbShaderStage stage;
    unsigned size;
    unsigned flags;
} NbShaderDesc;

typedef struct NbShader {
    unsigned id;
    unsigned version;
} NbShader;


NbShader    NbShaderCreate     (NbShaderDesc const *desc);
void        NbShaderDelete     (NbShader program);

