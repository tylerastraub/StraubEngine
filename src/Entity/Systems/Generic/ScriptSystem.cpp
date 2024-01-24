#include "ScriptSystem.h"
#include "ScriptComponent.h"

void ScriptSystem::init(std::shared_ptr<Audio> audio) {
    _audio = audio;
}

void ScriptSystem::update(entt::registry& ecs, float timescale) {
    auto entities = ecs.view<ScriptComponent>();
    for(auto ent : entities) {
        auto& script = ecs.get<ScriptComponent>(ent);
        script.script->update(ecs, ent, timescale, _audio);
    }
}