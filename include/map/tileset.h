#ifndef TILESET_H
#define TILESET_H

#include "map/tile.h"
#include "utils/direction.h"

class Tileset {
private:
    std::vector<Tile*> tiles;

public:
    Tileset();
    ~Tileset();
    int LoadNeighbors(SDL_Renderer *rend, const char *file);
};

#endif