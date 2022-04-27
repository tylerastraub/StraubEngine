#ifndef RENDER_PLANE_H
#define RENDER_PLANE_H

#include "Tilemap.h"

#include <memory>

enum class Plane {
    NOVAL = -1,
    FOREGROUND = 0, // Plane in front of the main plane. Should only be used for render planes that are supposed to block the focal ground
    FOCALGROUND = 1, // The main ground. Directly behind the player
    BACKGROUND_1 = 2, // Foremost background layer
    BACKGROUND_2 = 3, // Second foremost background layer
    BACKGROUND_3 = 4, // Deepest background layer
};

class RenderPlane {
public:
    RenderPlane(Plane layerIndex);
    ~RenderPlane() = default;

    void render(int xOffset, int yOffset);

    void setTileset(Spritesheet* spritesheet);
    void setGameSize(int w, int h);
    void setTilemap(std::shared_ptr<Tilemap> tilemap);
    void setParallaxScale(float scale);

    Plane getLayerIndex();
    Tilemap* getTilemap();

private:
    Plane _layerIndex = Plane::NOVAL;
    std::shared_ptr<Tilemap> _tilemap;
    float _parallaxScale = 1.f;
};

#endif