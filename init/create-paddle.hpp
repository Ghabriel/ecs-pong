#pragma once

#include "../constants.hpp"
#include "../framework/ecs/userland.hpp"
#include "../shapes/Rectangle.hpp"

ecs::Entity createPaddle(ecs::ComponentManager& world, const Rectangle& boardArea, float x) {
    using constants::PADDLE_WIDTH;
    using constants::PADDLE_HEIGHT;
    float y = boardArea.corner.y + (boardArea.height / 2);

    return world.createEntity(
        Drawable { },
        Position { x + PADDLE_WIDTH / 2, y },
        RectangularObject { PADDLE_WIDTH, PADDLE_HEIGHT }
    );
}
