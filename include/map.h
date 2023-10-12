#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SDL.h>

#include "matrix.h"
#include "chunk.h"
#include "camera.h"

class Map {
private:
    Matrix<Chunk> chunk_matrix;

public:
    int InitChunkMatrix(int w, int h);
    int UpdateChunks(Camera cam);
    int RenderChunks(SDL_Renderer *rend, Camera cam);
};

#endif