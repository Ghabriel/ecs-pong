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
    std::array<OrientedLineSegment, 4> borders;
    std::function<void(MovingRectangle&)> handlePaddleMove;
    std::function<void(MovingCircle&)> handleBallMove;
};

void handlePaddleMove(MovingRectangle& paddle, const sf::RectangleShape& boardArea) {
    auto& [rectangle, velocity] = paddle;
    auto& [corner, width, height] = rectangle;

    Point midPoint = rectangle.getMidPoint();
    Point nextMidPoint = midPoint + velocity;
    sf::Vector2f boardPosition = boardArea.getPosition();
    float boardHeight = boardArea.getSize().y;
    float boardBottomY = boardPosition.y + boardHeight;

    if (nextMidPoint.y - height / 2 < boardPosition.y) {
        corner.y = boardPosition.y;
    } else if (nextMidPoint.y + height / 2 > boardBottomY) {
        corner.y = boardBottomY - height;
    } else {
        corner += velocity;
    }
}

class App : public react::Component<AppProps, AppState> {
 public:
    App() {
        float width = 800;
        float height = 600;
        state.boardArea = sf::RectangleShape(sf::Vector2f(width, height));

        Point corner { 0, 0 };
        Rectangle board { corner, width, height };
        state.borders = board.getOrientedEdges();

        state.handlePaddleMove = [this](MovingRectangle& paddle) {
            handlePaddleMove(paddle, state.boardArea);
        };

        state.handleBallMove = [this](MovingCircle& ball) {
            bool deflected = false;

            for (const OrientedLineSegment& edge : state.borders) {
                deflected = deflected || interact(ball, edge.segment, -edge.normal);
            }

            deflected = deflected || interact(ball, leftPaddle.getData().rectangle);
            deflected = deflected || interact(ball, rightPaddle.getData().rectangle);

            if (!deflected) {
                ball.circle.center += ball.velocity;
            }
        };
    }

    void render(void* context, react::Maestro& maestro) override {
        auto& window = *static_cast<sf::RenderWindow*>(context);

        maestro.renderChild(leftPaddle, { state.boardArea, state.handlePaddleMove, 20 });
        maestro.renderChild(rightPaddle, { state.boardArea, state.handlePaddleMove, 760 });
        maestro.renderChild(ball, { state.boardArea, state.handleBallMove });
    }

 private:
    Paddle<true> leftPaddle;
    Paddle<false> rightPaddle;
    Ball ball;
};
