#ifndef DIALOGUE_TRIGGER_H
#define DIALOGUE_TRIGGER_H

#include "vec2.h"

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

#endif