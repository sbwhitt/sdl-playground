#ifndef CIRCLE_H
#define CIRCLE_H

#include "point.h"

struct Circle {
    Point center{0, 0};
    int radius;

    Circle(Point p, int r) {
        center.x = p.x;
        center.y = p.y;
        radius = r;
    }
};

#endif