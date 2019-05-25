#pragma once

#include <iostream>
#include "../Component.hpp"

struct AProps { };
struct AState {
    int counter = 0;
};

class SubComponentA : public Component<AProps, AState> {
 public:
    void render(void* context, Maestro& maestro) override {
        std::cout << "SubComponentA::render()\n";
    }
};
