#include "FloatingPointLightMap.h"

#include <queue>
#include <algorithm>
#include <cmath>

void FloatingPointLightMap::allocate(int width, int depth) {
    _lightMapWidth = width;
    _lightMapDepth = depth;
    for(int y = 0; y < depth; ++y) {
        std::vector<LightMapNode> row;
        for(int x = 0; x < width; ++x) {
            row.push_back(LightMapNode{});
        }
        _lightMap.push_back(row);
    }
}

uint16_t FloatingPointLightMap::addLightSource(Light light) {
    light.id = _currentLightId;
    ++_currentLightId;
    if(_currentLightId == SDL_MAX_UINT16) _currentLightId = 0;
    _lightSources.push_back(light);
    updateLightMap(light);

    return light.id;
}

std::list<Light>::iterator FloatingPointLightMap::removeLightSource(uint16_t lightId) {
    for(auto it = _lightSources.begin(); it != _lightSources.end(); ++it) {
        if(it->id == lightId) {
            // Update lightmap by removing light's brightness from lightmap...
            Light light = *it;
            light.brightness *= -1;
            light.falloff *= -1;
            updateLightMap(light);
            // ...then remove the light from the lightSources list
            return _lightSources.erase(it);
        }
    }
    std::cout << "Error: attempting to remove nonexistent light source. ID: " << lightId << std::endl;
    return _lightSources.end();
}

void FloatingPointLightMap::cleanUpLightSources(entt::registry& ecs) {
    for(auto it = _lightSources.begin(); it != _lightSources.end(); ++it) {
        auto light = *it;
        if(light.owner != entt::null) {
            if(!ecs.valid(light.owner)) {
                it = removeLightSource(light.id);
                --it;
            }
        }
    }
}

Hue FloatingPointLightMap::calculateEntityHue(strb::vec2f pos) {
    if(!isLightInBounds(pos)) return {0x00, 0x00, 0x00};
    int red = 0;
    int green = 0;
    int blue = 0;
    for(auto light : _lightSources) {
        float maxDistance = 1.f / light.falloff;
        float distance = std::hypot(light.pos.x - pos.x, light.pos.y - pos.y);
        if(distance >= maxDistance) continue;
        float lightStrength = (maxDistance - distance) / maxDistance;
        red += light.hue.red * lightStrength * light.brightness;
        green += light.hue.green * lightStrength * light.brightness;
        blue += light.hue.blue * lightStrength * light.brightness;
    }
    if(red > 255) red = 255;
    if(green > 255) green = 255;
    if(blue > 255) blue = 255;

    return Hue{static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue)};
}

Hue FloatingPointLightMap::getHue(strb::vec2f pos) {
    // bounds check
    if(!isLightInBounds(pos)) return Hue();
    int brightness = getBrightness(pos);
    Hue hue = _lightMap[pos.y][pos.x].hue;
    if(brightness < 0) return Hue();
    else if(brightness > 255.f) brightness = 255.f;
    hue.red *= ((float) brightness / 255.f);
    hue.blue *= ((float) brightness / 255.f);
    hue.green *= ((float) brightness / 255.f);
    return hue;
}

int FloatingPointLightMap::getBrightness(strb::vec2f pos) {
    // bounds check
    if(!isLightInBounds(pos)) return 0;
    LightMapNode light = _lightMap[pos.y][pos.x];
    if(light.brightness < 0) return 0;
    else if(light.brightness > 255) return 255;
    return light.brightness;
}

bool FloatingPointLightMap::hasLight(uint16_t lightId) {
    for(auto light : _lightSources) {
        if(light.id == lightId) return true;
    }
    return false;
}

bool FloatingPointLightMap::isLightInBounds(strb::vec2f pos) {
    if(pos.x < 0 || pos.x >= _lightMapWidth || pos.y < 0 || pos.y >= _lightMapDepth) {
        return false;
    }
    return true;
}

void FloatingPointLightMap::updateLightMap(Light light) {
    strb::vec2f neighbors[8] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    // calculate directional light falloff so that moving lights appear smoother
    strb::vec2f posRemainder = {light.pos.x - std::floor(light.pos.x) - 0.5f, light.pos.y - std::floor(light.pos.y) - 0.5f};
    float directionalFalloff[8] = {
        light.falloff * (1 - posRemainder.x), // {1, 0}
        light.falloff * (1 - posRemainder.y), // {0, 1}
        light.falloff * (1 + posRemainder.x), // {-1, 0}
        light.falloff * (1 + posRemainder.y), // {0, -1}
        light.falloff * (std::hypot(1 - posRemainder.x, 1 - posRemainder.y)), // {1, 1}
        light.falloff * (std::hypot(1 - posRemainder.x, 1 + posRemainder.y)), // {1, -1}
        light.falloff * (std::hypot(1 + posRemainder.x, 1 - posRemainder.y)), // {-1, 1}
        light.falloff * (std::hypot(1 + posRemainder.x, 1 + posRemainder.y))  // {-1, -1}
    };
    size_t neighborsSize = 8;

    std::queue<Light> lightQueue;
    lightQueue.push(light);
    std::vector<Light> checkedLights;
    Light currentLight;
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
        checkedLights.push_back(currentLight);
        addLightToLightMap(currentLight);
        if(std::abs(currentLight.brightness) - std::abs(currentLight.falloff) > 0) {
            for(size_t i = 0; i < neighborsSize; ++i) {
                strb::vec2f neighbor = neighbors[i];
                // use directional falloff for first iteration only
                float falloff = (currentLight.pos == light.pos) ? directionalFalloff[i] : light.falloff;
                if(isLightInBounds(currentLight.pos + neighbor)) {
                    Light nextLight;
                    nextLight.pos = currentLight.pos + neighbor;
                    nextLight.brightness = currentLight.brightness - falloff;
                    nextLight.falloff = falloff;
                    nextLight.hue = currentLight.hue;
                    nextLight.id = currentLight.id;
                    lightQueue.push(nextLight);
                }
            }
        }
    }
}

void FloatingPointLightMap::addLightToLightMap(Light light) {
    // bounds check
    if(!isLightInBounds(light.pos)) return;
    auto& sources = _lightMap[light.pos.y][light.pos.x].lightSources;
    if(light.brightness < 0.f) {
        for(auto it = sources.begin(); it != sources.end(); ++it) {
            if(it->id == light.id) {
                sources.erase(it);
                break;
            }
        }
    }
    else {
        bool hasLight = false;
        for(auto it = sources.begin(); it != sources.end(); ++it) {
            if(it->id == light.id) {
                hasLight = true;
                break;
            }
        }
        if(!hasLight) sources.push_back(light);
    }
    light.brightness = std::round(light.brightness * 255.f);
    if(light.brightness < 0.f && std::abs(light.brightness) >= _lightMap[light.pos.y][light.pos.x].brightness) {
        _lightMap[light.pos.y][light.pos.x].brightness = 0;
    }
    else {
        _lightMap[light.pos.y][light.pos.x].brightness += light.brightness;
    }
    updateHueInLightMap(light.pos);
}

// todo: change this to take Light as parameter, check for light ID, and remove
// old/add new light to node's sources instead of recalculating entirely
void FloatingPointLightMap::updateHueInLightMap(strb::vec2f pos) {
    LightMapNode& node = _lightMap[pos.y][pos.x];
    float red = 0;
    float green = 0;
    float blue = 0;
    float totalBrightness = 0.f;
    for(auto light : node.lightSources) {
        if(light.id == SDL_MAX_UINT16) continue;
        totalBrightness += light.brightness;
    }
    for(auto light : node.lightSources) {
        float weight = light.brightness / totalBrightness;
        red += light.hue.red * weight;
        green += light.hue.green * weight;
        blue += light.hue.blue * weight;
    }
    float max = (red > green) ? red : green;
    if(blue > max) max = blue;
    red = red / max * 255.f;
    green = green / max * 255.f;
    blue = blue / max * 255.f;
    node.hue = {
        static_cast<uint8_t>(red),
        static_cast<uint8_t>(green),
        static_cast<uint8_t>(blue)
    };
}