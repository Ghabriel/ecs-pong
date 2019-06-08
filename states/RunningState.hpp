#pragma once

#include "../events/BaseEvents.hpp"
#include "../events/TransitionEvent.hpp"
#include "../framework/ecs/ComponentManager.hpp"
#include "../framework/ecs/EventManager.hpp"
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
        state::StateMachine& stateMachine,
        events::EventManager& eventManager
    ) : world(world), stateMachine(stateMachine), eventManager(eventManager) {
        scoreListenerId = eventManager.registerEventListener(
            std::unique_ptr<TeamEvent>(new TransitionEvent(stateMachine))
        );
    }

    void onEnter() override {
        eventManager.enableEventListener<TeamEvent>("score-event", scoreListenerId);
    }

    void onExit() override {
        eventManager.disableEventListener<TeamEvent>("score-event", scoreListenerId);
    }

    void update(const sf::Time& elapsedTime) override {
        unsigned elapsedTimeMicro = elapsedTime.asMicroseconds();
        float normalizedElapsedTime = elapsedTimeMicro / 1000000.0;

        useInputSystem(world);
        useMovementSystem(world, normalizedElapsedTime);
        usePaddleBoundingSystem(world);
        useScoringSystem(world, eventManager);
    }

    void render(sf::RenderWindow& window) override {
        useRenderingSystem(world, window);
    }

 private:
    ecs::ComponentManager& world;
    state::StateMachine& stateMachine;
    events::EventManager& eventManager;
    events::ListenerId scoreListenerId;
};
