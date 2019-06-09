#pragma once

#include "../engine-glue/ecs.hpp"
#include "../engine/shapes/Rectangle.hpp"

void createScoreboard(ecs::ComponentManager& world, const Rectangle& boardArea) {
    ecs::Entity id = world.createEntity(
        Drawable { },
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