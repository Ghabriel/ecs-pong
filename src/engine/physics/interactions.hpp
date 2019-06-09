#pragma once

#include <vector>
#include "../shapes/Line.hpp"
#include "../shapes/MovingCircle.hpp"
#include "../shapes/Point.hpp"
#include "../shapes/Rectangle.hpp"
#include "find-angle-between.hpp"
#include "find-closest-edges.hpp"
#include "find-collision-point.hpp"
#include "rotate.hpp"

Vector getNormalVector(const std::vector<OrientedLineSegment>& parts) {
    Vector normal { 0, 0 };

    for (const OrientedLineSegment& edge : parts) {
        normal += edge.normal;
    }

    return normal.normalize();
}

/**
 * Interaction between a moving ball and a static line segment with a given
 * normal vector. Bounces the ball if needed.
 */
bool interact(MovingCircle& ball, const LineSegment& segment, const Vector& normal) {
    auto& [circle, velocity] = ball;
    auto& [center, radius] = circle;

    Point closestPoint = center - radius * normal;
    Line ballTrajectory { closestPoint, velocity };
    Line extendedEdge = Line::fromSegment(segment);
    Point collisionPoint = findCollisionPoint(ballTrajectory, extendedEdge);

    if (!segment.containsPoint(collisionPoint)) {
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

/**
 * Interaction between a moving ball and a static rectangle. Bounces the ball
 * if needed.
 */
bool interact(MovingCircle& ball, const Rectangle& block) {
    std::vector<OrientedLineSegment> closestEdges = findClosestEdges(block, ball.circle);
    Vector normal = getNormalVector(closestEdges);

    return interact(ball, closestEdges[0].segment, normal);
}
