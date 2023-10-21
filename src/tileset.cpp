#include <iostream>
#include <fstream>
#include <external/json.hpp>
using json = nlohmann::json;

#include "map/tileset.h"
#include "utils/resource.h"

Tileset::Tileset() {}

Tileset::~Tileset() {
    for (auto t : this->tiles) {
        delete t;
        t = NULL;
    }
}

int Tileset::LoadNeighbors(SDL_Renderer *rend, const char *file) {
    std::ifstream f(file);
    json j = json::parse(f);

    int width = j["width"];
    int height = j["height"];
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
        tile->Load(rend, Resource{path, width, height}, type);
    
        this->tiles.push_back(tile);
    }

    return 0;
}
