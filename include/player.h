#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity {
private:
public:
    int Push(double amnt);
    int Update(Camera cam);
};

#endif