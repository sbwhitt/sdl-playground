#include "render/texture.h"

Texture::Texture() {}

Texture::Texture(SDL_Renderer *rend, Resource r) {
    this->LoadFromResource(rend, r);
}

Texture::~Texture() {
    SDL_DestroyTexture(this->texture);
    this->texture = NULL;

    for (int i = 0; i < this->anims.size(); i++) {
        delete this->anims[i];
        this->anims[i] = NULL;
    }
    this->anims.clear();
}

int Texture::LoadFromResource(SDL_Renderer *rend, Resource res) {
    this->texture = SDL_CreateTextureFromSurface(rend, SDL_LoadBMP(res.file));
    if (this->texture == nullptr) {
        SDLErrorMsg("SDL error loading texture: ");
        return 1;
    }

    this->rect.x = 0;
    this->rect.y = 0;
    this->rect.w = res.width;
    this->rect.h = res.height;

    return 0;
}

int Texture::SetAlpha(Uint8 a) {
    this->alpha = a;
    if (SDL_SetTextureAlphaMod(this->texture, this->alpha) != 0 ||
        SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND) != 0)
    {
        SDLErrorMsg("texture.h error setting alpha: ");
        return 1;
    }

    return 0;
}

int Texture::ModAlpha(Uint8 mod) {
    this->alpha += mod;
    if (SDL_SetTextureAlphaMod(this->texture, this->alpha) != 0 ||
        SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND) != 0)
    {
        SDLErrorMsg("texture.h error setting alpha: ");
        return 1;
    }

    return 0;
}

int Texture::ApplyAnimation(Animation *a) {
    switch(a->type) {
        case ALPHA:
            this->SetAlpha(a->value);
            break;
        case POS_X:
            this->rect.x = a->value;
            break;
        case POS_Y:
            this->rect.y = a->value;
            break;
    }

    return 0;
}

int Texture::AddAnimation(Animation *a) {
    this->anims.push_back(a);
    this->ApplyAnimation(a);

    return 0;
}

int Texture::UpdateAnimations(int dt) {
    for (int i = 0; i < this->anims.size(); i++) {
        this->anims[i]->Update(dt);
        this->ApplyAnimation(this->anims[i]);
    }

    return 0;
}

int Texture::Render(SDL_Renderer *rend) {
    if (SDL_RenderCopyEx(rend, this->texture, NULL, &this->rect, this->angle, NULL, SDL_FLIP_NONE) != 0) {
        SDLErrorMsg("SDL error drawing texture: ");
        return 1;
    }

    return 0;
}
