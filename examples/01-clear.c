#define tapp_IMPLEMENTATION
#define tgfx_IMPLEMENTATION
#include "../tiny_app.h"
#include "../tiny_gfx.h"

tgfx_Buffer    *cmd;
tgfx_PassDesc  pass;

void Init(void) {
        cmd = tgfx_CreateBuffer(&(tgfx_BufferDesc){
                .type = tgfx_BufferType_Command,
        });

        pass = (tgfx_PassDesc) {
                .colors[0] = { .action = tgfx_PassAction_Clear, .value = { 1.0f, 0.0f, 0.0f, 1.0f }}
        };
}

bool Update(float dt) {
        if (tapp_IsKeyDown(tapp_Key_Escape)) {
                return false;
        }

        float g = pass.colors[0].value[2] + 0.01f;
        pass.colors[0].value[2] = g > 1.0f ? 0.0f : g;
        tgfx_BeginPass(cmd, &pass);
        tgfx_EndPass(cmd);
        tgfx_SubmitCommands(cmd);
        return true;
}

tapp_AppDesc tapp_Main(int argc, char **argv) {
        return (tapp_AppDesc){
                .title = "tapp | Clear",
                .width = 640,
                .height = 480,
                .init = Init,
                .update = Update
        };
}
