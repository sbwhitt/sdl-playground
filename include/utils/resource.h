#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

#include "geometry/point.h"

struct Resource {
    std::string file;
    int width;
    int height;

    Resource() {}
    Resource(std::string path, int width, int height) {
        this->file = path;
        this->width = width;
        this->height = height;
    }
};

#endif