#pragma once

#include "../shapes/LineSegment.hpp"
#include "../shapes/Point.hpp"

namespace physics {
    float findSquaredDistance(const Point& p1, const Point& p2) {
        return (p2 - p1).getSquaredNorm();
    }

    float findSquaredDistance(const LineSegment& edge, const Point& point) {
        float squaredLength = edge.getSquaredLength();
        Vector direction = edge.getDirection();
        float t = direction.dot(point - edge.p1) / squaredLength;
        t = std::clamp(t, 0.f, 1.f);
        Point projection = edge.p1 + t * direction;

        return findSquaredDistance(point, projection);
    }
}
