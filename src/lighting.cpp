#include <stdlib.h>
#include <SDL_render.h>

#include "render/lighting.h"
#include "utils/error.h"
#include "render/texture.h"
#include "animations/a_from_to.h"
#include "animations/a_increase.h"

Lighting::~Lighting() {
    for (int i = 0; i < this->textures.size(); i++) {
        delete this->textures[i];
        this->textures[i] = NULL;
    }
}

int Lighting::Load(SDL_Renderer *rend, std::vector<Resource> rs) {
    for (int i = 0; i < rs.size(); i++) {
        this->textures.push_back(new Texture{rend, rs[i]});
        if (i == 0) {
            this->textures[i]->AddAnimation(new A_FromTo{ALPHA, 0, 25, 3});
        }
        else if (i == 1) {
            this->textures[i]->AddAnimation(new A_FromTo{ALPHA, 25, 0, 3});
        }
        else if (i == 2) {
            this->textures[i]->AddAnimation(new A_FromTo{ALPHA, 0, 30, 5});
        }
    }

    return 0;
}

int Lighting::Update(int dt) {
    for (int i = 0; i < this->textures.size(); i++) this->textures[i]->UpdateAnimations(dt);

    return 0;
}

int Lighting::Draw(SDL_Renderer *rend) {
    for (int i = 0; i < this->textures.size(); i++) {
        this->textures[i]->Render(rend);
    }

    return 0;
}
