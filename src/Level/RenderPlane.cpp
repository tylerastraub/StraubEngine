#include "RenderPlane.h"

RenderPlane::RenderPlane(Plane layerIndex) : _layerIndex(layerIndex) {}

void RenderPlane::render(int xOffset, int yOffset) {
    _tilemap->render(xOffset / _parallaxScale, yOffset / _parallaxScale);
}

void RenderPlane::setTileset(Spritesheet* spritesheet) {
    _tilemap->setTileset(spritesheet);
}

void RenderPlane::setGameSize(int w, int h) {
    _tilemap->setGameSize(w, h);
}

void RenderPlane::setTilemap(std::shared_ptr<Tilemap> tilemap) {
    _tilemap = tilemap;
}

void RenderPlane::setParallaxScale(float scale) {
    _parallaxScale = scale;
}

Plane RenderPlane::getLayerIndex() {
    return _layerIndex;
}

Tilemap* RenderPlane::getTilemap() {
    return _tilemap.get();
}