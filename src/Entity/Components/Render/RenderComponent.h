#pragma once

#include "rect2.h"
#include "vec2.h"

/**
 * @brief Render component used if entity should be rendered when on screen
 **/
struct RenderComponent {
    // RenderCopy parameters
    strb::rect2i renderQuad = {0, 0, 0, 0};
    strb::vec2i renderQuadOffset = {0, 0};
};