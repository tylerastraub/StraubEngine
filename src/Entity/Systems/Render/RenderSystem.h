#pragma once

#include "System.h"
#include "vec2.h"

#include <SDL.h>

class RenderSystem : public System {
public:
    RenderSystem() = default;
    ~RenderSystem() = default;

    void update(float timescale);

    void render(SDL_Renderer* renderer, int renderXOffset = 0, int renderYOffset = 0);

    void setRenderBounds(strb::vec2i renderBounds);

private:
    strb::vec2i _renderBounds = {0, 0};

};