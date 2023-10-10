#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <SDL.h>

#include "circle.h"
#include "point.h"

int DrawLine(SDL_Renderer *rend, Point p1, Point p2);
int DrawPoints(SDL_Renderer *rend, std::vector<Point> points);
int DrawMouseLines(SDL_Renderer *rend, int w, int h);
int DrawTriangle(SDL_Renderer *rend, int length, int x, int y);
int DrawCircle(SDL_Renderer *rend, Point center, int radius);
int DrawCircles(SDL_Renderer *rend, std::vector<Circle> circles);

#endif