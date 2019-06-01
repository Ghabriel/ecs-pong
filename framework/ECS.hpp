#pragma once

#include <unordered_map>
#include "../components/CircularObject.hpp"
#include "../components/Drawable.hpp"
#include "../components/RectangularObject.hpp"
#include "../components/Velocity.hpp"

namespace ecs {
    using Entity = unsigned;

    template<typename T>
    using ComponentData = std::unordered_map<Entity, T>;

    struct ECS {
        Entity nextEntityId = 0;
        ComponentData<CircularObject> circularObjects;
        ComponentData<Drawable> drawables;
        ComponentData<RectangularObject> rectangularObjects;
        ComponentData<Velocity> velocities;
    };

    template<typename T>
    constexpr ComponentData<T>& entityData(ECS&);

    template<typename T>
    constexpr const ComponentData<T>& entityData(const ECS&);

    template<>
    constexpr ComponentData<CircularObject>& entityData(ECS& ecs) {
        return ecs.circularObjects;
    }

    template<>
    constexpr const ComponentData<CircularObject>& entityData(const ECS& ecs) {
        return ecs.circularObjects;
    }

    template<>
    constexpr ComponentData<Drawable>& entityData(ECS& ecs) {
        return ecs.drawables;
    }

    template<>
    constexpr const ComponentData<Drawable>& entityData(const ECS& ecs) {
        return ecs.drawables;
    }

    template<>
    constexpr ComponentData<RectangularObject>& entityData(ECS& ecs) {
        return ecs.rectangularObjects;
    }

    template<>
    constexpr const ComponentData<RectangularObject>& entityData(const ECS& ecs) {
        return ecs.rectangularObjects;
    }

    template<>
    constexpr ComponentData<Velocity>& entityData(ECS& ecs) {
        return ecs.velocities;
    }

    template<>
    constexpr const ComponentData<Velocity>& entityData(const ECS& ecs) {
        return ecs.velocities;
    }
}
