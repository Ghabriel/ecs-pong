#pragma once

#include "../events/BaseEvents.hpp"
#include "../framework/ecs/ComponentManager.hpp"
#include "../framework/ecs/EventManager.hpp"

void useScoringSystem(
    ecs::ComponentManager& world,
    events::EventManager& eventManager
) {
    world.query<ScoringBounds, Position>(
        [&world, &eventManager](ecs::Entity, const ScoringBounds& bounds, const Position& pos) {
            float x = pos.location.x;

            if (x <= bounds.lowerBound || x >= bounds.upperBound) {
                Team scoringTeam = (x <= bounds.lowerBound) ? Team::Right : Team::Left;
                // world.notify<ScoreListener>(scoringTeam);
                eventManager.emit("score-event", scoringTeam);
            }
        }
    );
}
