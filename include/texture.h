#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL_render.h>
#include <SDL_rect.h>

#include "point.h"

class Texture {
private:
    SDL_Texture *sdl_tex;
    SDL_Rect dest_rect;
public:
    int Load(SDL_Renderer *rend, const char *file);
    int Draw(SDL_Renderer *rend, Point pos);
    int Destroy();
};

#endif