#include "LightMap.h"

#include <queue>
#include <algorithm>
#include <cmath>

void LightMap::allocate(int width, int depth) {
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
uint16_t LightMap::addLightSource(strb::vec2f pos, float brightness, Hue hue, float falloff) {
    Light light;
    light.id = _currentLightId;
    ++_currentLightId;
    light.pos = {std::floor(pos.x), std::floor(pos.y)};
    light.brightness = brightness;
    light.falloff = falloff;
    light.hue = hue;
    _lightSources.push_back(light);
    updateLightMap(light);

    return light.id;
}

void LightMap::removeLightSource(uint16_t lightId) {
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
}

Hue LightMap::getBrightness(strb::vec2f pos) {
    // bounds check
    if(!isLightInBounds(pos)) return Hue();
    std::pair<int, Hue> hue = _lightMap[pos.y][pos.x];
    if(hue.first < 0) return Hue();
    else if(hue.first > 255) return Hue();
    hue.second.red *= ((float) hue.first / (float) 255);
    hue.second.blue *= ((float) hue.first / (float) 255);
    hue.second.green *= ((float) hue.first / (float) 255);
    return hue.second;
}

bool LightMap::isLightInBounds(strb::vec2f pos) {
    if(pos.x < 0 || pos.x >= _lightMapWidth || pos.y < 0 || pos.y >= _lightMapDepth) {
        return false;
    }
    return true;
}

void LightMap::updateLightMap(Light light) {

    strb::vec2i neighbors[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    float falloff = light.falloff;

    std::queue<Light> lightQueue;
    lightQueue.push(light);
    std::vector<Light> checkedLights;
    Light currentLight;
    int iterations = 0; // debug
    while(!lightQueue.empty()) {
        currentLight = lightQueue.front();
        lightQueue.pop();
        // this should be really done with std::find_if + lambda
        bool alreadyCheckedLight = false;
        for(auto light : checkedLights) {
            if(light.pos == currentLight.pos) {
                alreadyCheckedLight = true;
                break;
            }
        }
        if(alreadyCheckedLight) continue;
        ++iterations;
        checkedLights.push_back(currentLight);
        addLightToLightMap(currentLight.pos, currentLight.brightness, currentLight.hue);
        if(std::abs(currentLight.brightness) - std::abs(falloff) > 0) {
            for(auto neighbor : neighbors) {
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

void LightMap::addLightToLightMap(strb::vec2f pos, float brightness, Hue hue) {
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