# tiny
A collection of single header libraries focused on game development

## Features
- No dependencies other than the C Standard Library
- Each library is completely independent from each other

## Libraries

**Total LoC: 1511**

|file|version|LoC|description|
|:--:|:-----:|:-:|-----------|
|[tiny_app.h](https://github.com/nosbod18/tiny/blob/main/tiny_app.h)  |0.3.0|477|Platform window, input and main loop abstraction|
|[tiny_ds.h](https://github.com/nosbod18/tiny/blob/main/tiny_ds.h)    |0.3.0|171|Generic data structures                         |
|[tiny_gfx.h](https://github.com/nosbod18/tiny/blob/main/tiny_gfx.h)  |0.3.0|372|3D graphics                                     |
|[tiny_math.h](https://github.com/nosbod18/tiny/blob/main/tiny_math.h)|0.3.0|491|2D and 3D vector and matrix math                |

## Example
```c
#define TAPP_IMPLEMENTATION
#include "tiny_app.h"

tapp_desc tapp_main(int argc, char **argv) {
        return (tapp_desc){0};
}
```
Check out the `examples` directory for more
