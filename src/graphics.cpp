#include <vector>
#include <SDL.h>

#include "render/renderer.h"
#include "render/graphics.h"
#include "geometry/point.h"
#include "geometry/line.h"

int DrawLine(Renderer *rend, Point p1, Point p2) {
    rend->RenderLine(p1.x, p1.y, p2.x, p2.y);

    return 0;
}

int DrawLine(Renderer *rend, Line l) {
    rend->RenderLine(l.start.x, l.start.y, l.end.x, l.end.y);

    return 0;
}

int DrawMouseLines(Renderer *rend, int w, int h) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    DrawLine(rend, Point{0, 0}, Point{x, y});
    DrawLine(rend, Point{w, 0}, Point{x, y});
    DrawLine(rend, Point{0, h}, Point{x, y});
    DrawLine(rend, Point{w, h}, Point{x, y});
    DrawLine(rend, Point{w/2, h}, Point{x, y});
    DrawLine(rend, Point{w, h/2}, Point{x, y});
    DrawLine(rend, Point{w/2, 0}, Point{x, y});
    DrawLine(rend, Point{0, h/2}, Point{x, y});

    return 0;
}

int DrawTriangle(Renderer *rend, int length, int x, int y) {
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
int DrawCircle(Renderer *rend, Point center, int radius) {
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y) {
        rend->RenderPoint(center.x + x, center.y + y);
        rend->RenderPoint(center.x + y, center.y + x);
        rend->RenderPoint(center.x - y, center.y + x);
        rend->RenderPoint(center.x - x, center.y + y);
        rend->RenderPoint(center.x - x, center.y - y);
        rend->RenderPoint(center.x - y, center.y - x);
        rend->RenderPoint(center.x + y, center.y - x);
        rend->RenderPoint(center.x + x, center.y - y);

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

int DrawGradient(Renderer *rend, SDL_Rect r, Color c1, Color c2) {
    rend->SetRenderColor(c1);

    int x1 = r.x;
    int x2 = r.x;
    int y1 = r.y;
    int y2 = r.y + r.h;

    float dr = (float)(c2.r - c1.r) / (float)r.w;
    float dg = (float)(c2.g - c1.g) / (float)r.w;
    float db = (float)(c2.b - c1.b) / (float)r.w;
    float delta_r, delta_g, delta_b = 0.0;

    Color current{c1.r, c1.g, c1.b};
    for (int i = 0; i < r.w; i++) {
        rend->SetRenderColor(current);
    
        rend->RenderLine(x1, y1, x2, y2);
        x1++;
        x2++;

        delta_r += dr;
        if (delta_r <= -1 || delta_r >= 1) {
            current.r += (Uint8)delta_r;
            delta_r = 0.0;
        }

        delta_g += dg;
        if (delta_g <= -1 || delta_g >= 1) {
            current.g += (Uint8)delta_g;
            delta_g = 0.0;
        }

        delta_b += db;
        if (delta_b <= -1 || delta_b >= 1) {
            current.b += (Uint8)delta_b;
            delta_b = 0.0;
        }
    }

    return 0;
}
