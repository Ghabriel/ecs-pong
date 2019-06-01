#pragma once

#include <SFML/Graphics.hpp>
#include "../framework/ComponentManager.hpp"

void renderCircles(ecs::ComponentManager& world, sf::RenderWindow& window) {
    world.query<Drawable, CircularObject>(
        [&window](Entity, Drawable, const CircularObject& obj) {
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
    world.query<Drawable, RectangularObject>(
        [&window](Entity, Drawable, const RectangularObject& obj) {
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
