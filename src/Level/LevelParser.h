#pragma once

#include "Tile.h"
#include "Level.h"
#include "SpritesheetID.h"
#include "PrefabType.h"

#include <vector>
#include <string>

class LevelParser {
public:
    LevelParser() = default;
    ~LevelParser() = default;

    static std::vector<std::vector<Tile>> parseLevelFromTxt(std::string filePath);
    static Level parseLevelFromTmx(std::string filePath, SpritesheetID spritesheetId);

private:
    static PrefabType convertStringToPrefabType(std::string prefabTypeString);

};