#include <fstream>
#include <external/json.hpp>
using json = nlohmann::json;

#include "map/tileset.h"
#include "utils/resource.h"

Tileset::Tileset() {}

Tileset::~Tileset() {
    for (std::unordered_map<TileType, Tile*>::iterator it = this->tiles.begin(); it != this->tiles.end(); it++) {
        delete (it->second);
    }
    this->tiles.clear();
}

int Tileset::LoadNeighbors(SDL_Renderer *rend, const char *file) {
    std::ifstream f(file);
    json j = json::parse(f);

    this->tile_width = j["width"];
    this->tile_height = j["height"];

    auto tiles = j["tiles"];
    for (auto& t : tiles) {
        Tile *tile = new Tile();
    
        auto n = t["neighbors"];
        for (auto& d : n["up"])    { tile->neighbors[0].push_back(d); }
        for (auto& d : n["right"]) { tile->neighbors[1].push_back(d); }
        for (auto& d : n["down"])  { tile->neighbors[2].push_back(d); }
        for (auto& d : n["left"])  { tile->neighbors[3].push_back(d); }

        auto path = t["path"];
        TileType type = t["type"];
        tile->Load(rend, Resource{path, this->tile_width, this->tile_height}, type);
    
        this->tiles[type] = tile;
    }

    return 0;
}

TileType Tileset::GetRandomTileType() {
    return (TileType)(rand() % TYPE_COUNT);
}

TileType Tileset::GetNeighbor(TileType type, Direction dir) {
    std::vector<TileType> neighbs = this->tiles[type]->neighbors[dir];
    int choice = rand() % neighbs.size();
    return neighbs[choice];
}

TileType Tileset::GetNeighborMulti(TileType type1, Direction dir1, TileType type2, Direction dir2) {
    std::vector<TileType> neighbs1 = this->tiles[type1]->neighbors[dir1];
    std::vector<TileType> neighbs2 = this->tiles[type2]->neighbors[dir2];
    TileType res = TILE_EMPTY;
    for (auto n1 : neighbs1) {
        for (auto n2 : neighbs2) {
            if (n2 == n1) res = n1;
        }
    }
    return res;
}

int Tileset::RenderTile(SDL_Renderer *rend, TileType type, SDL_Rect rect) {
    if (tiles[type]->Render(rend, rect) != 0) {
        SDLErrorMsg("tileset.cpp error rendering tile: ");
        return 1;
    }

    return 0;
}
