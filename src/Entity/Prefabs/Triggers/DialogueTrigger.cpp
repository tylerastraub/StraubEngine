#include "DialogueTrigger.h"
#include "EntityRegistry.h"
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

        void update(Entity owner, float timescale, Audio* audio) override {
            auto ecs = EntityRegistry::getInstance();
        }

    private:

    };
}

namespace prefab {
    Entity DialogueTrigger::create() {
        return create({0, 0, 0, 0}, true, false, -1);
    }

    Entity DialogueTrigger::create(SDL_Rect triggerRect, bool triggerOnce, bool entityMustBeGrounded, int conversationId) {
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
            TriggerType::DIALOGUE,
            std::make_shared<OnTriggerScript>(),
            triggerOnce,
            entityMustBeGrounded
        });
        ecs->addComponent<DialogueTriggerComponent>(ent, DialogueTriggerComponent{conversationId});

        return ent;
    }
}