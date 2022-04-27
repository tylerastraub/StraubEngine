#include "Level.h"

#include <iostream>

void Level::render(int xOffset, int yOffset) {
    _renderPlanes[Plane::FOCALGROUND]->render(xOffset, yOffset);
}

void Level::setTileset(Spritesheet* spritesheet) {
    for(auto plane : _renderPlanes) {
        plane.second->setTileset(spritesheet);
    }
}

void Level::setGameSize(int w, int h) {
    for(auto plane : _renderPlanes) {
        plane.second->setGameSize(w, h);
    }
}

void Level::setCollisionMap(std::shared_ptr<CollisionMap> cMap) {
    _cMap = cMap;
}

void Level::addRenderPlane(Plane layerIndex, std::shared_ptr<RenderPlane> plane) {
    if(_renderPlanes[layerIndex] != nullptr) 
        std::cout << "Note: overwriting plane at layer index " << (int) layerIndex << "!" << std::endl;

    _renderPlanes[layerIndex] = plane;
}

Tilemap* Level::getTilemap() {
    return _renderPlanes[Plane::FOCALGROUND]->getTilemap();
}