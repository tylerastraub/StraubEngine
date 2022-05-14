#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "RenderPlane.h"

/**
 * @brief Render component used if entity should be rendered when on screen
 **/
struct RenderComponent {
    // RenderCopy parameters
    SDL_Rect renderQuad = {0, 0, 0, 0};
    SDL_Point renderQuadOffset = {0, 0};
    Plane renderPlane = Plane::NOVAL;
};

#endif