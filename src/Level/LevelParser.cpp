#include "LevelParser.h"
#include "CollisionMap.h"
#include "RenderPlane.h"

#include <SDL.h>

Level LevelParser::parseLevel(tson::Map* map) {
    Level level;
    tson::Tileset* tileset = nullptr;

    for(auto layer : map->getLayers()) {
        if(layer.getName() == "COLLISIONMAP") {
            std::shared_ptr<CollisionMap> cMap = std::make_shared<CollisionMap>();
            cMap->allocate(layer.getSize().x, layer.getSize().y);
            for(auto &[pos, tileObject] : layer.getTileObjects()) {
                bool collides = tileObject.getTile()->getType() == "solid" ? true : false;
                cMap->setCollisionMapIndex(tileObject.getPosition().x, tileObject.getPosition().y, collides);
            }
            level.setCollisionMap(cMap);
        }
        else {
            std::shared_ptr<RenderPlane> plane = std::make_shared<RenderPlane>(getLayerPlane(layer.getName()));
            std::shared_ptr<Tilemap> tilemap = std::make_shared<Tilemap>();
            tilemap->allocate(layer.getSize().x, layer.getSize().y);
            int tileSize = -1;
            for(auto &[pos, tileObject] : layer.getTileObjects()) {
                tileset = tileObject.getTile()->getTileset();
                if(tileSize == -1) tileSize = tileset->getTileSize().x;
                tson::Rect tsonRect = tileObject.getDrawingRect();
                TileType type = getTileType(tileObject.getTile()->getType());
                SDL_Rect rect = {tsonRect.x / tsonRect.width, tsonRect.y / tsonRect.height, tsonRect.width, tsonRect.height};
                tilemap->setTile(tileObject.getPositionInTileUnits().x, tileObject.getPositionInTileUnits().y, {type, rect});
            }
            tilemap->setTileSize(tileSize);
            plane->setTilemap(tilemap);
            level.addRenderPlane(plane->getLayerIndex(), plane);
        }
    }

    return level;
}

Plane LevelParser::getLayerPlane(std::string layerName) {
    if(layerName == "foreground") {
        return Plane::FOREGROUND;
    }
    else if(layerName == "focalground") {
        return Plane::FOCALGROUND;
    }
    else if(layerName == "background1") {
        return Plane::BACKGROUND_1;
    }
    else if(layerName == "background2") {
        return Plane::BACKGROUND_2;
    }
    else if(layerName == "background3") {
        return Plane::BACKGROUND_3;
    }
    
    return Plane::NOVAL;
}

TileType LevelParser::getTileType(std::string type) {
    if(type == "ground") {
        return TileType::GROUND;
    }
    else if(type == "wall") {
        return TileType::WALL;
    }
    
    return TileType::NOVAL;
 }