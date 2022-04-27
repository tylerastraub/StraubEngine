#ifndef SPRITESHEET_PROPERTIES
#define SPRITESHEET_PROPERTIES

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
    SDL_Point center = {-1, -1};
};

#endif