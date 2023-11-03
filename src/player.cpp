#include <math.h>

#include "game_objects/player.h"

Player::Player() {}

int Player::Push(double amnt) {
    // x = cos(angle*pi / 180), y = sin(tex->angle*pi / 180) (converting tex->angle from degrees to radians)
    Vec2 v{cos((this->tex->angle*M_PI)/180)*amnt, sin((this->tex->angle*M_PI)/180)*amnt};
    this->AddVelocity(v);

    return 0;
}
