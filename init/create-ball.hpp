#pragma once

#include <random>
#include "../constants.hpp"
#include "../events/BaseEvents.hpp"
#include "../framework/ecs/ComponentManager.hpp"
#include "../framework/ecs/EventManager.hpp"
#include "../shapes/Rectangle.hpp"

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

class BallResetEvent : public TeamEvent {
 public:
    BallResetEvent(
        ecs::ComponentManager& world,
        ecs::Entity ballId,
        Point midPoint
    ) : world(world), ballId(ballId), midPoint(midPoint) { }

    virtual void operator()(const Team& team) override {
        world.getData<Position>(ballId) = { midPoint };
        world.getData<Velocity>(ballId) = Velocity { generateVelocity() };
    }

 private:
    ecs::ComponentManager& world;
    ecs::Entity ballId;
    Point midPoint;
};

ecs::Entity createBall(
    ecs::ComponentManager& world,
    const Rectangle& boardArea,
    events::EventManager& eventManager
) {
    Point midPoint = boardArea.getMidPoint();

    ecs::Entity id = world.createEntity(
        CircularObject { constants::BALL_RADIUS },
        Drawable { },
        Position { midPoint },
        ScoringBounds { 0, boardArea.width },
        Velocity { generateVelocity() }
    );

    events::ListenerId listenerId = eventManager.registerEventListener(
        std::unique_ptr<TeamEvent>(new BallResetEvent(world, id, midPoint))
    );

    eventManager.enableEventListener<TeamEvent>("score-event", listenerId);

    return id;
}
