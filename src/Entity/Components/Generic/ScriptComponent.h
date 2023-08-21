#pragma once

#include "Audio.h"

#include <memory>
#include <cstdint>
#include <entt/entity/registry.hpp>

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
    virtual void update(entt::registry& ecs, entt::entity owner, float timescale, std::shared_ptr<Audio> audio) = 0;

private:

};

struct ScriptComponent {
    std::shared_ptr<IScript> script = nullptr;
};