#ifndef TILE_H
#define TILE_H

#include <vector>

#include "utils/resource.h"
#include "utils/direction.h"
#include "render/texture.h"

enum TileType {
    TILE_BL = 0,
    TILE_BR = 1,
    TILE_HORI = 2,
    TILE_VERT = 3,
    TILE_TL = 4,
    TILE_TR = 5
};

// TODO: create tileset.h to store tile info and load tiles from res based on tileset type
class Tile {
private:
    // indexing from utils/direction.h
    // 0 = U; 1 = R; 2 = D; 3 = L;
    std::vector< std::vector<TileType> > neighbors{4};
    Texture *tex = new Texture();
    TileType type;

public:
    ~Tile();
    int Load(SDL_Renderer *rend, Resource res, TileType type);
    bool IsNeighbor(TileType type, Direction dir);
};

#endif