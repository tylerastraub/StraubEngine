#pragma once

#include "vec2.h"

#include <list>
#include <vector>
#include <cstdint>

/**
 * Common hue colors:
 * - Soft warm: {0xfe, 0xd8, 0x92}
 * - Bright warm: {0xff, 0xf5, 0x91}
 * - Cool: {0x9f, 0xed, 0xd7}
 * - Neutral, slightly dull: {0xe7, 0xdf, 0xc0}
 */
struct Hue {
    uint8_t red = 0xFF;
    uint8_t green = 0xFF;
    uint8_t blue = 0xFF;
};

struct Light {
    uint16_t id;
    // The light's tile position
    strb::vec2f pos = {0.f, 0.f};
    // The light's brightness from a scale of 0-1
    float brightness = 0.f;
    // The rate at which the light falls off the further it gets from the source (from 0-1). Default is 0.2
    float falloff = 0.2f;
    
    Hue hue;
};

/**
 * @brief 2D lightmap used for creating static lighting map.
 * Lighting is calculated using a integer position.
 */
class LightMap {
public:
    LightMap() = default;
    ~LightMap() = default;

    void allocate(int width, int depth);

    uint16_t addLightSource(strb::vec2f pos, float brightness, Hue hue, float falloff = 0.2f);
    void removeLightSource(uint16_t lightId);

    Hue getBrightness(strb::vec2f pos);

private:
    bool isLightInBounds(strb::vec2f pos);
    void updateLightMap(Light light);
    void addLightToLightMap(strb::vec2f pos, float brightness, Hue hue);

    uint16_t _currentLightId = 0;

    std::list<Light> _lightSources;
    std::vector<std::vector<std::pair<int, Hue>>> _lightMap;

    int _lightMapWidth = 0;
    int _lightMapDepth = 0;
};