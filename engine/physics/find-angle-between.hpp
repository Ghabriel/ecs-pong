#pragma once

#include "../shapes/Point.hpp"

float findAngleBetween(const Vector& u, const Vector& v) {
    float angle = std::atan2(v.y, v.x) - std::atan2(u.y, u.x);

    if (angle < 0) {
        angle += 2 * M_PI;
    }

    return angle;
}
