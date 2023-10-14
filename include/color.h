#ifndef COLOR_H
#define COLOR_H

#include <stdlib.h>

struct Color {
    int r;
    int g;
    int b;
    int a = 255;

    Color() {}
    Color(int red, int green, int blue) {
        r = red;
        g = green;
        b = blue;
    }
    Color(int red, int green, int blue, int alpha) {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }
};

Color GetRandomColor();
Color GetColorIncremented(Color c);
Color GetColorDecremented(Color c);

#endif