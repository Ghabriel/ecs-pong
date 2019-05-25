#pragma once

struct Point {
    float x;
    float y;
};

Point operator+(const Point& lhs, const Point& rhs) {
    return { lhs.x + rhs.x, lhs.y + rhs.y };
}

Point operator-(const Point& lhs, const Point& rhs) {
    return { lhs.x - rhs.x, lhs.y - rhs.y };
}

using Vector = Point;

struct Circle {
    Point center;
    float radius;
};
