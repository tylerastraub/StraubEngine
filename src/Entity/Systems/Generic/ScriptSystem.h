#pragma once

#include "Audio.h"

#include <entt/entity/registry.hpp>
#include <memory>

class ScriptSystem {
public:
    ScriptSystem() = default;
    ~ScriptSystem() = default;

    void init(std::shared_ptr<Audio> audio);

    void update(entt::registry& ecs, float timescale);

private:
    std::shared_ptr<Audio> _audio = nullptr;

};