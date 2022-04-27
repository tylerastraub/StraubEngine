#include "ScriptSystem.h"
#include "EntityRegistry.h"
#include "ScriptComponent.h"

void ScriptSystem::update(float timescale) {
    auto ecs = EntityRegistry::getInstance();
    for(auto ent : _entities) {
        auto& script = ecs->getComponent<ScriptComponent>(ent);
        script.script->update(ent, timescale);
    }
}