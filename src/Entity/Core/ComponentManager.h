#pragma once

#include "EntityConstants.h"
#include "ComponentArray.h"

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <iostream>

using ComponentType = std::uint16_t;

class ComponentManager {
public:
    ComponentManager() = default;
    ~ComponentManager() = default;

    template<typename T>
    T& getComponent(Entity entity) {
        return getComponentArray<T>()->getData(entity);
    }

    template<typename T>
    ComponentType getComponentType() {
        const char * typeName = typeid(T).name();
        if(_componentTypes.find(typeName) != _componentTypes.end()) {
            return _componentTypes[typeName];
        }
        else {
            registerComponent<T>();
            return getComponentType<T>();
        }
    }

    template<typename T>
    std::list<Entity> getAllOf() {
        return getComponentArray<T>()->getAllOf();
    }

    template<typename T>
    bool hasComponent(Entity entity) {
        return getComponentArray<T>()->hasComponent(entity);
    }

    template<typename T>
    void addComponent(Entity entity, T component) {
        getComponentArray<T>()->insertData(entity, component);
    }

    template<typename T>
    void removeComponent(Entity entity, T component) {
        getComponentArray<T>()->removeData(entity, component);
    }

    void entityDestroyed(Entity entity) {
        for(auto keyValue : _componentArrays) {
            keyValue.second->entityDestroyed(entity);
        }
    }

private:
    template<typename T>
    void registerComponent() {
        const char * typeName = typeid(T).name();
        if(_componentTypes.find(typeName) == _componentTypes.end()) {
            _componentTypes[typeName] = _nextAvailableComponentType;
            _componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
            ++_nextAvailableComponentType;
        }
        else {
            std::cout << "Component already registered: " << typeName << std::endl;
        }
    }
    
    template<typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray() {
        const char* typeName = typeid(T).name();
        if(_componentTypes.find(typeName) != _componentTypes.end()) {
            return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[typeName]);
        }
        else {
            registerComponent<T>();
            return getComponentArray<T>();
        }
    }

    std::unordered_map<const char *, ComponentType> _componentTypes;
    std::unordered_map<const char *, std::shared_ptr<IComponentArray>> _componentArrays;

    ComponentType _nextAvailableComponentType = 0;

};