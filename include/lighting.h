#ifndef LIGHTING_H
#define LIGHTING_H

#include <vector>
#include <SDL_render.h>

#include "texture.h"
#include "resource.h"

class Lighting {
private:
    int timer = 0;
    std::vector<Texture*> textures;

public:
    ~Lighting();
    int Load(SDL_Renderer *rend, std::vector<Resource> rs);
    int Update(int dt);
    int Draw(SDL_Renderer *rend);
};

#endif