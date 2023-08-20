#pragma once

#include "EntityComponentSystem.h"

// Singleton instance used to call ECS
class EntityRegistry {
public:
    static EntityComponentSystem* getInstance() {
        if(_instance == nullptr) _instance = new EntityComponentSystem();
        return _instance;
    }

private:
    EntityRegistry() = default;

    static inline EntityComponentSystem* _instance = nullptr;

};