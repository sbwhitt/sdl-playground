#include <SDL_render.h>

#include "map.h"
#include "chunk.h"

int Map::InitChunkMatrix(int w, int h) {
    this->chunk_matrix.Build(3, 3);
    Chunk c1{BLUE, w, h};
    Chunk c2{RED, w, h};
    this->chunk_matrix.FillAlternate(c1, c2);

    return 0;
}

int Map::RenderChunks(SDL_Renderer *rend) {
    for (int i = 0; i < this->chunk_matrix.rows; i++) {
        for (int j = 0; j < this->chunk_matrix.cols; j++) {
            if (this->chunk_matrix[i][j].type == BLUE) {
                SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);
            }
            else if (this->chunk_matrix[i][j].type == RED) {
                SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
            }
            SDL_Rect r;
            r.x = (i) * this->chunk_matrix[i][j].width;
            r.y = (j) * this->chunk_matrix[i][j].height;
            r.w = this->chunk_matrix[i][j].width;
            r.h = this->chunk_matrix[i][j].height;
            SDL_RenderFillRect(rend, &r);
        }
    }

    return 0;
}
