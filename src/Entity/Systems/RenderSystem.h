#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "System.h"
#include "vec2.h"

#include <SDL.h>

class RenderSystem : public System {
public:
    RenderSystem() = default;
    ~RenderSystem() = default;

    /**
     * @brief Updates the render quad position between the previous render quad position and the current transform position.
     * 
     * @param percent The percent from 0-1 between the previous pos and the current pos the render quad should be. Usually a function of time.
     **/ 
    void updateRenderQuadSmoothMovement(float percent);

    void render(SDL_Renderer* renderer, int renderXOffset = 0, int renderYOffset = 0);

    void setRenderBounds(strb::vec2 renderBounds);

private:
    strb::vec2 _renderBounds = {0, 0};

};

#endif