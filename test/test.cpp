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

void print(Matrix<Chunk> m) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d\t", m[i][j].type);   
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

void printVec(std::vector<Chunk> v) {
    for (int i = 0; i < v.size(); i++) {
        printf("%d ", v[i].type);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    printf("test started\n");

    Map m;
    m.InitChunkMatrix(3, 3, 100, 100);
    print(m.GetChunkMatrix());

    Matrix mat = m.GetChunkMatrix();
    // std::vector<Chunk> s{Chunk{RED, 101, 101}, Chunk{RED, 101, 101}, Chunk{RED, 101, 101}};
    // mat.Extend(LEFT, s);
    // print(mat);

    auto vr = mat.GetCol(2);
    auto vc = mat.GetCol(1);

    printf("get row 2: \n");
    printVec(vr);
    printf("get col 1: \n");
    printVec(vc);

    // mat.Extend(UP, s);
    // print(mat, 1, 1);

    // mat.Extend(DOWN, s);
    // print(mat, 1, 1);

    return 0;
}
