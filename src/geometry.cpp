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
