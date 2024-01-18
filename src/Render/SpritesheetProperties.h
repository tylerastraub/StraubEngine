#pragma once

#include "vec2.h"

#include <SDL.h>

struct SpritesheetProperties {
    int xTileIndex = 0;
    int yTileIndex = 0;
    bool isAnimated = false;
    bool isLooped = false;
    int numOfFrames = 1;
    int msBetweenFrames = 79;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0.0;
    strb::vec2f center = {-1.f, -1.f};
};