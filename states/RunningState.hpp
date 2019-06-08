#pragma once

#include "../framework/ecs/ComponentManager.hpp"
#include "../framework/state-management/State.hpp"
#include "../framework/state-management/StateMachine.hpp"
#include "../systems/input-system.hpp"
#include "../systems/movement-system.hpp"
#include "../systems/paddle-bounding-system.hpp"
#include "../systems/rendering-system.hpp"
#include "../systems/scoring-system.hpp"

class RunningState : public state::State {
 public:
    RunningState(
        ecs::ComponentManager& world,
        state::StateMachine& stateMachine
    ) : world(world), stateMachine(stateMachine) {
        scoreListener = world.createEntity();
    }

    void onEnter() override {
        auto callback = [this](Team team) {
            stateMachine.pushState("waiting");
        };

        world.addComponent<ScoreListener>(scoreListener, { callback });
    }

    void onExit() override {
        world.removeComponent<ScoreListener>(scoreListener);
    }

    void update(const sf::Time& elapsedTime) override {
        unsigned elapsedTimeMicro = elapsedTime.asMicroseconds();
        float normalizedElapsedTime = elapsedTimeMicro / 1000000.0;

        useInputSystem(world);
        useMovementSystem(world, normalizedElapsedTime);
        usePaddleBoundingSystem(world);
        useScoringSystem(world);
    }

    void render(sf::RenderWindow& window) override {
        useRenderingSystem(world, window);
    }

 private:
    ecs::ComponentManager& world;
    state::StateMachine& stateMachine;
    ecs::Entity scoreListener;
};
