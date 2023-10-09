#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SDL.h>

#include "window.h"
#include "control.h"
#include "texture.h"

class Game {
private:
    bool running = true;
    int ticks = 0;
    Window window;
    SDL_Renderer *renderer;
    Control ctrl;
    Texture fish;

    int Init();
    int Load(SDL_Renderer *rend);
    int HandleKeyDown(SDL_Keycode key);
    int HandleKeyUp(SDL_Keycode key);
    int HandleMouseDown(SDL_MouseButtonEvent button);
    int HandleEvents();
    int HandleKeys();
    int Update(SDL_Renderer *rend);
    int Draw(SDL_Renderer *rend);
    int Cleanup();

public:
    Game();
    int Execute();
};

#endif