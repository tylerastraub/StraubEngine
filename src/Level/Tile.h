#pragma once

#include "rect2.h"

enum class TileType {
    NOVAL = -1,
    SOLID,
    PLATFORM,
    HAZARD,
};

struct Tile {
    TileType type = TileType::NOVAL;
    strb::rect2i spritesheetRect = {0, 0, 0, 0};
};