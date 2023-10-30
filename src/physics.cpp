#include "physics/physics.h"
#include "geometry/geometry.h"
#include "utils/direction.h"

bool InCollisionRange(Hitbox h1, Hitbox h2) {
    // length of both hitboxes from their centers to corner, min dist required to collide
    int diag_length = Distance(h1.center, h1.lines[UP].start) + Distance(h2.center, h2.lines[UP].start);
    if (Distance(h1.center, h2.center) > diag_length) {
        return false;
    }

    return true;
}

bool HasCollision(Hitbox h1, Hitbox h2) {
    // check if in range for collision first
    if (!InCollisionRange(h1, h2)) return false;

    for (int i = 0; i < h1.lines.size(); i++) for (int j = 0; j < h2.lines.size(); j++) {
        if (Intersects(h1.lines[i], h2.lines[j])) return true;
    }

    return false;
}
