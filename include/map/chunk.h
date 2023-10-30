#ifndef CHUNK_H
#define CHUNK_H

#include <SDL_rect.h>

#include "map/tile.h"
#include "geometry/point.h"

struct Chunk {
    SDL_Rect dest_rect;
    TileType tile_type;
    Point world_pos{0, 0};

    Chunk();
    Chunk(TileType type, int w, int h);
    ~Chunk();
    bool Contains(Point p);
};

#endif