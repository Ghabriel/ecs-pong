#pragma once

#include <functional>
#include "../framework/Component.hpp"
#include "../shapes/MovingRectangle.hpp"
#include "../shapes/Point.hpp"
#include "../shapes/Rectangle.hpp"

struct PaddleProps {
    sf::RectangleShape boardArea;
    std::function<void(MovingRectangle&)> onMoveAttempt;
    float x;
};

struct PaddleState {
    sf::RectangleShape body;
    MovingRectangle data;
};

template<bool KeyboardControlled>
class Paddle : public react::Component<PaddleProps, PaddleState> {
 public:
   void init() override {
        float width = 20;
        float height = 200;
        float y = getCentralizedY(height);

        Point corner { props.x, y };
        Rectangle rectangle { corner, width, height };
        Vector velocity { 0, 0 };
        state.data = { rectangle, velocity };

        state.body = sf::RectangleShape(sf::Vector2f(width, height));
        state.body.setFillColor(sf::Color::White);
    }

    void render(void* context, react::Maestro& maestro) override {
        auto& window = *static_cast<sf::RenderWindow*>(context);
        sf::RectangleShape& body = state.body;
        MovingRectangle& data = state.data;

        if constexpr (KeyboardControlled) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                data.velocity = { 0, -3 };
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                data.velocity = { 0, 3 };
            } else {
                data.velocity = { 0, 0 };
            }
        }

        props.onMoveAttempt(data);

        body.setPosition(data.rectangle.corner.x, data.rectangle.corner.y);

        window.draw(body);
    }

    MovingRectangle& getData() {
        return state.data;
    }

    void reset() {
        init();
    }

 private:
    float getCentralizedY(float height) const {
        auto& boardPosition = props.boardArea.getPosition();
        auto& boardSize = props.boardArea.getSize();

        return boardPosition.y + (boardSize.y / 2) - (height / 2);
    }
};
