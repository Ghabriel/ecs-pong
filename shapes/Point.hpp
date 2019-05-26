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

    float dot(const Point& p) const {
        return (x * p.x) + (y * p.y);
    }
};

Point operator+(const Point& lhs, const Point& rhs) {
    return { lhs.x + rhs.x, lhs.y + rhs.y };
}

Point operator-(const Point& lhs, const Point& rhs) {
    return { lhs.x - rhs.x, lhs.y - rhs.y };
}

Point operator*(float scalar, const Point& p) {
    return { scalar * p.x, scalar * p.y };
}

using Vector = Point;
