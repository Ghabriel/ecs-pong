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

    bool containsPoint(const Point& p) const {
        float squaredLength = getSquaredLength();
        float d1 = (p - p1).norm();
        float d2 = (p - p2).norm();
        float squaredSum = (d1 + d2) * (d1 + d2);

        return std::abs(squaredSum - squaredLength) < 1e-3;
    }
};
