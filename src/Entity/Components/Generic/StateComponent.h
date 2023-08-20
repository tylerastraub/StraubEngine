#pragma once

enum class EntityState {
    NOVAL = -1,
    IDLE,
    MOVING,
};

struct StateComponent {
    EntityState state = EntityState::NOVAL;
};