#pragma once

#include "rect2.h"
#include "vec2.h"

struct RenderComponent {
    strb::rect2f renderQuad = {0, 0, 0, 0};
    strb::vec2f renderQuadOffset = {0, 0};
};