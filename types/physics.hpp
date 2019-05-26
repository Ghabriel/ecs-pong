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
        // std::cout << "-----\n";
        // for (const auto& edge : closestEdges) {
        //     std::cout << "edge: " << edge << "\n";
        // }
        // std::cout << "center: " << center << "\n";
        // std::cout << "velocity: " << velocity << "\n";
        // std::cout << "collisionPoint: " << collisionPoint << "\n";
        // std::cout << "squaredDistanceToCollision: " << squaredDistanceToCollision << "\n";
        // std::cout << "velocity norm^2: " << velocity.getSquaredNorm() << "\n";

        return false;
    }

    float theta = findAngleBetween(-velocity, normal);

    Point projectedDestination = center + velocity;
    Vector depth = projectedDestination - collisionPoint;
    Point reflectedPosition = rotate(center, 2 * theta, collisionPoint);

    std::cout << "-------------\n";
    std::cout << "center: " << center << "\n";
    std::cout << "velocity: " << velocity << "\n";

    if ((reflectedPosition - collisionPoint).getSquaredNorm() > 1e-3) {
        Vector reflectionDirection = (reflectedPosition - collisionPoint).normalize();
        center = collisionPoint + depth.norm() * reflectionDirection;
    }

    velocity = rotate(-velocity, 2 * theta);

    // for (const auto& edge : closestEdges) {
    //     std::cout << "edge: " << edge << "\n";
    // }
    std::cout << "theta: " << (theta * 180 / M_PI) << "\n";
    std::cout << "collisionPoint: " << collisionPoint << "\n";
    std::cout << "projectedDestination: " << projectedDestination << "\n";
    std::cout << "depth: " << depth << "\n";
    std::cout << "reflectedPosition: " << reflectedPosition << "\n";
    std::cout << "[new] center: " << center << "\n";
    std::cout << "[new] velocity: " << velocity << "\n";

    return true;



    // if (x + radius + vx > 760) {
    //     float depth = x + radius + vx - 760;
    //     x = 760 - depth - radius;
    //     vx *= -1;
    // } else {
    //     x += vx;
    //     y += vy;
    // }
}
