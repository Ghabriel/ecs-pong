#pragma once

#include <iostream>
#include "Component.hpp"
#include "Maestro.hpp"
#include "components/SubComponentA.hpp"
#include "components/SubComponentB.hpp"

struct AppProps { };

struct AppState {
    int counter = 0;
};

class App : public Component<AppProps, AppState> {
 public:
    void render(void* context, Maestro& maestro) override {
        auto* window = static_cast<int*>(context);

        // draw your things
        std::cout << "Window: " << *window << std::endl;
        std::cout << "App::render(" << state.counter << ")\n";

        maestro.renderChild(a1, {});
        maestro.renderChild(b, {});
        maestro.renderChild(a2, {});

        state.counter++;
    }

 private:
    SubComponentA a1;
    SubComponentB b;
    SubComponentA a2;
};
