#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL_render.h>
#include <SDL_rect.h>

#include "resource.h"
#include "point.h"

class Texture {
private:
    SDL_Texture *sdl_tex;
    SDL_Rect dest_rect;
public:
    ~Texture();
    int LoadFromResource(SDL_Renderer *rend, Resource res);
    int Move(int x, int y);
    int Draw(SDL_Renderer *rend);
    int Destroy();
};

#endif