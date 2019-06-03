#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "components/Input.hpp"
#include "components/RectangularObject.hpp"
#include "components/Scoreboard.hpp"
#include "components/ScoreListener.hpp"
#include "framework/ComponentManager.hpp"
#include "helpers/create-ball.hpp"
#include "helpers/create-paddle.hpp"
#include "shapes/Rectangle.hpp"
#include "systems/input-system.hpp"
#include "systems/render-world.hpp"
#include "systems/movement-system.hpp"
#include "systems/rectangle-bounds-system.hpp"
#include "systems/scoring-system.hpp"

using ecs::Entity;

void createScoreboard(ecs::ComponentManager& world, const Rectangle& boardArea) {
    Entity id = world.createEntity(
        Scoreboard { { 0, 0 } },
        Position { boardArea.width / 2, 30 }
    );

    auto callback = [&world, id](Team team) {
        Scoreboard& scoreboard = world.getData<Scoreboard>(id);
        std::pair<unsigned, unsigned>& scores = scoreboard.scores;
        switch (team) {
            case Team::Left:
                std::cout << "Left scored\n";
                scores.first++;
                break;
            case Team::Right:
                std::cout << "Right scored\n";
                scores.second++;
                break;
        }
    };

    world.addComponent<ScoreListener>(id, { callback });
}

Entity createLeftPaddle(ecs::ComponentManager& world, const Rectangle& boardArea) {
    Entity id = createPaddle(world, boardArea, 20);
    world.addComponent<Input>(id, { });
    return id;
}

Entity createRightPaddle(ecs::ComponentManager& world, const Rectangle& boardArea) {
    return createPaddle(world, boardArea, 760);
}

class Game {
 public:
    void init() {
        Rectangle boardArea { {0, 0}, 800, 600 };
        createScoreboard(world, boardArea);
        createLeftPaddle(world, boardArea);
        createRightPaddle(world, boardArea);
        createBall(world, boardArea);
    }

    void update(const sf::Time& elapsedTime) {
        unsigned elapsedTimeMicro = elapsedTime.asMicroseconds();
        float normalizedElapsedTime = elapsedTimeMicro / 1000000.0;

        applyInput(world);
        applyMovement(world, normalizedElapsedTime);
        applyRectangleBounds(world);
        applyScoring(world);
    }

    void render(sf::RenderWindow& window) {
        renderWorld(world, window);
    }

 private:
    ecs::ComponentManager world;
};
