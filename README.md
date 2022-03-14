# tiny
A collection of single header libraries focused on game development. Each library is dual licensed under
the public domain or MIT. Documentation generated using [microdoc](https://github.com/nosbod18/microdoc)
is provided for each library under the `docs/` directory

|                             library                                  | version | LoC |                description                        |
| :------------------------------------------------------------------: |:-------:| :-: | ------------------------------------------------- |
| [tiny_app.h](https://github.com/nosbod18/tiny/blob/main/tiny_app.h)  |  0.0.5  | 408 | Platform window, input, and main loop abstraction |
| [tiny_ds.h](https://github.com/nosbod18/tiny/blob/main/tiny_ds.h)    |  0.0.8  | 328 | Generic data structures                           |
| [tiny_gfx.h](https://github.com/nosbod18/tiny/blob/main/tiny_gfx.h)  |  0.0.3  | 370 | 3D graphics API wrapper                           |
| [tiny_math.h](https://github.com/nosbod18/tiny/blob/main/tiny_math.h)|  0.1.0  | 452 | 2D and 3D vector and matrix math                  |

**Total LoC:** 1558

## Features
- No dependencies other than the C Standard Library
- Each library is completely independent from each other

## Minimal example
Opens a window using `tiny_app.h` and enters the main loop until the window is closed.
```c
#define TINY_APP_IMPL
#include "tiny_app.h"

tapp_desc tapp_main(int argc, char **argv) {
        return (tapp_desc){0};
}
```
Check out the `examples` directory for more
