#include <SDL_render.h>

#include "render.h"
#include "error.h"
#include "color.h"

int SetRenderColor(SDL_Renderer *rend, Color c) {
    if (SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, c.a) != 0) {
        SDLErrorMsg("render.cpp error setting draw color: ");
        return 1;
    }
    return 0;
}
