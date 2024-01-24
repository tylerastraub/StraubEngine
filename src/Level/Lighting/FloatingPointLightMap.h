#pragma once

#include "vec2.h"

#include <list>
#include <vector>
#include <cstdint>
#include <entt/entity/registry.hpp>

#include "Hue.h"
#include "Light.h"

/**
 * @brief 2D lightmap used for creating static lighting map.
 * Lighting is calculated using a floating point position.
 */
class FloatingPointLightMap {
public:
    struct LightMapNode {
        int brightness = 0;
        Hue hue = {0xFF, 0xFF, 0xFF};
        std::list<Light> lightSources;
    };

    FloatingPointLightMap() = default;
    ~FloatingPointLightMap() = default;

    void allocate(int width, int depth);

    uint16_t addLightSource(Light light);
    std::_List_iterator<Light> removeLightSource(uint16_t lightId);

    void cleanUpLightSources(entt::registry& ecs);

    Hue calculateEntityHue(strb::vec2f pos);

    Hue getHue(strb::vec2f pos);
    int getBrightness(strb::vec2f pos);

    bool hasLight(uint16_t lightId);

private:
    bool isLightInBounds(strb::vec2f pos);
    void updateLightMap(Light light);
    void addLightToLightMap(Light light);
    void updateHueInLightMap(strb::vec2f pos);

    uint16_t _currentLightId = 0;

    std::list<Light> _lightSources;
    std::vector<std::vector<LightMapNode>> _lightMap;

    int _lightMapWidth = 0;
    int _lightMapDepth = 0;
};