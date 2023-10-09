#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>

#include "point.h"

int DrawLine(SDL_Renderer *rend, Point p1, Point p2);
int DrawTriangle(SDL_Renderer *rend, int length, int x, int y);

#endif