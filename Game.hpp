#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "framework/ComponentManager.hpp"
#include "init/create-ball.hpp"
#include "init/create-paddle.hpp"
#include "init/create-scoreboard.hpp"
#include "init/create-walls.hpp"
#include "shapes/Rectangle.hpp"
#include "systems/input-system.hpp"
#include "systems/movement-system.hpp"
#include "systems/paddle-bounding-system.hpp"
#include "systems/rendering-system.hpp"
#include "systems/scoring-system.hpp"

class Game {
 public:
    void init() {
        Rectangle boardArea { {0, 0}, 800, 600 };
        createWalls(world, boardArea);
        createScoreboard(world, boardArea);
        createPlayerPaddle(boardArea, 20);
        createBotPaddle(boardArea, 760);
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

    void createPlayerPaddle(const Rectangle& boardArea, float x) {
        ecs::Entity id = createPaddle(world, boardArea, x);
        world.addComponent<Input>(id, { });
    }

    void createBotPaddle(const Rectangle& boardArea, float x) {
        createPaddle(world, boardArea, x);
    }
};
