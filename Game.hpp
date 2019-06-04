#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "framework/ComponentManager.hpp"
#include "helpers/create-ball.hpp"
#include "helpers/create-paddle.hpp"
#include "helpers/create-scoreboard.hpp"
#include "helpers/create-walls.hpp"
#include "shapes/Rectangle.hpp"
#include "systems/input-system.hpp"
#include "systems/movement-system.hpp"
#include "systems/paddle-bounding-system.hpp"
#include "systems/rendering-system.hpp"
#include "systems/scoring-system.hpp"

ecs::Entity createLeftPaddle(ecs::ComponentManager& world, const Rectangle& boardArea) {
    ecs::Entity id = createPaddle(world, boardArea, 20);
    world.addComponent<Input>(id, { });
    return id;
}

ecs::Entity createRightPaddle(ecs::ComponentManager& world, const Rectangle& boardArea) {
    return createPaddle(world, boardArea, 760);
}

class Game {
 public:
    void init() {
        Rectangle boardArea { {0, 0}, 800, 600 };
        createWalls(world, boardArea);
        createScoreboard(world, boardArea);
        createLeftPaddle(world, boardArea);
        createRightPaddle(world, boardArea);
        createBall(world, boardArea);
    }

    void update(const sf::Time& elapsedTime) {
        unsigned elapsedTimeMicro = elapsedTime.asMicroseconds();
        float normalizedElapsedTime = elapsedTimeMicro / 1000000.0;

        useInputSystem(world);
        useMovementSystem(world, normalizedElapsedTime);
        usePaddleBoundingSystem(world);
        useScoringSystem(world);
    }

    void render(sf::RenderWindow& window) {
        useRenderingSystem(world, window);
    }

 private:
    ecs::ComponentManager world;
};
