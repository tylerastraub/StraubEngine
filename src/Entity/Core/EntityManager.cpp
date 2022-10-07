#include "EntityManager.h"

#include <iostream>

EntityManager::EntityManager() {
    for(Entity id = 0; id < entityConstants::MAX_ENTITIES; ++id) {
        _availableIds.push(id);
    }
}

Entity EntityManager::createEntity() {
    if(_activeEntities < entityConstants::MAX_ENTITIES) {
        Entity id = _availableIds.front();
        _availableIds.pop();
        ++_activeEntities;
        
        return id;
    }

    std::cout << "Error: currently at max entities (" << entityConstants::MAX_ENTITIES << ")" << std::endl;
    return -1;
}

void EntityManager::destroyEntity(Entity entity) {
    if(entity < entityConstants::MAX_ENTITIES) {
        _signatures[entity].reset();
        _availableIds.push(entity);
        --_activeEntities;
    }
    else {
        std::cout << "Error: invalid entity ID for destruction entity " << entity << std::endl;
    }
}

void EntityManager::setSignature(Entity entity, Signature signature) {
    if(entity < entityConstants::MAX_ENTITIES) {
        _signatures[entity] = signature;
    }
    else {
        std::cout << "Error: invalid entity ID for setting signature entity " << entity << std::endl;
    }
}

Signature EntityManager::getSignature(Entity entity) {
    if(entity < entityConstants::MAX_ENTITIES) {
        return _signatures[entity];
    }
    else {
        std::cout << "Error: invalid entity ID for getting signature entity " << entity << std::endl;
    }
    return Signature();
}