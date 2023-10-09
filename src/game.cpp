#include <iostream>

#include "game.h"
#include "graphics.h"
#include "mouse.h"

Game::Game() {}

int Game::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL video init error: " << SDL_GetError() << std::endl;
        return 1;
    }

    this->window.Create(300, 100, 960, 720);
    if (this->window.SDL_win == nullptr) {
        std::cout << "SDL create window error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    this->renderer = SDL_CreateRenderer(this->window.SDL_win, -1, 0);
    if (this->renderer == nullptr) {
        SDL_DestroyWindow(this->window.SDL_win);
        std::cout << "SDL create renderer error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    return 0;
}

int Game::Load() {
    for (int i = 0; i < 50; i++) {
        Circle c{Point{10 + (i*10), 10 + (i*10)}, 25};
        this->circles.push_back(c);
    }    

    return 0;
}

int Game::Execute() {
    if (this->Init() != 0) return 1;

    if (this->Load() != 0) return 1;

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
    switch (key) {
        case SDLK_q:
            this->running = false;
    }

    return 0;
}

int Game::HandleMouseDown(SDL_MouseButtonEvent button) {
    switch (button.button) {
        case SDL_BUTTON_LEFT:
        case SDL_BUTTON_MIDDLE:
        case SDL_BUTTON_RIGHT:
        default:
            return 0;
    }
    
    return 0;
}

int Game::HandleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                this->running = false;
            case SDL_KEYDOWN:
                this->HandleKeyDown(event.key.keysym.sym);
            case SDL_MOUSEBUTTONDOWN:
                this->HandleMouseDown(event.button);
            default:
                continue;
        }
    }

    return 0;
}

int Game::Update(SDL_Renderer *rend) {
    this->HandleEvents();

    this->ticks = SDL_GetTicks();

    return 0;
}

int Game::Draw(SDL_Renderer *rend) {
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    
    SDL_RenderClear(rend);

    SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);

    DrawCircles(rend, this->circles);

    SDL_RenderPresent(rend);
    return 0;
}

int Game::Cleanup() {
    SDL_DestroyWindow(this->window.SDL_win);
    SDL_DestroyRenderer(this->renderer);

    SDL_Quit();
    return 0;
}
