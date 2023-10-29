#ifndef HITBOX_H
#define HITBOX_H

#include "utils/line.h"
#include "render/renderer.h"

class Hitbox {
private:
    int width;
    int height;
    Point center;
    Line top;
    Line left;
    Line bottom;
    Line right;

public:
    Hitbox();
    Hitbox(int width, int height, Point center);
    int Rotate(double angle);
    int Update(Point c, double angle);
    bool Collides(Hitbox h);
    int Draw(Renderer *rend);
};

#endif