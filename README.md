# Tiny
A collection of single header libraries focused on game development. Each library is dual licensed under public domain and MIT.

|                             library                                  | version |  LoC  |                description                        |
| :------------------------------------------------------------------: |:-------:| :---: | ------------------------------------------------- |
| [tiny_app.h](https://github.com/nosbod18/tiny/blob/main/tiny_app.h)  |  0.0.5  |  1007 | Platform window, input, and main loop abstraction |
| [tiny_ds.h](https://github.com/nosbod18/tiny/blob/main/tiny_ds.h)    |  0.0.9  |   303 | Generic data structures                           |
| [tiny_ecs.h](https://github.com/nosbod18/tiny/blob/main/tiny_ecs.h)  |  0.0.3  |   583 | Minimal archetypal entity component system        |
| [tiny_gfx.h](https://github.com/nosbod18/tiny/blob/main/tiny_gfx.h)  |  0.0.3  |   426 | OpenGL abstraction                                |
| [tiny_math.h](https://github.com/nosbod18/tiny/blob/main/tiny_math.h)|  0.1.0  |   357 | 2D and 3D vector and matrix math                  |

**Total LoC (Lines of Code):** 2676

## Features
- No dependencies other than system headers
- Completely independent libraries
- Simple APIs

## Minimal example
Uses `tiny_app.h` to open a window and enter the main loop until the window is closed.
```c
#define TAPP_IMPL
#include "tiny_app.h"

tapp_desc tapp_main(int argc, char **argv) {
        return (tapp_desc){0};
}
```
Check out the `examples/` directory for more
