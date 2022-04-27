#include "PhysicsSystem.h"
#include "EntityRegistry.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"

#include <iostream>
#include <algorithm>

bool PhysicsSystem::updateSingleEntity(float timescale, Entity entity) {
    bool entityMoved = false;
    auto ecs = EntityRegistry::getInstance();
    Tilemap* tilemap = _level.getTilemap();
    auto& rigidBody = ecs->getComponent<RigidBodyComponent>(entity);
    auto& transform = ecs->getComponent<TransformComponent>(entity);

    transform.lastPosition = transform.position; // always update this since last position is based on tile position previous turn
    if(rigidBody.velocity.x != 0.f || rigidBody.velocity.y != 0.f) {
        entityMoved = true;
        transform.position += rigidBody.velocity;

        // slow entity down based on acceleration
        // x slow
        if(rigidBody.velocity.x > 0.f) {
            rigidBody.velocity.x -= rigidBody.acceleration.x;
            if(rigidBody.velocity.x < 0.f) rigidBody.velocity.x = 0.f;
        }
        else if(rigidBody.velocity.x < 0.f) {
            rigidBody.velocity.x += rigidBody.acceleration.x;
            if(rigidBody.velocity.x > 0.f) rigidBody.velocity.x = 0.f;
        }
        // y slow
        if(rigidBody.velocity.y > 0.f) {
            rigidBody.velocity.y -= rigidBody.acceleration.y;
            if(rigidBody.velocity.y < 0.f) rigidBody.velocity.y = 0.f;
        }
        else if(rigidBody.velocity.y < 0.f) {
            rigidBody.velocity.y += rigidBody.acceleration.y;
            if(rigidBody.velocity.y > 0.f) rigidBody.velocity.y = 0.f;
        }
    }
    return entityMoved;
}

bool PhysicsSystem::updateAllButEntities(float timescale, std::list<Entity> entities) {
    bool entityMoved = false;
    auto ecs = EntityRegistry::getInstance();
    Tilemap* tilemap = _level.getTilemap();
    for(auto ent : _entities) {
        if(std::find(entities.begin(), entities.end(), ent) != entities.end()) continue;
        auto& rigidBody = ecs->getComponent<RigidBodyComponent>(ent);
        auto& transform = ecs->getComponent<TransformComponent>(ent);

        transform.lastPosition = transform.position; // always update this since last position is based on tile position previous turn
        if(rigidBody.velocity.x != 0.f || rigidBody.velocity.y != 0.f) {
            entityMoved = true;
            transform.position += rigidBody.velocity;

            // slow entity down based on acceleration
            // x slow
            if(rigidBody.velocity.x > 0.f) {
                rigidBody.velocity.x -= rigidBody.acceleration.x;
                if(rigidBody.velocity.x < 0.f) rigidBody.velocity.x = 0.f;
            }
            else if(rigidBody.velocity.x < 0.f) {
                rigidBody.velocity.x += rigidBody.acceleration.x;
                if(rigidBody.velocity.x > 0.f) rigidBody.velocity.x = 0.f;
            }
            // y slow
            if(rigidBody.velocity.y > 0.f) {
                rigidBody.velocity.y -= rigidBody.acceleration.y;
                if(rigidBody.velocity.y < 0.f) rigidBody.velocity.y = 0.f;
            }
            else if(rigidBody.velocity.y < 0.f) {
                rigidBody.velocity.y += rigidBody.acceleration.y;
                if(rigidBody.velocity.y > 0.f) rigidBody.velocity.y = 0.f;
            }
        }
    }
    return entityMoved;
}

bool PhysicsSystem::update(float timescale) {
    bool entityMoved = false;
    auto ecs = EntityRegistry::getInstance();
    Tilemap* tilemap = _level.getTilemap();
    for(auto ent : _entities) {
        auto& rigidBody = ecs->getComponent<RigidBodyComponent>(ent);
        auto& transform = ecs->getComponent<TransformComponent>(ent);

        // todo: check for collisions first, if there is a move, then do the following code
        transform.lastPosition = transform.position; // always update this since last position is based on tile position previous turn
        if(rigidBody.velocity.x != 0.f || rigidBody.velocity.y != 0.f) {
            entityMoved = true;
            transform.position += rigidBody.velocity;

            // slow entity down based on acceleration
            // x slow
            if(rigidBody.velocity.x > 0.f) {
                rigidBody.velocity.x -= rigidBody.acceleration.x;
                if(rigidBody.velocity.x < 0.f) rigidBody.velocity.x = 0.f;
            }
            else if(rigidBody.velocity.x < 0.f) {
                rigidBody.velocity.x += rigidBody.acceleration.x;
                if(rigidBody.velocity.x > 0.f) rigidBody.velocity.x = 0.f;
            }
            // y slow
            if(rigidBody.velocity.y > 0.f) {
                rigidBody.velocity.y -= rigidBody.acceleration.y;
                if(rigidBody.velocity.y < 0.f) rigidBody.velocity.y = 0.f;
            }
            else if(rigidBody.velocity.y < 0.f) {
                rigidBody.velocity.y += rigidBody.acceleration.y;
                if(rigidBody.velocity.y > 0.f) rigidBody.velocity.y = 0.f;
            }
        }
    }
    return entityMoved;
}

void PhysicsSystem::setLevel(Level level) {
    _level = level;
}