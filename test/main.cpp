#include <iostream>
#include <vector>

#include "matrix.h"
#include "chunk.h"

void print(Matrix<int> m) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print(Matrix<Chunk> m) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", m[i][j].type);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char **argv) {
    printf("test started\n");

    Matrix<Chunk> m;
    m.Build(3, 3);
    m.FillAlternate(Chunk{BLUE, 0, 0}, Chunk{RED, 0, 0});

    print(m);

    return 0;
}
