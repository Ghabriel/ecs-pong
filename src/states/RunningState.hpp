#pragma once

#include "../engine-glue/ecs.hpp"
#include "../engine/state-management/State.hpp"
#include "../engine/state-management/StateMachine.hpp"
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
        scoreListenerId = world.createEntity();

        auto callback = [&stateMachine](Team team) {
            stateMachine.pushState("waiting");
        };

        scoreListener = ScoreListener { callback };
    }

    void onEnter() override {
        world.addComponent(scoreListenerId, scoreListener);
    }

    void onExit() override {
        world.removeComponent<ScoreListener>(scoreListenerId);
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
    ecs::Entity scoreListenerId;
    ScoreListener scoreListener;
};
