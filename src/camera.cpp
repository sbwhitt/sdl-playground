#include <iostream>

#include <SDL_render.h>
#include <SDL_rect.h>

#include "camera.h"
#include "point.h"
#include "graphics.h"
#include "entity.h"

int Camera::Init(int w, int h) {
    this->width = w;
    this->height = h;
    this->center = Point{w/2, h/2};

    return 0;
}

bool Camera::Contains(SDL_Rect r) {
    SDL_Rect cam_rect;
    cam_rect.x = this->center.x - (this->width/2);
    cam_rect.y = this->center.y - (this->height/2);
    cam_rect.w = this->width;
    cam_rect.h = this->height;

    return SDL_HasIntersection(&cam_rect, &r);
}

Point Camera::GetPosition() {
    return Point{this->center.x - this->width/2, this->center.y - this->height/2};
}

int Camera::Follow(Entity *ent) {
    // get difference in fish and cam world position
    Point d = ent->world_pos - this->world_pos;
    // place fish on screen wrt cam center offset by d
    ent->PlaceOnScreen(this->center + d);

    // update cam world pos to follow fish
    Point p = ent->GetScreenPosition();
    int dx = p.x - this->center.x;
    int dy = p.y - this->center.y;
    this->Move((int)(dx/8), (int)(dy/8));

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
    DrawCircle(rend, Point{this->center.x, this->center.y}, 10);
    
    SDL_Rect cam_rect;
    cam_rect.x = this->center.x - this->width/2;
    cam_rect.y = this->center.y - this->height/2;
    cam_rect.w = this->width;
    cam_rect.h = this->height;
    SDL_RenderDrawRect(rend, &cam_rect);

    return 0;
}
