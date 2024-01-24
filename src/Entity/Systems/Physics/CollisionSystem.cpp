#include "CollisionSystem.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"

void CollisionSystem::updateLevelCollisionsOnXAxis(entt::registry& ecs, Level level) {
    auto view = ecs.view<TransformComponent, CollisionComponent, PhysicsComponent>();
    for(auto entity : view) {
        auto& transform = ecs.get<TransformComponent>(entity);
        auto& physics = ecs.get<PhysicsComponent>(entity);
        auto& collision = ecs.get<CollisionComponent>(entity);
        int ts = level.getTileSize();

        collision.collisionRect.x = transform.position.x + collision.collisionRectOffset.x;

        strb::vec2i topLeftTile = {static_cast<int>(std::floor(collision.collisionRect.x)) / ts,
            static_cast<int>(std::floor(collision.collisionRect.y)) / ts};
        strb::vec2i bottomRightTile = {static_cast<int>(std::ceil(collision.collisionRect.x + collision.collisionRect.w)) / ts,
            static_cast<int>(std::ceil(collision.collisionRect.y + collision.collisionRect.h - 1)) / ts};

        std::vector<strb::vec2i> tileCollisions;
        if(physics.velocity.x < 0) {
            collision.collidingRight = false;
            // get all tiles to the left
            for(int y = topLeftTile.y; y <= bottomRightTile.y; ++y) {
                Tile t = level.getTileAt(topLeftTile.x, y);
                if(t.type == TileType::SOLID) {
                    tileCollisions.push_back({topLeftTile.x, y});
                }
            }

            if(tileCollisions.size()) {
                // we have a hit!
                strb::vec2i tilePos = *tileCollisions.begin();
                transform.position.x = tilePos.x * ts + ts - collision.collisionRectOffset.x;
                collision.collisionRect.x = transform.position.x + collision.collisionRectOffset.x;
                physics.velocity.x = 0;
                collision.collidingLeft = true;
            }
            else {
                collision.collidingLeft = false;
            }
        }
        else if(physics.velocity.x > 0) {
            collision.collidingLeft = false;
            // get all tiles to the right
            for(int y = topLeftTile.y; y <= bottomRightTile.y; ++y) {
                Tile t = level.getTileAt(bottomRightTile.x, y);
                if(t.type == TileType::SOLID) {
                    tileCollisions.push_back({bottomRightTile.x, y});
                }
            }

            if(tileCollisions.size()) {
                // we have a hit!
                strb::vec2i tilePos = *tileCollisions.begin();
                transform.position.x = tilePos.x * ts - collision.collisionRect.w - collision.collisionRectOffset.x;
                collision.collisionRect.x = transform.position.x + collision.collisionRectOffset.x;
                physics.velocity.x = 0;
                collision.collidingRight = true;
            }
            else {
                collision.collidingRight = false;
            }
        }
    }
}

void CollisionSystem::updateLevelCollisionsOnYAxis(entt::registry& ecs, Level level) {
    auto view = ecs.view<TransformComponent, CollisionComponent, PhysicsComponent>();
    for(auto entity : view) {
        auto& transform = ecs.get<TransformComponent>(entity);
        auto& physics = ecs.get<PhysicsComponent>(entity);
        auto& collision = ecs.get<CollisionComponent>(entity);
        int ts = level.getTileSize();

        collision.collisionRect.y = transform.position.y + collision.collisionRectOffset.y;

        strb::vec2i topLeftTile = {static_cast<int>(std::floor(collision.collisionRect.x)) / ts,
            static_cast<int>(std::floor(collision.collisionRect.y)) / ts};
        strb::vec2i bottomRightTile = {static_cast<int>(std::ceil(collision.collisionRect.x + collision.collisionRect.w - 1)) / ts,
            static_cast<int>(std::ceil(collision.collisionRect.y + collision.collisionRect.h)) / ts};

        std::vector<strb::vec2i> tileCollisions;
        if(physics.velocity.y < 0) {
            collision.collidingDown = false;
            // get all tiles above us
            for(int x = topLeftTile.x; x <= bottomRightTile.x; ++x) {
                Tile t = level.getTileAt(x, topLeftTile.y);
                if(t.type == TileType::SOLID) {
                    tileCollisions.push_back({x, topLeftTile.y});
                }
            }

            if(tileCollisions.size()) {
                // we have a hit!
                strb::vec2i tilePos = *tileCollisions.begin();
                transform.position.y = tilePos.y * ts + ts - collision.collisionRectOffset.y;
                collision.collisionRect.y = transform.position.y + collision.collisionRectOffset.y;
                physics.velocity.y = 0;
                collision.collidingUp = true;
            }
            else {
                collision.collidingUp = false;
            }
        }
        else if(physics.velocity.y > 0) {
            collision.collidingUp = false;
            // get all tiles below us
            for(int x = topLeftTile.x; x <= bottomRightTile.x; ++x) {
                Tile t = level.getTileAt(x, bottomRightTile.y);
                if(t.type == TileType::SOLID) {
                    tileCollisions.push_back({x, bottomRightTile.y});
                }
            }

            if(tileCollisions.size()) {
                // we have a hit!
                strb::vec2i tilePos = *tileCollisions.begin();
                transform.position.y = tilePos.y * ts - collision.collisionRect.h - collision.collisionRectOffset.y;
                collision.collisionRect.y = transform.position.y + collision.collisionRectOffset.y;
                physics.velocity.y = 0;
                collision.collidingDown = true;
                physics.touchingGround = true;
            }
            else {
                collision.collidingDown = false;
                physics.touchingGround = false;
            }
        }
    }
}