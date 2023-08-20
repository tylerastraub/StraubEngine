#pragma once

#include <cstdint>
#include <SDL.h>

using Entity = std::uint16_t;

namespace prefab {
    class DialogueTrigger {
    public:
        DialogueTrigger() = default;
        ~DialogueTrigger() = default;

        static Entity create();
        static Entity create(SDL_Rect triggerRect, bool triggerOnce, bool entityMustBeGrounded, int conversationId);

    private:

    };
}