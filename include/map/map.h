#ifndef MAP_H
#define MAP_H

#include "map/chunk.h"
#include "map/tileset.h"
#include "utils/matrix.h"
#include "game_objects/camera.h"

class Map {
private:
    Matrix<Chunk> chunk_matrix;
    Tileset *tileset = new Tileset();
    std::vector<Chunk> to_render;

    Chunk GenerateUpFrom(std::unordered_map<Direction, TileType> neighbors, Point pos);
    Chunk GenerateDownFrom(std::unordered_map<Direction, TileType> neighbors, Point pos);
    Chunk GenerateLeftFrom(std::unordered_map<Direction, TileType> neighbors, Point pos);
    Chunk GenerateRightFrom(std::unordered_map<Direction, TileType> neighbors, Point pos);
    int GenerateChunks(Direction dir, std::vector<Chunk> adj);
    int CenterChunks(int r, int c);

public:
    ~Map();
    int InitChunkMatrix(int row, int col);
    int LoadTileset(SDL_Renderer *rend, std::string path);
    int UpdateChunks(Point player_pos, Camera cam);
    int RenderChunks(SDL_Renderer *rend, Camera cam);
};

#endif