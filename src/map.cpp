#include <string>
#include <vector>
#include <SDL_render.h>

#include "map/map.h"
#include "map/chunk.h"
#include "map/tileset.h"
#include "utils/error.h"
#include "utils/resource.h"
#include "render/render.h"
#include "render/texture.h"

Map::~Map() {
    delete this->tileset;
    this->tileset = NULL;
}

int Map::InitChunkMatrix(int row, int col) {
    this->chunk_matrix.Build(row, col);
    for (int i = 0; i < this->chunk_matrix.rows; i++) {
        for (int j = 0; j < this->chunk_matrix.cols; j++) {
            this->chunk_matrix[i][j] = Chunk{
                this->tileset->GetRandomTileType(),
                this->tileset->tile_width,
                this->tileset->tile_height
            };
            Point p{(j - 1) * this->chunk_matrix[i][j].dest_rect.w, (i - 1) * this->chunk_matrix[i][j].dest_rect.h};
            this->chunk_matrix[i][j].world_pos = p;
        }
    }

    return 0;
}

int Map::LoadTileset(SDL_Renderer *rend, std::string path) {
    this->tileset->LoadNeighbors(rend, "res/tilesets/simple.json");
    this->InitChunkMatrix(3, 3);

    return 0;
}

// TODO: things are becoming quite incomprehensible here
Chunk Map::GenerateUpFrom(std::unordered_map<Direction, TileType> neighbors, Point pos) {
    TileType type = neighbors.size() > 1 ?
        this->tileset->GetNeighborMulti(neighbors[RIGHT], RIGHT, neighbors[UP], UP) :
        this->tileset->GetNeighbor(neighbors[UP], UP);
    Chunk c{
        type,
        this->tileset->tile_width,
        this->tileset->tile_height
    };
    c.world_pos.x = pos.x;
    c.world_pos.y += pos.y - this->tileset->tile_height;
    return c;
}

Chunk Map::GenerateDownFrom(std::unordered_map<Direction, TileType> neighbors, Point pos) {
    TileType type = neighbors.size() > 1 ?
        this->tileset->GetNeighborMulti(neighbors[RIGHT], RIGHT, neighbors[UP], UP) :
        this->tileset->GetNeighbor(neighbors[UP], UP);
    Chunk c{
        type,
        this->tileset->tile_width,
        this->tileset->tile_height
    };
    c.world_pos.x = pos.x;
    c.world_pos.y += pos.y + this->tileset->tile_height;
    return c;
}

Chunk Map::GenerateLeftFrom(std::unordered_map<Direction, TileType> neighbors, Point pos) {
    TileType type = neighbors.size() > 1 ?
        this->tileset->GetNeighborMulti(neighbors[RIGHT], RIGHT, neighbors[UP], UP) :
        this->tileset->GetNeighbor(neighbors[UP], UP);
    Chunk c{
        type,
        this->tileset->tile_width,
        this->tileset->tile_height
    };
    c.world_pos.x += pos.x - this->tileset->tile_width;
    c.world_pos.y = pos.y;
    return c;
}

Chunk Map::GenerateRightFrom(std::unordered_map<Direction, TileType> neighbors, Point pos) {
    TileType type = neighbors.size() > 1 ?
        this->tileset->GetNeighborMulti(neighbors[RIGHT], RIGHT, neighbors[UP], UP) :
        this->tileset->GetNeighbor(neighbors[UP], UP);
    Chunk c{
        type,
        this->tileset->tile_width,
        this->tileset->tile_height
    };
    c.world_pos.x += pos.x + this->tileset->tile_width;
    c.world_pos.y = pos.y;
    return c;
}

int Map::GenerateChunks(Direction dir, std::vector<Chunk> adj) {
    std::vector<Chunk> v;
    std::unordered_map<Direction, TileType> neighbors;
    for (int i = 0; i < adj.size(); i++) {
        switch (dir) {
            case UP: {
                if (i > 1) neighbors[RIGHT] = v[i-1].tile_type;
                neighbors[UP] = adj[i].tile_type;
                v.push_back(GenerateUpFrom(neighbors, adj[i].world_pos));
                break;
            }
            case DOWN: {
                if (i > 1) neighbors[RIGHT] = v[i-1].tile_type;
                neighbors[DOWN] = adj[i].tile_type;
                v.push_back(GenerateDownFrom(neighbors, adj[i].world_pos));
                break;
            }
            case LEFT: {
                if (i > 1) neighbors[DOWN] = v[i-1].tile_type;
                neighbors[LEFT] = adj[i].tile_type;
                v.push_back(GenerateLeftFrom(neighbors, adj[i].world_pos));
                break;
            }
            case RIGHT: {
                if (i > 1) neighbors[DOWN] = v[i-1].tile_type;
                neighbors[RIGHT] = adj[i].tile_type;
                v.push_back(GenerateRightFrom(neighbors, adj[i].world_pos));
                break;
            }
        }
        neighbors.clear();
    }
    this->chunk_matrix.Extend(dir, v);
    return 0;
}

// TODO: is this necessary?
int Map::CenterChunks(int r, int c) {
    if (r == 0) {
        this->GenerateChunks(UP, this->chunk_matrix.GetRow(0));
    }
    else if (r == this->chunk_matrix.rows-1) {
        this->GenerateChunks(DOWN, this->chunk_matrix.GetRow(r));
    }
    if (c == 0) {
        this->GenerateChunks(LEFT, this->chunk_matrix.GetCol(0));
    }
    else if (c == this->chunk_matrix.cols-1) {
        this->GenerateChunks(RIGHT, this->chunk_matrix.GetCol(c));
    }

    return 0;
}

// TODO: too long
int Map::UpdateChunks(Point player_pos, Camera cam) {
    // checking if player is on an edge chunk so matrix can be extended
    for (int i = 0; i < this->chunk_matrix.rows; i++) {
        for (int j = 0; j < this->chunk_matrix.cols; j++) {
            if (this->chunk_matrix[i][j].Contains(player_pos)) {
                this->CenterChunks(i, j);
            }
        }
    }
    // updating chunks and finding which to render
    for (int i = 0; i < this->chunk_matrix.rows; i++) {
        for (int j = 0; j < this->chunk_matrix.cols; j++) {
            Point d = this->chunk_matrix[i][j].world_pos - cam.world_pos;
            this->chunk_matrix[i][j].dest_rect.x = d.x;
            this->chunk_matrix[i][j].dest_rect.y = d.y;
            if (cam.Contains(this->chunk_matrix[i][j].dest_rect)) {
                this->to_render.push_back(this->chunk_matrix[i][j]);
            }
        }
    }

    return 0;
}

int Map::RenderChunks(SDL_Renderer *rend, Camera cam) {
    for (int i = 0; i < this->to_render.size(); i++) {
        if (this->tileset->RenderTile(rend, this->to_render[i].tile_type, this->to_render[i].dest_rect) != 0) {
            SDLErrorMsg("map.cpp error rendering chunk tile: ");
            return 1;
        }
    }
    this->to_render.clear();

    return 0;
}
