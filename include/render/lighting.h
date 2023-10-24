#ifndef LIGHTING_H
#define LIGHTING_H

#include <vector>

#include "render/renderer.h"
#include "render/texture.h"
#include "utils/resource.h"

class Lighting {
private:
    int timer = 0;
    std::vector<Texture*> textures;

public:
    ~Lighting();
    int Load(Renderer *rend, std::vector<Resource> rs);
    int Update(int dt);
    int Draw(Renderer *rend);
};

#endif