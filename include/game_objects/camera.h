#ifndef CAMERA_H
#define CAMERA_H

#include <SDL_render.h>
#include <SDL_rect.h>

#include "utils/point.h"

class Camera {
private:
    float zoom = 1.0;

public:
    int width;
    int height;
    Point world_pos{0, 0};

    int Init(int w, int h);
    Point GetCenter();
    bool Contains(SDL_Rect r);
    int Follow(Point scr_pos);
    int DrawOutline(SDL_Renderer *rend);
    int Move(int x, int y);
};

#endif