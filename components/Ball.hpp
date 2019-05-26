#pragma once

#include <functional>
#include "../framework/Component.hpp"
#include "../shapes/Circle.hpp"
#include "../shapes/Point.hpp"
#include "../types/physics.hpp"

struct BallProps {
    sf::RectangleShape boardArea;
    std::function<void(MovingCircle&)> onMoveAttempt;
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
        Vector velocity { 1, 0.1 };
        state.data = { circle, velocity };

        state.body = sf::CircleShape(radius);
        state.body.setFillColor(sf::Color::White);
    }

    void render(void* context, react::Maestro& maestro) override {
        auto& window = *static_cast<sf::RenderWindow*>(context);
        sf::CircleShape& body = state.body;
        MovingCircle& data = state.data;

        props.onMoveAttempt(data);

        body.setPosition(
            data.circle.center.x - data.circle.radius,
            data.circle.center.y - data.circle.radius
        );

        window.draw(body);
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
};
