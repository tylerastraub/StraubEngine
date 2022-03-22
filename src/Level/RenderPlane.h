#ifndef RENDER_PLANE_H
#define RENDER_PLANE_H

#include "Tilemap.h"

#include <memory>

namespace Plane {
    enum Plane {
        NOVAL = -1,
        // Plane in front of the main plane. Should only be used for render planes that are supposed to block the focal grouhnd
        FOREGROUND = 0,
        FOCALGROUND = 1,
        BACKGROUND_1 = 2,
        BACKGROUND_2 = 3,
        BACKGROUND_3 = 4,
    };
};

class RenderPlane {
public:
    RenderPlane(Plane::Plane layerIndex);
    ~RenderPlane() = default;

    void setTilemap(std::shared_ptr<Tilemap> tilemap);
    void setParallaxScale(float scale);

    Plane::Plane getLayerIndex();

private:
    Plane::Plane _layerIndex = Plane::NOVAL;
    std::shared_ptr<Tilemap> _tilemap;
    float _parallaxScale = 1.f;
};

#endif