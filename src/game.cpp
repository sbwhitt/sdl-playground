#include <iostream>

#include "game.h"
#include "error.h"
#include "graphics.h"
#include "mouse.h"
#include "map.h"

#define WIN_WIDTH 960
#define WIN_HEIGHT 720

Game::Game() {}

int Game::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDLErrorMsg("SDL video init error: ");
        return 1;
    }

    if (this->window.Create(300, 100, WIN_WIDTH, WIN_HEIGHT) != 0) {
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

    this->map.InitChunkMatrix(101, 101, WIN_WIDTH, WIN_HEIGHT);

    return 0;
}

int Game::Load(SDL_Renderer *rend) {
    Resource f{"res/fish.bmp", 200, 100};
    if (this->fish.LoadFromResource(rend, f) != 0) {
        SDLErrorMsg("SDL error loading resource: ");
        return 1;
    }

    this->fish.PlaceOnScreen(this->cam.center);

    return 0;
}

int Game::Execute() {
    if (this->Init() != 0) return 1;

    if (this->Load(this->renderer) != 0) return 1;

    while(this->running) {
        // loose cap at 60 fps
        while (SDL_GetTicks() - this->ticks < 17) {
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
    // if (this->ctrl.CheckKey(SDLK_w)) {
    //     this->fish.Push(0, -0.3);
    // }
    // if (this->ctrl.CheckKey(SDLK_s)) {
    //     this->fish.Push(0, 0.3);
    // }
    // if (this->ctrl.CheckKey(SDLK_a)) {
    //     this->fish.Push(-0.3, 0);
    // }
    // if (this->ctrl.CheckKey(SDLK_d)) {
    //     this->fish.Push(0.3, 0);
    // }
    if (this->ctrl.CheckKey(SDLK_q)) {
        this->fish.Rotate(-3.5);
    }
    if (this->ctrl.CheckKey(SDLK_e)) {
        this->fish.Rotate(3.5);
    }
    if (this->ctrl.CheckKey(SDLK_SPACE)) {
        this->fish.Push(1);
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

    this->map.UpdateChunks(this->cam);
    this->fish.Update(this->cam);

    this->cam.Follow(this->fish.GetScreenPosition());

    this->ticks = SDL_GetTicks();

    return 0;
}

int Game::Draw(SDL_Renderer *rend) {
    SDL_SetRenderDrawColor(rend, 50, 150, 200, 255);
    SDL_RenderClear(rend);

    this->map.RenderChunks(rend, this->cam);
    this->fish.Draw(rend, this->cam);

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
