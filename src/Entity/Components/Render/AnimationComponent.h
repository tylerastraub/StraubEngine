#pragma once

#include "StateComponent.h"

struct AnimationComponent {
    int msSinceAnimationStart = 0;
    int xIndex = 0;
    EntityState lastState = EntityState::NOVAL;
};