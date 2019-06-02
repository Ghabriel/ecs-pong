#pragma once

#include "../components/CircularObject.hpp"
#include "../components/RectangularObject.hpp"
#include "../components/Velocity.hpp"
#include "../framework/ComponentManager.hpp"
#include "../shapes/Circle.hpp"
#include "../shapes/Rectangle.hpp"

void applyMovement(ecs::ComponentManager& world, float elapsedTime) {
    world.query<Velocity, CircularObject>(
        [elapsedTime](Entity, Velocity& v, CircularObject& obj) {
            Circle& body = obj.body;
            body.center += v.value * elapsedTime;
        }
    );

    world.query<Velocity, RectangularObject>(
        [elapsedTime](Entity, Velocity& v, RectangularObject& obj) {
            Rectangle& body = obj.body;
            body.corner += v.value * elapsedTime;
        }
    );
}
