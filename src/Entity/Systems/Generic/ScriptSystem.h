#pragma once

#include "Audio.h"

#include <entt/entity/registry.hpp>
#include <memory>

class ScriptSystem {
public:
    ScriptSystem() = default;
    ~ScriptSystem() = default;

    void update(entt::registry& ecs, std::shared_ptr<Audio> audio, float timescale);

private:

};