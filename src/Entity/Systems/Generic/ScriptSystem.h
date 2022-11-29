#ifndef SCRIPT_SYSTEM_H
#define SCRIPT_SYSTEM_H

#include "System.h"

class ScriptSystem : public System {
public:
    ScriptSystem() = default;
    ~ScriptSystem() = default;

    void update(float timescale);

private:

};

#endif