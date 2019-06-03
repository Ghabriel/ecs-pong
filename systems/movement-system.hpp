#pragma once

#include "../components/Position.hpp"
#include "../components/Velocity.hpp"
#include "../framework/ComponentManager.hpp"

void applyMovement(ecs::ComponentManager& world, float elapsedTime) {
    world.query<Velocity, Position>(
        [elapsedTime](ecs::Entity, Velocity& v, Position& pos) {
            pos.location += v.value * elapsedTime;
        }
    );
}
