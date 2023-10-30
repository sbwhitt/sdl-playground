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
    Vec2 vel{0, 0};
    Vec2 acc{0, 0};
    Texture *tex = new Texture();

public:
    Point world_pos{0, 0};
    Hitbox hitbox;

    ~Entity();
    int LoadTexture(Renderer *rend, Resource r);
    int Move(int x, int y);
    int Place(Point p);
    int PlaceOnScreen(Point p);
    Point GetScreenPosition();
    SDL_Rect GetRect();
    bool Collides(Entity *e);
    int Rotate(int d);
    int Update(Camera cam);
    int Follow(Point scr_pos);
    int Draw(Renderer *rend, Camera cam);
};

#endif