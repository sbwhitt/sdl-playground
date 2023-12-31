#ifndef HITBOX_H
#define HITBOX_H

#include <vector>

#include "geometry/line.h"
#include "render/renderer.h"

class Hitbox {
private:
public:
    Point center;
    // UP, RIGHT, DOWN, LEFT
    std::vector<Line> lines{4};
    int width;
    int height;

    Hitbox();
    Hitbox(int width, int height, Point center);
    int Rotate(double angle);
    int Update(Point c, double angle);
    int Draw(Renderer *rend);
};

#endif