#pragma once

#include <iostream>
#include "../Component.hpp"

struct BProps { };
struct BState {
    int counter = 0;
};

class SubComponentB : public Component<BProps, BState> {
 public:
    void render(void* context, Maestro& maestro) override {
        std::cout << "SubComponentB::render()\n";
    }
};
