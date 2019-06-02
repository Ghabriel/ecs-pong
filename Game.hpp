#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "components/RectangularObject.hpp"
#include "framework/ComponentManager.hpp"
#include "helpers/create-ball.hpp"
#include "helpers/create-paddle.hpp"
#include "shapes/Rectangle.hpp"
#include "systems/render-world.hpp"
#include "systems/update-world.hpp"

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

    void update(const sf::Time& elapsedTime) {
        unsigned elapsedTimeMicro = elapsedTime.asMicroseconds();
        float normalizedElapsedTime = elapsedTimeMicro / 1000000.0;
        updateWorld(world, normalizedElapsedTime, boardArea);
    }

    void render(sf::RenderWindow& window) {
        renderWorld(world, window);
    }

 private:
    ecs::ComponentManager world;
    Rectangle boardArea { {0, 0}, 800, 600 };
};
