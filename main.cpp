#include <SFML/Graphics.hpp>
#include "App.hpp"
#include "Maestro.hpp"

int main(int, char**) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "react.cpp");
    Maestro maestro(&window);
    maestro.setRootComponent<App>();

    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        maestro.render();
        window.display();
    }
}
