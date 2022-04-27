#include "SpritesheetPropertiesComponent.h"

void SpritesheetPropertiesComponent::addSpritesheetProperties(EntityState state, Direction direction, SpritesheetProperties properties) {
    std::string key = std::to_string((int) state) + "-" + std::to_string((int) direction);
    _propertiesMap[key] = properties;
}

void SpritesheetPropertiesComponent::setPrimarySpritesheetProperties(SpritesheetProperties properties) {
    _primarySpritesheetProperties = properties;
}

SpritesheetProperties SpritesheetPropertiesComponent::getSpritesheetProperties(EntityState state, Direction direction) {
    std::string key = std::to_string((int) state) + "-" + std::to_string((int) direction);
    return _propertiesMap[key];
}

SpritesheetProperties SpritesheetPropertiesComponent::getPrimarySpritesheetProperties() {
    return _primarySpritesheetProperties;
}