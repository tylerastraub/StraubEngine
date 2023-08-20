#pragma once

#include <SDL.h>

enum class TileType {
    NOVAL = -1,
    SOLID,
    PLATFORM,
    HAZARD,
};

struct Tile {
    TileType type = TileType::NOVAL;
    SDL_Rect spritesheetRect = {0, 0, 0, 0};
};