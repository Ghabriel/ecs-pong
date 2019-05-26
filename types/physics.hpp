#pragma once

#include <vector>
#include "../physics/find-closest-edges.hpp"
#include "../physics/find-collision-point.hpp"
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
    {}

    Line ballTrajectory { center, velocity };
    std::vector<LineSegment> closestEdges = findClosestEdges(block, circle);
    Line extendedEdge = Line::fromSegment(closestEdges[0]);
    Point collisionPoint = findCollisionPoint(ballTrajectory, extendedEdge);

    std::cout << "-------------\n";
    // for (const auto& edge : closestEdges) {
    //     std::cout << "edge: " << edge << "\n";
    // }
    std::cout << "ball trajectory: " << ballTrajectory << "\n";
    std::cout << "closest edge: " << closestEdges[0] << "\n";
    std::cout << "extended edge: " << extendedEdge << "\n";
    std::cout << "collision point: " << collisionPoint << "\n";
    std::cout << "contains? " << closestEdges[0].containsPoint(collisionPoint) << "\n";

    if (!closestEdges[0].containsPoint(collisionPoint)) {
        return false;
    }

    // Vector normal { -1, 0 }; // TODO
    // float theta = findAngleBetween(normal, -velocity);

    // Point projectedDestination = center + velocity;
    // Vector depth = projectedDestination - collisionPoint;
    // Line normalLine { collisionPoint, normal };
    // Point reflectedPosition = rotate(center, 2 * theta, normalLine);

    // ball.center = depth.norm() * (reflectedPosition - collisionPoint).normalize();
    // ball.velocity = rotate(-velocity, 2 * theta, normalLine);

    return false;



    // if (x + radius + vx > 760) {
    //     float depth = x + radius + vx - 760;
    //     x = 760 - depth - radius;
    //     vx *= -1;
    // } else {
    //     x += vx;
    //     y += vy;
    // }
}
