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
            std::shared_ptr<RenderPlane> plane = std::make_shared<RenderPlane>((Plane::Plane) layer.getId());
            std::shared_ptr<Tilemap> tmap = std::make_shared<Tilemap>();
            for(auto &[pos, tileObject] : layer.getTileObjects()) {
                tileset = tileObject.getTile()->getTileset();
                tson::Rect tsonRect = tileObject.getDrawingRect();
                SDL_Rect rect = {tsonRect.x / tsonRect.width, tsonRect.y / tsonRect.height, tsonRect.width, tsonRect.height};
                tmap->setTile(tileObject.getPositionInTileUnits().x, tileObject.getPositionInTileUnits().y, rect);
            }
            plane->setTilemap(tmap);
            level.addRenderPlane(plane->getLayerIndex(), plane);
        }
    }

    return level;
}