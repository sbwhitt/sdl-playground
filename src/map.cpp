#include <SDL_render.h>

#include "map.h"
#include "chunk.h"
#include "camera.h"

int Map::InitChunkMatrix(int w, int h) {
    this->chunk_matrix.Build(3, 3);
    // don't need?
    // this->chunk_matrix.FillAlternate(c1, c2);
    //
    bool first = true;
    for (int i = 0; i < this->chunk_matrix.rows; i++) {
        for (int j = 0; j < this->chunk_matrix.cols; j++) {
            if (first) {
                this->chunk_matrix[i][j] = Chunk{BLUE, w, h};
            }
            else {
                this->chunk_matrix[i][j] = Chunk{RED, w, h};
            }
            Point p{(i) * this->chunk_matrix[i][j].width, (j) * this->chunk_matrix[i][j].height};
            this->chunk_matrix[i][j].world_pos = p;
            first = !first;
        }
    }

    return 0;
}

int Map::RenderChunks(SDL_Renderer *rend, Camera cam) {
    for (int i = 0; i < this->chunk_matrix.rows; i++) {
        for (int j = 0; j < this->chunk_matrix.cols; j++) {
            if (this->chunk_matrix[i][j].type == BLUE) {
                SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);
            }
            else if (this->chunk_matrix[i][j].type == RED) {
                SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
            }
            Point d = this->chunk_matrix[i][j].world_pos - (cam.world_pos);
            // Chunk.GetRect() should do this
            SDL_Rect r;
            r.x = d.x;
            r.y = d.y;
            r.w = this->chunk_matrix[i][j].width;
            r.h = this->chunk_matrix[i][j].height;
            //
            if (cam.Contains(r)) {
                SDL_RenderFillRect(rend, &r);
            }
        }
    }

    return 0;
}
