# Axiom

> ***ax-i-om***\
> Mathematics\
> a statement or proposition on which an abstractly defined structure is based.

Axiom is collection of single header libraries focused on game development. Collectively, the libraries are indented to provide a
jumping-off point for your own engine or game development

Each library is licensed under the public domain.

|                                 Library                                 | Version |  LoC  |                    Description                    |
| :---------------------------------------------------------------------: |:-------:| :---: | ------------------------------------------------- |
| [axiom_app.h](https://github.com/nosbod18/axiom/blob/main/axiom_app.h)  |  0.06   |  976  | Platform window, input, and main loop abstraction |
| [axiom_ds.h](https://github.com/nosbod18/axiom/blob/main/axiom_ds.h)    |  0.08   |  337  | Generic data structures                           |
| [axiom_ecs.h](https://github.com/nosbod18/axiom/blob/main/axiom_ecs.h)  |  0.03   |  564  | Minimal archetypal entity component system        |
| [axiom_gfx.h](https://github.com/nosbod18/axiom/blob/main/axiom_gfx.h)  |  0.03   |  469  | OpenGL abstraction                                |
| [axiom_math.h](https://github.com/nosbod18/axiom/blob/main/axiom_math.h)|  0.06   |  474  | 2D and 3D vector and matrix math                  |
| [axiom_term.h](https://github.com/nosbod18/axiom/blob/main/axiom_term.h)|  0.01   |  211  | Utilities for terminal based interfaces           |

**Total LoC:** 3031

## Features
- No external dependencies
- No inter-dependencies between libraries
- Simple APIs

## Minimal example
Uses `axiom_app.h` to open a window and enter the main loop until the window is closed.
```c
#define app_IMPL
#include "axiom_app.h"

app_desc app_main(int argc, char **argv) {
    return (app_desc){0};
}
```
Check out the [examples](https://github.com/nosbod18/axiom/blob/main/examples) directory for more

## Naming convention
Since these libraries are single headers, the private implementation and data are still availible to be used in the file where the respective `*_IMPL`
macro is defined. This means some extra care from my end is required to distinctly separate the public interfaces from the private ones. I do this in `Axiom` by way of underscores.
Two consecutive underscores anywhere in a name means that type or function is intended to be private and shouldn't be called by the user's program.