#include "DialogueTrigger.h"
#include "DialogueBox.h"
// Components
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "TriggerComponent.h"
#include "DialogueTriggerComponent.h"
#include "ScriptComponent.h"

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
    entt::entity DialogueTrigger::create(entt::registry& ecs) {
        return create(ecs, {0, 0, 0, 0}, true, false, -1);
    }

    entt::entity DialogueTrigger::create(entt::registry& ecs, strb::rect2i triggerRect, bool triggerOnce, bool entityMustBeGrounded, int conversationId) {
        entt::entity ent = ecs.create();

        CollisionComponent collision;
        collision.collisionRect = triggerRect;
        collision.collisionRectOffset = {0, 0};
        
        ecs.emplace<CollisionComponent>(ent, collision);

        ecs.emplace<TransformComponent>(ent, TransformComponent{
            {(float) triggerRect.x, (float) triggerRect.y},
            {(float) triggerRect.x, (float) triggerRect.y}
        });

        ecs.emplace<TriggerComponent>(ent, TriggerComponent{
            TriggerType::DIALOGUE,
            std::make_shared<OnTriggerScript>(),
            triggerOnce,
            entityMustBeGrounded
        });
        ecs.emplace<DialogueTriggerComponent>(ent, DialogueTriggerComponent{conversationId});

        return ent;
    }
}