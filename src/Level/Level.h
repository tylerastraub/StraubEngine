#ifndef LEVEL_H
#define LEVEL_H

#include "CollisionMap.h"
#include "RenderPlane.h"

#include <memory>
#include <map>

class Level {
public:
    Level() = default;
    ~Level() = default;

    // Set tile size in pixels. Should be square
    void setTileSize(int size);
    void setCollisionMap(std::shared_ptr<CollisionMap> cMap);
    void addRenderPlane(Plane::Plane layerIndex, std::shared_ptr<RenderPlane> plane);

    int getTileSize();

private:
    int _tileSize = 0;
    std::shared_ptr<CollisionMap> _cMap = nullptr;
    std::map<Plane::Plane, std::shared_ptr<RenderPlane>> _renderPlanes;

};

#endif