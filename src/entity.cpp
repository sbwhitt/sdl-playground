#include <SDL_render.h>
#include <SDL_rect.h>

#include "entity.h"
#include "error.h"
#include "point.h"
#include "vec2.h"

Entity::~Entity() {
    SDL_DestroyTexture(this->sdl_tex);
    this->sdl_tex = NULL;
}

int Entity::LoadFromResource(SDL_Renderer *rend, Resource res) {
    this->sdl_tex = SDL_CreateTextureFromSurface(rend, SDL_LoadBMP(res.file));
    if (this->sdl_tex == nullptr) {
        SDLErrorMsg("SDL error loading texture: ");
        return 1;
    }

    this->dest_rect.x = 0;
    this->dest_rect.y = 0;
    this->dest_rect.w = res.width;
    this->dest_rect.h = res.height;

    return 0;
}

int Entity::Move(int x, int y) {
    this->world_pos.x += x;
    this->world_pos.y += y;

    // printf("player posish: %d, %d\n", this->world_pos.x, this->world_pos.y);

    return 0;
}

int Entity::PlaceOnScreen(Point p) {
    // place at point centered
    this->dest_rect.x = p.x - this->dest_rect.w/2;
    this->dest_rect.y = p.y - this->dest_rect.h/2;

    return 0;
}

Point Entity::GetScreenPosition() {
    // get position centered
    return Point{this->dest_rect.x + this->dest_rect.w/2, this->dest_rect.y + this->dest_rect.h/2};
}

SDL_Rect Entity::GetRect() {
    return this->dest_rect;
}

int Entity::Rotate(int d) {
    // keeping angle between 0 and 360 degrees because... i want to?
    if ((this->angle + d) > 360) {
        this->angle = (this->angle + d) - 360;
    }
    else if ((this->angle + d) < 0) {
        this->angle = (this->angle + d) + 360;
    }
    else this->angle += d;

    return 0;
}

int Entity::Update(Camera cam) {
    Point d = this->world_pos - cam.world_pos;
    this->PlaceOnScreen(d);

    return 0;
}

int Entity::Follow(Point scr_pos) {
    int dx = scr_pos.x - this->dest_rect.w - this->world_pos.x;
    int dy = scr_pos.y - this->dest_rect.h - this->world_pos.y;
    this->Move(dx/4, dy/4);

    return 0;
}

int Entity::Draw(SDL_Renderer *rend, Camera cam) {
    if (cam.Contains(this->GetRect())) {
        if (SDL_RenderCopyEx(rend, this->sdl_tex, NULL, &this->dest_rect, this->angle, NULL, SDL_FLIP_NONE) != 0) {
            SDLErrorMsg("SDL error drawing texture: ");
            return 1;
        }
    }

    return 0;
}
