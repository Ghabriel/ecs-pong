#pragma once

#include <functional>
#include <random>
#include "../framework/Component.hpp"
#include "../shapes/Circle.hpp"
#include "../shapes/MovingCircle.hpp"
#include "../shapes/Point.hpp"

struct BallProps {
    sf::RectangleShape boardArea;
    std::function<void(MovingCircle&)> onMoveAttempt;
    bool moving = false;
};

struct BallState {
    sf::CircleShape body;
    MovingCircle data;
};

class Ball : public react::Component<BallProps, BallState> {
 public:
    void init() override {
        float x = getCentralizedX();
        float y = getCentralizedY();
        float radius = 10;

        Point center { x, y };
        Circle circle { center, radius };
        Vector velocity = generateVelocity();
        state.data = { circle, velocity };

        state.body = sf::CircleShape(radius);
        state.body.setFillColor(sf::Color::White);
    }

    void render(void* context, react::Maestro& maestro) override {
        auto& window = *static_cast<sf::RenderWindow*>(context);
        sf::CircleShape& body = state.body;
        MovingCircle& data = state.data;

        if (props.moving) {
            props.onMoveAttempt(data);
        }

        body.setPosition(
            data.circle.center.x - data.circle.radius,
            data.circle.center.y - data.circle.radius
        );

        window.draw(body);
    }

    void reset() {
        init();
    }

 private:
    float getCentralizedX() const {
        auto& boardPosition = props.boardArea.getPosition();
        auto& boardSize = props.boardArea.getSize();

        return boardPosition.x + (boardSize.x / 2);
    }

    float getCentralizedY() const {
        auto& boardPosition = props.boardArea.getPosition();
        auto& boardSize = props.boardArea.getSize();

        return boardPosition.y + (boardSize.y / 2);
    }

    Vector generateVelocity() const {
        std::random_device randomDevice;
        std::mt19937 generator(randomDevice());
        std::uniform_int_distribution<int> dist(-5, 5);
        int x = 0;
        int y = 0;
        int squaredSpeed = 0;

        while (squaredSpeed < 20 || squaredSpeed > 50) {
            x = 0;
            y = 0;

            while (x == 0) {
                x = dist(generator);
            }

            while (y == 0) {
                y = dist(generator);
            }

            squaredSpeed = x * x + y * y;
        }

        return { static_cast<float>(x), static_cast<float>(y) };
    }
};
