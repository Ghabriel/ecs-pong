#pragma once

#include <algorithm>
#include "../components/Bounds.hpp"
#include "../components/RectangularObject.hpp"
#include "../framework/ComponentManager.hpp"
#include "../shapes/Rectangle.hpp"

void applyRectangleBounds(ecs::ComponentManager& world) {
    world.findAll<Position>()
        .join<RectangularObject>()
        .forEach([&world](Position& pos, const RectangularObject& obj) {
            world.findAll<Wall>().forEach([&pos, &obj](const Wall& wall) {
                const LineSegment& lineSegment = wall.body.segment;
                const Vector& normal = wall.body.normal;

                // TODO: implement proper collision detection
                float wallY = lineSegment.p1.y;
                float halfHeight = obj.height / 2;
                if (normal == Vector { 0, 1 }) {
                    pos.location.y = std::max(pos.location.y, wallY + halfHeight);
                } else if (normal == Vector { 0, -1 }) {
                    pos.location.y = std::min(pos.location.y, wallY - halfHeight);
                }
            });
        });
}
