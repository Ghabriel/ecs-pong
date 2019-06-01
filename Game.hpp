#pragma once

#include "components/RectangularObject.hpp"
#include "framework/ComponentManager.hpp"
#include "helpers/create-ball.hpp"
#include "helpers/create-paddle.hpp"
#include "shapes/Rectangle.hpp"

using ecs::Entity;

Entity createLeftPaddle(ecs::ComponentManager& world, const Rectangle& boardArea) {
    return createPaddle(world, boardArea, 20);
}

Entity createRightPaddle(ecs::ComponentManager& world, const Rectangle& boardArea) {
    return createPaddle(world, boardArea, 760);
}

class Game {
 public:
    void init() {
        createLeftPaddle(world, boardArea);
        createRightPaddle(world, boardArea);
        createBall(world, boardArea);
    }

    void render() {
        // TODO
    }

 private:
    ecs::ComponentManager world;
    Rectangle boardArea { {0, 0}, 800, 600 };
};
