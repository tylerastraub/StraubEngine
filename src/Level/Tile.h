#ifndef TILE_H
#define TILE_H

#include <SDL.h>

enum class TileType {
    NOVAL = -1,
    GROUND,
    WALL,
};

struct Tile {
    TileType type;
    SDL_Rect spritesheetRect;
};

#endif