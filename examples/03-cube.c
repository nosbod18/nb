#define tapp_IMPLEMENTATION
#define tgfx_IMPLEMENTATION
#define tm_IMPLEMENTATION
#include "../tiny_app.h"
#include "../tiny_gfx.h"
#include "../tiny_math.h"

float const vertices[] = {
        -1.0f, -1.0f, -1.0f,   1.0f, 0.0f, 0.0f, 1.0f, // North
         1.0f, -1.0f, -1.0f,   1.0f, 0.0f, 0.0f, 1.0f,
         1.0f,  1.0f, -1.0f,   1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,   1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,   0.0f, 1.0f, 0.0f, 1.0f, // South
         1.0f, -1.0f,  1.0f,   0.0f, 1.0f, 0.0f, 1.0f,
         1.0f,  1.0f,  1.0f,   0.0f, 1.0f, 0.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,   0.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,   0.0f, 0.0f, 1.0f, 1.0f, // East
        -1.0f,  1.0f, -1.0f,   0.0f, 0.0f, 1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,   0.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,   0.0f, 0.0f, 1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,   1.0f, 0.5f, 0.0f, 1.0f, // West
         1.0f,  1.0f, -1.0f,   1.0f, 0.5f, 0.0f, 1.0f,
         1.0f,  1.0f,  1.0f,   1.0f, 0.5f, 0.0f, 1.0f,
         1.0f, -1.0f,  1.0f,   1.0f, 0.5f, 0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,   0.0f, 0.5f, 1.0f, 1.0f, // Bottom
        -1.0f, -1.0f,  1.0f,   0.0f, 0.5f, 1.0f, 1.0f,
         1.0f, -1.0f,  1.0f,   0.0f, 0.5f, 1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,   0.0f, 0.5f, 1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,   1.0f, 0.0f, 0.5f, 1.0f, // Top
        -1.0f,  1.0f,  1.0f,   1.0f, 0.0f, 0.5f, 1.0f,
         1.0f,  1.0f,  1.0f,   1.0f, 0.0f, 0.5f, 1.0f,
         1.0f,  1.0f, -1.0f,   1.0f, 0.0f, 0.5f, 1.0f
};

unsigned short const indices[] = {
         0,  1,  2,   0,  2,  3, // North
         6,  5,  4,   7,  6,  4, // South
         8,  9, 10,   8, 10, 11, // East
        14, 13, 12,  15, 14, 12, // West
        16, 17, 18,  16, 18, 19, // Bottom
        22, 21, 20,  23, 22, 20  // Top
};

char const *vss =
        "#version 330 core\n"
        "layout(location = 0) in vec2 aPosition;\n"
        "layout(location = 1) in vec4 aColor;\n"
        "out vec4 vColor;\n"
        "void main(void) {\n"
        "       gl_Position = vec4(aPosition, 0.0, 1.0);\n"
        "       vColor = aColor;\n"
        "}\n";

char const *fss =
        "#version 330 core\n"
        "in vec4 vColor;\n"
        "out vec4 fColor;\n"
        "void main(void) {\n"
        "       fColor = vColor;\n"
        "}\n";


tgfx_Buffer     *cmd = NULL;
tgfx_Buffer     *vbo = NULL;
tgfx_Buffer     *ibo = NULL;
tgfx_Program    *prg = NULL;
tgfx_Pipeline   *pip = NULL;

tm_Vector2 rotation  = {0};


void Init(void) {
        cmd = tgfx_CreateBuffer(&(tgfx_BufferDesc){
                .type = tgfx_BufferType_Command
        });

        vbo = tgfx_CreateBuffer(&(tgfx_BufferDesc){
                .data = vertices,
                .size = sizeof vertices
        });

        ibo = tgfx_CreateBuffer(&(tgfx_BufferDesc){
                .data = indices,
                .size = sizeof indices,
                .type = tgfx_BufferType_Index
        });

        prg = tgfx_CreateProgram(&(tgfx_ProgramDesc){
                .vs.source = vss,
                .fs.source = fss,
        });

        pip = tgfx_CreatePipeline(&(tgfx_PipelineDesc){
                .layout.attributes = {
                        [0] = { .type = tgfx_VertexType_Float, .count = 2 },
                        [1] = { .type = tgfx_VertexType_Float, .count = 4 },
                },
                .program = prg,
        });
}

bool Update(float dt) {
        if (tapp_IsKeyDown(tapp_Key_Escape)) {
                return false;
        }

        float w = tapp_GetWidth();
        float h = tapp_GetHeight();

        tm_Matrix proj     = tm_Perspective(60.0f, w / h, 0.01f, 10.0f);
        tm_Matrix view     = tm_LookAt((tm_Vector3){0.0f, 1.5f, 6.0f}, (tm_Vector3){0}, (tm_Vector3){0.0f, 1.0f, 0.0f});
        tm_Matrix viewProj = tm_MatrixMul(proj, view);

        rotation.x += 1.0f * t;
        rotation.y += 2.0f * t;

        tm_Matrix rxm   = tm_Rotate((tm_Vector3){1.0f, 0.0f, 0.0f}, rotation.x);
        tm_Matrix rym   = tm_Rotate((tm_Vector3){0.0f, 1.0f, 0.0f}, rotation.y);
        tm_Matrix model = tm_MatrixMul(rxm, rym);
        tm_Matrix mvp   = tm_MatrixMul(viewProj, model);

        tgfx_Bindings bind = {
                .vertexBuffers[0] = vbo,
                .indexBuffer = ibo
        };

        tgfx_BeginPass(cmd, &(tgfx_PassDesc){0});
                tgfx_UpdateProgram(prg, 0, &mvp);
                tgfx_UsePipeline(cmd, pip);
                tgfx_UseBindings(cmd, bind);
                tgfx_Draw(cmd, 3, 0);
        tgfx_EndPass(cmd);

        tgfx_SubmitCommands(cmd);
        return true;
}

void Quit(void) {
        tgfx_DeleteBuffer(cmd);
        tgfx_DeleteBuffer(vbo);
        tgfx_DeleteBuffer(ibo);
        tgfx_DeleteProgram(prg);
        tgfx_DeletePipeline(pip);
}


tapp_AppDesc tapp_Main(int argc, char **argv) {
        return (tapp_AppDesc){
                .title    = "Hello Triangle",
                .width    = 640,
                .height   = 480,
                .onInit   = Init,
                .onUpdate = Update,
                .onQuit   = Quit
        };
}
