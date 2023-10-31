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

Entity::~Entity() {
    delete this->tex;
    this->tex = NULL;
}

int Entity::LoadTexture(Renderer *rend, Resource r) {
    this->tex->LoadFromResource(rend, r);
    this->hitbox = Hitbox{r.width, r.height, this->world_pos};

    return 0;
}

int Entity::Move(int x, int y) {
    this->world_pos.x += x;
    this->world_pos.y += y;

    return 0;
}

int Entity::Place(Point p) {
    this->world_pos.x = p.x;
    this->world_pos.y = p.y;

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

    this->hitbox.Update(this->world_pos, this->tex->angle);

    return 0;
}

int Entity::Follow(Point scr_pos) {
    int dx = scr_pos.x - this->tex->rect.w - this->world_pos.x;
    int dy = scr_pos.y - this->tex->rect.h - this->world_pos.y;
    this->Move(dx/4, dy/4);

    return 0;
}

int Entity::Draw(Renderer *rend, Camera cam) {
    // get difference in player and cam world position
    Point d = this->world_pos - cam.world_pos;
    // place player on screen wrt cam center offset by d
    this->PlaceOnScreen(d);

    if (cam.Contains(this->tex->rect)) {
        this->tex->Render(rend);
    }

    return 0;
}
