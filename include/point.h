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
};

#endif