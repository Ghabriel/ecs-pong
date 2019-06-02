#pragma once

#include <SFML/Graphics.hpp>
#include "../components/CircularObject.hpp"
#include "../components/Drawable.hpp"
#include "../components/RectangularObject.hpp"
#include "../framework/ComponentManager.hpp"
#include "../shapes/Circle.hpp"
#include "../shapes/Rectangle.hpp"

void renderCircles(ecs::ComponentManager& world, sf::RenderWindow& window) {
    world.findAll<Drawable>()
        .join<CircularObject>()
        .forEach(
            [&window](const CircularObject& obj) {
                const Circle& body = obj.body;
                sf::CircleShape circle(body.radius);
                circle.setFillColor(sf::Color::White);

                circle.setPosition(
                    body.center.x - body.radius,
                    body.center.y - body.radius
                );

                window.draw(circle);
            }
        );
}

void renderRectangles(ecs::ComponentManager& world, sf::RenderWindow& window) {
    world.findAll<Drawable>()
        .join<RectangularObject>()
        .forEach(
            [&window](const RectangularObject& obj) {
                const Rectangle& body = obj.body;
                sf::RectangleShape rect(sf::Vector2f(body.width, body.height));
                rect.setFillColor(sf::Color::White);

                rect.setPosition(body.corner.x, body.corner.y);

                window.draw(rect);
            }
        );
}

void renderWorld(ecs::ComponentManager& world, sf::RenderWindow& window) {
    renderCircles(world, window);
    renderRectangles(world, window);
}
