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

class Tile {
private:
    // indexing from utils/direction.h
    // 0 = U; 1 = R; 2 = D; 3 = L;
    std::vector< std::vector<TileType> > neighbors{4};
    Texture *tex = new Texture();
    TileType type;

    int SetupNeighbors() {
        return 0;
    }

public:
    ~Tile() {
        delete this->tex;
        this->tex = NULL;
    }
    int Load(SDL_Renderer *rend, Resource res, TileType type) {
        this->tex->LoadFromResource(rend, res);
        this->type = type;

        this->SetupNeighbors();

        return 0;
    }
    bool IsNeighbor(Direction dir, TileType type) {
        for (int i = 0; i < this->neighbors[dir].size(); i++) {
            if (this->type == this->neighbors[dir][i]) return true;
        }
        return false;
    }
};

#endif