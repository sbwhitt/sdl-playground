#include "game_objects/hitbox.h"
#include "game_objects/entity.h"
#include "render/renderer.h"

Hitbox::Hitbox() {}

Hitbox::Hitbox(int width, int height, Point center) {
    this->width = width;
    this->height = height;
    this->center = center;

    this->top = Line{
        Point{center.x - (int)(this->width/2), center.y - (int)(this->height/2)},
        Point{center.x + (int)(this->width/2), center.y - (int)(this->height/2)},
    };

    this->left = Line{
        Point{center.x - (int)(this->width/2), center.y - (int)(this->height/2)},
        Point{center.x - (int)(this->width/2), center.y + (int)(this->height/2)},
    };

    this->bottom = Line{
        Point{center.x - (int)(this->width/2), center.y + (int)(this->height/2)},
        Point{center.x + (int)(this->width/2), center.y + (int)(this->height/2)},
    };

    this->right = Line{
        Point{center.x + (int)(this->width/2), center.y - (int)(this->height/2)},
        Point{center.x + (int)(this->width/2), center.y + (int)(this->height/2)},
    };
}

int Hitbox::Rotate(double angle) {
    this->top.RotateAround(angle, this->center);
    this->left.RotateAround(angle, this->center);
    this->bottom.RotateAround(angle, this->center);
    this->right.RotateAround(angle, this->center);

    return 0;
}

int Hitbox::Update(Point c, double angle) {
    this->center = c;

    this->top = Line{
        Point{center.x - (int)(this->width/2), center.y - (int)(this->height/2)},
        Point{center.x + (int)(this->width/2), center.y - (int)(this->height/2)},
    };

    this->left = Line{
        Point{center.x - (int)(this->width/2), center.y - (int)(this->height/2)},
        Point{center.x - (int)(this->width/2), center.y + (int)(this->height/2)},
    };

    this->bottom = Line{
        Point{center.x - (int)(this->width/2), center.y + (int)(this->height/2)},
        Point{center.x + (int)(this->width/2), center.y + (int)(this->height/2)},
    };

    this->right = Line{
        Point{center.x + (int)(this->width/2), center.y - (int)(this->height/2)},
        Point{center.x + (int)(this->width/2), center.y + (int)(this->height/2)},
    };

    this->Rotate(angle);

    return 0;
}

bool Hitbox::Collides(Hitbox h) {
    if (this->left.Intersects(h.top)) return true;

    return false;
}

int Hitbox::Draw(Renderer *rend) {
    rend->RenderLine(this->top);
    rend->RenderLine(this->left);
    rend->RenderLine(this->bottom);
    rend->RenderLine(this->right);

    return 0;
}
