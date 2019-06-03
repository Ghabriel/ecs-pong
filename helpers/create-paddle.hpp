#pragma once

#include "../components/Bounds.hpp"
#include "../components/Drawable.hpp"
#include "../components/Position.hpp"
#include "../components/RectangularObject.hpp"
#include "../framework/ComponentManager.hpp"
#include "../shapes/Rectangle.hpp"

ecs::Entity createPaddle(ecs::ComponentManager& world, const Rectangle& boardArea, float x) {
    constexpr float width = 20;
    constexpr float height = 200;
    float y = boardArea.corner.y + (boardArea.height / 2);

    return world.createEntity(
        Bounds { 0, boardArea.height },
        Drawable { },
        Position { x + width / 2, y },
        RectangularObject { width, height }
    );
}
