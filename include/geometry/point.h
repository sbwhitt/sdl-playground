#ifndef POINT_H
#define POINT_H

#include <math.h>

struct Point {
    int x;
    int y;

    Point() {}
    Point(int px, int py) {
        x = px;
        y = py;
    }
    Point operator+(Point a) {
        return Point{x + a.x, y + a.y};
    }
    Point operator-(Point a) {
        return Point{x - a.x, y - a.y};
    }
    Point& operator+=(Point v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    bool operator==(Point a) {
        return (x == a.x && y == a.y);
    }
};

#endif