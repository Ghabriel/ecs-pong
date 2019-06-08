#pragma once

#include "../framework/state-management/StateMachine.hpp"
#include "BaseEvents.hpp"

class TransitionEvent : public TeamEvent {
 public:
    TransitionEvent(state::StateMachine& stateMachine) : stateMachine(stateMachine) { }

    virtual void operator()(const Team& team) override {
        stateMachine.pushState("waiting");
    }

 private:
    state::StateMachine& stateMachine;
};
