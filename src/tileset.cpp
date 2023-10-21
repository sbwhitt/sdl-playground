#include <iostream>
#include <fstream>
#include <external/json.hpp>
using json = nlohmann::json;

#include "map/tileset.h"

Tileset::Tileset() {}

Tileset::~Tileset() {}

int Tileset::LoadNeighbors(const char *file) {
    // std::ifstream f(file);
    // json j = json::parse(f);

    // auto tiles = j["tiles"];
    // for (auto& t : tiles) {
    //     std::cout << t["type"].dump(4) << std::endl;
    //     std::cout << t["neighbors"].dump(4) << std::endl;
    // }

    return 0;
}
