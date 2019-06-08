#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "framework/ecs/ComponentManager.hpp"
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
    void init(float width, float height) {
        using constants::PADDLE_WIDTH;
        using constants::PADDLE_BORDER_DISTANCE;
        Rectangle boardArea { {0, 0}, width, height };
        createWalls(world, boardArea);
        createScoreboard(world, boardArea);
        createPlayerPaddle(boardArea, PADDLE_BORDER_DISTANCE);
        createBotPaddle(boardArea, width - PADDLE_WIDTH - PADDLE_BORDER_DISTANCE);
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
