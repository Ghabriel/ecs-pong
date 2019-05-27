#pragma once

#include "LineSegment.hpp"
#include "Point.hpp"

struct OrientedLineSegment {
    LineSegment segment;
    Vector normal;
};
