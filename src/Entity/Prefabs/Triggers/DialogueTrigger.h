#pragma once

#include "rect2.h"

#include <cstdint>
#include <entt/entity/registry.hpp>

namespace prefab {
    class DialogueTrigger {
    public:
        DialogueTrigger() = default;
        ~DialogueTrigger() = default;

        static entt::entity create(entt::registry& ecs);
        static entt::entity create(entt::registry& ecs, strb::rect2f triggerRect, bool triggerOnce, bool entityMustBeGrounded, int conversationId);

    private:

    };
}