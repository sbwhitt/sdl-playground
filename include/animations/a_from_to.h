#ifndef A_FROM_TO
#define A_FROM_TO

#include "animations/animation.h"

class A_FromTo : public Animation {
private:
    int from;
    int to;
    bool dir = true;

public:
    A_FromTo(int f, int t, int i) {
        this->from = f;
        this->value = f;
        this->to = t;
        this->interval = i;
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