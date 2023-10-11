#ifndef CHUNK_H
#define CHUNK_H

enum ChunkType {
    BLUE = 0,
    RED = 1
};

struct Chunk {
    int width;
    int height;
    ChunkType type;

    Chunk(ChunkType t, int w, int h) {
        this->type = t;
        this->width = w;
        this->height = h;
    }
};

#endif