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
        e1->Move(1, 0);
    }
    else if (e1->hitbox.center.x <= e2->hitbox.center.x) {
        e1->Move(-1, 0);
    }
    if (e1->hitbox.center.y > e2->hitbox.center.y) {
        e1->Move(0, 1);
    }
    else if (e1->hitbox.center.y <= e2->hitbox.center.y) {
        e1->Move(0, -1);
    }
    return 0;
}

// handling e1 colliding with e2
int HandleCollision(Entity *e1, Entity *e2) {
    bool done = false;
    while (HasCollision(e1->hitbox, e2->hitbox)) {
        Separate(e1, e2);
        done = true;
    }
    if (done) {
        Point d{e1->hitbox.center.x - e2->hitbox.center.x, e1->hitbox.center.y - e2->hitbox.center.y};
        double mag = sqrt( (d.x*d.x) + (d.y*d.y) );
        Vec2 norm{d.x / mag, d.y / mag};
        e1->vel.x = e1->vel.x * norm.x;
        e1->vel.y = e1->vel.y * norm.y;
    }

    return 0;
}

int HandleCollisions(Entity *collider, std::vector<Entity*> entities) {
    for (auto e : entities) {
        if (collider != e && collider->type != ENT_OBSTACLE) {
            HandleCollision(collider, e);
        }
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
