#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL_stdinc.h>

struct Animation {
    int timer = 0;
    Uint8 value;
    Uint8 from;
    Uint8 to;
    int interval;
    bool dir = true;

    Animation() {}
    Animation(Uint8 f, Uint8 t, int i) {
        this->from = f;
        this->value = f;
        this->to = t;
        this->interval = i;
    }
    int Update(int dt) {
        this->timer += dt;
        if (this->timer >= this->interval*dt) {
            this->timer = 0;
            if (this->dir) this->value += 1;
            else this->value -= 1;
            if (this->value == this->to || this->value == this->from) {
                this->dir = !this->dir;
            }
        }

        return 0;
    }
};

#endif