# tiny_math.h
A header only vector and matrix math library. Depends on `<math.h>` for `sin`, `cos`, `tan`, `sqrt` only.

## Note
All types defined in this library are nothing more that `typedef`'d arrays, and as such new ones cannot be returned from functions.
An `out` variable must be provided to each function where the result is a vector.
## Vector
A vector is defined by the type and number of elements it holds. For example, a vector of 3 floats would be `tm_float3`. Generally, a vector
of type T that holds N elements is defined as `tm_TN`.

### API
```c
void tm_TN_copy   (tm_TN out, tm_TN a)
void tm_TN_add    (tm_TN out, tm_TN a, tm_TN b)
void tm_TN_sub    (tm_TN out, tm_TN a, tm_TN b)
void tm_TN_mul    (tm_TN out, tm_TN a, tm_TN b)
void tm_TN_div    (tm_TN out, tm_TN a, tm_TN b)
void tm_TN_adds   (tm_TN out, tm_TN a, T b)
void tm_TN_subs   (tm_TN out, tm_TN a, T b)
void tm_TN_muls   (tm_TN out, tm_TN a, T b)
void tm_TN_divs   (tm_TN out, tm_TN a, T b)
T    tm_TN_dot    (tm_TN a, tm_TN b)
T    tm_TN_mag2   (tm_TN a) // Returns the magnitude of `a` squared
T    tm_TN_mag    (tm_TN a)
T    tm_TN_min_val(tm_TN a) // Returns the smallest component of `a`
T    tm_TN_max_val(tm_TN a) // Returns the largest component of `a`
void tm_TN_min    (tm_TN out, tm_TN a, tm_TN b)
void tm_TN_max    (tm_TN out, tm_TN a, tm_TN b)
void tm_TN_norm   (tm_TN out, tm_TN a, tm_TN b)
```
#### Dimension specific functions
```c
void tm_T2_rotate   (tm_T2 out, tm_T2 a, T degrees)
void tm_T3_cross    (tm_T3 out, tm_T3 a, tm_T3 b)
```
## Matrix
A matrix is exactly the same as a vector, except it a two demensional array instead of a one dimensional one. A matrix is named the same way
as a vector with a small change to represent the second dimension, e.g. `float4x4` represents a 4x4 matrix of floats. In general, a matrix of
type T and holds R rows and C columns is defined as `tm_TRxC`.

### API
```c
void tm_TRxC_copy   (tm_TRxC out, tm_TRxC a)
void tm_TRxC_add    (tm_TRxC out, tm_TRxC a, tm_TRxC b)
void tm_TRxC_sub    (tm_TRxC out, tm_TRxC a, tm_TRxC b)
void tm_TRxC_mul    (tm_TRxC out, tm_TRxC a, tm_TRxC b)
void tm_TRxC_div    (tm_TRxC out, tm_TRxC a, tm_TRxC b)
void tm_TRxC_adds   (tm_TRxC out, tm_TRxC a, T b)
void tm_TRxC_subs   (tm_TRxC out, tm_TRxC a, T b)
void tm_TRxC_muls   (tm_TRxC out, tm_TRxC a, T b)
void tm_TRxC_divs   (tm_TRxC out, tm_TRxC a, T b)
void tm_TRxC_addn   (tm_TRxC out, int n, tm_TRxC in[]) // These 4 functions operate on `n` matrices passed in as an array
void tm_TRxC_subn   (tm_TRxC out, int n, tm_TRxC in[])
void tm_TRxC_muln   (tm_TRxC out, int n, tm_TRxC in[])
void tm_TRxC_divn   (tm_TRxC out, int n, tm_TRxC in[])
```
#### Dimension specific functions
```c
void tm_T3x3_translate      (tm_T3x3 out, T2 t)
void tm_T3x3_rotate         (tm_T3x3 out, T degrees)
void tm_T3x3_scale          (tm_T3x3 out, T2 s)
void tm_T3x3_scale_uni      (tm_T3x3 out, T s)
void tm_T4x4_translate      (tm_T4x4 out, T3 v)
void tm_T4x4_rotate         (tm_T4x4 out, T3 axis, T degrees)
void tm_T4x4_rotate_x       (tm_T4x4 out, T degrees)
void tm_T4x4_rotate_y       (tm_T4x4 out, T degrees)
void tm_T4x4_rotate_z       (tm_T4x4 out, T degrees)
void tm_T4x4_scale          (tm_T4x4 out, T3 s)
void tm_T4x4_scale_uni      (tm_T4x4 out, T s)
void tm_T4x4_lookat         (tm_T4x4 out, T3 eye, T3 target, T3 up)
void tm_T4x4_perspective    (tm_T4x4 out, T fov_degrees, T aspect, T near, T far)
void tm_T4x4_ortho          (tm_T4x4 out, T left, T right, T bottom, T top, T near, T far)
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
