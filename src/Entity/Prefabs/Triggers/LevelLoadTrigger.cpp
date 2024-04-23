#include "LevelLoadTrigger.h"
// Components
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "TriggerComponent.h"
#include "DialogueTriggerComponent.h"
#include "ScriptComponent.h"
#include "LevelLoadTriggerComponent.h"

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
    entt::entity LevelLoadTrigger::create(entt::registry& ecs) {
        return create(ecs, {0, 0, 0, 0}, "", -1);
    }

    entt::entity LevelLoadTrigger::create(entt::registry& ecs, strb::rect2f triggerRect, std::string levelPath, int playerSpawnID) {
        entt::entity trigger = ecs.create();

        CollisionComponent collision;
        collision.collisionRect = triggerRect;
        collision.collisionRectOffset = {0, 0};
        ecs.emplace<CollisionComponent>(trigger, collision);

        ecs.emplace<TransformComponent>(trigger, TransformComponent{
            {(float) triggerRect.x, (float) triggerRect.y},
            {(float) triggerRect.x, (float) triggerRect.y}
        });

        ecs.emplace<TriggerComponent>(trigger, TriggerComponent{
            TriggerType::LEVEL_LOAD,
            std::make_shared<OnTriggerScript>(),
            false,
            false
        });

        ecs.emplace<LevelLoadTriggerComponent>(trigger, LevelLoadTriggerComponent{levelPath, playerSpawnID});

        return trigger;
    }
}