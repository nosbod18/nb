#define tapp_IMPLEMENTATION
#define tgfx_IMPLEMENTATION
#define tm_IMPLEMENTATION
#include "../tiny_app.h"
#include "../tiny_gfx.h"
#include "../tiny_math.h"

tgfx_Buffer    *cmd = NULL;
tgfx_Buffer    *vbo = NULL;
tgfx_Buffer    *ibo = NULL;
tgfx_Program   *prg = NULL;
tgfx_Pipeline  *pip = NULL;
tm_Vector2      rot  = {0};

void Init(void) {
        cmd = tgfx_CreateBuffer(&(tgfx_BufferDesc){
                .type = tgfx_BufferType_Command
        });

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

        vbo = tgfx_CreateBuffer(&(tgfx_BufferDesc){
                .data = vertices,
                .size = sizeof vertices
        });

        unsigned short const indices[] = {
                 0,  1,  2,   0,  2,  3, // North
                 6,  5,  4,   7,  6,  4, // South
                 8,  9, 10,   8, 10, 11, // East
                14, 13, 12,  15, 14, 12, // West
                16, 17, 18,  16, 18, 19, // Bottom
                22, 21, 20,  23, 22, 20  // Top
        };

        ibo = tgfx_CreateBuffer(&(tgfx_BufferDesc){
                .data = indices,
                .size = sizeof indices,
                .type = tgfx_BufferType_Index
        });

        prg = tgfx_CreateProgram(&(tgfx_ProgramDesc){
                .vs.source =
                        "#version 330 core\n"
                        "layout(location = 0) in vec2 aPosition;\n"
                        "layout(location = 1) in vec4 aColor;\n"
                        "out vec4 vColor;\n"
                        "void main(void) {\n"
                        "       gl_Position = vec4(aPosition, 0.0, 1.0);\n"
                        "       vColor = aColor;\n"
                        "}\n",
                .fs.source =
                        "#version 330 core\n"
                        "in vec4 vColor;\n"
                        "out vec4 fColor;\n"
                        "void main(void) {\n"
                        "       fColor = vColor;\n"
                        "}\n",
        });

        pip = tgfx_CreatePipeline(&(tgfx_PipelineDesc){
                .layout.attributes = {
                        [0] = { .type = tgfx_VertexType_Float, .count = 2 },
                        [1] = { .type = tgfx_VertexType_Float, .count = 4 },
                },
                .program = prg,
        });
}

bool Event(tapp_Event event) {
        if (event.type == tapp_EventType_KeyRelease && event.key.sym == tapp_Key_Escape) {
                return false;
        }

        return true;
}

void Update(float dt) {
        tm_Matrix proj     = tm_Perspective(60.0f, tapp_GetAspectRatio(), 0.01f, 10.0f);
        tm_Matrix view     = tm_LookAt((tm_Vector3){0.0f, 1.5f, 6.0f}, (tm_Vector3){0}, (tm_Vector3){0.0f, 1.0f, 0.0f});
        tm_Matrix viewProj = tm_MatrixMul(proj, view);

        rot.x += 1.0f * dt;
        rot.y += 2.0f * dt;

        tm_Matrix rxm   = tm_Rotate((tm_Vector3){1.0f, 0.0f, 0.0f}, rot.x);
        tm_Matrix rym   = tm_Rotate((tm_Vector3){0.0f, 1.0f, 0.0f}, rot.y);
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
                .window.title   = "Hello Triangle",
                .onInit         = Init,
                .onEvent        = Event,
                .onUpdate       = Update,
                .onQuit         = Quit
        };
}
