// #include "LevelParser.h"
// #include "CollisionMap.h"
// #include "RenderPlane.h"
// #include "EntityRegistry.h"

// #include <SDL.h>

// Level LevelParser::parseLevel(tson::Map* map) {
//     Level level;
//     tson::Tileset* tileset = nullptr;

//     for(auto layer : map->getLayers()) {
//         int tileSize = -1;
//         if(layer.getName() == "collisionmap") {
//             if(map->getLayer("focalground") == nullptr) continue;
//             std::shared_ptr<CollisionMap> cMap = std::make_shared<CollisionMap>();
//             // object layers don't have actual sizes so we gotta do this
//             cMap->allocate(map->getLayer("focalground")->getSize().x, map->getLayer("focalground")->getSize().y);
//             tileSize = map->getTilesets()[0].getTileSize().x;
//             for(auto object : layer.getObjects()) {
//                 bool collides = object.getType() == "solid" ? true : false;
//                 cMap->setCollisionMapIndex(object.getPosition().x / tileSize, object.getPosition().y / tileSize, collides);
//             }
//             level.setCollisionMap(cMap);
//         }
//         else if(layer.getName() == "objectmap") {
//             if(map->getLayer("focalground") == nullptr) continue;
//             for(auto object : layer.getObjects()) {
//                 // parse tiled objects here
//             }
//         }
//         else {
//             std::shared_ptr<RenderPlane> plane = std::make_shared<RenderPlane>(getLayerPlane(layer.getName()));
//             std::shared_ptr<Tilemap> tilemap = std::make_shared<Tilemap>();
//             tilemap->allocate(layer.getSize().x, layer.getSize().y);
//             for(auto &[pos, tileObject] : layer.getTileObjects()) {
//                 tileset = tileObject.getTile()->getTileset();
//                 if(tileSize == -1) tileSize = tileset->getTileSize().x;
//                 tson::Rect tsonRect = tileObject.getDrawingRect();
//                 TileType type = getTileType(tileObject.getTile()->getType());
//                 SDL_Rect rect = {tsonRect.x / tsonRect.width, tsonRect.y / tsonRect.height, tsonRect.width, tsonRect.height};
//                 tilemap->setTile(tileObject.getPositionInTileUnits().x, tileObject.getPositionInTileUnits().y, {type, rect});
//             }
//             tilemap->setTileSize(tileSize);
//             plane->setTilemap(tilemap);
//             level.addRenderPlane(plane->getLayerIndex(), plane);
//         }
//     }

//     return level;
// }

// Plane LevelParser::getLayerPlane(std::string layerName) {
//     if(layerName == "foreground") {
//         return Plane::FOREGROUND;
//     }
//     else if(layerName == "focalground") {
//         return Plane::FOCALGROUND;
//     }
//     else if(layerName == "background_shallow") {
//         return Plane::BACKGROUND_SHALLOW;
//     }
//     else if(layerName == "background_deep") {
//         return Plane::BACKGROUND_DEEP;
//     }
//     else if(layerName == "background_deepest") {
//         return Plane::BACKGROUND_DEEPEST;
//     }
    
//     return Plane::NOVAL;
// }

// TileType LevelParser::getTileType(std::string type) {
//     if(type == "solid") {
//         return TileType::SOLID;
//     }
//     else if(type == "platform") {
//         return TileType::PLATFORM;
//     }
    
//     return TileType::NOVAL;
// }