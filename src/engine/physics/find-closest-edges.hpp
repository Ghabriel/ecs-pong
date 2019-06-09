#pragma once

#include <vector>
#include "find-squared-distance.hpp"
#include "../shapes/Circle.hpp"
#include "../shapes/LineSegment.hpp"
#include "../shapes/Rectangle.hpp"

std::vector<OrientedLineSegment> findClosestEdges(const Rectangle& rect, const Circle& circle) {
    std::array<OrientedLineSegment, 4> edges = rect.getOrientedEdges();
    std::vector<OrientedLineSegment> result;
    result.reserve(4);
    float distance = -1;

    for (const OrientedLineSegment& edge : edges) {
        float d = findSquaredDistance(edge.segment, circle.center);

        if (std::abs(d - distance) < 1e-3) {
            result.push_back(edge);
        } else if (distance == -1 || d < distance) {
            result.clear();
            result.push_back(edge);
            distance = d;
        }
    }

    return result;
}
