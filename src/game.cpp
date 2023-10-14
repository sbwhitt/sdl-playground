#include <iostream>

#include "game.h"
#include "error.h"
#include "render.h"
#include "map.h"

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

    if (this->window.Create(150, 30, WIN_WIDTH, WIN_HEIGHT) != 0) {
        SDL_Quit();
        return 1;
    }

    // TODO: add renderer to window obj?
    this->renderer = SDL_CreateRenderer(this->window.SDL_win, -1, 0);
    if (this->renderer == nullptr) {
        SDL_DestroyWindow(this->window.SDL_win);
        SDLErrorMsg("SDL create renderer error: ");
        SDL_Quit();
        return 1;
    }

    this->cam.Init(WIN_WIDTH, WIN_HEIGHT);

    this->map.InitChunkMatrix(3, 3, WIN_WIDTH, WIN_HEIGHT);

    return 0;
}

int Game::Load(SDL_Renderer *rend) {
    Resource f{"res/fish.bmp", 200, 100};
    if (this->player.LoadFromResource(rend, f) != 0) {
        SDLErrorMsg("SDL error loading resource: ");
        return 1;
    }

    this->player.PlaceOnScreen(this->cam.GetCenter());

    return 0;
}

int Game::Execute() {
    if (this->Init() != 0) return 1;

    if (this->Load(this->renderer) != 0) return 1;

    while(this->running) {
        int dt = SDL_GetTicks() - this->ticks;
        while (dt < FRAME_DELAY) {
            continue;
        }

        if (this->Update(this->renderer) != 0 ||
            this->Draw(this->renderer)   != 0) 
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
        this->player.Rotate(-5);
    }
    if (this->ctrl.CheckKey(SDLK_e)) {
        this->player.Rotate(5);
    }
    if (this->ctrl.CheckKey(SDLK_SPACE)) {
        this->player.Push(0.66);
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

int Game::Update(SDL_Renderer *rend) {
    this->HandleEvents();
    this->HandleKeys();

    this->map.UpdateChunks(this->player.world_pos, this->cam);
    this->player.Update(this->cam);

    this->cam.Follow(this->player.GetScreenPosition());

    this->ticks = SDL_GetTicks();

    return 0;
}

int Game::Draw(SDL_Renderer *rend) {
    SetRenderColor(rend, Color{0, 0, 0});
    SDL_RenderClear(rend);

    this->map.RenderChunks(rend, this->cam);
    this->player.Draw(rend, this->cam);

    // this->cam.DrawOutline(rend);

    SDL_RenderPresent(rend);
    return 0;
}

int Game::Cleanup() {
    SDL_DestroyWindow(this->window.SDL_win);
    SDL_DestroyRenderer(this->renderer);

    SDL_Quit();
    return 0;
}
