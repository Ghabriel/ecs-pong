#pragma once

#include "../engine-glue/ecs.hpp"
#include "../engine/shapes/LineSegment.hpp"
#include "../engine/shapes/Point.hpp"
#include "../engine/shapes/Rectangle.hpp"

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
