#pragma once

#include <SFML/Graphics.hpp>
#include "Component.hpp"
#include "Maestro.hpp"
#include "components/SubComponentA.hpp"
#include "components/SubComponentB.hpp"

struct AppProps { };

struct AppState {
    int counter = 0;
    sf::CircleShape shape;
};

class App : public Component<AppProps, AppState> {
 public:
    App() {
        state.shape = sf::CircleShape(100.f);
        state.shape.setFillColor(sf::Color::Red);
    }

    void render(void* context, Maestro& maestro) override {
        auto& window = *static_cast<sf::RenderWindow*>(context);

        state.shape.setPosition(state.counter, 0);
        window.draw(state.shape);

        maestro.renderChild(a, {});
        maestro.renderChild(b, {});

        state.counter++;
    }

 private:
    SubComponentA a;
    SubComponentB b;
};
