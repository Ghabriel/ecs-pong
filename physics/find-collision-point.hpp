#pragma once

#include <vector>
#include "find-squared-distance.hpp"
#include "../shapes/Line.hpp"

Point findCollisionPoint(const Line& l1, const Line& l2) {
    float dx = l1.point.x - l2.point.x;
    float dy = l1.point.y - l2.point.y;
    auto [vx, vy] = l1.direction;
    auto [ux, uy] = l2.direction;
    float t = (ux * dy - uy * dx) / (vx * uy - vy * ux);

    return l1.pointAt(t);
}