#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <SDL_stdinc.h>
#include <SDL_render.h>
#include <SDL_rect.h>

#include "resource.h"
#include "error.h"
#include "animation.h"

struct Texture {
    Uint8 alpha;
    double angle = 0;
    SDL_Texture *texture = NULL;
    SDL_Rect rect;
    std::vector<Animation> anims;

    Texture() {}
    Texture(SDL_Renderer *rend, Resource r) {
        this->LoadFromResource(rend, r);
    }
    ~Texture() {
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
    }
    int LoadFromResource(SDL_Renderer *rend, Resource res) {
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
    int SetAlpha(Uint8 a) {
        this->alpha = a;
        if (SDL_SetTextureAlphaMod(this->texture, this->alpha) != 0 ||
            SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND) != 0)
        {
            SDLErrorMsg("texture.h error setting alpha: ");
            return 1;
        }

        return 0;
    }
    int ModAlpha(Uint8 mod) {
        this->alpha += mod;
        if (SDL_SetTextureAlphaMod(this->texture, this->alpha) != 0 ||
            SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND) != 0)
        {
            SDLErrorMsg("texture.h error setting alpha: ");
            return 1;
        }

        return 0;
    }
    int UpdateAnimations(int dt) {
        for (int i = 0; i < this->anims.size(); i++) {
            this->anims[i].Update(dt);
            this->SetAlpha(this->anims[i].value);
        }

        return 0;
    }
    int Render(SDL_Renderer *rend) {
        if (SDL_RenderCopyEx(rend, this->texture, NULL, &this->rect, this->angle, NULL, SDL_FLIP_NONE) != 0) {
            SDLErrorMsg("SDL error drawing texture: ");
            return 1;
        }

        return 0;
    }
};

#endif