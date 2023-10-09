#include "window.h"

int Window::Create(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->SDL_win = SDL_CreateWindow("that's right I did it", x, y, w, h, 0);

    return 0;
}
