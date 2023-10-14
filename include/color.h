#ifndef COLOR_H
#define COLOR_H

#include <SDL_stdinc.h>
#include <stdlib.h>

struct Color {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a = 255;

    Color() {}
    Color(Uint8 red, Uint8 green, Uint8 blue) {
        r = red;
        g = green;
        b = blue;
    }
    Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
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