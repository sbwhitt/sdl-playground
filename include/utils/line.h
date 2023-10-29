#ifndef LINE_H
#define LINE_H

#include "utils/point.h"

class Line {
private:
public:
    Point start;
    Point end;

    Line();
    Line(Point start, Point end);
    int RotateAround(double angle, Point c);
    bool Intersects(Line l);
};

#endif