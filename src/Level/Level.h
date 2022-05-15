#ifndef LEVEL_H
#define LEVEL_H

#include "CollisionMap.h"
#include "RenderPlane.h"
#include "vec2.h"
#include "DirectionComponent.h"

#include <memory>
#include <unordered_map>

class Level {
public:
    Level() = default;
    ~Level() = default;

    void render(int xOffset, int yOffset);
    void renderBackground(int xOffset, int yOffset);
    
    void setTileset(Spritesheet* spritesheet);
    void setGameSize(int w, int h);
    void setCollisionMap(std::shared_ptr<CollisionMap> cMap);
    void addRenderPlane(Plane layerIndex, std::shared_ptr<RenderPlane> plane);

    // Gets the tilemap for the focalground
    Tilemap* getTilemap();
    CollisionMap* getCollisionMap();
    int getTileSize();

private:
    std::shared_ptr<CollisionMap> _cMap = nullptr;
    std::unordered_map<Plane, std::shared_ptr<RenderPlane>> _renderPlanes;

};

#endif