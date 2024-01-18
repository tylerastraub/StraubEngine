#pragma once

#include "vec2.h"

#include <SDL.h>
#include <entt/entity/registry.hpp>

class RenderSystem {
public:
    RenderSystem() = default;
    ~RenderSystem() = default;

    void update(entt::registry& ecs, float timescale);

    void render(SDL_Renderer* renderer, entt::registry& ecs, strb::vec2f renderOffset = {0.f, 0.f});

    void setRenderBounds(strb::vec2i renderBounds);

private:
    strb::vec2i _renderBounds = {0, 0};

};