#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

class Window {
private:
public:
    int x;
    int y;
    int w;
    int h;
    SDL_Window *SDL_win;

    int Create(int x, int y, int w, int h);
};

#endif