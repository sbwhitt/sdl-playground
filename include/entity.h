#ifndef ENTITY_H
#define ENTITY_H

#include <SDL_render.h>
#include <SDL_rect.h>

#include "resource.h"
#include "point.h"
#include "vec2.h"
#include "camera.h"

class Entity {
protected:
    double angle = 0;
    Vec2 vel{0, 0};
    Vec2 acc{0, 0};
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
    int Update(Camera cam);
    int Follow(Point scr_pos);
    int Draw(SDL_Renderer *rend, Camera cam);
};

#endif