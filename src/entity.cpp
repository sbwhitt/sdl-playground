#include <algorithm>
#include <SDL_rect.h>

#include "render/renderer.h"
#include "game_objects/entity.h"
#include "geometry/point.h"
#include "geometry/geometry.h"
#include "physics/physics.h"
#include "utils/vec2.h"
#include "utils/error.h"
#include "utils/resource.h"

Entity::Entity() {}

Entity::Entity(EntityType type) {
    this->type = type;
}

Entity::~Entity() {
    delete this->tex;
    this->tex = NULL;
}

int Entity::LoadTexture(Renderer *rend, Resource r) {
    this->tex->LoadFromResource(rend, r);
    this->hitbox = Hitbox{r.width, r.height, this->world_pos};

    return 0;
}

int Entity::AddVelocity(Vec2 v) {
    if (abs(this->vel.x + v.x) < this->MAX_VELOCITY) this->vel.x += v.x;
    if (abs(this->vel.y + v.y) < this->MAX_VELOCITY) this->vel.y += v.y;

    return 0;
}

int Entity::AddVelocity(double x, double y) {
    if (abs(this->vel.x + x) < this->MAX_VELOCITY) this->vel.x += x;
    if (abs(this->vel.y + y) < this->MAX_VELOCITY) this->vel.y += y;

    return 0;
}

int Entity::BuildHitbox(Point center, double angle) {
    this->hitbox.Update(this->world_pos, this->tex->angle);

    return 0;
}

// move by x, y; updates current hitbox position and angle
int Entity::Move(int x, int y) {
    this->world_pos.x += x;
    this->world_pos.y += y;

    this->BuildHitbox(this->world_pos, this->tex->angle);

    return 0;
}

int Entity::Follow(Point pos) {
    int dx = pos.x - this->tex->rect.w - this->world_pos.x;
    int dy = pos.y - this->tex->rect.h - this->world_pos.y;
    // this->Move(dx/4, dy/4);
    if (abs(dx) > 100) this->AddVelocity((dx/abs(dx)) * 0.5, 0);
    if (abs(dy) > 100) this->AddVelocity(0, (dy/abs(dy)) * 0.5);

    return 0;
}

int Entity::Place(Point p) {
    this->world_pos.x = p.x;
    this->world_pos.y = p.y;

    this->BuildHitbox(this->world_pos, this->tex->angle);

    return 0;
}

int Entity::PlaceOnScreen(Point p) {
    // place at point centered
    this->tex->rect.x = p.x - this->tex->rect.w/2;
    this->tex->rect.y = p.y - this->tex->rect.h/2;

    return 0;
}

Point Entity::GetScreenPosition() {
    // get position centered
    return Point{this->tex->rect.x + this->tex->rect.w/2, this->tex->rect.y + this->tex->rect.h/2};
}

SDL_Rect Entity::GetRect() {
    return this->tex->rect;
}

int Entity::Rotate(int d) {
    // keeping tex->angle between 0 and 360 degrees because... i want to?
    if ((this->tex->angle + d) > 360) {
        this->tex->angle = (this->tex->angle + d) - 360;
    }
    else if ((this->tex->angle + d) < 0) {
        this->tex->angle = (this->tex->angle + d) + 360;
    }
    else this->tex->angle += d;

    return 0;
}

int Entity::Update(int dt) {
    this->Move((int)this->vel.x, (int)this->vel.y);

    return 0;
}

int Entity::Draw(Renderer *rend, Camera cam) {
    if (cam.Contains(this->world_pos, this->tex->rect.w, this->tex->rect.h)) {
        // get difference in player and cam world position
        Point d = this->world_pos - cam.world_pos;
        // place player on screen wrt cam center offset by d
        this->PlaceOnScreen(d);
        this->tex->Render(rend);
    }

    return 0;
}
