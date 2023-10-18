#ifndef ENTITY_H
#define ENTITY_H

#include <SDL_render.h>
#include <SDL_rect.h>

#include "resource.h"
#include "utils/point.h"
#include "utils/vec2.h"
#include "game_objects/camera.h"
#include "texture.h"

class Entity {
protected:
    Vec2 vel{0, 0};
    Vec2 acc{0, 0};
    Texture *tex = new Texture();

public:
    Point world_pos{0, 0};

    ~Entity();
    int LoadTexture(SDL_Renderer *rend, Resource r);
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