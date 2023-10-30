#ifndef PHYSICS_H
#define PHYSICS_H

#include "game_objects/entity.h"
#include "game_objects/hitbox.h"

bool InCollisionRange(Hitbox h1, Hitbox h2);
bool HasCollision(Hitbox h1, Hitbox h2);

#endif