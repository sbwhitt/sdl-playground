#include <SDL_render.h>

#include "map.h"
#include "error.h"
#include "chunk.h"

int Map::InitChunkMatrix(int r, int c, int w, int h) {
    this->chunk_matrix.Build(r, c);
    bool first = true;
    for (int i = 0; i < this->chunk_matrix.rows; i++) {
        for (int j = 0; j < this->chunk_matrix.cols; j++) {
            if (first) {
                this->chunk_matrix[i][j] = Chunk{BLUE, w, h};
            }
            else {
                this->chunk_matrix[i][j] = Chunk{RED, w, h};
            }
            Point p{(-i + 1) * this->chunk_matrix[i][j].dest_rect.w, (-j + 1) * this->chunk_matrix[i][j].dest_rect.h};
            this->chunk_matrix[i][j].world_pos = p;
            first = !first;
        }
    }

    return 0;
}

Matrix<Chunk> Map::GetChunkMatrix() {
    return this->chunk_matrix;
}

int Map::GenerateChunks(ExtendDir dir) {
    return 0;
}

int Map::CenterChunks(int r, int c) {
    return 0;
}

// TODO: use player_pos to get center of chunk mat and extend accordingly
int Map::UpdateChunks(Point player_pos, Camera cam) {
    // update relative on-screen position wrt cam and apply to rect
    for (int i = 0; i < this->chunk_matrix.rows; i++) {
        for (int j = 0; j < this->chunk_matrix.cols; j++) {
            Point d = this->chunk_matrix[i][j].world_pos - (cam.world_pos);
            this->chunk_matrix[i][j].dest_rect.x = d.x;
            this->chunk_matrix[i][j].dest_rect.y = d.y;
            if (this->chunk_matrix[i][j].Contains(player_pos)) {
                this->CenterChunks(i, j);
            }
            SDL_Rect r = this->chunk_matrix[i][j].dest_rect;
            if (cam.Contains(r)) {
                this->to_render.push_back(this->chunk_matrix[i][j]);
            }
        }
    }

    return 0;
}

int Map::RenderChunks(SDL_Renderer *rend, Camera cam) {
    for (int i = 0; i < this->to_render.size(); i++) {
        if (this->to_render[i].type == BLUE) {
            SDL_SetRenderDrawColor(rend, 50, 50, 200, 255);
        }
        else if (this->to_render[i].type == RED) {
            SDL_SetRenderDrawColor(rend, 200, 50, 50, 255);
        }
        SDL_Rect r = this->to_render[i].dest_rect;
        if (cam.Contains(r)) {
            if (SDL_RenderFillRect(rend, &r) != 0) {
                SDLErrorMsg("map.cpp error rendering chunk rect: ");
                return 1;
            }
        }
    }
    this->to_render.clear();

    return 0;
}
