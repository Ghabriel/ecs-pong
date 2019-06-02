#pragma once

#include <algorithm>
#include "../components/Bounds.hpp"
#include "../components/RectangularObject.hpp"
#include "../framework/ComponentManager.hpp"
#include "../shapes/Rectangle.hpp"

void applyRectangleBounds(ecs::ComponentManager& world) {
    world.query<Bounds, RectangularObject>(
        [](Entity, const Bounds& bounds, RectangularObject& obj) {
            Rectangle& body = obj.body;
            float lowerBound = bounds.lowerBound;
            float upperBound = bounds.upperBound - body.height;
            float& y = body.corner.y;

            y = std::clamp(y, lowerBound, upperBound);
        }
    );
}
