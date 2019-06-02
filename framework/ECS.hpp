#pragma once

#include <unordered_map>
#include "../components/Bounds.hpp"
#include "../components/CircularObject.hpp"
#include "../components/Drawable.hpp"
#include "../components/RectangularObject.hpp"
#include "../components/ScoreListener.hpp"
#include "../components/ScoringBounds.hpp"
#include "../components/Velocity.hpp"

namespace ecs {
    using Entity = unsigned;

    template<typename T>
    using ComponentData = std::unordered_map<Entity, T>;

    struct ECS {
        Entity nextEntityId = 0;
        ComponentData<Bounds> bounds;
        ComponentData<CircularObject> circularObjects;
        ComponentData<Drawable> drawables;
        ComponentData<RectangularObject> rectangularObjects;
        ComponentData<ScoreListener> scoreListeners;
        ComponentData<ScoringBounds> scoringBounds;
        ComponentData<Velocity> velocities;
    };

    template<typename T>
    constexpr ComponentData<T>& entityData(ECS&);

    template<typename T>
    constexpr const ComponentData<T>& entityData(const ECS&);

    template<>
    constexpr ComponentData<Bounds>& entityData(ECS& ecs) {
        return ecs.bounds;
    }

    template<>
    constexpr const ComponentData<Bounds>& entityData(const ECS& ecs) {
        return ecs.bounds;
    }

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
    constexpr ComponentData<ScoreListener>& entityData(ECS& ecs) {
        return ecs.scoreListeners;
    }

    template<>
    constexpr const ComponentData<ScoreListener>& entityData(const ECS& ecs) {
        return ecs.scoreListeners;
    }

    template<>
    constexpr ComponentData<ScoringBounds>& entityData(ECS& ecs) {
        return ecs.scoringBounds;
    }

    template<>
    constexpr const ComponentData<ScoringBounds>& entityData(const ECS& ecs) {
        return ecs.scoringBounds;
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
