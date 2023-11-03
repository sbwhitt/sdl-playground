#include <iostream>

#include <SDL_render.h>
#include <SDL_rect.h>

#include "game_objects/camera.h"
#include "geometry/point.h"
#include "render/graphics.h"
#include "render/renderer.h"
#include "game_objects/entity.h"

int Camera::Init(int w, int h) {
    this->width = w;
    this->height = h;
    this->world_pos.x -= this->width/2;
    this->world_pos.y -= this->height/2;

    return 0;
}

Point Camera::GetCenter() {
    return Point{this->world_pos.x + (int)this->width/2, this->world_pos.y + (int)this->height/2};
}

bool Camera::Contains(Point p) {
    SDL_Rect cam_rect;
    cam_rect.x = this->world_pos.x;
    cam_rect.y = this->world_pos.y;
    cam_rect.w = this->width;
    cam_rect.h = this->height;

    return (p.x >= cam_rect.x && p.x <= cam_rect.x + cam_rect.w &&
            p.y >= cam_rect.y && p.y <= cam_rect.y + cam_rect.h);
}

bool Camera::Contains(Point p, int w, int h) {
    SDL_Rect r;
    r.x = p.x; r.y = p.y;
    r.w = w; r.h = h;
    
    return this->Contains(r);
}

bool Camera::Contains(SDL_Rect r) {
    SDL_Rect cam_rect;
    cam_rect.x = this->world_pos.x;
    cam_rect.y = this->world_pos.y;
    cam_rect.w = this->width;
    cam_rect.h = this->height;

    return SDL_HasIntersection(&cam_rect, &r);
}

int Camera::Follow(Point pos) {
    // update cam world pos to follow point
    auto center = this->GetCenter();
    int dx = pos.x - center.x;
    int dy = pos.y - center.y;
    this->Move(dx, dy);

    return 0;
}

int Camera::Move(int x, int y) {
    this->world_pos.x += x;
    this->world_pos.y += y;

    return 0;
}

int Camera::DrawOutline(Renderer *rend) {
    // draw cam center
    rend->SetRenderColor(Color{255, 0, 0});

    DrawCircle(rend, Point{(int)this->width/2, (int)this->height/2}, 10);
    
    SDL_Rect cam_rect;
    cam_rect.x = 0;
    cam_rect.y = 0;
    cam_rect.w = this->width;
    cam_rect.h = this->height;
    rend->RenderRect(cam_rect);

    return 0;
}
