#include <SDL.h>

#include "mouse.h"

Point GetMousePosition() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return Point{x, y};
}
