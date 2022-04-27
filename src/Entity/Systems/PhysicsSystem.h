#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "System.h"
#include "Level.h"

class PhysicsSystem : public System {
public:
    PhysicsSystem() = default;
    ~PhysicsSystem() = default;

    bool updateSingleEntity(float timescale, Entity entity);
    bool updateAllButEntities(float timescale, std::list<Entity> entities);
    bool update(float timescale);

    void setLevel(Level level);

private:
    Level _level;

};

#endif