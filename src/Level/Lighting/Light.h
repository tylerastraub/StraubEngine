#pragma once

#include "Hue.h"

#include <SDL.h>
#include <entt/entity/registry.hpp>

struct Light {
    uint16_t id = SDL_MAX_UINT16;
    // The light's absolute position
    strb::vec2f pos = {0.f, 0.f};
    // The light's brightness from a scale of 0-1
    float brightness = 0.f;
    // The rate at which the light falls off the further it gets from the source (from 0-1). Default is 0.2
    float falloff = 0.2f;

    Hue hue;
    
    entt::entity owner = entt::null;

    float lastBrightness = 0.f;
};