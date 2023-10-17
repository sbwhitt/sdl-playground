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
        bool dir = (i % 2 == 0);
        this->textures[i]->a = Animation{0, 20, i+5};
    }

    return 0;
}

// TODO: animate all bg textures differently
int Lighting::Update(int dt) {
    for (int i = 0; i < this->textures.size(); i++) {
        this->textures[i]->a.Update(dt);
        this->textures[i]->SetAlpha(this->textures[i]->a.value);
    }

    return 0;
}

int Lighting::Draw(SDL_Renderer *rend) {
    for (int i = 0; i < this->textures.size(); i++) {
        this->textures[i]->Render(rend);
    }

    return 0;
}
