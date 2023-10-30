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

// find point of intersection between two lines if it exists and store result in res
// # https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
bool GetIntersection(Point p1, Point p2, Point p3, Point p4, Point *res) {
    float s1_x = p2.x - p1.x; float s1_y = p2.y - p1.y;
    float s2_x = p4.x - p3.x; float s2_y = p4.y - p3.y;

    float s = (-s1_y * (p1.x - p3.x) + s1_x * (p1.y - p3.y)) / (-s2_x * s1_y + s1_x * s2_y);
    float t = ( s2_x * (p1.y - p3.y) - s2_y * (p1.x - p3.x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 and s <= 1 and t >= 0 and t <= 1) {
        if (res != NULL) {
            float x = (float)p1.x + (t * s1_x);
            float y = (float)p1.y + (t * s1_y);
            res->x = (int)x;
            res->y = (int)y;
        }
        return true;
    }

    return false;
}
