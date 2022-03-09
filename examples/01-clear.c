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

bool Event(tapp_Event event){
        if (event.type == tapp_EventType_KeyRelease && event.key.sym == tapp_Key_Escape) {
                return false;
        }

        return true;
}

void Update(float dt) {
        float g = pass.colors[0].value.g + 0.01f;
        pass.colors[0].value.g = g > 1.0f ? 0.0f : g;

        tgfx_BeginPass(cmd, &pass);
        tgfx_EndPass(cmd);
        tgfx_SubmitCommands(cmd);
}

void Quit(void) {
        tgfx_DeleteBuffer(cmd);
}

tapp_AppDesc tapp_Main(int argc, char **argv) {
        return (tapp_AppDesc){
                .window.title = "tapp | Clear",
                .onInit       = Init,
                .onEvent      = Event,
                .onUpdate     = Update,
                .onQuit       = Quit
        };
}
