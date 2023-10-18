#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SDL.h>

#include "window/window.h"
#include "control/control.h"
#include "game_objects/camera.h"
#include "render/lighting.h"
#include "map/map.h"
#include "game_objects/entity.h"
#include "game_objects/player.h"

class Game {
private:
    bool running = true;
    int ticks = 0;
    Window window;
    SDL_Renderer *renderer;
    Control ctrl;
    Camera cam;
    Map map;
    Player player;
    Entity buddy;
    Lighting lighting;

    int Init();
    int Load(SDL_Renderer *rend);
    int HandleKeyDown(SDL_Keycode key);
    int HandleMouseDown(SDL_MouseButtonEvent button);
    int HandleEvents();
    int HandleKeys();
    int Update(SDL_Renderer *rend, int dt);
    int Draw(SDL_Renderer *rend);
    int Cleanup();

public:
    Game();
    int Execute();
};

#endif