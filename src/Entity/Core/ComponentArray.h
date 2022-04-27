#ifndef COMPONENT_ARRAY_H
#define COMPONENT_ARRAY_H

#include "IComponentArray.h"
#include "EntityConstants.h"

#include <list>

/**
 * @brief ComponentArray class to keep track of all entity's components.
 * 
 * @tparam the generic component type
 */
template<typename T>
class ComponentArray : public IComponentArray {
public:
    ComponentArray() {
        for(size_t i = 0; i < entityConstants::MAX_ENTITIES; ++i) {
            _entityToIndexMap[i] = -1;
        }
    }
    ~ComponentArray() = default;

    void entityDestroyed(Entity entity) override {
        if(entity < entityConstants::MAX_ENTITIES) {
            if(_entityToIndexMap[entity] != -1) {
                removeData(entity);
            }
        }
    }

    void insertData(Entity entity, T component) {
        if(entity < entityConstants::MAX_ENTITIES && _entityToIndexMap[entity] == -1) {
            size_t index = _size;
            _entityToIndexMap[entity] = index;
            _componentArray[index] = component;
            _componentEntityPool.push_back(entity);
            ++_size;
        }
    }

    void removeData(Entity entity) {
        if(entity < entityConstants::MAX_ENTITIES) {
            size_t oldIndex = _entityToIndexMap[entity];
            std::swap(_componentArray[entity], _componentArray[_size - 1]);
            _entityToIndexMap[_size - 1] = oldIndex;
            _entityToIndexMap[entity] = -1;
            for(auto it = _componentEntityPool.begin(); it != _componentEntityPool.end(); ++it) {
                if(*it == entity) {
                    _componentEntityPool.erase(it);
                    break;
                }
            }
            --_size;
        }
    }

    T& getData(Entity entity) {
        if(entity < entityConstants::MAX_ENTITIES) {
            int index = _entityToIndexMap[entity];
            if(index != -1) {
                return _componentArray[index];
            }
        }

        return defaultValue();
    }

    const std::list<Entity> getAllOf() {
        return _componentEntityPool;
    }

    bool hasComponent(Entity entity) {
        if(entity < entityConstants::MAX_ENTITIES) return _entityToIndexMap[entity] != -1;
        return false;
    }

private:
    /**
     * @brief Method for creating default value for templated return. Probably not super safe.
     * Taken from https://stackoverflow.com/a/48308107
     * 
     * @return Default T value
     */
    static T& defaultValue() {
        static T* t = new T{};
        return *t;
    }

    /**
     * @brief -1 is considered an 'empty' index
     */
    T _componentArray[entityConstants::MAX_ENTITIES];
    /**
     * @brief Maps entities to their place in the component array to keep it packed.
     */
    int _entityToIndexMap[entityConstants::MAX_ENTITIES];
    /**
     * @brief The list of entities currently who have the component. This decreases entity lookup time at the expense of more memory. 
     */
    std::list<Entity> _componentEntityPool;

    // Number of valid items in the component array currently
    size_t _size = 0;
};

#endif