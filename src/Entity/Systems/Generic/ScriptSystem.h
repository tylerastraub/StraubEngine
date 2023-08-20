#pragma once

#include "System.h"

class ScriptSystem : public System {
public:
    ScriptSystem() = default;
    ~ScriptSystem() = default;

    void update(float timescale);

private:

};