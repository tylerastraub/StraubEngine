#ifndef SPRITESHEET_REGISTRY_H
#define SPRITESHEET_REGISTRY_H

#include "Spritesheet.h"

#include <unordered_map>
#include <memory>

// Singleton instance used to call ECS
class SpritesheetRegistry {
public:
    static void addSpritesheet(std::string spritesheetId, std::shared_ptr<Spritesheet> spritesheet) {
        _spritesheets[spritesheetId] = spritesheet;
    }

    static Spritesheet* getSpritesheet(std::string spritesheetId) {
        return _spritesheets[spritesheetId].get();
    }

    static std::unordered_map<std::string, std::shared_ptr<Spritesheet>> getInstance() {
        return _spritesheets;
    }

private:
    SpritesheetRegistry() = default;

    static inline std::unordered_map<std::string, std::shared_ptr<Spritesheet>> _spritesheets;

};

#endif