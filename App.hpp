#pragma once

#include <SFML/Graphics.hpp>
#include "components/Ball.hpp"
#include "components/Paddle.hpp"
#include "debug.hpp"
#include "framework/Component.hpp"
#include "framework/Maestro.hpp"
#include "physics/interactions.hpp"

struct AppProps { };

struct AppState {
    sf::RectangleShape boardArea;
    std::function<void(MovingCircle&)> handleBallMove;
};

class App : public react::Component<AppProps, AppState> {
 public:
    App() {
        state.boardArea = sf::RectangleShape(sf::Vector2f(800, 600));

        state.handleBallMove = [this](MovingCircle& ball) {
            // std::cout << "left data: " << leftPaddle.getData() << "\n";
            // std::cout << "right data: " << rightPaddle.getData() << "\n";

            bool deflected = interact(ball, leftPaddle.getData());
            deflected = deflected || interact(ball, rightPaddle.getData());

            if (!deflected) {
                ball.circle.center += ball.velocity;
            }
        };
    }

    void render(void* context, react::Maestro& maestro) override {
        auto& window = *static_cast<sf::RenderWindow*>(context);

        maestro.renderChild(leftPaddle, { state.boardArea, 20 });
        maestro.renderChild(rightPaddle, { state.boardArea, 760 });
        maestro.renderChild(ball, { state.boardArea, state.handleBallMove });
    }

 private:
    Paddle<true> leftPaddle;
    Paddle<false> rightPaddle;
    Ball ball;
};
