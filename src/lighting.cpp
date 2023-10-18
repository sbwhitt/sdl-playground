#include <stdlib.h>
#include <SDL_render.h>

#include "lighting.h"
#include "utils/error.h"
#include "texture.h"
#include "animations/a_from_to.h"

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
            this->textures[i]->AddAnimation(new A_FromTo{ALPHA, 0, 20, 3});
            this->textures[i]->AddAnimation(new A_FromTo{POS_X, 0, 5, 6});
            this->textures[i]->AddAnimation(new A_FromTo{POS_Y, 0, 5, 6});
        }
        else if (i == 1) {
            this->textures[i]->AddAnimation(new A_FromTo{ALPHA, 0, 30, 4});
            this->textures[i]->AddAnimation(new A_FromTo{POS_Y, 7, 2, 5});
            this->textures[i]->AddAnimation(new A_FromTo{POS_X, 7, 2, 5});
        }
        else if (i == 2) {
            this->textures[i]->AddAnimation(new A_FromTo{ALPHA, 20, 10, 3});
            this->textures[i]->AddAnimation(new A_FromTo{POS_X, 5, 0, 7});
            this->textures[i]->AddAnimation(new A_FromTo{POS_Y, 5, 0, 7});
        }
        else if (i == 3) {
            this->textures[i]->AddAnimation(new A_FromTo{ALPHA, 15, 5, 3});
            this->textures[i]->AddAnimation(new A_FromTo{POS_Y, 0, 10, 8});
            this->textures[i]->AddAnimation(new A_FromTo{POS_X, 0, 10, 8});
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
