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
    sf::Font font;

    bool ballMoving = false;
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
                state.rightScore++;
                reset();
            } else if (interact(ball, rightBorder.segment, -rightBorder.normal)) {
                state.leftScore++;
                reset();
            } else {
                updateBall(
                    ball,
                    state.borders,
                    { leftPaddle.getData().rectangle, rightPaddle.getData().rectangle }
                );
            }
        };

        state.font.loadFromFile("resources/arial.ttf");
    }

    void render(void* context, react::Maestro& maestro) override {
        auto& window = *static_cast<sf::RenderWindow*>(context);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            state.ballMoving = true;
        }

        renderScoreboard(window);

        maestro.renderChild(leftPaddle, { state.boardArea, state.handlePaddleMove, 20 });
        maestro.renderChild(rightPaddle, { state.boardArea, state.handlePaddleMove, 760 });
        maestro.renderChild(ball, { state.boardArea, state.handleBallMove, state.ballMoving });
    }

    void renderScoreboard(sf::RenderWindow& window) {
        sf::Vector2f boardPosition = state.boardArea.getPosition();
        float boardWidth = state.boardArea.getSize().x;

        sf::Text scoreboard(
            std::to_string(state.leftScore) + " - " + std::to_string(state.rightScore),
            state.font
        );
        scoreboard.setCharacterSize(30);
        scoreboard.setStyle(sf::Text::Bold);

        float scoreboardWidth = scoreboard.getLocalBounds().width;
        scoreboard.setPosition(sf::Vector2f((boardWidth - scoreboardWidth) / 2, 5));

        window.draw(scoreboard);
    }

    void reset() {
        state.ballMoving = false;
        leftPaddle.reset();
        rightPaddle.reset();
        ball.reset();
    }

 private:
    Paddle<true> leftPaddle;
    Paddle<false> rightPaddle;
    Ball ball;
};
