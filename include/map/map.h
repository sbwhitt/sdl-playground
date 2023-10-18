#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SDL.h>

#include "utils/matrix.h"
#include "map/chunk.h"
#include "utils/point.h"
#include "game_objects/camera.h"

class Map {
private:
    int chunk_height;
    int chunk_width;
    Matrix<Chunk> chunk_matrix;
    std::vector<Chunk> to_render;

    Chunk GenerateUpFrom(Chunk c1);
    Chunk GenerateDownFrom(Chunk c1);
    Chunk GenerateLeftFrom(Chunk c1);
    Chunk GenerateRightFrom(Chunk c1);
    int GenerateChunks(ExtendDir dir, std::vector<Chunk> adj);
    int CenterChunks(int r, int c);

public:
    int InitChunkMatrix(int r, int c, int w, int h);
    Matrix<Chunk> GetChunkMatrix();
    int UpdateChunks(Point player_pos, Camera cam);
    int RenderChunks(SDL_Renderer *rend, Camera cam);
};

#endif