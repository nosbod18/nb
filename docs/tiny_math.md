# tiny_math.h
A header only vector and matrix math library. Depends on `<math.h>` for `sin`, `cos`, `tan`, `sqrt` only.

## Note
All types defined in this library are nothing more that `typedef`'d arrays, and as such new ones cannot be returned from functions.
An `out` variable must be provided to each function where the result is a vector.
## Defines
#### `TINY_MATH_NO_INLINE`
If `TINY_MATH_NO_INLINE` is defined, inlining won't be done on the functions. `TM_FUNC` can also be defined to whatever the user wants
if a custom function scoping or attribute is wanted.
#### `TINY_MATH_NO_SHORT_NAMES`
If `TINY_MATH_NO_SHORT_NAMES` is defined, each type and function will have the tm_ prefix. This is useful if a function or type
has a naming conflict with another type or function in the project. Alternatively, the user can define `TM_PREFIX` to create a custom
naming prefix, so long as it is of the form `#define TM_PREFIX(x) CUSTOM_PREFIX##x`.
## Vector
A vector is defined by the type and number of elements it holds. For example, a vector of 3 floats would be `float3`. Generally, a vector
of type T that holds N elements is defined as `TN`.

### API
```c
void TN_add    (TN out, TN a, TN b)
void TN_sub    (TN out, TN a, TN b)
void TN_mul    (TN out, TN a, TN b)
void TN_div    (TN out, TN a, TN b)
void TN_adds   (TN out, TN a, T b)
void TN_subs   (TN out, TN a, T b)
void TN_muls   (TN out, TN a, T b)
void TN_divs   (TN out, TN a, T b)
T    TN_dot    (TN a, TN b)
T    TN_mag2   (TN a) // Returns the magnitude of `a` squared
T    TN_mag    (TN a)
T    TN_min_val(TN a) // Returns the smallest component of `a`
T    TN_max_val(TN a) // Returns the largets component of `a`
void TN_min    (Tout, TN a, TN b)
void TN_max    (Tout, TN a, TN b)
void TN_norm   (Tout, TN a, TN b)
```
#### Dimension specific functions
```c
void T2_rotate(T2 out, T2 a, T degrees)
void T3_cross(T3 out, T3 a, T3 b)
```
## Matrix
A matrix is exactly the same as a vector, except it a two demensional array instead of a one dimensional one. A matrix is named the same way
as a vector with a small change to represent the second dimension, e.g. `float4x4` represents a 4x4 matrix of floats. In general, a matrix of
type T and holds R rows and C columns is defined as `TRxC`.

### API
```c
void TRxC_add    (TRxC out, TRxC a, TRxC b)
void TRxC_sub    (TRxC out, TRxC a, TRxC b)
void TRxC_mul    (TRxC out, TRxC a, TRxC b)
void TRxC_div    (TRxC out, TRxC a, TRxC b)
void TRxC_adds   (TRxC out, TRxC a, T b)
void TRxC_subs   (TRxC out, TRxC a, T b)
void TRxC_muls   (TRxC out, TRxC a, T b)
void TRxC_divs   (TRxC out, TRxC a, T b)
void TRxC_addn   (TRxC out, int n, TRxC in[]) // These 4 functions operate on `n` matrices passed in as an array
void TRxC_subn   (TRxC out, int n, TRxC in[])
void TRxC_muln   (TRxC out, int n, TRxC in[])
void TRxC_divn   (TRxC out, int n, TRxC in[])
```
#### Dimension specific functions
```c
void T3x3_translate                 (T3x3 out, T2 t)
void T3x3_rotate                    (T3x3 out, T degrees)
void T3x3_scale                     (T3x3 out, T2 s)
void T3x3_scale_uni                 (T3x3 out, T s)
void T4x4_translate                 (T4x4 out, T3 v)
void T4x4_rotate                    (T4x4 out, T3 axis, T degrees)
void T4x4_rotate_x                  (T4x4 out, T degrees)
void T4x4_rotate_y                  (T4x4 out, T degrees)
void T4x4_rotate_z                  (T4x4 out, T degrees)
void T4x4_scale                     (T4x4 out, T3 s)
void T4x4_scale_uni                 (T4x4 out, T s)
void T4x4_lookat                    (T4x4 out, T3 eye, T3 target, T3 up)
void T4x4_perspective               (T4x4 out, T fov_degrees, T aspect, T near, T far)
void T4x4_perspective_default       (T4x4 out, T aspect)
void T4x4_ortho                     (T4x4 out, T left, T right, T bottom, T top, T near, T far)
void T4x4_ortho_aabb                (T4x4 out, T3 min, T3 max)
void T4x4_ortho_default             (T4x4 out, float aspect)
```
## Predefined types
```c
TM_VECTOR(int,    2)
TM_VECTOR(int,    3)
TM_VECTOR(int,    4)
TM_VECTOR(float,  2)
TM_VECTOR(float,  3)
TM_VECTOR(float,  4)
TM_VECTOR(double, 2)
TM_VECTOR(double, 3)
TM_VECTOR(double, 4)
TM_VECTOR_SPECIFIC(float)
TM_VECTOR_SPECIFIC(double)

TM_MATRIX(float,  3, 3)
TM_MATRIX(float,  4, 4)
TM_MATRIX(double, 3, 3)
TM_MATRIX(double, 4, 4)
TM_MATRIX_SPECIFIC(float)
TM_MATRIX_SPECIFIC(double)
```
## License
This software is available under 2 licenses -- choose whichever you prefer.
#### ALTERNATIVE A - MIT License
Copyright (c) 2022 Evan Dobson
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

#### ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
