#pragma once

#include "SpritesheetProperties.h"
#include "StateComponent.h"
#include "DirectionComponent.h"
#include "Spritesheet.h"

#include <unordered_map>

class SpritesheetPropertiesComponent {
public:
    SpritesheetPropertiesComponent() = default;
    ~SpritesheetPropertiesComponent() = default;

    void addSpritesheetProperties(EntityState state, Direction direction, SpritesheetProperties properties);
    void setPrimarySpritesheetProperties(SpritesheetProperties properties);

    SpritesheetProperties getSpritesheetProperties(EntityState state, Direction direction);
    SpritesheetProperties getPrimarySpritesheetProperties();
    
    Spritesheet* spritesheet = nullptr;

private:
    std::unordered_map<std::string, SpritesheetProperties> _propertiesMap;
    SpritesheetProperties _primarySpritesheetProperties;
};