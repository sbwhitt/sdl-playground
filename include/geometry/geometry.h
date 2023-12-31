#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "geometry/point.h"
#include "geometry/line.h"

int Distance(Point p1, Point p2);
bool Intersects(Line l1, Line l2);
bool GetIntersection(Point p1, Point p2, Point p3, Point p4, Point *res);

#endif