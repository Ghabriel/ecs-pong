#pragma once

#include <random>
#include "../components/CircularObject.hpp"
#include "../components/Drawable.hpp"
#include "../components/ScoreListener.hpp"
#include "../components/ScoringBounds.hpp"
#include "../components/Velocity.hpp"
#include "../framework/ComponentManager.hpp"
#include "../shapes/Circle.hpp"

using ecs::Entity;

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

Entity createBall(ecs::ComponentManager& world, const Rectangle& boardArea) {
    constexpr float radius = 10;

    Point center = boardArea.getMidPoint();
    Circle circle { center, radius };

    Entity id = world.createEntity(
        CircularObject { circle },
        Drawable { },
        ScoringBounds { 0, boardArea.width },
        Velocity { generateVelocity() }
    );

    auto scoringCallback = [&world, id, circle](Team) {
        world.getData<CircularObject>(id) = CircularObject { circle };
        world.getData<Velocity>(id) = Velocity { generateVelocity() };
    };

    world.createEntity(
        ScoreListener { scoringCallback }
    );

    return id;
}
