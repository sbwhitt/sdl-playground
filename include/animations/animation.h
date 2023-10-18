#ifndef ANIMATION_H
#define ANIMATION_H

#include "error.h"

enum AnimationType {
    ALPHA = 0,
    POS_X = 1,
    POS_Y = 2
};

class Animation {
protected:
    int interval;
    int timer = 0;

public:
    AnimationType type;
    int value;

    Animation() {}
    virtual int Update(int dt) {
        ErrorMsg("unimplemented method in animation.h");

        return 1;
    }
};

#endif