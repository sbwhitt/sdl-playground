#include "color.h"

Color GetRandomColor() {
    return Color{rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1};
}

Color GetColorIncremented(Color c) {
    int r = c.r + 1;
    if (r > 255) r = 0;
    int g = c.g + 1;
    if (g > 255) g = 0;
    int b = c.b + 1;
    if (b > 255) b = 0;

    return Color{r, g, b};
}

Color GetColorDecremented(Color c) {
    int r = c.r - 1;
    if (r < 0) r = 255;
    int g = c.g - 1;
    if (g < 0) g = 255;
    int b = c.b - 1;
    if (b < 0) b = 255;

    return Color{r, g, b};
}
