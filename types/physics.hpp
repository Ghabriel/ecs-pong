#pragma once

#include <vector>
#include "../physics/find-angle-between.hpp"
#include "../physics/find-closest-edges.hpp"
#include "../physics/find-collision-point.hpp"
#include "../physics/rotate.hpp"
#include "../shapes/Circle.hpp"
#include "../shapes/Line.hpp"
#include "../shapes/Point.hpp"
#include "../shapes/Rectangle.hpp"

struct MovingCircle {
    Circle circle;
    Vector velocity;
};

struct MovingRectangle {
    Rectangle rectangle;
    Vector velocity;
};

#include <iostream>
#include "debug.hpp"

bool interact(MovingCircle& ball, const Rectangle& block) {
    auto& [circle, velocity] = ball;
    auto& [center, radius] = circle;

    Line ballTrajectory { center, velocity };
    std::vector<LineSegment> closestEdges = findClosestEdges(block, circle);
    Line extendedEdge = Line::fromSegment(closestEdges[0]);
    Point collisionPoint = findCollisionPoint(ballTrajectory, extendedEdge);

    if (!closestEdges[0].containsPoint(collisionPoint)) {
        return false;
    }

    Vector normal { -1, 0 }; // TODO

    Vector centerToCollision = collisionPoint - center;
    float squaredDistanceToCollision = centerToCollision.getSquaredNorm();
    if (normal.dot(velocity) > 0 || squaredDistanceToCollision > velocity.getSquaredNorm()) {
        return false;
    }

    float theta = findAngleBetween(-velocity, normal);
    Point reflectedPosition = rotate(center, 2 * theta, collisionPoint);

    if ((reflectedPosition - collisionPoint).getSquaredNorm() > 1e-3) {
        Point projectedDestination = center + velocity;
        Vector depth = projectedDestination - collisionPoint;
        Vector reflectionDirection = (reflectedPosition - collisionPoint).normalize();
        center = collisionPoint + depth.norm() * reflectionDirection;
    }

    velocity = rotate(-velocity, 2 * theta);

    return true;
}
