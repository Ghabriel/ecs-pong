#pragma once

namespace react {
    class Maestro;

    class BaseComponent {
        friend class Maestro;
     public:
        virtual void render(void* context, Maestro&) = 0;
    };
}
