#include <SDL_render.h>

#include "texture.h"
#include "error.h"

int Texture::Load(SDL_Renderer *rend, const char *file) {
    this->sdl_tex = SDL_CreateTextureFromSurface(rend, SDL_LoadBMP(file));
    if (this->sdl_tex == nullptr) {
        SDLErrorMsg("SDL error loading texture: ");
        return 1;
    }    

    return 0;
}
