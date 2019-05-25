#pragma once

#include <iostream>
#include "../Component.hpp"

struct AProps { };

struct AState {
    sf::CircleShape shape;
};

class SubComponentA : public Component<AProps, AState> {
 public:
    SubComponentA() {
        state.shape = sf::CircleShape(50.f);
        state.shape.setFillColor(sf::Color::Green);
        state.shape.setPosition(0, 200);
    }

    void render(void* context, Maestro& maestro) override {
        auto& window = *static_cast<sf::RenderWindow*>(context);

        window.draw(state.shape);
    }
};
