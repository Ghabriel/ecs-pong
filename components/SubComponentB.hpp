#pragma once

#include "../framework/Component.hpp"

struct BProps { };

struct BState {
    sf::CircleShape shape;
};

class SubComponentB : public react::Component<BProps, BState> {
 public:
    SubComponentB() {
        state.shape = sf::CircleShape(50.f);
        state.shape.setFillColor(sf::Color::Blue);
        state.shape.setPosition(0, 400);
    }

    void render(void* context, react::Maestro& maestro) override {
        auto& window = *static_cast<sf::RenderWindow*>(context);

        window.draw(state.shape);
    }
};
