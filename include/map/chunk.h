#ifndef CHUNK_H
#define CHUNK_H

#include <SDL_rect.h>

#include "utils/point.h"
#include "utils/color.h"

struct Chunk {
    SDL_Rect dest_rect;
    Color color;
    Point world_pos{0, 0};

    Chunk() {}
    Chunk(Color c, int w, int h) {
        color = c;
        dest_rect.w = w;
        dest_rect.h = h;
    }
    bool Contains(Point p) {
        bool contains_x = p.x >= world_pos.x && p.x < world_pos.x + dest_rect.w;
        bool contains_y = p.y >= world_pos.y && p.y < world_pos.y + dest_rect.h;
        return contains_x && contains_y;
    }
};

#endif