#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <SDL_rect.h>

#include "utils/color.h"
#include "geometry/point.h"
#include "geometry/line.h"
#include "render/renderer.h"

int DrawLine(Renderer *rend, Point p1, Point p2);
int DrawLine(Renderer *rend, Line l);
int DrawPoints(Renderer *rend, std::vector<Point> points);
int DrawMouseLines(Renderer *rend, int w, int h);
int DrawTriangle(Renderer *rend, int length, int x, int y);
int DrawCircle(Renderer *rend, Point center, int radius);
int DrawGradient(Renderer *rend, SDL_Rect r, Color c1, Color c2);

#endif