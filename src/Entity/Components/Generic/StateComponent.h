#ifndef STATE_COMPONENT_H
#define STATE_COMPONENT_H

enum class EntityState {
    NOVAL = -1,
    IDLE,
    READY_TO_MOVE,
    MOVING,
    TURNING,
    SHOVED,
};

struct StateComponent {
    EntityState state = EntityState::NOVAL;
};

#endif