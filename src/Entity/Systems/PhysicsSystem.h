#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "System.h"
#include "Level.h"

class PhysicsSystem : public System {
public:
    PhysicsSystem() = default;
    ~PhysicsSystem() = default;

    bool updateX(float timescale);
    bool updateY(float timescale);

    void setLevel(Level level);

private:
    void moveToZero(float &value, float amount);

    Level _level;

};

#endif