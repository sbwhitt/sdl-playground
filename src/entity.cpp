#include <iostream>
#include <SDL_render.h>
#include <SDL_rect.h>

#include "entity.h"
#include "error.h"
#include "point.h"

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
    this->angle += d;

    return 0;
}

int Entity::Draw(SDL_Renderer *rend) {
    if (SDL_RenderCopyEx(rend, this->sdl_tex, NULL, &this->dest_rect, this->angle, NULL, SDL_FLIP_NONE) != 0) {
        SDLErrorMsg("SDL error drawing texture: ");
        return 1;
    }

    return 0;
}
