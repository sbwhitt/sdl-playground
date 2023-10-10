#include <iostream>

#include "camera.h"
#include "texture.h"

int Camera::Init(int w, int h) {
    this->width = w;
    this->height = h;
    this->center = Point{w/2, h/2};

    return 0;
}

bool Camera::Contains(Point p) {
    int x0 = this->center.x - (this->width/2);
    int x1 = this->center.x + (this->width/2);
    int y0 = this->center.y - (this->height/2);
    int y1 = this->center.y + (this->height/2);

    return (p.x >= x0 and p.x <= x1 and p.y >= y0 and p.y <= y1);
}

int Camera::Follow(Point p) {
    this->center.x = p.x;
    this->center.y = p.y;

    return 0;
}
