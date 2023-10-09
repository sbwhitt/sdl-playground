#include <iostream>
#include <SDL_error.h>

#include "error.h"

void SDLErrorMsg(const char *msg) {
    std::cout << msg << SDL_GetError() << std::endl;
}
