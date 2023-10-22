#ifndef TILESET_H
#define TILESET_H

#include <unordered_map>
#include <SDL_rect.h>
#include <SDL_render.h>

#include "map/tile.h"
#include "map/tile_type.h"

class Tileset {
private:
public:
    int tile_width;
    int tile_height;
    std::unordered_map<TileType, Tile*> tiles;

    Tileset();
    ~Tileset();
    int LoadNeighbors(SDL_Renderer *rend, const char *file);
    TileType GetRandomTileType();
    int RenderTile(SDL_Renderer *rend, TileType type, SDL_Rect rect);
};

#endif