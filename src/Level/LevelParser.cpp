#include "LevelParser.h"
#include "FileIO.h"
#include "SpritesheetRegistry.h"
#include "vec2.h"
// Prefabs
#include "DialogueTrigger.h"
#include "PrefabSpawnTrigger.h"

#include <algorithm>
#include <iostream>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <entt/entity/registry.hpp>

Level LevelParser::parseLevelFromTmx(entt::registry& ecs, std::string filePath, SpritesheetID spritesheetId) {
    Level level;
    level.setTileset(SpritesheetRegistry::getSpritesheet(spritesheetId));

    tmx::Map map;
    if(map.load(SDL_GetBasePath() + filePath)) {
        level.setTileSize(map.getTileSize().x);
        level.allocateTilemap(map.getTileCount().x, map.getTileCount().y);
        const auto& layers = map.getLayers();

        // Tilesets
        strb::vec2i tilesetSize;
        std::vector<tmx::Property> tileProperties;
        const auto& tilesets = map.getTilesets();
        for(const auto& tileset : tilesets) {
            //read out tile set properties, load textures etc...
            tilesetSize.x = tileset.getImageSize().x;
            tilesetSize.y = tileset.getImageSize().y;
        }

        // Custom map properties
        for(auto prop : map.getProperties()) {
            // if(prop.getName() == "propName" && prop.getType() == tmx::Property::Type::String) {
            //     level.setProperty(prop.getStringValue());
            // }
        }

        // Map layers
        for(const auto& layer : layers) {
            // Object layer
            if(layer->getType() == tmx::Layer::Type::Object) {
                const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
                const auto& objects = objectLayer.getObjects();
                if(layer->getName() == "objects") {
                    for(const auto& object : objects) {
                        if(object.getName() == "insert prefab name here") {
                            // create prefab here
                        }
                        // ============================== TRIGGERS ==============================
                        else if(object.getName() == "trigger") {
                            if(object.getClass() == "dialogue") {
                                auto aabb = object.getAABB();
                                int conversationId = -1;
                                bool triggerOnce = true;
                                bool entityMustBeGrounded = false;
                                for(auto prop : object.getProperties()) {
                                    if(prop.getName() == "conversationId" && prop.getType() == tmx::Property::Type::Int) {
                                        conversationId = prop.getIntValue();
                                    }
                                    else if(prop.getName() == "triggerOnce" && prop.getType() == tmx::Property::Type::Boolean) {
                                        triggerOnce = prop.getBoolValue();
                                    }
                                    else if(prop.getName() == "entityMustBeGrounded" && prop.getType() == tmx::Property::Type::Boolean) {
                                        entityMustBeGrounded = prop.getBoolValue();
                                    }
                                }
                                entt::entity trigger = prefab::DialogueTrigger::create(
                                    ecs,
                                    {(int) aabb.left, (int) aabb.top, (int) aabb.width, (int) aabb.height},
                                    triggerOnce,
                                    entityMustBeGrounded,
                                    conversationId
                                );
                            }
                            else if(object.getClass() == "prefabSpawn") {
                                auto aabb = object.getAABB();
                                PrefabType prefabType = PrefabType::NOVAL;
                                strb::vec2f prefabSpawnPos = {0.f, 0.f};
                                std::string prefabValue = "";
                                bool triggerOnce = true;
                                bool entityMustBeGrounded = false;
                                for(auto prop : object.getProperties()) {
                                    if(prop.getName() == "prefabType" && prop.getType() == tmx::Property::Type::String) {
                                        prefabType = convertStringToPrefabType(prop.getStringValue());
                                    }
                                    else if(prop.getName() == "triggerOnce" && prop.getType() == tmx::Property::Type::Boolean) {
                                        triggerOnce = prop.getBoolValue();
                                    }
                                    else if(prop.getName() == "entityMustBeGrounded" && prop.getType() == tmx::Property::Type::Boolean) {
                                        entityMustBeGrounded = prop.getBoolValue();
                                    }
                                    else if(prop.getName() == "prefabSpawnXPos" && prop.getType() == tmx::Property::Type::Float) {
                                        prefabSpawnPos.x = prop.getFloatValue();
                                    }
                                    else if(prop.getName() == "prefabSpawnYPos" && prop.getType() == tmx::Property::Type::Float) {
                                        prefabSpawnPos.y = prop.getFloatValue();
                                    }
                                    else if(prop.getName() == "prefabValue" && prop.getType() == tmx::Property::Type::String) {
                                        prefabValue = prop.getStringValue();
                                    }
                                }
                                entt::entity trigger = prefab::PrefabSpawnTrigger::create(
                                    ecs,
                                    {(int) aabb.left, (int) aabb.top, (int) aabb.width, (int) aabb.height},
                                    triggerOnce,
                                    entityMustBeGrounded,
                                    prefabType,
                                    prefabSpawnPos,
                                    prefabValue
                                );
                            }
                        }
                    }
                }
                // ============================== COLLISION MAP ==============================
                else if(layer->getName() == "collisionmap") {
                    for(const auto& object : objects) {
                        int xPos = object.getPosition().x / level.getTileSize();
                        int yPos = object.getPosition().y / level.getTileSize();
                        Tile tile = level.getTileAt(xPos, yPos);
                        if(object.getClass() == "solid") {
                            tile.type = TileType::SOLID;
                        }
                        else if(object.getClass() == "hazard") {
                            tile.type = TileType::HAZARD;
                        }
                        else if(object.getClass() == "platform") {
                            tile.type = TileType::PLATFORM;
                        }
                        level.setTileAt(xPos, yPos, tile);
                    }
                }
            }
            // ============================== TILE LAYERS ==============================
            else if(layer->getType() == tmx::Layer::Type::Tile) {
                const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
                auto& tiles = tileLayer.getTiles();
                for(size_t y = 0; y < map.getTileCount().y; ++y) {
                    for(size_t x = 0; x < map.getTileCount().x; ++x) {
                        int tileIndex = x + y * map.getTileCount().x;
                        auto id = tiles[tileIndex].ID;
                        // a tile ID of 0 = empty tile. as a result, all tile ID's are incremented by 1
                        // so we need to account for that. but first, check for empty tile:
                        if(id == 0) continue;
                        --id;
                        Tile tile = level.getTileAt(x, y);
                        auto xIndex = id % (int) (tilesetSize.x / level.getTileSize());
                        auto yIndex = id / (int) (tilesetSize.x / level.getTileSize());
                        tile.spritesheetRect = {
                            (int) xIndex,
                            (int) yIndex,
                            level.getTileSize(),
                            level.getTileSize()
                        };
                        level.setTileAt(x, y, tile);
                    }
                }
            }
        }
    }
    else {
        std::cout << "Error: failed to load level '" << filePath << "'!" << std::endl;
    }

    return level;
}

PrefabType LevelParser::convertStringToPrefabType(std::string prefabTypeString) {
    PrefabType result = PrefabType::NOVAL;
    if(prefabTypeString == "ITEM") {
        result = PrefabType::ITEM;
    }
    else if(prefabTypeString == "PROJECTILE") {
        result = PrefabType::PROJECTILE;
    }

    return result;
}