#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include "window.h"

class Game {
private:
    bool running = true;
    int ticks = 0;
    Window window;
    SDL_Renderer *renderer;

    int Init();
    int HandleKeyDown(SDL_Keycode key);
    int HandleMouseDown(SDL_MouseButtonEvent button);
    int HandleEvents();
    int Update(SDL_Renderer *rend);
    int Draw(SDL_Renderer *rend);
    int Cleanup();

public:
    Game();
    int Execute();
};

#endif