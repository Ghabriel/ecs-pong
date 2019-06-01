#pragma once

#include <unordered_map>
#include "../components/CircularObject.hpp"
#include "../components/RectangularObject.hpp"
#include "../components/Velocity.hpp"

namespace ecs {
    using Entity = unsigned;

    template<typename T>
    using ComponentData = std::unordered_map<Entity, T>;

    struct ECS {
        Entity nextEntityId = 0;
        ComponentData<CircularObject> circularObjects;
        ComponentData<RectangularObject> rectangularObjects;
        ComponentData<Velocity> velocities;
    };

    template<typename T>
    constexpr ComponentData<T>& entityData(ECS&);

    template<>
    constexpr ComponentData<CircularObject>& entityData(ECS& ecs) {
        return ecs.circularObjects;
    }

    template<>
    constexpr ComponentData<RectangularObject>& entityData(ECS& ecs) {
        return ecs.rectangularObjects;
    }

    template<>
    constexpr ComponentData<Velocity>& entityData(ECS& ecs) {
        return ecs.velocities;
    }
}
