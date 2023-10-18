#ifndef A_FROM_TO
#define A_FROM_TO

#include "animations/animation.h"

class A_FromTo : public Animation {
private:
    int from;
    int to;
    bool dir = true;

public:
    A_FromTo(AnimationType type, int from, int to, int interval) {
        this->type = type;
        this->from = from;
        this->value = from;
        this->to = to;
        this->interval = interval;

        if (this->from > this->to) this->dir = false;
    }
    int Update(int dt) override {
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