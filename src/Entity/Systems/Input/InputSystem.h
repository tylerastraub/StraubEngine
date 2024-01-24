#pragma once
#include "Keyboard.h"
#include "Controller.h"
#include "Settings.h"

#include <entt/entity/registry.hpp>
#include <memory>

class InputSystem {
public:
    InputSystem() = default;
    ~InputSystem() = default;

    void init(std::shared_ptr<Keyboard> keyboard, std::shared_ptr<Controller> controller, std::shared_ptr<Settings> settings);

    void update(entt::registry& ecs);

private:
    bool inputDown(InputEvent input);
    bool inputUp(InputEvent input);
    bool inputPressed(InputEvent input);
    bool inputReleased(InputEvent input);

    std::shared_ptr<Keyboard> _keyboard = nullptr;
    std::shared_ptr<Controller> _controller = nullptr;
    std::shared_ptr<Settings> _settings = nullptr;
};