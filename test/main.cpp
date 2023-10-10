#include <iostream>

#include "vec2.h"

int main(int argc, char **argv) {
    Vec2 v1{1, 1};
    Vec2 v2{0, 1};

    v1 += v2;

    printf("v1: %f, %f\n", v1.x, v1.y);
    printf("v2: %f, %f\n", v2.x, v2.y);
    return 0;
}
