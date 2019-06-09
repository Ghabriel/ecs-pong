#pragma once

#include <random>
#include "../constants.hpp"
#include "../engine/ecs/userland.hpp"
#include "../engine/shapes/Rectangle.hpp"

Vector generateVelocity() {
    using constants::BALL_MAX_AXIS_VELOCITY;
    using constants::BALL_MIN_SQUARED_VELOCITY;
    using constants::BALL_MAX_SQUARED_VELOCITY;
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<int> dist(-BALL_MAX_AXIS_VELOCITY, BALL_MAX_AXIS_VELOCITY);
    int x = 0;
    int y = 0;
    int squaredSpeed = 0;

    while (squaredSpeed < BALL_MIN_SQUARED_VELOCITY || squaredSpeed > BALL_MAX_SQUARED_VELOCITY) {
        x = 0;
        y = 0;

        while (x == 0) {
            x = dist(generator);
        }

        while (y == 0) {
            y = dist(generator);
        }

        squaredSpeed = x * x + y * y;
    }

    return { static_cast<float>(x), static_cast<float>(y) };
}

ecs::Entity createBall(ecs::ComponentManager& world, const Rectangle& boardArea) {
    Point midPoint = boardArea.getMidPoint();

    ecs::Entity id = world.createEntity(
        CircularObject { constants::BALL_RADIUS },
        Drawable { },
        Position { midPoint },
        ScoringBounds { 0, boardArea.width },
        Velocity { generateVelocity() }
    );

    auto scoringCallback = [&world, id, midPoint](Team) {
        world.getData<Position>(id) = { midPoint };
        world.getData<Velocity>(id) = Velocity { generateVelocity() };
    };

    world.createEntity(
        ScoreListener { scoringCallback }
    );

    return id;
}
