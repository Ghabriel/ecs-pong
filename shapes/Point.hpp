#pragma once

#include <cmath>

struct Point {
    float x;
    float y;

    float getSquaredNorm() const {
        return (x * x) + (y * y);
    }

    float norm() const {
        return std::sqrt(getSquaredNorm());
    }

    Point normalize() const {
        float n = norm();
        return { x / n, y / n };
    }

    float dot(const Point& p) const {
        return (x * p.x) + (y * p.y);
    }
};

Point operator+(const Point& lhs, const Point& rhs) {
    return { lhs.x + rhs.x, lhs.y + rhs.y };
}

Point& operator+=(Point& lhs, const Point& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

Point operator-(const Point& lhs, const Point& rhs) {
    return { lhs.x - rhs.x, lhs.y - rhs.y };
}

Point operator-(const Point& p) {
    return { -p.x, -p.y };
}

Point operator*(float scalar, const Point& p) {
    return { scalar * p.x, scalar * p.y };
}

Point operator/(const Point& p, float scalar) {
    return { p.x / scalar, p.y / scalar };
}

using Vector = Point;
