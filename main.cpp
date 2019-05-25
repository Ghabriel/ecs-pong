#include "App.hpp"
#include "Maestro.hpp"

int main(int, char**) {
    int context = 42;
    Maestro maestro(&context);
    maestro.setRootComponent<App>();

    maestro.render();
    std::cout << "--------------\n";
    maestro.render();
    std::cout << "--------------\n";
    maestro.render();
}
