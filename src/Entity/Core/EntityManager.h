#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "EntityConstants.h"

#include <cstdint>
#include <queue>
#include <bitset>

using Entity = std::uint16_t;
using Signature = std::bitset<entityConstants::MAX_COMPONENTS>;

class EntityManager {
public:
    EntityManager();
    ~EntityManager() = default;

    /**
     * @brief Creates an entity to be added to the entity manager
     * 
     * @return The entity ID of the newly created entity
     */
    Entity createEntity();

    /**
     * @brief Destroys an entity, freeing up that ID
     * 
     * @param entity The entity ID to be destroyed
     */
    void destroyEntity(Entity entity);

    /**
     * @brief Set the entity's component signature
     * 
     * @param entity The entity ID of the entity to be modified
     * @param signature The signature to add to the entity
     */
    void setSignature(Entity entity, Signature signature);

    /**
     * @brief Get's the signature of an entity
     * 
     * @param entity The entity ID of the entity whose signature is requested
     * @return The entity's component signature
     */
    Signature getSignature(Entity entity);

private:
    std::queue<Entity> _availableIds;
    Signature _signatures[entityConstants::MAX_ENTITIES];
    int _activeEntities = 0;
};

#endif