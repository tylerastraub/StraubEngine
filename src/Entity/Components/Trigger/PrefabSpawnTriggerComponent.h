#ifndef PREFAB_SPAWN_TRIGGER_COMPONENT_H
#define PREFAB_SPAWN_TRIGGER_COMPONENT_H

#include "PrefabType.h"
#include "vec2.h"

#include <string>

struct PrefabSpawnTriggerComponent {
    PrefabType prefabType = PrefabType::NOVAL;
    strb::vec2 prefabSpawnPos = {0.f, 0.f};
    std::string prefabValue = "";
};

#endif