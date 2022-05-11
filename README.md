# Axiom

> ***ax-i-om***\
> Mathematics\
> a statement or proposition on which an abstractly defined structure is based.

Axiom is collection of single header libraries focused on game development. Collectively, the libraries are indented to provide a
jumping-off point for your own engine or game development

Each library is dual licensed under public domain and MIT. Choose whichever best suits your needs.

|                                 library                                 | version |  LoC  |                    description                    |
| :---------------------------------------------------------------------: |:-------:| :---: | ------------------------------------------------- |
| [axiom_app.h](https://github.com/nosbod18/axiom/blob/main/axiom_app.h)  |  0.0.5  |  946  | Platform window, input, and main loop abstraction |
| [axiom_ds.h](https://github.com/nosbod18/axiom/blob/main/axiom_ds.h)    |  0.0.9  |  321  | Generic data structures                           |
| [axiom_ecs.h](https://github.com/nosbod18/axiom/blob/main/axiom_ecs.h)  |  0.0.3  |  545  | Minimal archetypal entity component system        |
| [axiom_gfx.h](https://github.com/nosbod18/axiom/blob/main/axiom_gfx.h)  |  0.0.3  |  472  | OpenGL abstraction                                |
| [axiom_math.h](https://github.com/nosbod18/axiom/blob/main/axiom_math.h)|  0.1.0  |  368  | 2D and 3D vector and matrix math                  |
| [axiom_tui.h](https://github.com/nosbod18/axiom/blob/main/axiom_tui.h)  |  0.0.1  |  143  | Utilities for terminal based interfaces           |

**Total LoC:** 2795

## Features
- No external dependencies
- No inter-dependencies between libraries
- Simple APIs

## Minimal example
Uses `axiom_app.h` to open a window and enter the main loop until the window is closed.
```c
#define AXA_IMPL
#include "axiom_app.h"

axa_desc axa_main(int argc, char **argv) {
    return (axa_desc){0};
}
```
Check out the `examples/` directory for more
