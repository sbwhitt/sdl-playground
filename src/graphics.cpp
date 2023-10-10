#include <vector>
#include <SDL.h>

#include "graphics.h"
#include "mouse.h"
#include "point.h"

int DrawLine(SDL_Renderer *rend, Point p1, Point p2) {
    SDL_RenderDrawLine(rend, p1.x, p1.y, p2.x, p2.y);

    return 0;
}

int DrawPoints(SDL_Renderer *rend, std::vector<Point> points) {
    if (points.size() > 0) DrawLine(rend, points.back(), GetMousePosition());
    if (points.size() < 2) return 0;

    for (uint8_t i = 0; i < points.size()-1; i++) {
        DrawLine(rend, points[i], points[i+1]);
    }

    return 0;
}

int DrawMouseLines(SDL_Renderer *rend, int w, int h) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    SDL_RenderDrawLine(rend, 0, 0, x, y);
    SDL_RenderDrawLine(rend, w, 0, x, y);
    SDL_RenderDrawLine(rend, 0, h, x, y);
    SDL_RenderDrawLine(rend, w, h, x, y);
    SDL_RenderDrawLine(rend, w/2, h, x, y);
    SDL_RenderDrawLine(rend, w, h/2, x, y);
    SDL_RenderDrawLine(rend, w/2, 0, x, y);
    SDL_RenderDrawLine(rend, 0, h/2, x, y);

    return 0;
}

int DrawTriangle(SDL_Renderer *rend, int length, int x, int y) {
    Point top_left{x - length, y - length};
    Point top_right{x + length, y - length};
    Point middle{x, y + length};

    DrawLine(rend, top_left, top_right);
    DrawLine(rend, top_right, middle);
    DrawLine(rend, middle, top_left);
    
    return 0;
}

// midpoint circle algorithm
// https://en.wikipedia.org/w/index.php?title=Midpoint_circle_algorithm
int DrawCircle(SDL_Renderer *rend, Point center, int radius) {
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y) {
        SDL_RenderDrawPoint(rend, center.x + x, center.y + y);
        SDL_RenderDrawPoint(rend, center.x + y, center.y + x);
        SDL_RenderDrawPoint(rend, center.x - y, center.y + x);
        SDL_RenderDrawPoint(rend, center.x - x, center.y + y);
        SDL_RenderDrawPoint(rend, center.x - x, center.y - y);
        SDL_RenderDrawPoint(rend, center.x - y, center.y - x);
        SDL_RenderDrawPoint(rend, center.x + y, center.y - x);
        SDL_RenderDrawPoint(rend, center.x + x, center.y - y);

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }    

    return 0;
}
