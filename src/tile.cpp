#include "map/tile.h"

Tile::~Tile() {
    delete this->tex;
    this->tex = NULL;
}

int Tile::Load(SDL_Renderer *rend, Resource res, TileType type) {
    this->tex->LoadFromResource(rend, res);
    this->type = type;

    return 0;
}

bool Tile::IsNeighbor(TileType type, Direction dir) {
    for (int i = 0; i < this->neighbors[dir].size(); i++) {
        if (type == this->neighbors[dir][i]) return true;
    }
    return false;
}
