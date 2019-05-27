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

Vector getNormalVector(const std::vector<OrientedLineSegment>& parts) {
    Vector normal { 0, 0 };

    for (const OrientedLineSegment& edge : parts) {
        normal += edge.normal;
    }

    return normal.normalize();
}

bool interact(MovingCircle& ball, const Rectangle& block) {
    auto& [circle, velocity] = ball;
    auto& [center, radius] = circle;

    std::vector<OrientedLineSegment> closestEdges = findClosestEdges(block, circle);
    Line extendedEdge = Line::fromSegment(closestEdges[0].segment);

    Vector normal = getNormalVector(closestEdges);
    Point closestPoint = center - radius * normal;
    Line ballTrajectory { closestPoint, velocity };
    Point collisionPoint = findCollisionPoint(ballTrajectory, extendedEdge);

    if (!closestEdges[0].segment.containsPoint(collisionPoint)) {
        return false;
    }

    Vector ballToCollision = collisionPoint - closestPoint;
    float squaredDistanceToCollision = ballToCollision.getSquaredNorm();
    if (normal.dot(velocity) > 0 || squaredDistanceToCollision > velocity.getSquaredNorm()) {
        return false;
    }

    float theta = findAngleBetween(-velocity, normal);
    Point reflectedPosition = rotate(closestPoint, 2 * theta, collisionPoint);

    if ((reflectedPosition - collisionPoint).getSquaredNorm() > 1e-3) {
        Point projectedDestination = closestPoint + velocity;
        Vector depth = projectedDestination - collisionPoint;
        Vector reflectionDirection = (reflectedPosition - collisionPoint).normalize();
        center = collisionPoint + depth.norm() * reflectionDirection + radius * normal;
    }

    velocity = rotate(-velocity, 2 * theta);

    return true;
}
