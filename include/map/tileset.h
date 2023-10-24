#ifndef TILESET_H
#define TILESET_H

#include <unordered_map>
#include <SDL_rect.h>

#include "map/tile.h"
#include "map/tile_type.h"
#include "render/renderer.h"

class Tileset {
private:
public:
    int tile_width;
    int tile_height;
    std::unordered_map<TileType, Tile*> tiles;

    Tileset();
    ~Tileset();
    int LoadNeighbors(Renderer *rend, const char *file);
    TileType GetRandomTileType();
    TileType GetNeighbor(TileType type, Direction dir);
    TileType GetNeighborMulti(TileType type1, Direction dir1, TileType type2, Direction dir2);
    int RenderTile(Renderer *rend, TileType type, SDL_Rect rect);
};

#endif