#pragma once

#include "../components/CircularObject.hpp"
#include "../components/ScoreListener.hpp"
#include "../components/Velocity.hpp"
#include "../framework/ComponentManager.hpp"
#include "../shapes/Circle.hpp"

void applyScoring(ecs::ComponentManager& world) {
    world.query<ScoringBounds, CircularObject>(
        [&world](Entity, const ScoringBounds& bounds, CircularObject& obj) {
            Circle& body = obj.body;
            float x = body.center.x;

            if (x <= bounds.lowerBound || x >= bounds.upperBound) {
                Team scoringTeam = (x <= bounds.lowerBound) ? Team::Right : Team::Left;
                world.notify<ScoreListener>(scoringTeam);
            }
        }
    );
}
