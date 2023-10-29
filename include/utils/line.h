#ifndef LINE_H
#define LINE_H

#include <math.h>

#include "utils/point.h"

struct Line {
    Point start;
    Point end;

    Line() {}
    Line(Point start, Point end) {
        this->start = start;
        this->end = end;
    }
    // https://math.stackexchange.com/questions/2443566/rotate-a-line-around-a-point-in-space
    // https://math.stackexchange.com/questions/2204520/how-do-i-rotate-a-line-segment-in-a-specific-point-on-the-line
    int RotateAround(double angle, Point c) {
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

        // int l = sqrt(pow(abs(start.x - end.x), 2) + pow(abs(start.y - end.y), 2));
        // printf("length of new line: %d\n", l);
        return 0;
    }
    bool Intersects(Line l) {
        if (this->start == l.start && this->end == l.end) return true;

        if (
            (
                l.start.x <= this->start.x &&
                ( 
                    (l.start.y >= this->start.y && l.start.y <= this->end.y) ||
                    (l.start.y <= this->start.y && l.start.y >= this->end.y)
                ) &&
                l.end.x >= this->start.x &&
                (
                    (l.end.y >= this->start.y && l.end.y <= this->end.y) ||
                    (l.end.y <= this->start.y && l.end.y >= this->end.y)
                )
            )
        ) {
            return true;
        }

        return false;
    }
};

#endif