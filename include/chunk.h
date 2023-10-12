#ifndef CHUNK_H
#define CHUNK_H

#include <SDL_rect.h>

#include "point.h"

enum ChunkType {
    BLUE = 0,
    RED = 1
};

struct Chunk {
    int width;
    int height;
    ChunkType type;
    Point world_pos{0, 0};

    Chunk() {}
    Chunk(ChunkType t, int w, int h) {
        this->type = t;
        this->width = w;
        this->height = h;
    }
    SDL_Rect GetRect() {
        SDL_Rect r;
        r.x = world_pos.x;
        r.y = world_pos.y;
        r.w = width;
        r.h = height;
        return r;
    }
};

#endif