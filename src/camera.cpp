#include <iostream>

#include <SDL_render.h>
#include <SDL_rect.h>

#include "game_objects/camera.h"
#include "utils/point.h"
#include "render/graphics.h"
#include "game_objects/entity.h"

int Camera::Init(int w, int h) {
    this->width = w;
    this->height = h;

    return 0;
}

Point Camera::GetCenter() {
    return Point{(int)this->width/2, (int)this->height/2};
}

bool Camera::Contains(SDL_Rect r) {
    SDL_Rect cam_rect;
    cam_rect.x = 0;
    cam_rect.y = 0;
    cam_rect.w = this->width;
    cam_rect.h = this->height;

    return SDL_HasIntersection(&cam_rect, &r);
}

int Camera::Follow(Point scr_pos) {
    // update cam world pos to follow point
    auto center = this->GetCenter();
    int dx = scr_pos.x - center.x;
    int dy = scr_pos.y - center.y;
    this->Move(dx, dy);

    return 0;
}

int Camera::Move(int x, int y) {
    this->world_pos.x += x;
    this->world_pos.y += y;

    return 0;
}

int Camera::DrawOutline(SDL_Renderer *rend) {
    // draw cam center
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);

    DrawCircle(rend, Point{(int)this->width/2, (int)this->height/2}, 10);
    
    SDL_Rect cam_rect;
    cam_rect.x = 0;
    cam_rect.y = 0;
    cam_rect.w = this->width;
    cam_rect.h = this->height;
    SDL_RenderDrawRect(rend, &cam_rect);

    return 0;
}
