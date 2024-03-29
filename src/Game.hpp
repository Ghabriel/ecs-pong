#pragma once

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "engine-glue/ecs.hpp"
#include "engine/shapes/Rectangle.hpp"
#include "engine/state-management/StateMachine.hpp"
#include "init/create-ball.hpp"
#include "init/create-paddle.hpp"
#include "init/create-scoreboard.hpp"
#include "init/create-walls.hpp"
#include "states/RunningState.hpp"
#include "states/WaitingState.hpp"

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

        stateMachine.registerState("waiting", std::make_unique<WaitingState>(world, stateMachine));
        stateMachine.registerState("running", std::make_unique<RunningState>(world, stateMachine));
        stateMachine.pushState("waiting");
    }

    void update(const sf::Time& elapsedTime) {
        stateMachine.getState().update(elapsedTime);
    }

    void render(sf::RenderWindow& window) {
        stateMachine.getState().render(window);
    }

 private:
    ecs::ComponentManager world;
    state::StateMachine stateMachine;

    void createPlayerPaddle(const Rectangle& boardArea, float x) {
        ecs::Entity id = createPaddle(world, boardArea, x);
        world.addComponent<Input>(id, { });
    }

    void createBotPaddle(const Rectangle& boardArea, float x) {
        createPaddle(world, boardArea, x);
    }
};
