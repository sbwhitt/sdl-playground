#include <SDL_render.h>

#include "map.h"
#include "error.h"
#include "color.h"
#include "chunk.h"
#include "render.h"

int Map::InitChunkMatrix(int r, int c, int w, int h) {
    this->chunk_width = w;
    this->chunk_height = h;
    this->chunk_matrix.Build(r, c);
    for (int i = 0; i < this->chunk_matrix.rows; i++) {
        for (int j = 0; j < this->chunk_matrix.cols; j++) {
            this->chunk_matrix[i][j] = Chunk{GetRandomColor(), w, h};
            Point p{(j - 1) * this->chunk_matrix[i][j].dest_rect.w, (i - 1) * this->chunk_matrix[i][j].dest_rect.h};
            this->chunk_matrix[i][j].world_pos = p;
        }
    }

    return 0;
}

Matrix<Chunk> Map::GetChunkMatrix() {
    return this->chunk_matrix;
}

// TODO: too long
int Map::GenerateChunks(ExtendDir dir, std::vector<Chunk> adj) {
    switch (dir) {
        case UP: {
            std::vector<Chunk> v;
            for (int i = 0; i < adj.size(); i++) {
                Chunk c{GetColorIncremented(adj[i].color), this->chunk_width, this->chunk_height};
                c.world_pos.x = adj[i].world_pos.x;
                c.world_pos.y += adj[i].world_pos.y - this->chunk_height;
                v.push_back(c);
            }
            this->chunk_matrix.Extend(UP, v);
            break;
        }
        case DOWN: {
            std::vector<Chunk> v;
            for (int i = 0; i < adj.size(); i++) {
                Chunk c{GetColorDecremented(adj[i].color), this->chunk_width, this->chunk_height};
                c.world_pos.x = adj[i].world_pos.x;
                c.world_pos.y += adj[i].world_pos.y + this->chunk_height;
                v.push_back(c);
            }
            this->chunk_matrix.Extend(DOWN, v);
            break;
        }
        case LEFT: {
            std::vector<Chunk> v;
            for (int i = 0; i < adj.size(); i++) {
                Chunk c{GetColorDecremented(adj[i].color), this->chunk_width, this->chunk_height};
                c.world_pos.x += adj[i].world_pos.x - this->chunk_width;
                c.world_pos.y = adj[i].world_pos.y;
                v.push_back(c);
            }
            this->chunk_matrix.Extend(LEFT, v);
            break;
        }
        case RIGHT: {
            std::vector<Chunk> v;
            for (int i = 0; i < adj.size(); i++) {
                Chunk c{GetColorIncremented(adj[i].color), this->chunk_width, this->chunk_height};
                c.world_pos.x += adj[i].world_pos.x + this->chunk_width;
                c.world_pos.y = adj[i].world_pos.y;
                v.push_back(c);
            }
            this->chunk_matrix.Extend(RIGHT, v);
            break;
        }
    }
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
            Point d = this->chunk_matrix[i][j].world_pos - (cam.world_pos);
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
