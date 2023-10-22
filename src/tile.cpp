#include "map/tile.h"
#include "map/tileset.h"
#include "utils/error.h"

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

int Tile::Render(SDL_Renderer *rend, SDL_Rect rect) {
    this->tex->rect = rect;
    if (this->tex->Render(rend) != 0) {
        SDLErrorMsg("tile.cpp error rendering tile: ");
        return 1;
    }

    return 0;
}
