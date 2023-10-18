#include <SDL_render.h>

#include "render.h"
#include "utils/error.h"
#include "utils/color.h"

int SetRenderColor(SDL_Renderer *rend, Color c) {
    if (SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, c.a) != 0) {
        SDLErrorMsg("render.cpp error setting draw color: ");
        return 1;
    }
    return 0;
}
