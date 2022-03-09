#define tapp_IMPLEMENTATION
#define tgfx_IMPLEMENTATION
#include "../tiny_app.h"
#include "../tiny_gfx.h"

tgfx_Buffer   *cmd = NULL;
tgfx_Buffer   *vbo = NULL;
tgfx_Program  *prg = NULL;
tgfx_Pipeline *pip = NULL;

void Init(void) {
        cmd = tgfx_CreateBuffer(&(tgfx_BufferDesc){
                .type = tgfx_BufferType_Command
        });

        float const vertices[] = {
                 0.0f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f,
                 0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
                -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
        };

        vbo = tgfx_CreateBuffer(&(tgfx_BufferDesc){
                .data = vertices,
                .size = sizeof vertices,
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
        tgfx_Bindings bind = {
                .vertexBuffers[0] = vbo,
        };

        tgfx_BeginPass(cmd, &(tgfx_PassDesc){0});
                tgfx_UsePipeline(cmd, pip);
                tgfx_UseBindings(cmd, bind);
                tgfx_Draw(cmd, 3, 0);
        tgfx_EndPass(cmd);

        tgfx_SubmitCommands(cmd);
}

void Quit(void) {
        tgfx_DeleteBuffer(cmd);
        tgfx_DeleteBuffer(vbo);
        tgfx_DeleteProgram(prg);
        tgfx_DeletePipeline(pip);
}

tapp_AppDesc tapp_Main(int argc, char **argv) {
        return (tapp_AppDesc){
                .window.title   = "tapp | Hello Triangle",
                .onInit         = Init,
                .onUpdate       = Update,
                .onQuit         = Quit
        };
}
