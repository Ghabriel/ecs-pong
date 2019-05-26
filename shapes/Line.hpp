#pragma once

#include "LineSegment.hpp"
#include "Point.hpp"

struct Line {
    Point point;
    Vector direction;

    static Line fromSegment(const LineSegment& l) {
        return { l.p1, (l.p2 - l.p1) };
    }

    Point pointAt(float t) const {
        return point + t * direction;
    }
};
