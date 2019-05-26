#pragma once

#include <vector>
#include "find-squared-distance.hpp"
#include "../shapes/Circle.hpp"
#include "../shapes/LineSegment.hpp"
#include "../shapes/Rectangle.hpp"

std::vector<LineSegment> findClosestEdges(const Rectangle& rect, const Circle& circle) {
    std::array<LineSegment, 4> edges = rect.getEdges();
    std::vector<LineSegment> result;
    result.reserve(4);
    float distance = -1;

    for (const LineSegment& edge : edges) {
        float d = findSquaredDistance(edge, circle.center);

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
