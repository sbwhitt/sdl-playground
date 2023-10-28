#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <SDL_render.h>

#include "window/window.h"
#include "utils/color.h"

class Renderer {
private:
    Window *win;
    SDL_Renderer *SDL_rend;

public:
    Renderer();
    ~Renderer();
    int Create(Window *win, Uint32 flags);
    SDL_Texture* CreateTexture(std::string file);
    int SetRenderColor(Color c);
    int Clear();
    int RenderTexture(SDL_Texture *texture, SDL_Rect *rect, double angle);
    int RenderPoint(int x, int y);
    int RenderLine(int x1, int x2, int y1, int y2);
    int RenderRect(SDL_Rect r);
    void RenderPresent();
};

#endif