#pragma once

#include <string>

struct LevelLoadTriggerComponent {
    std::string levelPath = "";
    int playerSpawnID = -1;
};