#pragma once

#include "rect2.h"
#include "vec2.h"

#include <entt/entity/registry.hpp>

namespace prefab {
    class CameraTargetTrigger {
    public:
        CameraTargetTrigger() = default;
        ~CameraTargetTrigger() = default;

        static entt::entity create(entt::registry& ecs);
        static entt::entity create(entt::registry& ecs, strb::rect2f triggerRect, bool entityMustBeGrounded, strb::vec2f cameraTarget);

    private:

    };
}