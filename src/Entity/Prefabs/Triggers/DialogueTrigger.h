#pragma once

#include "rect2.h"

#include <cstdint>

using Entity = std::uint16_t;

namespace prefab {
    class DialogueTrigger {
    public:
        DialogueTrigger() = default;
        ~DialogueTrigger() = default;

        static Entity create();
        static Entity create(strb::rect2i triggerRect, bool triggerOnce, bool entityMustBeGrounded, int conversationId);

    private:

    };
}