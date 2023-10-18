#ifndef A_INCREASE
#define A_INCREASE

#include "animations/animation.h"

class A_Increase : public Animation {
private:
    int by;

public:
    A_Increase(AnimationType type, int by, int interval) {
        this->type = type;
        this->by = by;
        this->value = by;
        this->interval = interval;
    }

    int Update(int dt) {
        this->timer += dt;
        if (this->timer >= this->interval*dt) {
            this->timer = 0;
            this->value += this->by; 
        }

        return 0;
    }
};

#endif