#pragma once

#include <iostream>
#include "engine/physics/interactions.hpp"
#include "engine/shapes/Circle.hpp"
#include "engine/shapes/Line.hpp"
#include "engine/shapes/LineSegment.hpp"
#include "engine/shapes/MovingCircle.hpp"
#include "engine/shapes/Point.hpp"
#include "engine/shapes/Rectangle.hpp"

std::ostream& operator<<(std::ostream& stream, const Point& p) {
    return stream << "(" << p.x << ", " << p.y << ")";
}

std::ostream& operator<<(std::ostream& stream, const Circle& c) {
    return stream << "(" << c.center << ", r = " << c.radius << ")";
}

std::ostream& operator<<(std::ostream& stream, const Line& l) {
    return stream << "(P = " << l.point << ", v = " << l.direction << ")";
}

std::ostream& operator<<(std::ostream& stream, const LineSegment& l) {
    return stream << "(" << l.p1 << ", " << l.p2 << ")";
}

std::ostream& operator<<(std::ostream& stream, const Rectangle& r) {
    return stream << "(" << r.corner << ", w = " << r.width << ", h = " << r.height << ")";
}


std::ostream& operator<<(std::ostream& stream, const MovingCircle& c) {
    return stream << "(circle = " << c.circle << ", velocity = " << c.velocity << ")";
}
