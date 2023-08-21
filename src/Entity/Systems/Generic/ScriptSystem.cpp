#include "ScriptSystem.h"
#include "ScriptComponent.h"

void ScriptSystem::update(entt::registry& ecs, std::shared_ptr<Audio> audio, float timescale) {
    auto entities = ecs.view<ScriptComponent>();
    for(auto ent : entities) {
        auto& script = ecs.get<ScriptComponent>(ent);
        script.script->update(ecs, ent, timescale, audio);
    }
}