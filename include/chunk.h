#ifndef CHUNK_H
#define CHUNK_H

#include <SDL_rect.h>

#include "point.h"

enum ChunkType {
    BLUE = 0,
    RED = 1
};

struct Chunk {
    SDL_Rect dest_rect;
    ChunkType type;
    Point world_pos{0, 0};

    Chunk() {}
    Chunk(ChunkType t, int w, int h) {
        this->type = t;
        this->dest_rect.w = w;
        this->dest_rect.h = h;
    }
    bool Contains(Point p) {
        return (p.x >= dest_rect.x && p.x <= dest_rect.x + dest_rect.w &&
                p.y >= dest_rect.h && p.y <= dest_rect.y + dest_rect.h);
    }
};

#endif