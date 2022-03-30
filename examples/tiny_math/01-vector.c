// Notice, `tiny_math.h` is purely header only, no TM_IMPL required
#include "tiny_math.h"

int main(void) {
        tm_float2 a = {1.f, 2.f};
        tm_float2 b = {5.f, 6.f};
        tm_float2 c;
        tm_float2_add(c, a, b);
}

