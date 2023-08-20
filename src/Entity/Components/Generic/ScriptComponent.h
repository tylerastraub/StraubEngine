#pragma once

#include "Audio.h"

#include <memory>
#include <cstdint>

using Entity = std::uint16_t;

class IScript {
public:
    IScript() = default;
    virtual ~IScript() = default;

    /**
     * @brief Update the script.
     * 
     * @param timescale The timescale to update by - is usually fixed.
     * @param phase The current phase the TurnSystem is in. Scripts can choose to ignore this.
     */
    virtual void update(Entity owner, float timescale, Audio* audio) = 0;

private:

};

struct ScriptComponent {
    std::shared_ptr<IScript> script = nullptr;
};