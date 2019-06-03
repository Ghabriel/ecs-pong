#pragma once

#include <algorithm>
#include "../components/Bounds.hpp"
#include "../components/RectangularObject.hpp"
#include "../framework/ComponentManager.hpp"
#include "../shapes/Rectangle.hpp"

void applyRectangleBounds(ecs::ComponentManager& world) {
    world.query<Bounds, Position, RectangularObject>(
        [](ecs::Entity, const Bounds& bounds, Position& pos, const RectangularObject& obj) {
            float lowerBound = bounds.lowerBound + obj.height / 2;
            float upperBound = bounds.upperBound - obj.height / 2;
            float& y = pos.location.y;

            y = std::clamp(y, lowerBound, upperBound);
        }
    );
}
