#pragma once

#include "../framework/ecs/ComponentManager.hpp"
#include "../physics/interactions.hpp"
#include "../shapes/Circle.hpp"
#include "../shapes/MovingCircle.hpp"
#include "../shapes/Rectangle.hpp"

void useMovementSystem(ecs::ComponentManager& world, float elapsedTime) {
    world.query<Velocity, Position, CircularObject>(
        [&world, elapsedTime](ecs::Entity, Velocity& v, Position& pos, const CircularObject& obj) {
            Circle body { pos.location, obj.radius };
            Vector velocity = v.value * elapsedTime;
            MovingCircle ball { body, velocity };

            bool deflected = false;

            world.query<Wall>([&ball, &deflected](ecs::Entity, const Wall& wall) {
                deflected = deflected || interact(ball, wall.body.segment, wall.body.normal);
            });

            if (!deflected) {
                world.query<Position, RectangularObject>(
                    [&ball, &deflected](ecs::Entity, const Position& pos, const RectangularObject& obj) {
                        Point paddleCorner {
                            pos.location.x - obj.width / 2,
                            pos.location.y - obj.height / 2
                        };
                        Rectangle paddle { paddleCorner, obj.width, obj.height };
                        deflected = deflected || interact(ball, paddle);
                    }
                );
            }

            if (!deflected) {
                ball.circle.center += ball.velocity;
            }

            pos.location = ball.circle.center;
            v.value = ball.velocity / elapsedTime;
        }
    );

    world.findAll<Velocity>()
        .join<Position>()
        .join<RectangularObject>()
        .forEach([elapsedTime](Velocity& v, Position& pos) {
            pos.location += v.value * elapsedTime;
        });
}
