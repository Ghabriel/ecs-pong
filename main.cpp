#include <SFML/Graphics.hpp>
// #include "App.hpp"
#include "framework/ComponentManager.hpp"

int main(int, char**) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "ECS Pong");
    ecs::ComponentManager componentManager;
    // react::Maestro maestro(&window);
    // maestro.setRootComponent<App>();

    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        // maestro.render();
        window.display();
    }
}
