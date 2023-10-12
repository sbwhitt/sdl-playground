#ifndef CAMERA_H
#define CAMERA_H

#include <SDL_render.h>
#include <SDL_rect.h>

#include "point.h"

class Camera {
private:
    float zoom = 1.0;

public:
    int width;
    int height;
    Point center{0, 0};
    Point world_pos{0, 0};

    int Init(int w, int h);
    bool Contains(SDL_Rect r);
    Point GetPosition();
    int Follow(Point scr_pos);
    int DrawOutline(SDL_Renderer *rend);
    int Move(int x, int y);
};

#endif