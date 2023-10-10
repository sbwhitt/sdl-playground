#ifndef ENTITY_H
#define ENTITY_H

#include <SDL_render.h>
#include <SDL_rect.h>

#include "resource.h"
#include "point.h"

class Entity {
private:
    double angle = 0;
    SDL_Texture *sdl_tex;
    SDL_Rect dest_rect;

public:
    Point world_pos{0, 0};

    ~Entity();
    int LoadFromResource(SDL_Renderer *rend, Resource res);
    int Move(int x, int y);
    int PlaceOnScreen(Point p);
    Point GetScreenPosition();
    SDL_Rect GetRect();
    int Rotate(int d);
    int Draw(SDL_Renderer *rend);
};

#endif