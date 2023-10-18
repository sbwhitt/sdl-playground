#ifndef ANIMATION_H
#define ANIMATION_H

#include "error.h"

class Animation {
protected:
    int interval;
    int timer = 0;

public:
    int value;

    Animation() {}
    virtual int Update(int dt) {
        ErrorMsg("unimplemented method in animation.h");

        return 1;
    }
};

#endif