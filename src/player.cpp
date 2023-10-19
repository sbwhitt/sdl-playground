#include <math.h>

#include "game_objects/player.h"

#define MAX_VELOCITY 50

int Player::Push(double amnt) {
    // x = cos(angle*pi / 180), y = sin(tex->angle*pi / 180) (converting tex->angle from degrees to radians)
    Vec2 p{cos((this->tex->angle*M_PI)/180)*amnt, sin((this->tex->angle*M_PI)/180)*amnt};
    if (this->vel.x < MAX_VELOCITY) { this->vel.x += p.x; }
    if (this->vel.y < MAX_VELOCITY) { this->vel.y += p.y; }
    // this->vel += p;

    return 0;
}

int Player::Update(Camera cam) {
    if (this->vel.x > 0) this->vel.x -= 0.2;
    else if (this->vel.x < 0) this->vel.x += 0.2;
    if (this->vel.y > 0) this->vel.y -= 0.2;
    else if (this->vel.y < 0) this->vel.y += 0.2;

    this->Move((int)this->vel.x, (int)this->vel.y);

    // get difference in player and cam world position
    Point d = this->world_pos - cam.world_pos;
    // place player on screen wrt cam center offset by d
    //this->PlaceOnScreen(cam.center + d);
    this->PlaceOnScreen(d);

    return 0;
}
