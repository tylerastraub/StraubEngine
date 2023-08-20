#pragma once

#include <cstdint>

using Entity = std::uint16_t;

/**
 * @brief Interface class for the component array. Required so that when an entity is destroyed, we
 * can destroy its array mappings in a generic ComponentArray. (I don't really get this rn)
 */
class IComponentArray {
public:
    IComponentArray() = default;
    virtual ~IComponentArray() = default;

    virtual void entityDestroyed(Entity entity) = 0;

private:

};