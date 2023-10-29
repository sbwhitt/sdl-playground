#include <SDL_render.h>

#include "render/renderer.h"
#include "render/texture.h"
#include "window/window.h"
#include "utils/color.h"
#include "utils/error.h"

Renderer::Renderer() {}

Renderer::~Renderer() {
    SDL_DestroyRenderer(this->SDL_rend);
    this->SDL_rend = NULL;
    this->win = NULL;
}

int Renderer::Create(Window *win, Uint32 flags) {
    this->SDL_rend = SDL_CreateRenderer(win->SDL_win, -1, flags);
    if (this->SDL_rend == nullptr) {
        SDL_DestroyWindow(win->SDL_win);
        SDLErrorMsg("renderer.cpp create renderer error: ");
        SDL_Quit();
        return 1;
    }

    return 0;
}

SDL_Texture* Renderer::CreateTexture(std::string file) {
    SDL_Texture *t = SDL_CreateTextureFromSurface(this->SDL_rend, SDL_LoadBMP(file.c_str()));
    if (t == nullptr) {
        SDLErrorMsg("renderer.cpp error creating texture: ");
        return nullptr;
    }

    return t;
}

int Renderer::SetRenderColor(Color c) {
    if (SDL_SetRenderDrawColor(this->SDL_rend, c.r, c.g, c.b, c.a) != 0) {
        SDLErrorMsg("render.cpp error setting draw color: ");
        return 1;
    }

    return 0;
}

int Renderer::Clear() {
    if (SDL_RenderClear(this->SDL_rend) != 0) {
        SDLErrorMsg("renderer.cpp error clearing: ");
        return 1;
    }

    return 0;
}

int Renderer::RenderTexture(SDL_Texture *texture, SDL_Rect *rect, double angle) {
    if (SDL_RenderCopyEx(this->SDL_rend, texture, NULL, rect, angle, NULL, SDL_FLIP_NONE) != 0) {
        SDLErrorMsg("renderer.cpp error drawing texture: ");
        return 1;
    }

    return 0;
}

int Renderer::RenderPoint(int x, int y) {
    SDL_RenderDrawPoint(this->SDL_rend, x, y);

    return 0;
}

int Renderer::RenderLine(int x1, int y1, int x2, int y2) {
    if (SDL_RenderDrawLine(this->SDL_rend, x1, y1, x2, y2) != 0) {
        SDLErrorMsg("renderer.cpp error drawing line: ");
        return 1;
    }

    return 0;
}

int Renderer::RenderLine(Line l) {
    return this->RenderLine(l.start.x, l.start.y, l.end.x, l.end.y);
}

int Renderer::RenderRect(SDL_Rect r) {
    SDL_RenderDrawRect(this->SDL_rend, &r);

    return 0;
}

void Renderer::RenderPresent() {
    SDL_RenderPresent(this->SDL_rend);
}
