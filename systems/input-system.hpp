#pragma once

#include "../components/Input.hpp"
#include "../components/Velocity.hpp"
#include "../framework/ComponentManager.hpp"

void applyInput(ecs::ComponentManager& world) {
    world.query<Input>(
        [&world](ecs::Entity id, Input) {
            Vector velocity;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                velocity = { 0, -350 };
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                velocity = { 0, 350 };
            } else {
                world.removeComponent<Velocity>(id);
                return;
            }

            if (world.hasComponent<Velocity>(id)) {
                world.getData<Velocity>(id) = { velocity };
            } else {
                world.addComponent<Velocity>(id, { velocity });
            }
        }
    );
}
