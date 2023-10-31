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

int Player::Update(int dt) {
    this->Move((int)this->vel.x, (int)this->vel.y);

    this->hitbox.Update(this->world_pos, this->tex->angle);

    if (this->vel.x > 0) this->vel.x -= 0.2;
    else if (this->vel.x < 0) this->vel.x += 0.2;
    if (this->vel.y > 0) this->vel.y -= 0.2;
    else if (this->vel.y < 0) this->vel.y += 0.2;

    return 0;
}
