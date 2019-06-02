#pragma once

#include "../components/Bounds.hpp"
#include "../components/Drawable.hpp"
#include "../components/RectangularObject.hpp"
#include "../framework/ComponentManager.hpp"
#include "../shapes/Rectangle.hpp"

using ecs::Entity;

Entity createPaddle(ecs::ComponentManager& world, const Rectangle& boardArea, float x) {
    constexpr float width = 20;
    constexpr float height = 200;
    float y = boardArea.corner.y + (boardArea.height / 2) - (height / 2);

    Point corner { x, y };
    Rectangle rectangle { corner, width, height };

    return world.createEntity(
        Bounds { 0, boardArea.height },
        Drawable { },
        RectangularObject { rectangle }
    );
}
