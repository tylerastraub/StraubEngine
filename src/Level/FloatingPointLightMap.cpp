#include "FloatingPointLightMap.h"

#include <queue>
#include <algorithm>
#include <cmath>

void FloatingPointLightMap::allocate(int width, int depth) {
    _lightMapWidth = width;
    _lightMapDepth = depth;
    for(int y = 0; y < depth; ++y) {
        std::vector<std::pair<int, Hue>> row;
        for(int x = 0; x < width; ++x) {
            row.push_back({0, Hue()});
        }
        _lightMap.push_back(row);
    }
}

/**
 * @brief Adds a light source to the LightMap
 * 
 * @param pos Position of the light
 * @param brightness Brightness of the light, where 0 is pitch black and 1 is full brightness
 * @param falloff How fast the light fades out. A brightness of 0.2 means each subsequent tile is 20% dimmer
 * @return uint16_t The light ID (used to remove the light, which is necessary for dynamic/moving lights)
 */
uint16_t FloatingPointLightMap::addLightSource(strb::vec2f pos, float brightness, Hue hue, float falloff) {
    Light light;
    light.id = _currentLightId;
    ++_currentLightId;
    light.pos = pos;
    light.brightness = brightness;
    light.falloff = falloff;
    light.hue = hue;
    _lightSources.push_back(light);
    updateLightMap(light);

    return light.id;
}

void FloatingPointLightMap::removeLightSource(uint16_t lightId) {
    for(auto it = _lightSources.begin(); it != _lightSources.end(); ++it) {
        if(it->id == lightId) {
            // Update lightmap by removing light's brightness from lightmap...
            Light light = *it;
            light.brightness *= -1;
            light.falloff *= -1;
            updateLightMap(light);
            // ...then remove the light from the lightSources list
            _lightSources.erase(it);
            return;
        }
    }
    std::cout << "Error: attempting to remove nonexistent light source. ID: " << lightId << std::endl;
}

Hue FloatingPointLightMap::getHue(strb::vec2f pos) {
    // bounds check
    if(!isLightInBounds(pos)) return Hue();
    std::pair<int, Hue> hue = _lightMap[pos.y][pos.x];
    if(hue.first < 0) return Hue();
    else if(hue.first > 255) return Hue();
    hue.second.red *= ((float) hue.first / 255.f);
    hue.second.blue *= ((float) hue.first / 255.f);
    hue.second.green *= ((float) hue.first / 255.f);
    return hue.second;
}

int FloatingPointLightMap::getBrightness(strb::vec2f pos) {
    // bounds check
    if(!isLightInBounds(pos)) return 0;
    std::pair<int, Hue> light = _lightMap[pos.y][pos.x];
    if(light.first < 0) return 0;
    else if(light.first > 255) return 255;
    return light.first;
}

bool FloatingPointLightMap::isLightInBounds(strb::vec2f pos) {
    if(pos.x < 0 || pos.x >= _lightMapWidth || pos.y < 0 || pos.y >= _lightMapDepth) {
        return false;
    }
    return true;
}

// iterations are inconsistent - sometimes barely moving (but staying in the same tile) will have a different lightmap result
void FloatingPointLightMap::updateLightMap(Light light) {
    strb::vec2i neighbors[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    // calculate directional light falloff so that moving lights appear smoother
    strb::vec2f posRemainder = {light.pos.x - std::floor(light.pos.x) - 0.5f, light.pos.y - std::floor(light.pos.y) - 0.5f};
    float directionalFalloff[4] = {
        light.falloff * (1 - posRemainder.x),
        light.falloff * (1 - posRemainder.y),
        light.falloff * (1 + posRemainder.x),
        light.falloff * (1 + posRemainder.y)
    };
    size_t neighborsSize = 4;

    std::queue<Light> lightQueue;
    lightQueue.push(light);
    std::vector<Light> checkedLights;
    Light currentLight;
    int iterations = 0; // debug
    int counter = 0;
    while(!lightQueue.empty()) {
        currentLight = lightQueue.front();
        lightQueue.pop();
        // this should be really done with std::find_if + lambda
        bool alreadyCheckedLight = false;
        for(auto light : checkedLights) {
            if((int) light.pos.x == (int) currentLight.pos.x && (int) light.pos.y == (int) currentLight.pos.y) {
                alreadyCheckedLight = true;
                break;
            }
        }
        if(alreadyCheckedLight) continue;
        ++iterations;
        checkedLights.push_back(currentLight);
        addLightToLightMap(currentLight.pos, currentLight.brightness, currentLight.hue);
        if(std::abs(currentLight.brightness) - std::abs(currentLight.falloff) > 0) {
            for(size_t i = 0; i < neighborsSize; ++i) {
                strb::vec2i neighbor = neighbors[i];
                // use directional falloff for first iteration only
                float falloff = (currentLight.pos == light.pos) ? directionalFalloff[i] : light.falloff;
                if(isLightInBounds(currentLight.pos + neighbor)) {
                    Light nextLight;
                    nextLight.pos = currentLight.pos + neighbor;
                    nextLight.brightness = currentLight.brightness - falloff;
                    nextLight.falloff = falloff;
                    nextLight.hue = currentLight.hue;
                    lightQueue.push(nextLight);
                }
            }
        }
    }
    // std::cout << "LightMap: " << iterations << " iterations ran" << std::endl;
}

void FloatingPointLightMap::addLightToLightMap(strb::vec2f pos, float brightness, Hue hue) {
    // bounds check
    if(!isLightInBounds(pos)) return;
    brightness *= 255;
    if(brightness < 0 && std::abs(brightness) >= _lightMap[pos.y][pos.x].first) {
        _lightMap[pos.y][pos.x].first = 0;
    }
    else {
        _lightMap[pos.y][pos.x].first += brightness;
    }
    _lightMap[pos.y][pos.x].second = hue;
}
