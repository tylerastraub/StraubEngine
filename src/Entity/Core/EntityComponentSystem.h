#ifndef ENTITY_COMPONENT_SYSTEM_H
#define ENTITY_COMPONENT_SYSTEM_H

#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

/**
 * @brief Entity Component System used to create, destroy, and manage entities, as well as all components and systems.
 * Users must register all components and systems after initializing the EntityComponentSystem. In the future, this will be cleaned up
 * to make this sleeker, but until we are at a point where that is necessary, this is how it will look.
 * 
 * Modified version of the following EntityComponentSystem - https://austinmorlan.com/posts/entity_component_system
 * 
 * TODO: Add observer methods
 */
class EntityComponentSystem {
public:
    EntityComponentSystem() = default;
    ~EntityComponentSystem() = default;

    /**
     * @brief Initializes the entity component system. May also be called to reset the system.
     */
    void init() {
        for(size_t i = 0; i < entityConstants::MAX_ENTITIES; ++i) {
            _watchers[i].clear();
        }
        _watchers->clear();
        _entityManager = std::make_unique<EntityManager>();
        _componentManager = std::make_unique<ComponentManager>();
        _systemManager = std::make_unique<SystemManager>();
    }

    // Entity
    /**
     * @brief Creates an entity that is immediately added to the entity component system
     * 
     * @return The entity's unique identifier
     */
    Entity createEntity() {
        return _entityManager->createEntity();
    }

    /**
     * @brief Removes the entity from the system
     */
    void destroyEntity(Entity entity) {
        for(auto system : _watchers[entity]) {
            system->onEntityDelete(entity);
        }
        _watchers[entity].clear();
        _entityManager->destroyEntity(entity);
        _componentManager->entityDestroyed(entity);
        _systemManager->entityDestroyed(entity);
    }

    void addWatcher(System* system, Entity entity) {
        _watchers[entity].push_back(system);
    }

    void reregisterEntity(Entity entity) {
        _systemManager->entitySignatureChanged(entity, _entityManager->getSignature(entity));
    }

    // Component
    /**
     * @brief Adds a component to the entity
     */
    template<typename T>
    void addComponent(Entity entity, T component) {
        _componentManager->addComponent(entity, component);
        
        Signature signature = _entityManager->getSignature(entity);
        signature.set(_componentManager->getComponentType<T>(), true);
        _entityManager->setSignature(entity, signature);

        _systemManager->entitySignatureChanged(entity, signature);
    }

    /**
     * @brief Gets the component owned by the entity
     * 
     * @return The reference to the entity's component, or a blank component if the entity does not have it.
     */
    template<typename T>
    T& getComponent(Entity entity) {
        return _componentManager->getComponent<T>(entity);
    }
    
    /**
     * @brief Gets the component type in a human readable string. Used for hash table mapping usually.
     * 
     * @return The component type
     */
    template<typename T>
    ComponentType getComponentType() {
        return _componentManager->getComponentType<T>();
    }

    /**
     * @brief Determines whether or not the entity has a given component
     * 
     * @return True if entity has component, false if not
     */
    template<typename T>
    bool hasComponent(Entity entity) {
        return _componentManager->hasComponent<T>(entity);
    }

    /**
     * @brief Gets all entities that own the specified component
     * 
     * @return The list of all entities with the specified component
     */
    template<typename T>
    std::list<Entity> getAllOf() {
        return _componentManager->getAllOf<T>();
    } 

    // System
    /**
     * @brief Registers a system in the entity component system so that it can interact with entities properly.
     * 
     * @return A shared pointer to the system created in the entity component system.
     */
    template<typename T>
    std::shared_ptr<T> registerSystem() {
        return _systemManager->registerSystem<T>();
    }

    /**
     * @brief Determines which components are required to have an entity added to a system. 
     */
    template<typename T>
    void setSystemSignature(Signature signature) {
        _systemManager->setSignature<T>(signature);
    }

private:
    std::unique_ptr<EntityManager> _entityManager = nullptr;
    std::unique_ptr<ComponentManager> _componentManager = nullptr;
    std::unique_ptr<SystemManager> _systemManager = nullptr;
    std::vector<System*> _watchers[entityConstants::MAX_ENTITIES];

};

#endif