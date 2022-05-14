#ifndef STATE_COMPONENT_H
#define STATE_COMPONENT_H

enum class EntityState {
    NOVAL = -1,
    IDLE,
    MOVING,
};

struct StateComponent {
    EntityState state = EntityState::NOVAL;
};

#endif