#include <string>
#include <vector>
#include <SDL_render.h>

#include "map/map.h"
#include "map/chunk.h"
#include "map/tileset.h"
#include "utils/error.h"
#include "utils/color.h"
#include "utils/resource.h"
#include "render/render.h"
#include "render/texture.h"

Map::~Map() {
    delete this->tileset;
    this->tileset = NULL;
}

int Map::InitChunkMatrix(int row, int col, int width, int height) {
    this->chunk_width = width;
    this->chunk_height = height;
    this->chunk_matrix.Build(row, col);
    for (int i = 0; i < this->chunk_matrix.rows; i++) {
        for (int j = 0; j < this->chunk_matrix.cols; j++) {
            this->chunk_matrix[i][j] = Chunk{Color{20, 80, 150}, width, height};
            Point p{(j - 1) * this->chunk_matrix[i][j].dest_rect.w, (i - 1) * this->chunk_matrix[i][j].dest_rect.h};
            this->chunk_matrix[i][j].world_pos = p;
        }
    }

    return 0;
}

int Map::LoadTileset(SDL_Renderer *rend, std::string path) {
    this->tileset->LoadNeighbors(rend, "res/tilesets/simple.json");

    return 0;
}

Matrix<Chunk> Map::GetChunkMatrix() {
    return this->chunk_matrix;
}

Chunk Map::GenerateUpFrom(Chunk c1) {
    Chunk c2{GetColorIncremented(c1.color), this->chunk_width, this->chunk_height};
    c2.world_pos.x = c1.world_pos.x;
    c2.world_pos.y += c1.world_pos.y - this->chunk_height;
    return c2;
}

Chunk Map::GenerateDownFrom(Chunk c1) {
    Chunk c2{GetColorDecremented(c1.color), this->chunk_width, this->chunk_height};
    c2.world_pos.x = c1.world_pos.x;
    c2.world_pos.y += c1.world_pos.y + this->chunk_height;
    return c2;
}

Chunk Map::GenerateLeftFrom(Chunk c1) {
    Chunk c2{GetColorDecremented(c1.color), this->chunk_width, this->chunk_height};
    c2.world_pos.x += c1.world_pos.x - this->chunk_width;
    c2.world_pos.y = c1.world_pos.y;
    return c2;
}

Chunk Map::GenerateRightFrom(Chunk c1) {
    Chunk c2{GetColorIncremented(c1.color), this->chunk_width, this->chunk_height};
    c2.world_pos.x += c1.world_pos.x + this->chunk_width;
    c2.world_pos.y = c1.world_pos.y;
    return c2;
}

int Map::GenerateChunks(Direction dir, std::vector<Chunk> adj) {
    std::vector<Chunk> v;
    for (int i = 0; i < adj.size(); i++) {
        switch (dir) {
            case UP: {
                v.push_back(GenerateUpFrom(adj[i]));
                break;
            }
            case DOWN: {
                v.push_back(GenerateDownFrom(adj[i]));
                break;
            }
            case LEFT: {
                v.push_back(GenerateLeftFrom(adj[i]));
                break;
            }
            case RIGHT: {
                v.push_back(GenerateRightFrom(adj[i]));
                break;
            }
        }
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
        SetRenderColor(rend, this->to_render[i].color);
        SDL_Rect r = this->to_render[i].dest_rect;
        if (SDL_RenderFillRect(rend, &r) != 0) {
            SDLErrorMsg("map.cpp error rendering chunk rect: ");
            return 1;
        }
    }
    this->to_render.clear();

    return 0;
}
