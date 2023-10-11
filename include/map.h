#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SDL.h>

#include "chunk.h"

class Map {
private:
    std::vector<std::vector<ChunkType>> grid;

public:
    Map() {
        this->grid = std::vector<std::vector<ChunkType>>(3, std::vector<ChunkType>(3));
    }
    int InitGrid();
    int RenderChunks(SDL_Renderer *rend);
};

#endif