#include <SDL_render.h>
#include <SDL_rect.h>

#include "texture.h"
#include "error.h"
#include "point.h"

int Texture::Load(SDL_Renderer *rend, const char *file) {
    this->sdl_tex = SDL_CreateTextureFromSurface(rend, SDL_LoadBMP(file));
    if (this->sdl_tex == nullptr) {
        SDLErrorMsg("SDL error loading texture: ");
        return 1;
    }

    return 0;
}

int Texture::Draw(SDL_Renderer *rend, Point pos) {
    this->dest_rect.x = pos.x;
    this->dest_rect.y = pos.y;
    this->dest_rect.w = 200;
    this->dest_rect.h = 100;
    
    if (SDL_RenderCopy(rend, this->sdl_tex, NULL, &this->dest_rect) != 0) {
        SDLErrorMsg("SDL error drawing texture: ");
        return 1;
    }

    return 0;
}

int Texture::Destroy() {
    SDL_DestroyTexture(this->sdl_tex);
    this->sdl_tex = NULL;

    return 0;
}
