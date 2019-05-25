#pragma once

#include "BaseComponent.hpp"

namespace react {
    class Maestro;

    template<typename TProps, typename TState>
    class Component : public BaseComponent {
        friend class Maestro;
     public:
        using PropsType = TProps;
        using StateType = TState;

     protected:
        TProps props;
        TState state;
    };
}
