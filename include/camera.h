#ifndef CAMERA_H
#define CAEMRA_H

#include <SDL_rect.h>

#include "point.h"

class Camera {
private:
    float zoom = 1.0;

public:
    int width;
    int height;
    Point center{0, 0};

    int Init(int w, int h);
    bool Contains(SDL_Rect r);
    int Follow(Point p);
};

#endif