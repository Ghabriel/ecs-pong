#pragma once

#include "../framework/ComponentManager.hpp"

void useScoringSystem(ecs::ComponentManager& world) {
    world.query<ScoringBounds, Position>(
        [&world](ecs::Entity, const ScoringBounds& bounds, const Position& pos) {
            float x = pos.location.x;

            if (x <= bounds.lowerBound || x >= bounds.upperBound) {
                Team scoringTeam = (x <= bounds.lowerBound) ? Team::Right : Team::Left;
                world.notify<ScoreListener>(scoringTeam);
            }
        }
    );
}
