#include "game_objects/hitbox.h"
#include "game_objects/entity.h"
#include "render/renderer.h"
#include "utils/direction.h"
#include "geometry/geometry.h"

Hitbox::Hitbox() {}

Hitbox::Hitbox(int width, int height, Point center) {
    this->width = width;
    this->height = height;
    this->center = center;

    this->lines[UP] = Line{
        Point{center.x - (int)(this->width/2), center.y - (int)(this->height/2)},
        Point{center.x + (int)(this->width/2), center.y - (int)(this->height/2)},
    };

    this->lines[RIGHT] = Line{
        Point{center.x + (int)(this->width/2), center.y - (int)(this->height/2)},
        Point{center.x + (int)(this->width/2), center.y + (int)(this->height/2)},
    };

    this->lines[DOWN] = Line{
        Point{center.x - (int)(this->width/2), center.y + (int)(this->height/2)},
        Point{center.x + (int)(this->width/2), center.y + (int)(this->height/2)},
    };

    this->lines[LEFT] = Line{
        Point{center.x - (int)(this->width/2), center.y - (int)(this->height/2)},
        Point{center.x - (int)(this->width/2), center.y + (int)(this->height/2)},
    };
}

int Hitbox::Rotate(double angle) {
    for (int i = 0; i < this->lines.size(); i++) {
        this->lines[i].RotateAround(angle, this->center);
    }

    return 0;
}

int Hitbox::Update(Point c, double angle) {
    this->center = c;

    this->lines[UP] = Line{
        Point{center.x - (int)(this->width/2), center.y - (int)(this->height/2)},
        Point{center.x + (int)(this->width/2), center.y - (int)(this->height/2)},
    };

    this->lines[RIGHT] = Line{
        Point{center.x + (int)(this->width/2), center.y - (int)(this->height/2)},
        Point{center.x + (int)(this->width/2), center.y + (int)(this->height/2)},
    };

    this->lines[DOWN] = Line{
        Point{center.x - (int)(this->width/2), center.y + (int)(this->height/2)},
        Point{center.x + (int)(this->width/2), center.y + (int)(this->height/2)},
    };

    this->lines[LEFT] = Line{
        Point{center.x - (int)(this->width/2), center.y - (int)(this->height/2)},
        Point{center.x - (int)(this->width/2), center.y + (int)(this->height/2)},
    };

    this->Rotate(angle);

    return 0;
}

bool Hitbox::Collides(Hitbox h) {
    // check if in range for collision first
    // length of both hitboxes from their centers to corner, min dist required to collide
    int diag_length = Distance(this->center, this->lines[UP].start) + Distance(h.center, h.lines[UP].start);
    if (Distance(this->center, h.center) > diag_length) {
        return false;
    }

    for (int i = 0; i < this->lines.size(); i++) {
        for (int j = 0; j < h.lines.size(); j++) {
            if (Intersects(this->lines[i], h.lines[j])) return true;
        }
    }

    return false;
}

int Hitbox::Draw(Renderer *rend) {
    for (int i = 0; i < this->lines.size(); i++) {
        rend->RenderLine(this->lines[i]);
    }

    return 0;
}
