#include <SDL_render.h>

#include "map.h"
#include "chunk.h"

#define GRID_SIZE 3

int Map::InitGrid() {
    ChunkType current = BLUE;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            this->grid[i][j] = current;
            if (current == BLUE) current = RED;
            else current = BLUE;
        }
    }

    return 0;
}

int Map::RenderChunks(SDL_Renderer *rend) {
    return 0;
}
