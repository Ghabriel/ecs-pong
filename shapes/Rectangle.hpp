#pragma once

#include "LineSegment.hpp"
#include "OrientedLineSegment.hpp"
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

    std::array<OrientedLineSegment, 4> getOrientedEdges() const {
        auto [e1, e2, e3, e4] = getEdges();

        OrientedLineSegment o1 { e1, {0, -1} };
        OrientedLineSegment o2 { e2, {1, 0} };
        OrientedLineSegment o3 { e3, {0, 1} };
        OrientedLineSegment o4 { e4, {-1, 0} };

        return { o1, o2, o3, o4 };
    }
};
