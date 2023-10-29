#include <math.h>

#include "utils/line.h"

Line::Line() {}

Line::Line(Point start, Point end) {
    this->start = start;
    this->end = end;
}

// https://math.stackexchange.com/questions/2204520/how-do-i-rotate-a-line-segment-in-a-specific-point-on-the-line
int Line::RotateAround(double angle, Point c) {
    double theta = (M_PI/180) * angle;

    double startx = ((start.x - c.x) * cos(theta) - (start.y - c.y) * sin(theta)) + c.x;
    double starty = ((start.x - c.x) * sin(theta) + (start.y - c.y) * cos(theta)) + c.y;

    Point new1{
        (int)round(startx),
        (int)round(starty)
    };

    double endx = ((end.x - c.x) * cos(theta) - (end.y - c.y) * sin(theta)) + c.x;
    double endy = ((end.x - c.x) * sin(theta) + (end.y - c.y) * cos(theta)) + c.y;

    Point new2{
        (int)round(endx),
        (int)round(endy),
    };

    this->start = new1;
    this->end = new2;

    return 0;
}

// https://stackoverflow.com/questions/3838329/how-can-i-check-if-two-segments-intersect
bool ccw(Point a, Point b, Point c) {
    return (c.y - a.y) * (b.x - a.x) > (b.y - a.y) * (c.x - a.x);
}

bool Line::Intersects(Line l) {
    if (this->start == l.start && this->end == l.end) return true;

    return (ccw(this->start, l.start, l.end) != ccw(this->end, l.start, l.end) &&
            ccw(this->start, this->end, l.start) != ccw(this->start, this->end, l.end));

    return false;
}
