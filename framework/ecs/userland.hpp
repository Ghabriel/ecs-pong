#pragma once

#include "ComponentManager.hpp"
#include "ECS.hpp"
#include "../../components/CircularObject.hpp"
#include "../../components/Drawable.hpp"
#include "../../components/Input.hpp"
#include "../../components/Position.hpp"
#include "../../components/RectangularObject.hpp"
#include "../../components/Scoreboard.hpp"
#include "../../components/ScoreListener.hpp"
#include "../../components/ScoringBounds.hpp"
#include "../../components/Velocity.hpp"
#include "../../components/Wall.hpp"

namespace ecs {
    using ECS = GenericECS<
        CircularObject,
        Drawable,
        Input,
        Position,
        RectangularObject,
        Scoreboard,
        ScoreListener,
        ScoringBounds,
        Velocity,
        Wall
    >;

    using ComponentManager = GenericComponentManager<ECS>;
}
