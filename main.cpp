#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main(int, char**) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "ECS Pong");
    Game game;
    game.init();

    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        game.render();
        window.display();
    }
}
