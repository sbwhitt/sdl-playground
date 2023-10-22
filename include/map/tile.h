#ifndef TILE_H
#define TILE_H

#include <SDL_render.h>

#include "map/tile_type.h"
#include "render/texture.h"
#include "utils/direction.h"

class Tile {
private:
    TileType type;
    Texture *tex = new Texture();

public:
    // indexing from utils/direction.h
    // 0 = U; 1 = R; 2 = D; 3 = L;
    std::vector< std::vector<TileType> > neighbors{4};

    ~Tile();
    int Load(SDL_Renderer *rend, Resource res, TileType type);
    bool IsNeighbor(TileType type, Direction dir);
    int Render(SDL_Renderer *rend, SDL_Rect rect);
};

#endif