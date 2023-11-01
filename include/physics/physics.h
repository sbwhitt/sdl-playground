#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>

#include "game_objects/entity.h"
#include "game_objects/hitbox.h"
#include "geometry/point.h"

bool InCollisionRange(Hitbox h1, Hitbox h2);
bool HasCollision(Hitbox h1, Hitbox h2);
std::vector<Point> GetCollisionPoints(Hitbox h1, Hitbox h2);
int Separate(Entity *e1, Entity *e2);
int HandleCollision(Entity *e1, Entity *e2);
int HandleFriction(Entity *e);

#endif