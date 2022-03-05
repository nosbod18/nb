#ifndef __tiny_app_h__
#define __tiny_app_h__

#include <stdint.h>
#include <stdbool.h>


typedef struct tapp_AppDesc {
        char const *title;
        int width;
        int height;
        void (*init)(void);
        bool (*update)(float dt);
        void (*quit)(void);
} tapp_AppDesc;


tapp_AppDesc    tapp_Main               (int argc, char **argv);

int             tapp_GetMainWindow      (void);
void            tapp_SetTargetFps       (int fps);

// ---- Input ------------------

bool            tapp_IsKeyDown          (int key);
bool            tapp_IsKeyPressed       (int key);
bool            tapp_IsKeyReleased      (int key);
bool            tapp_IsMouseDown        (int button);
bool            tapp_IsMousePressed     (int button);
bool            tapp_IsMouseReleased    (int button);

void            tapp_GetMousePosition   (float *x, float *y);
void            tapp_GetMouseScroll     (float *x, float *y);
void            tapp_GetMouseDelta      (float *x, float *y);

bool            tapp_IsMouseTrapped     (void);
bool            tapp_IsMouseHidden      (void);
void            tapp_SetMouseTrapped    (bool trapped);
void            tapp_SetMouseHidden     (bool hidden);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                                                                                    ////
////                                                                                                                                                    ////
////                                                                   Implementation                                                                   ////
////                                                                                                                                                    ////
////                                                                                                                                                    ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef tapp_IMPLEMENTATION
#ifndef __tiny_app_c__
#define __tiny_app_c__

typedef struct tapp_Input {
        struct {
                uint64_t keys[4]; // tapp_Key_Last / 64
        } keyboard[2];

        struct {
                uint8_t buttons;
                float xposition, yposition;
                float xscroll, yscroll;
                bool isTrapped;
                bool isHidden;
        } mouse[2];
} tapp_Input;


void   *tapp_CreateWindow       (char const *title, int width, int height);
void    tapp_DeleteWindow       (void *window);
void    tapp_ProcessEvents      (void *window);
void    tapp_Present            (void const *window);


// ---- Entry point ------------

int main(int argc, char **argv) {
        tapp_AppDesc desc = tapp_Main();

        void *window = tapp_CreateWindow(desc.title, desc.width, desc.height);
        float dt = 0.0f;

        while (tapp__ProcessEvents(window)) {
                if (!desc.update(dt)) {
                        break;
                }
        }

        tapp_DeleteWindow(window);
}


#endif // !__tiny_app_c__
#endif // tapp_IMPLEMENTATION
#endif // !__tiny_app_h__

