#include <iostream>
#include <SDL_render.h>
#include <SDL_rect.h>

#include "texture.h"
#include "error.h"
#include "point.h"

Texture::~Texture() {
    SDL_DestroyTexture(this->sdl_tex);
    this->sdl_tex = NULL;
}

int Texture::LoadFromResource(SDL_Renderer *rend, Resource res) {
    this->sdl_tex = SDL_CreateTextureFromSurface(rend, SDL_LoadBMP(res.file));
    if (this->sdl_tex == nullptr) {
        SDLErrorMsg("SDL error loading texture: ");
        return 1;
    }

    this->dest_rect.x = 0;
    this->dest_rect.y = 0;
    this->dest_rect.w = res.width;
    this->dest_rect.h = res.height;

    return 0;
}

int Texture::Move(int x, int y) {
    this->dest_rect.x += x;
    this->dest_rect.y += y;

    std::cout << dest_rect.x << ", " << dest_rect.y << std::endl;

    return 0;
}

int Texture::Draw(SDL_Renderer *rend) {    
    if (SDL_RenderCopy(rend, this->sdl_tex, NULL, &this->dest_rect) != 0) {
        SDLErrorMsg("SDL error drawing texture: ");
        return 1;
    }

    return 0;
}
