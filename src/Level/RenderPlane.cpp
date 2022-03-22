#include "RenderPlane.h"

RenderPlane::RenderPlane(Plane::Plane layerIndex) : _layerIndex(layerIndex) {}

void RenderPlane::setTilemap(std::shared_ptr<Tilemap> tilemap) {
    _tilemap = tilemap;
}

void RenderPlane::setParallaxScale(float scale) {
    _parallaxScale = scale;
}

Plane::Plane RenderPlane::getLayerIndex() {
    return _layerIndex;
}