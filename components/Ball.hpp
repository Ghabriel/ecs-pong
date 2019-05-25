#pragma once

#include "../framework/Component.hpp"

struct BallProps {
    sf::RectangleShape boardArea;
};

struct BallState {
    sf::CircleShape body;
    float x = 0;
    float y = 0;
};

class Ball : public react::Component<BallProps, BallState> {
 public:
    Ball() {
        state.body = sf::CircleShape(10);
        state.body.setFillColor(sf::Color::White);
    }

    void render(void* context, react::Maestro& maestro) override {
        auto& window = *static_cast<sf::RenderWindow*>(context);
        sf::CircleShape& body = state.body;

        float x = state.x + getCentralizedX();
        float y = state.y + getCentralizedY();
        body.setPosition(x, y);

        window.draw(body);
    }

 private:
    float getCentralizedX() const {
        auto& boardPosition = props.boardArea.getPosition();
        auto& boardSize = props.boardArea.getSize();
        float radius = state.body.getRadius();

        return boardPosition.x + (boardSize.x / 2) - radius;
    }

    float getCentralizedY() const {
        auto& boardPosition = props.boardArea.getPosition();
        auto& boardSize = props.boardArea.getSize();
        float radius = state.body.getRadius();

        return boardPosition.y + (boardSize.y / 2) - radius;
    }
};
