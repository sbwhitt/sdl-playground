#include <iostream>

// stopping undefined reference to WinMain
#define SDL_MAIN_HANDLED

#include "game.h"

#define SCR_WIDTH 960
#define SCR_HEIGHT 720

int main(int argc, char **argv) {
    Game game;

    if (game.Execute() != 0) {
        std::cout << "error exiting game.run" << std::endl;
    }

    return 0;
}
