#pragma once

#include "../framework/Component.hpp"
#include "../shapes/Point.hpp"
#include "../shapes/Rectangle.hpp"
#include "../types/physics.hpp"

struct PaddleProps {
    sf::RectangleShape boardArea;
    float x;
};

struct PaddleState {
    sf::RectangleShape body;
    Rectangle data;
};

template<bool KeyboardControlled>
class Paddle : public react::Component<PaddleProps, PaddleState> {
 public:
   void init() override {
        float width = 20;
        float height = 200;
        float y = getCentralizedY(height);

        Point corner { props.x, y };
        state.data = { corner, width, height };

        state.body = sf::RectangleShape(sf::Vector2f(width, height));
        state.body.setFillColor(sf::Color::White);
    }

    void render(void* context, react::Maestro& maestro) override {
        auto& window = *static_cast<sf::RenderWindow*>(context);
        sf::RectangleShape& body = state.body;
        Rectangle& data = state.data;

        if constexpr (KeyboardControlled) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                data.corner.y -= 3;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                data.corner.y += 3;
            }
        }

        body.setPosition(data.corner.x, data.corner.y);

        window.draw(body);
    }

    Rectangle& getData() {
        return state.data;
    }

 private:
    float getCentralizedY(float height) const {
        auto& boardPosition = props.boardArea.getPosition();
        auto& boardSize = props.boardArea.getSize();

        return boardPosition.y + (boardSize.y / 2) - (height / 2);
    }
};
