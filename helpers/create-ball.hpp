#pragma once

#include <random>
#include "../components/CircularObject.hpp"
#include "../components/Velocity.hpp"
#include "../framework/ComponentManager.hpp"
#include "../shapes/Circle.hpp"

using ecs::Entity;

Vector generateVelocity() {
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<int> dist(-5, 5);
    int x = 0;
    int y = 0;
    int squaredSpeed = 0;

    while (squaredSpeed < 20 || squaredSpeed > 50) {
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
    Vector velocity = generateVelocity();

    Entity id = world.createEntity();
    world.addComponent<CircularObject>(id, { circle });
    world.addComponent<Velocity>(id, { velocity });
    return id;
}
