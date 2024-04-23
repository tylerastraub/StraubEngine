#include "CameraTargetTrigger.h"
// Components
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "TriggerComponent.h"
#include "DialogueTriggerComponent.h"
#include "ScriptComponent.h"
#include "CameraTargetTriggerComponent.h"

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
    entt::entity CameraTargetTrigger::create(entt::registry& ecs) {
        return create(ecs, {0.f, 0.f, 0.f, 0.f}, false, {0.f, 0.f});
    }

    entt::entity CameraTargetTrigger::create(entt::registry& ecs, strb::rect2f triggerRect, bool entityMustBeGrounded, strb::vec2f cameraTarget) {
        entt::entity trigger = ecs.create();

        CollisionComponent collision;
        collision.collisionRect = triggerRect;
        collision.collisionRectOffset = {0.f, 0.f};
        ecs.emplace<CollisionComponent>(trigger, collision);

        ecs.emplace<TransformComponent>(trigger, TransformComponent{
            {triggerRect.x, triggerRect.y},
            {triggerRect.x, triggerRect.y}
        });

        ecs.emplace<TriggerComponent>(trigger, TriggerComponent{
            TriggerType::CAMERA_TARGET,
            std::make_shared<OnTriggerScript>(),
            false,
            entityMustBeGrounded
        });

        ecs.emplace<CameraTargetTriggerComponent>(trigger, CameraTargetTriggerComponent{cameraTarget});

        return trigger;
    }
}