#pragma once

#include <unordered_map>
#include "../components/Bounds.hpp"
#include "../components/CircularObject.hpp"
#include "../components/Drawable.hpp"
#include "../components/Input.hpp"
#include "../components/RectangularObject.hpp"
#include "../components/ScoreListener.hpp"
#include "../components/ScoringBounds.hpp"
#include "../components/Velocity.hpp"

namespace ecs {
    using Entity = unsigned;

    template<typename T>
    using ComponentData = std::unordered_map<Entity, T>;

    namespace __detail {
        template<typename T>
        struct FieldContainer {
            ComponentData<T> field;
            static constexpr ComponentData<T> FieldContainer::* address = &FieldContainer::field;
        };

        template<typename... Ts>
        struct GenericECS : FieldContainer<Ts>... {
            Entity nextEntityId = 0;
        };
    }

    using ECS = __detail::GenericECS<
        Bounds,
        CircularObject,
        Drawable,
        Input,
        RectangularObject,
        ScoreListener,
        ScoringBounds,
        Velocity
    >;

    template<typename T>
    constexpr ComponentData<T>& entityData(ECS& ecs) {
        constexpr auto field = __detail::FieldContainer<T>::address;
        return ecs.*field;
    }

    template<typename T>
    constexpr const ComponentData<T>& entityData(const ECS& ecs) {
        constexpr auto field = __detail::FieldContainer<T>::address;
        return ecs.*field;
    }
}
