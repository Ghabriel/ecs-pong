#pragma once

#include <iostream>
#include "physics.hpp"
#include "../shapes/Circle.hpp"
#include "../shapes/Line.hpp"
#include "../shapes/LineSegment.hpp"
#include "../shapes/Point.hpp"
#include "../shapes/Rectangle.hpp"

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

std::ostream& operator<<(std::ostream& stream, const MovingRectangle& r) {
    return stream << "(rectangle = " << r.rectangle << ", velocity = " << r.velocity << ")";
}
