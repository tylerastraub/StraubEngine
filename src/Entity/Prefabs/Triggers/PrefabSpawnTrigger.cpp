#include "PrefabSpawnTrigger.h"
#include "EntityRegistry.h"
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

        void update(Entity owner, float timescale, Audio* audio) override {
            auto ecs = EntityRegistry::getInstance();
        }

    private:

    };
}

namespace prefab {
    Entity PrefabSpawnTrigger::create() {
        return create({0, 0, 0, 0}, true, false, PrefabType::NOVAL, {0.f, 0.f}, "");
    }

    Entity PrefabSpawnTrigger::create(
        SDL_Rect triggerRect,
        bool triggerOnce,
        bool entityMustBeGrounded,
        PrefabType prefabType,
        strb::vec2f prefabSpawnPos,
        std::string prefabValue
    ) {
        auto ecs = EntityRegistry::getInstance();
        Entity ent = ecs->createEntity();

        CollisionComponent collision;
        collision.collisionRect = triggerRect;
        collision.collisionRectOffset = {0, 0};
        
        ecs->addComponent<CollisionComponent>(ent, collision);

        ecs->addComponent<TransformComponent>(ent, TransformComponent{
            {(float) triggerRect.x, (float) triggerRect.y},
            {(float) triggerRect.x, (float) triggerRect.y}
        });

        ecs->addComponent<TriggerComponent>(ent, TriggerComponent{
            TriggerType::PREFAB_SPAWN,
            std::make_shared<OnTriggerScript>(),
            triggerOnce,
            entityMustBeGrounded
        });
        ecs->addComponent<PrefabSpawnTriggerComponent>(ent, PrefabSpawnTriggerComponent{
            prefabType,
            prefabSpawnPos,
            prefabValue
        });

        return ent;
    }
}