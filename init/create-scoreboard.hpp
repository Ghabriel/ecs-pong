#pragma once

#include "../events/BaseEvents.hpp"
#include "../framework/ecs/ComponentManager.hpp"
#include "../framework/ecs/EventManager.hpp"
#include "../shapes/Rectangle.hpp"

class ScoreboardUpdateEvent : public TeamEvent {
 public:
    ScoreboardUpdateEvent(
        ecs::ComponentManager& world,
        ecs::Entity scoreboardId
    ) : world(world), scoreboardId(scoreboardId) { }

    virtual void operator()(const Team& team) override {
        Scoreboard& scoreboard = world.getData<Scoreboard>(scoreboardId);
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
    }

 private:
    ecs::ComponentManager& world;
    ecs::Entity scoreboardId;
};

void createScoreboard(
    ecs::ComponentManager& world,
    const Rectangle& boardArea,
    events::EventManager& eventManager
) {
    ecs::Entity id = world.createEntity(
        Drawable { },
        Scoreboard { { 0, 0 } },
        Position { boardArea.width / 2, 30 }
    );

    events::ListenerId listenerId = eventManager.registerEventListener(
        std::unique_ptr<TeamEvent>(new ScoreboardUpdateEvent(world, id))
    );

    eventManager.enableEventListener<TeamEvent>("score-event", listenerId);
}