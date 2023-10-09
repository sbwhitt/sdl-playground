#include <SDL.h>

#include "graphics.h"
#include "point.h"

int DrawLine(SDL_Renderer *rend, Point p1, Point p2) {
    SDL_RenderDrawLine(rend, p1.x, p1.y, p2.x, p2.y);

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
