#ifndef RENDER_H
#define RENDER_H

#include <SDL_render.h>

#include "utils/color.h"

int SetRenderColor(SDL_Renderer *rend, Color c);

#endif