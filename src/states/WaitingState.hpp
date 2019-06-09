#pragma once

#include "../engine-glue/ecs.hpp"
#include "../engine/state-management/State.hpp"
#include "../engine/state-management/StateMachine.hpp"
#include "../systems/rendering-system.hpp"

class WaitingState : public state::State {
 public:
    WaitingState(
        ecs::ComponentManager& world,
        state::StateMachine& stateMachine
    ) : world(world), stateMachine(stateMachine) { }

    void update(const sf::Time& elapsedTime) override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            stateMachine.pushState("running");
        }
    }

    void render(sf::RenderWindow& window) override {
        useRenderingSystem(world, window);
    }

 private:
    ecs::ComponentManager& world;
    state::StateMachine& stateMachine;
};
