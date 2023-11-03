#ifndef PLAYER_H
#define PLAYER_H

#include "game_objects/entity.h"

class Player : public Entity {
private:
public:
    EntityType type = ENT_PLAYER;

    Player();
    int Push(double amnt);
};

#endif