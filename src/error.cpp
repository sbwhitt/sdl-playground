#include <iostream>
#include <SDL_error.h>

#include "utils/error.h"

void SDLErrorMsg(const char *msg) {
    printf("%s\n", msg);
    printf("\t%s\n", SDL_GetError());
}

void ErrorMsg(const char *msg) {
    printf("Error: %s\n", msg);
}
