#include "map/chunk.h"
#include "map/tile.h"
#include "geometry/point.h"

Chunk::Chunk() {}

Chunk::Chunk(TileType type, int w, int h) {
    this->tile_type = type;
    dest_rect.w = w;
    dest_rect.h = h;
}

Chunk::~Chunk() {}

bool Chunk::Contains(Point p) {
    bool contains_x = p.x >= world_pos.x && p.x < world_pos.x + dest_rect.w;
    bool contains_y = p.y >= world_pos.y && p.y < world_pos.y + dest_rect.h;
    return contains_x && contains_y;
}
