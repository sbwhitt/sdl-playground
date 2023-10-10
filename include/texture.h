#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL_render.h>
#include <SDL_rect.h>

#include "resource.h"
#include "point.h"

class Texture {
private:
    double angle = 0;
    SDL_Texture *sdl_tex;
    SDL_Rect dest_rect;

public:
    Point world_pos{0, 0};

    ~Texture();
    int LoadFromResource(SDL_Renderer *rend, Resource res);
    int Move(int x, int y);
    int PlaceOnScreen(Point p);
    Point GetScreenPosition();
    SDL_Rect GetRect();
    int Rotate(int d);
    int Draw(SDL_Renderer *rend);
    int Destroy();
};

#endif