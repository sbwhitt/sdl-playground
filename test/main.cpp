#include <iostream>
#include <vector>

// stopping undefined reference to WinMain
#define SDL_MAIN_HANDLED

#include "map.h"
#include "matrix.h"
#include "chunk.h"

void print(Matrix<int> m, int r, int c) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == r && j == r) {
                printf("[%d] ", m[i][j]);
            }
            else printf(" %d  ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print(Matrix<Chunk> m, int r, int c) {
    for (int i = 0; i < 3; i++) {
        printf("row %d: \n", i);
        for (int j = 0; j < 3; j++) {
            if (i == r && j == r) {
                printf("[%d: %d, %d] \t", m[i][j].type, m[i][j].world_pos.x, m[i][j].world_pos.y);
            }
            else printf(" %d: %d, %d  \t", m[i][j].type, m[i][j].world_pos.x, m[i][j].world_pos.y);
        }
        printf("\n");
    }
    printf("\n");
}

// void ShiftRow

int main(int argc, char **argv) {
    printf("test started\n");

    Map m;
    m.InitChunkMatrix(3, 3, 100, 100);
    print(m.GetChunkMatrix(), 1, 1);

    Matrix mat = m.GetChunkMatrix();
    std::vector<Chunk> s{Chunk{RED, 101, 101}, Chunk{RED, 101, 101}, Chunk{RED, 101, 101}};
    mat.ExtendDown(s);
    print(mat, 1, 1);

    return 0;
}
