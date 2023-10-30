#include "geometry/geometry.h"
#include "geometry/point.h"

int Distance(Point p1, Point p2) {
    return (int)( sqrt( pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) ) );
}

// https://stackoverflow.com/questions/3838329/how-can-i-check-if-two-segments-intersect
bool ccw(Point a, Point b, Point c) {
    return (c.y - a.y) * (b.x - a.x) > (b.y - a.y) * (c.x - a.x);
}

bool Intersects(Line l1, Line l2) {
    if (l1.start == l2.start && l1.end == l2.end) return true;

    return (ccw(l1.start, l2.start, l2.end) != ccw(l1.end, l2.start, l2.end) &&
            ccw(l1.start, l1.end, l2.start) != ccw(l1.start, l1.end, l2.end));

    return false;
}

// find point of intersection if it exists and store result in res
bool GetIntersection(Line l1, Line l2, Point *res) {
    Point s1{l1.end.x - l1.start.x, l1.end.y - l1.start.y};
    Point s2{l2.end.x - l2.start.x, l2.end.y - l2.start.y};

    float s = (-s1.y * (l1.start.x - l2.start.x) + s1.x * (l1.start.y - l2.start.y)) / (-s2.x * s1.y + s1.x * s2.y);
    float t = ( s2.x * (l1.start.y - l2.start.y) - s2.y * (l1.start.x - l2.start.x)) / (-s2.x * s1.y + s1.x * s2.y);

    if (s >= 0 and s <= 1 and t >= 0 and t <= 1) {
        if (res != NULL) {
            res->x = l1.start.x + (t * s1.x);
            res->y = l1.start.y + (t * s1.y);
        }
        return true;
    }

    return false;
}
