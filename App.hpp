#pragma once

#include <SFML/Graphics.hpp>
#include "components/SubComponentA.hpp"
#include "components/SubComponentB.hpp"
#include "framework/Component.hpp"
#include "framework/Maestro.hpp"

struct AppProps { };

struct AppState {
    int counter = 0;
    sf::CircleShape shape;
};

class App : public react::Component<AppProps, AppState> {
 public:
    App() {
        state.shape = sf::CircleShape(100.f);
        state.shape.setFillColor(sf::Color::Red);
    }

    void render(void* context, react::Maestro& maestro) override {
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
