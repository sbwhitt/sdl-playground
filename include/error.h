#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <SDL_error.h>

void SDLErrorMsg(const char *msg) {
    std::cout << msg << SDL_GetError() << std::endl;
}

#endif