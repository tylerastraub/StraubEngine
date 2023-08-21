#pragma once

#include "rect2.h"
#include "vec2.h"

struct RenderComponent {
    strb::rect2i renderQuad = {0, 0, 0, 0};
    strb::vec2i renderQuadOffset = {0, 0};
};