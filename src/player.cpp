#include <math.h>

#include "game_objects/player.h"

#define MAX_VELOCITY 16

int Player::Push(double amnt) {
    // x = cos(angle*pi / 180), y = sin(tex->angle*pi / 180) (converting tex->angle from degrees to radians)
    Vec2 p{cos((this->tex->angle*M_PI)/180)*amnt, sin((this->tex->angle*M_PI)/180)*amnt};
    if (abs(this->vel.x) < MAX_VELOCITY) { this->vel.x += p.x; }
    if (abs(this->vel.y) < MAX_VELOCITY) { this->vel.y += p.y; }
    // this->vel += p;

    return 0;
}
