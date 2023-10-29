#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SDL.h>

#include "window/window.h"
#include "control/control.h"
#include "game_objects/camera.h"
#include "render/renderer.h"
#include "render/lighting.h"
#include "map/map.h"
#include "game_objects/entity.h"
#include "game_objects/player.h"

class Game {
private:
    bool running = true;
    int ticks = 0;
    Window *window = new Window();
    Renderer *renderer = new Renderer();
    Control ctrl;
    Camera cam;
    Map map;
    Player player;
    Entity rock;

    int Init();
    int Load();
    int HandleKeyDown(SDL_Keycode key);
    int HandleMouseDown(SDL_MouseButtonEvent button);
    int HandleEvents();
    int HandleKeys();
    int Update(int dt);
    int Draw();
    int Cleanup();

public:
    Game();
    int Execute();
};

#endif