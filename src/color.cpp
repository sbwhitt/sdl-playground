#include <SDL_stdinc.h>

#include "utils/color.h"

Color GetRandomColor() {
    return Color{(Uint8)(rand() % 255 + 1), (Uint8)(rand() % 255 + 1), (Uint8)(rand() % 255 + 1)};
}

Color GetColorIncremented(Color c) {
    Uint8 r = c.r + 1;
    Uint8 g = c.g + 1;
    Uint8 b = c.b + 1;

    return Color{r, g, b};
}

Color GetColorDecremented(Color c) {
    Uint8 r = c.r - 1;
    Uint8 g = c.g - 1;
    Uint8 b = c.b - 1;

    return Color{r, g, b};
}
