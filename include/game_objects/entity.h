#ifndef ENTITY_H
#define ENTITY_H

#include <SDL_rect.h>

#include "utils/resource.h"
#include "geometry/point.h"
#include "utils/vec2.h"
#include "game_objects/camera.h"
#include "game_objects/hitbox.h"
#include "render/texture.h"
#include "render/renderer.h"

class Entity {
protected:
    Texture *tex = new Texture();

public:
    Vec2 vel{0, 0};
    Point world_pos{0, 0};
    Hitbox hitbox;

    ~Entity();
    int LoadTexture(Renderer *rend, Resource r);
    int Move(int x, int y);
    int Place(Point p);
    int PlaceOnScreen(Point p);
    Point GetScreenPosition();
    SDL_Rect GetRect();
    int Rotate(int d);
    int Update(int dt);
    int Follow(Point scr_pos);
    int Draw(Renderer *rend, Camera cam);
};

#endif