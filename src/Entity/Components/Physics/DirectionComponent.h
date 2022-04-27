#ifndef DIRECTION_COMPONENT_H
#define DIRECTION_COMPONENT_H

enum class Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST,
    NORTHEAST,
    NORTHWEST,
    SOUTHEAST,
    SOUTHWEST,
};

struct DirectionComponent {
    Direction direction;
};

#endif