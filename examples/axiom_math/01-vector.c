// Notice, `axiom_math.h` is purely header only, no AXM_IMPL required
#include "axiom_math.h"

int main(void) {
    axm_float2 a = {1.f, 2.f};
    axm_float2 b = {5.f, 6.f};
    axm_float2 c;
    axm_float2_add(c, a, b);
}
