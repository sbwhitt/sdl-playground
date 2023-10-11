#include <SDL_render.h>

#include "map.h"
#include "chunk.h"

#define GRID_SIZE 3

int Map::InitChunkMatrix(int w, int h) {
    this->chunk_matrix.Build(3, 3);
    Chunk c1{BLUE, w, h};
    Chunk c2{RED, w, h};
    this->chunk_matrix.FillAlternate(c1, c2);

    return 0;
}

int Map::RenderChunks(SDL_Renderer *rend) {
    return 0;
}
