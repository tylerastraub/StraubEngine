#pragma once

#include "PrefabType.h"
#include "vec2.h"

#include <string>

struct PrefabSpawnTriggerComponent {
    PrefabType prefabType = PrefabType::NOVAL;
    strb::vec2f prefabSpawnPos = {0.f, 0.f};
    std::string prefabValue = "";
};