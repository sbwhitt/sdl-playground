#include <iostream>
#include <SDL_rect.h>

#include "camera.h"
#include "texture.h"

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

int Camera::Follow(Point p) {
    this->center.x = p.x;
    this->center.y = p.y;

    return 0;
}
