#pragma once

#include "../framework/Component.hpp"

struct PaddleProps {
    sf::RectangleShape boardArea;
    float x;
};

struct PaddleState {
    sf::RectangleShape body;
    float y = 0;
};

class Paddle : public react::Component<PaddleProps, PaddleState> {
 public:
    Paddle() {
        state.body = sf::RectangleShape(sf::Vector2f(20, 200));
        state.body.setFillColor(sf::Color::White);
    }

    void render(void* context, react::Maestro& maestro) override {
        auto& window = *static_cast<sf::RenderWindow*>(context);
        sf::RectangleShape& body = state.body;

        float y = state.y + getCentralizedY();
        body.setPosition(props.x, y);

        window.draw(body);
    }

 private:
    float getCentralizedY() const {
        auto& boardPosition = props.boardArea.getPosition();
        auto& boardSize = props.boardArea.getSize();
        auto& paddleSize = state.body.getSize();

        return boardPosition.y + (boardSize.y / 2) - (paddleSize.y / 2);
    }
};
