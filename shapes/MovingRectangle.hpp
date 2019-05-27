#pragma once

#include "Point.hpp"
#include "Rectangle.hpp"

struct MovingRectangle {
    Rectangle rectangle;
    Vector velocity;
};
