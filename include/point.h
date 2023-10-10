#ifndef POINT_H
#define POINT_H

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
};

#endif