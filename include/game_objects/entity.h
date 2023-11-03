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

enum EntityType {
    ENT_PLAYER = 0,
    ENT_OBSTACLE = 1,
    ENT_FOLLOWER = 2,
    ENT_ENEMY = 3
};

class Entity {
protected:
    Texture *tex = new Texture();
    int MAX_VELOCITY = 16;

    int AddVelocity(Vec2 v);
    int AddVelocity(double x, double y);
    int BuildHitbox(Point center, double angle);

public:
    EntityType type;
    Vec2 vel{0, 0};
    Point world_pos{0, 0};
    Hitbox hitbox;

    Entity();
    Entity(EntityType type);
    ~Entity();
    int LoadTexture(Renderer *rend, Resource r);
    int Move(int x, int y);
    int Place(Point p);
    int PlaceOnScreen(Point p);
    Point GetScreenPosition();
    SDL_Rect GetRect();
    int Rotate(int d);
    int Update(int dt);
    int Follow(Point pos);
    int Draw(Renderer *rend, Camera cam);
};

#endif