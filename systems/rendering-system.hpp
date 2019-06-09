#pragma once

#include <SFML/Graphics.hpp>
#include "../framework/ecs/userland.hpp"
#include "../shapes/Circle.hpp"
#include "../shapes/Rectangle.hpp"

namespace rendering_system {
    void renderCircles(ecs::ComponentManager& world, sf::RenderWindow& window) {
        world.findAll<Drawable>()
            .join<Position>()
            .join<CircularObject>()
            .forEach(
                [&window](const Position& pos, const CircularObject& obj) {
                    sf::CircleShape circle(obj.radius);
                    circle.setFillColor(sf::Color::White);

                    circle.setPosition(
                        pos.location.x - obj.radius,
                        pos.location.y - obj.radius
                    );

                    window.draw(circle);
                }
            );
    }

    void renderRectangles(ecs::ComponentManager& world, sf::RenderWindow& window) {
        world.findAll<Drawable>()
            .join<Position>()
            .join<RectangularObject>()
            .forEach(
                [&window](const Position& pos, const RectangularObject& obj) {
                    sf::RectangleShape rect(sf::Vector2f(obj.width, obj.height));
                    rect.setFillColor(sf::Color::White);

                    rect.setPosition(
                        pos.location.x - obj.width / 2,
                        pos.location.y - obj.height / 2
                    );

                    window.draw(rect);
                }
            );
    }

    void renderScoreboard(ecs::ComponentManager& world, sf::RenderWindow& window) {
        static sf::Font font;
        static bool loadedFont = false;

        if (!loadedFont) {
            font.loadFromFile("resources/arial.ttf");
            loadedFont = true;
        }

        world.findAll<Drawable>()
            .join<Scoreboard>()
            .join<Position>()
            .forEach(
                [&window](const Scoreboard& scoreboard, const Position& pos) {
                    auto& [leftScore, rightScore] = scoreboard.scores;
                    {}

                    sf::Text text(
                        std::to_string(leftScore) + " - " + std::to_string(rightScore),
                        font
                    );
                    text.setCharacterSize(30);
                    text.setStyle(sf::Text::Bold);

                    auto [x, y] = pos.location;
                    sf::FloatRect bounds = text.getLocalBounds();
                    float width = bounds.width;
                    float height = bounds.height;
                    text.setPosition({ x - width / 2, y - height / 2 });

                    window.draw(text);
                }
            );
    }
}

void useRenderingSystem(ecs::ComponentManager& world, sf::RenderWindow& window) {
    using namespace rendering_system;
    renderCircles(world, window);
    renderRectangles(world, window);
    renderScoreboard(world, window);
}
