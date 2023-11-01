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

std::vector<Point> GetCollisionPoints(Hitbox h1, Hitbox h2) {
    std::vector<Point> collisions;
    for (int i = 0; i < h1.lines.size(); i++) for (int j = 0; j < h2.lines.size(); j++) {
        Point p;
        if (GetIntersection(h1.lines[i].start, h1.lines[i].end, h2.lines[j].start, h2.lines[j].end, &p)) {
            collisions.push_back(p);
        }
    }

    return collisions;
}

// moving e1 out of the bounds of e2
int Separate(Entity *e1, Entity *e2) {
    if (e1->hitbox.center.x > e2->hitbox.center.x) {
        e1->Move(2, 0);
    }
    else if (e1->hitbox.center.x <= e2->hitbox.center.x) {
        e1->Move(-2, 0);
    }
    if (e1->hitbox.center.y > e2->hitbox.center.y) {
        e1->Move(0, 2);
    }
    else if (e1->hitbox.center.y <= e2->hitbox.center.y) {
        e1->Move(0, -2);
    }
    e1->vel.x = e1->vel.x/2 * -1;
    e1->vel.y = e1->vel.y/2 * -1;
    return 0;
}

// handling e1 colliding with e2
int HandleCollision(Entity *e1, Entity *e2) {
    if (HasCollision(e1->hitbox, e2->hitbox)) {
        Separate(e1, e2);
    }

    return 0;
}

int HandleFriction(Entity *e) {
    if (e->vel.x > 0) e->vel.x -= 0.2;
    else if (e->vel.x < 0) e->vel.x += 0.2;
    if (e->vel.y > 0) e->vel.y -= 0.2;
    else if (e->vel.y < 0) e->vel.y += 0.2;

    return 0;
}
