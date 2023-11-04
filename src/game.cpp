#include <iostream>

#include "game.h"
#include "map/map.h"
#include "utils/error.h"
#include "render/renderer.h"
#include "render/graphics.h"
#include "physics/physics.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define FRAME_RATE 60
#define FRAME_DELAY (int)(1000 / FRAME_RATE)

Game::Game() {}

int Game::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDLErrorMsg("SDL video init error: ");
        return 1;
    }

    if (this->window->Create(150, 30, WIN_WIDTH, WIN_HEIGHT) != 0 ||
        this->renderer->Create(this->window, 0)              != 0 ||
        this->cam.Init(WIN_WIDTH, WIN_HEIGHT)                != 0)
    {
        ErrorMsg("game.cpp error initializing");
        SDL_Quit();
        return 1;
    }

    return 0;
}

int Game::Load() {
    this->map.LoadTileset(this->renderer, "res/tilesets/simple.json");

    this->player->LoadTexture(this->renderer, Resource{"res/fish.bmp", 200, 100});
    this->player->Place(Point{0, 0});
    this->entities.push_back(this->player);

    auto follow1 = new Entity(ENT_FOLLOWER);
    follow1->LoadTexture(this->renderer, Resource{"res/blowfish.bmp", 164, 128});
    follow1->Place(Point{-500, 100});
    this->entities.push_back(follow1);

    auto follow2 = new Entity(ENT_FOLLOWER);
    follow2->LoadTexture(this->renderer, Resource{"res/starfish.bmp", 128, 128});
    follow2->Place(Point{-100, 500});
    this->entities.push_back(follow2);

    auto rock1 = new Entity(ENT_OBSTACLE);
    rock1->LoadTexture(this->renderer, Resource{"res/rock.bmp", 150, 100});
    rock1->Place(Point{-150, -150});
    this->entities.push_back(rock1);

    auto rock2 = new Entity(ENT_OBSTACLE);
    rock2->LoadTexture(this->renderer, Resource{"res/rock.bmp", 150, 100});
    rock2->Place(Point{150, 150});
    this->entities.push_back(rock2);

    return 0;
}

int Game::Execute() {
    if (this->Init() != 0) return 1;

    if (this->Load() != 0) return 1;

    int dt = 0;
    while(this->running) {
        while (SDL_GetTicks() - this->ticks < FRAME_DELAY) {
            continue;
        }

        dt = SDL_GetTicks() - this->ticks;
        if (this->Update(dt) != 0 ||
            this->Draw() != 0) 
        {
            return 1;
        }
    }

    this->Cleanup();

    return 0;
}

int Game::HandleKeyDown(SDL_Keycode key) {
    this->ctrl.SetKey(key, true);
    switch (key) {
        case SDLK_ESCAPE:
            this->running = false;
            break;
    }

    return 0;
}

int Game::HandleMouseDown(SDL_MouseButtonEvent button) {
    switch (button.button) {
        case SDL_BUTTON_LEFT:
            break;
        case SDL_BUTTON_MIDDLE:
            break;
        case SDL_BUTTON_RIGHT:
            break;
    }
    
    return 0;
}

int Game::HandleKeys() {
    if (this->ctrl.CheckKey(SDLK_q)) {
        this->player->Rotate(-5);
    }
    if (this->ctrl.CheckKey(SDLK_e)) {
        this->player->Rotate(5);
    }
    if (this->ctrl.CheckKey(SDLK_SPACE)) {
        this->player->Push(1);
    }

    return 0;
}

int Game::HandleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                this->running = false;
                break;
            case SDL_KEYDOWN:
                this->HandleKeyDown(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                this->ctrl.SetKey(event.key.keysym.sym, false);
                break;
            case SDL_MOUSEBUTTONDOWN:
                this->HandleMouseDown(event.button);
                break;
        }
    }
    return 0;
}

int Game::Update(int dt) {
    this->HandleEvents();
    this->HandleKeys();

    this->map.UpdateChunks(this->player->world_pos);

    for (auto e : this->entities) {
        switch (e->type) {
            case ENT_FOLLOWER: {
                e->Follow(this->player->world_pos);
            }
        }
        HandleCollisions(e, this->entities);
        HandleFriction(e);
        e->Update(dt);
    }

    this->cam.Follow(this->player->world_pos);

    this->ticks = SDL_GetTicks();

    return 0;
}

int Game::Draw() {
    this->renderer->SetRenderColor(Color{0, 0, 0});
    this->renderer->Clear();

    this->map.DrawChunks(this->renderer, this->cam);
    for (auto e : this->entities) {
        e->Draw(this->renderer, this->cam);
    }
    this->player->Draw(this->renderer, this->cam);

    this->renderer->RenderPresent();
    return 0;
}

int Game::Cleanup() {
    delete this->window;
    this->window = NULL;

    delete this->renderer;
    this->renderer = NULL;

    for (auto e : this->entities) {
        delete e;
        e = NULL;
    }
    this->entities.clear();
    this->player = NULL;

    SDL_Quit();
    return 0;
}
