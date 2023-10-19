#include <vector>
#include <SDL.h>

#include "render/render.h"
#include "render/graphics.h"
#include "utils/point.h"

int DrawLine(SDL_Renderer *rend, Point p1, Point p2) {
    SDL_RenderDrawLine(rend, p1.x, p1.y, p2.x, p2.y);

    return 0;
}

// int DrawPoints(SDL_Renderer *rend, std::vector<Point> points) {
//     if (points.size() > 0) DrawLine(rend, points.back(), GetMousePosition());
//     if (points.size() < 2) return 0;

//     for (uint8_t i = 0; i < points.size()-1; i++) {
//         DrawLine(rend, points[i], points[i+1]);
//     }

//     return 0;
// }

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

int DrawGradient(SDL_Renderer *rend, SDL_Rect r, Color c1, Color c2) {
    SetRenderColor(rend, c1);

    int x1 = r.x;
    int x2 = r.x;
    int y1 = r.y;
    int y2 = r.y + r.h;

    // int dr = ((c1.r - c2.r) / r.w);
    // int dg = ((c1.g - c2.g) / r.w);
    // int db = ((c1.b - c2.b) / r.w);

    // Color d{
    //     dr,
    //     dg,
    //     db
    // };
    // Color current{
    //     d.r,
    //     d.g,
    //     d.b
    // };

    for (int i = 0; i < r.w; i++) {
        // SetRenderColor(rend, current);
    
        SDL_RenderDrawLine(rend, x1, y1, x2, y2);
        x1++;
        x2++;

        // current.r += d.r;
        // current.g += d.g;
        // current.b += d.b;
    }

    return 0;
}
