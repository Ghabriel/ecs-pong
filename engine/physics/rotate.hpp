#pragma once

#include "../shapes/Line.hpp"
#include "../shapes/Point.hpp"

Point rotate(const Point& point, float angle) {
    float sin = std::sin(angle);
    float cos = std::cos(angle);
    float x = cos * point.x - sin * point.y;
    float y = sin * point.x + cos * point.y;

    return { x, y };
}

Point rotate(const Point& point, float angle, const Point& axis) {
    return rotate(point - axis, angle) + axis;
}
