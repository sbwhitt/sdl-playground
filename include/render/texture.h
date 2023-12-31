#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <SDL_stdinc.h>
#include <SDL_rect.h>

#include "render/renderer.h"
#include "utils/resource.h"
#include "utils/error.h"
#include "animations/animation.h"

class Texture {
private:
    Uint8 alpha;
    SDL_Texture *texture = NULL;
    std::vector<Animation*> anims;

    int SetAlpha(Uint8 a);
    int ModAlpha(Uint8 mod);
    int ApplyAnimation(Animation *a);

public:
    double angle = 0;
    SDL_Rect rect;

    Texture();
    Texture(Renderer *rend, Resource r);
    ~Texture();
    int LoadFromResource(Renderer *rend, Resource res);
    int AddAnimation(Animation *a);
    int UpdateAnimations(int dt);
    int Render(Renderer *rend);
};

#endif