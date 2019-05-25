#pragma once

#include <memory>
#include "BaseComponent.hpp"

namespace react {
    class Maestro {
     public:
        Maestro(void* context) : context(context) { }

        template<typename TComponent>
        void setRootComponent(typename TComponent::PropsType props) {
            auto rootComponent = std::make_unique<TComponent>();
            rootComponent->props = props;

            root = std::move(rootComponent);
        }

        template<typename TComponent>
        void setRootComponent() {
            setRootComponent<TComponent>({});
        }

        void render() {
            root->render(context, *this);
        }

        template<typename TComponent>
        void renderChild(TComponent& component, typename TComponent::PropsType props) {
            component.props = props;
            component.render(context, *this);
        }

     private:
        void* context;
        std::unique_ptr<BaseComponent> root;
    };
}
