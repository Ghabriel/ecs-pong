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
    unsigned leftScore = 0;
    unsigned rightScore = 0;
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

void updateBall(
    MovingCircle& ball,
    const std::array<OrientedLineSegment, 4>& borders,
    const std::array<Rectangle, 2>& paddles
) {
    bool deflected = false;
    auto& [topBorder, rightBorder, bottomBorder, leftBorder] = borders;

    deflected = deflected || interact(ball, topBorder.segment, -topBorder.normal);
    deflected = deflected || interact(ball, bottomBorder.segment, -bottomBorder.normal);

    for (const Rectangle& paddle : paddles) {
        deflected = deflected || interact(ball, paddle);
    }

    if (!deflected) {
        ball.circle.center += ball.velocity;
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
            auto& [topBorder, rightBorder, bottomBorder, leftBorder] = state.borders;

            if (interact(ball, leftBorder.segment, -leftBorder.normal)) {
                state.leftScore++;
                reset();
            } else if (interact(ball, rightBorder.segment, -rightBorder.normal)) {
                state.rightScore++;
                reset();
            } else {
                updateBall(
                    ball,
                    state.borders,
                    { leftPaddle.getData().rectangle, rightPaddle.getData().rectangle }
                );
            }
        };
    }

    void render(void* context, react::Maestro& maestro) override {
        auto& window = *static_cast<sf::RenderWindow*>(context);

        maestro.renderChild(leftPaddle, { state.boardArea, state.handlePaddleMove, 20 });
        maestro.renderChild(rightPaddle, { state.boardArea, state.handlePaddleMove, 760 });
        maestro.renderChild(ball, { state.boardArea, state.handleBallMove });
    }

    void reset() {
        leftPaddle.reset();
        rightPaddle.reset();
        ball.reset();
    }

 private:
    Paddle<true> leftPaddle;
    Paddle<false> rightPaddle;
    Ball ball;
};
