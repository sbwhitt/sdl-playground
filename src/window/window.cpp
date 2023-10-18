#include "window/window.h"
#include "utils/error.h"

int Window::Create(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->SDL_win = SDL_CreateWindow("that's right I did it", x, y, w, h, 0);
    if (this->SDL_win == nullptr) {
        SDLErrorMsg("window.cpp create window error: ");
        return 1;
    }

    return 0;
}
