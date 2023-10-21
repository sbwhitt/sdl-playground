#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SDL.h>

#include "map/chunk.h"
#include "map/tileset.h"
#include "utils/matrix.h"
#include "utils/point.h"
#include "utils/direction.h"
#include "game_objects/camera.h"

class Map {
private:
    int chunk_height;
    int chunk_width;
    Matrix<Chunk> chunk_matrix;
    Tileset *tileset = new Tileset();
    std::vector<Chunk> to_render;

    Chunk GenerateUpFrom(Chunk c1);
    Chunk GenerateDownFrom(Chunk c1);
    Chunk GenerateLeftFrom(Chunk c1);
    Chunk GenerateRightFrom(Chunk c1);
    int GenerateChunks(Direction dir, std::vector<Chunk> adj);
    int CenterChunks(int r, int c);

public:
    ~Map();
    Matrix<Chunk> GetChunkMatrix();
    int InitChunkMatrix(int row, int col, int width, int height);
    int LoadTileset(SDL_Renderer *rend, std::string path);
    int UpdateChunks(Point player_pos, Camera cam);
    int RenderChunks(SDL_Renderer *rend, Camera cam);
};

#endif