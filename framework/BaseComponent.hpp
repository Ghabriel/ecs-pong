#pragma once

namespace react {
    class Maestro;

    class BaseComponent {
        friend class Maestro;
     public:
        virtual void init() { }
        virtual void render(void* context, Maestro&) = 0;

     private:
        bool isInitialized = false;
    };
}
