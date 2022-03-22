#include "Level.h"

#include <iostream>

void Level::setTileSize(int size) {
    _tileSize = size;
}

void Level::setCollisionMap(std::shared_ptr<CollisionMap> cMap) {
    _cMap = cMap;
}

void Level::addRenderPlane(Plane::Plane layerIndex, std::shared_ptr<RenderPlane> plane) {
    if(_renderPlanes[layerIndex] != nullptr) 
        std::cout << "Note: overwriting plane at layer index " << layerIndex << "!" << std::endl;

    _renderPlanes[layerIndex] = plane;
}

int Level::getTileSize() {
    return _tileSize;
}