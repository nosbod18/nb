#define AXIOM_MATH_IMPL
#include "axiom_math.h"

int main(void) {
    float2 a = {1.f, 2.f};
    float2 b = {5.f, 6.f};
    float2 c;
    float2_add(c, a, b);
}
