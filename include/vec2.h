#ifndef VEC2_H
#define VEC2_H

struct Vec2 {
    double x;
    double y;

    Vec2 () {}
    Vec2(double vx, double vy) {
        x = vx;
        y = vy;
    }
    Vec2 operator+(Vec2 v) {
        return Vec2{x + v.x, y + v.y};
    }
    Vec2 operator-(Vec2 v) {
        return Vec2{x - v.x, y - v.y};
    }
    Vec2& operator+=(Vec2 v) {
        x += v.x;
        y += v.y;
        return *this;
    }
};

#endif