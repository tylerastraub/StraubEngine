#pragma once

#include "EntityConstants.h"
#include "System.h"

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <iostream>

using Signature = std::bitset<entityConstants::MAX_COMPONENTS>;

class SystemManager {
public:
    SystemManager() = default;
    ~SystemManager() = default;

    template<typename T>
    std::shared_ptr<T> registerSystem() {
        const char * typeName = typeid(T).name();
        if(_systems.find(typeName) == _systems.end()) {
            auto system = std::make_shared<T>();
            _systems.insert({typeName, system});
            return system;
        }
        else {
            std::cout << "System already registered: " << typeName << std::endl;
        }
        return nullptr;
    }

    template<typename T>
    void setSignature(Signature signature) {
        const char * typeName = typeid(T).name();
        if(_signatures.find(typeName) == _signatures.end()) {
            _signatures.insert({typeName, signature});
        }
        else {
            std::cout << "Signature already set: " << typeName << std::endl;
        }
    }

    void entityDestroyed(Entity entity) {
        for(auto keyValue : _systems) {
            keyValue.second->_entities.erase(entity);
        }
    }

    void entitySignatureChanged(Entity entity, Signature entitySignature) {
        for(auto keyValue : _systems) {
            auto type = keyValue.first;
            auto system = keyValue.second;
            auto systemSignature = _signatures[type];
            if((entitySignature & systemSignature) == systemSignature) {
                system->_entities.insert(entity);
            }
            else {
                system->_entities.erase(entity);
            }
        }
    }

private:
    std::unordered_map<const char *, Signature> _signatures;
    std::unordered_map<const char *, std::shared_ptr<System>> _systems;

};