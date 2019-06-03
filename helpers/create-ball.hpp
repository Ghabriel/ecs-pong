#pragma once

#include <random>
#include "../components/CircularObject.hpp"
#include "../components/Drawable.hpp"
#include "../components/Position.hpp"
#include "../components/ScoreListener.hpp"
#include "../components/ScoringBounds.hpp"
#include "../components/Velocity.hpp"
#include "../framework/ComponentManager.hpp"
#include "../shapes/Circle.hpp"
#include "../shapes/Rectangle.hpp"

Vector generateVelocity() {
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<int> dist(-500, 500);
    int x = 0;
    int y = 0;
    int squaredSpeed = 0;

    while (squaredSpeed < 250000 || squaredSpeed > 320000) {
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
    constexpr float radius = 10;

    Point midPoint = boardArea.getMidPoint();

    ecs::Entity id = world.createEntity(
        CircularObject { radius },
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
