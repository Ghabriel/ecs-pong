#pragma once

#include "../framework/ecs/userland.hpp"
#include "../shapes/LineSegment.hpp"
#include "../shapes/Point.hpp"
#include "../shapes/Rectangle.hpp"

void createWalls(ecs::ComponentManager& world, const Rectangle& boardArea) {
    Point upperLeft { 0, 0 };
    Point upperRight { boardArea.width, 0 };
    Point lowerLeft { 0, boardArea.height };
    Point lowerRight { boardArea.width, boardArea.height };
    LineSegment upperSegment { upperLeft, upperRight };
    LineSegment lowerSegment { lowerLeft, lowerRight };

    world.createEntity(Wall { { upperSegment, { 0, 1 } } });
    world.createEntity(Wall { { lowerSegment, { 0, -1 } } });
}
