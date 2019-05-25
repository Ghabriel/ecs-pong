#pragma once

#include <SFML/Graphics.hpp>
#include "components/Ball.hpp"
#include "components/Paddle.hpp"
#include "framework/Component.hpp"
#include "framework/Maestro.hpp"

struct AppProps { };

struct AppState {
    sf::RectangleShape boardArea;
};

class App : public react::Component<AppProps, AppState> {
 public:
    App() {
        state.boardArea = sf::RectangleShape(sf::Vector2f(800, 600));
    }

    void render(void* context, react::Maestro& maestro) override {
        auto& window = *static_cast<sf::RenderWindow*>(context);

        maestro.renderChild(leftPaddle, { state.boardArea, 20 });
        maestro.renderChild(rightPaddle, { state.boardArea, 760 });
        maestro.renderChild(ball, { state.boardArea });
    }

 private:
    Paddle leftPaddle;
    Paddle rightPaddle;
    Ball ball;
};
