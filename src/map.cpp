#include <SDL_render.h>

#include "map.h"
#include "error.h"
#include "chunk.h"
#include "camera.h"

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

int Map::UpdateChunks(Camera cam) {
    // update relative on-screen position wrt cam and apply to rect
    for (int i = 0; i < this->chunk_matrix.rows; i++) {
        for (int j = 0; j < this->chunk_matrix.cols; j++) {
            Point d = this->chunk_matrix[i][j].world_pos - (cam.world_pos);
            this->chunk_matrix[i][j].dest_rect.x = d.x;
            this->chunk_matrix[i][j].dest_rect.y = d.y;
        }
    }

    return 0;
}

int Map::RenderChunks(SDL_Renderer *rend, Camera cam) {
    for (int i = 0; i < this->chunk_matrix.rows; i++) {
        for (int j = 0; j < this->chunk_matrix.cols; j++) {
            if (this->chunk_matrix[i][j].type == BLUE) {
                SDL_SetRenderDrawColor(rend, 50, 50, 200, 255);
            }
            else if (this->chunk_matrix[i][j].type == RED) {
                SDL_SetRenderDrawColor(rend, 200, 50, 50, 255);
            }
            SDL_Rect r = this->chunk_matrix[i][j].dest_rect;
            if (cam.Contains(r)) {
                if (SDL_RenderFillRect(rend, &r) != 0) {
                    SDLErrorMsg("map.cpp error rendering chunk rect: ");
                    return 1;
                }
            }
        }
    }

    return 0;
}
