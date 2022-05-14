#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include "StateComponent.h"

struct AnimationComponent {
    int msSinceAnimationStart = 0;
    int xIndex = 0;
    EntityState lastState = EntityState::NOVAL;
};

#endif