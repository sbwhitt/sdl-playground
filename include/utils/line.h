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

        // double startx = c.x + ( ((cos(theta) * -sin(theta))) * (start.x - c.x) );
        // double starty = c.y + ( ((sin(theta) * cos(theta))) * (start.y - c.y) );

        Point new1{
            (int)(startx),
            (int)(starty)
        };

        double endx = ((end.x - c.x) * cos(theta) - (end.y - c.y) * sin(theta)) + c.x;
        double endy = ((end.x - c.x) * sin(theta) + (end.y - c.y) * cos(theta)) + c.y;

        // double endx = c.x + ( ((cos(theta) * -sin(theta))) * (end.x - c.x) );
        // double endy = c.y + ( ((sin(theta) * cos(theta))) * (end.y - c.y) );

        Point new2{
            (int)(endx),
            (int)(endy),
        };

        this->start = new1;
        this->end = new2;

        int l = sqrt(pow(abs(start.x - end.x), 2) + pow(abs(start.y - end.y), 2));
        printf("length of new line: %d\n", l);
        return 0;
    }
};

#endif