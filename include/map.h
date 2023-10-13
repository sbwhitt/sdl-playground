#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SDL.h>

#include "matrix.h"
#include "chunk.h"
#include "point.h"
#include "camera.h"

class Map {
private:
    Matrix<Chunk> chunk_matrix;
    std::vector<Chunk> to_render;

public:
    int InitChunkMatrix(int r, int c, int w, int h);
    Matrix<Chunk> GetChunkMatrix();
    int GenerateChunks(ExtendDir dir);
    int UpdateChunks(Point player_pos, Camera cam);
    int RenderChunks(SDL_Renderer *rend, Camera cam);
};

#endif