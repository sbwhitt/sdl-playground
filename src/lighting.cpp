#include <stdlib.h>
#include <SDL_render.h>

#include "lighting.h"
#include "error.h"
#include "texture.h"

Lighting::~Lighting() {
    for (int i = 0; i < this->textures.size(); i++) {
        delete this->textures[i];
        this->textures[i] = NULL;
    }
}

int Lighting::Load(SDL_Renderer *rend, std::vector<Resource> rs) {
    for (int i = 0; i < rs.size(); i++) {
        this->textures.push_back(new Texture{rend, rs[i]});
        this->textures[i]->SetAlpha(0);
    }

    return 0;
}

int Lighting::Update(int dt) {
    this->timer += dt;
    if (this->timer > 40) {
        this->timer = 0;
    }

    return 0;
}

int Lighting::Draw(SDL_Renderer *rend) {
    for (int i = 0; i < this->textures.size(); i++) {
        this->textures[i]->Render(rend);
    }

    return 0;
}
