#ifndef RESOURCE_H
#define RESOURCE_H

#include "utils/point.h"

struct Resource {
    const char *file;
    int width;
    int height;

    Resource(const char *path, int w, int h) {
        file = path;
        width = w;
        height = h;
    }
};

#endif