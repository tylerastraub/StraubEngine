#pragma once

#include "Spritesheet.h"
#include "SpritesheetID.h"

#include <unordered_map>
#include <memory>

// Singleton instance used to call ECS
class SpritesheetRegistry {
public:
    static bool addSpritesheet(SDL_Renderer* renderer, SpritesheetID spritesheetId, std::string filePath, int tileWidth = 16, int tileHeight = 16) {
        std::shared_ptr<Spritesheet> spritesheet = std::make_shared<Spritesheet>();
        if(!spritesheet->load(renderer, filePath)) {
            std::cout << "Error: Failed to load " << filePath << std::endl;
            return false;
        }
        spritesheet->setTileWidth(tileWidth);
        spritesheet->setTileHeight(tileHeight);
        _spritesheets[spritesheetId] = spritesheet;
        return true;
    }

    static Spritesheet* getSpritesheet(SpritesheetID spritesheetId) {
        return _spritesheets[spritesheetId].get();
    }

    static std::unordered_map<SpritesheetID, std::shared_ptr<Spritesheet>> getInstance() {
        return _spritesheets;
    }

private:
    SpritesheetRegistry() = default;

    static inline std::unordered_map<SpritesheetID, std::shared_ptr<Spritesheet>> _spritesheets;

};