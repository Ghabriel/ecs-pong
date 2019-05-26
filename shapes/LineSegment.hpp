#pragma once

#include "Point.hpp"

struct LineSegment {
    Point p1;
    Point p2;

    float getSquaredLength() const {
        return (p2 - p1).getSquaredNorm();
    }

    Vector getDirection() const {
        return p2 - p1;
    }
};
