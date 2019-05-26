#pragma once

#include "LineSegment.hpp"
#include "Point.hpp"

struct Rectangle {
    Point corner;
    float width;
    float height;

    std::array<LineSegment, 4> getEdges() const {
        Point p2 { corner.x + width, corner.y };
        Point p3 { corner.x + width, corner.y + height };
        Point p4 { corner.x, corner.y + height };

        LineSegment e1 { corner, p2 };
        LineSegment e2 { p2, p3 };
        LineSegment e3 { p3, p4 };
        LineSegment e4 { p4, corner };

        return { e1, e2, e3, e4 };
    }
};
