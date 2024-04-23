#include "PrefabSpawnTrigger.h"
// Components
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "TriggerComponent.h"
#include "ScriptComponent.h"
#include "PrefabSpawnTriggerComponent.h"

namespace {
    class OnTriggerScript : public IScript {
    public:
        OnTriggerScript() = default;
        ~OnTriggerScript() = default;

        void update(entt::registry& ecs, entt::entity owner, float timescale, std::shared_ptr<Audio> audio) override {

        }

    private:

    };
}

namespace prefab {
    entt::entity PrefabSpawnTrigger::create(entt::registry& ecs) {
        return create(ecs, {0, 0, 0, 0}, true, false, PrefabType::NOVAL, {0.f, 0.f}, "");
    }

    entt::entity PrefabSpawnTrigger::create(
        entt::registry& ecs,
        strb::rect2f triggerRect,
        bool triggerOnce,
        bool entityMustBeGrounded,
        PrefabType prefabType,
        strb::vec2f prefabSpawnPos,
        std::string prefabValue
    ) {
        entt::entity ent = ecs.create();

        CollisionComponent collision;
        collision.collisionRect = triggerRect;
        collision.collisionRectOffset = {0.f, 0.f};
        
        ecs.emplace<CollisionComponent>(ent, collision);

        ecs.emplace<TransformComponent>(ent, TransformComponent{
            {triggerRect.x, triggerRect.y},
            {triggerRect.x, triggerRect.y}
        });

        ecs.emplace<TriggerComponent>(ent, TriggerComponent{
            TriggerType::PREFAB_SPAWN,
            std::make_shared<OnTriggerScript>(),
            triggerOnce,
            entityMustBeGrounded
        });
        ecs.emplace<PrefabSpawnTriggerComponent>(ent, PrefabSpawnTriggerComponent{
            prefabType,
            prefabSpawnPos,
            prefabValue
        });

        return ent;
    }
}