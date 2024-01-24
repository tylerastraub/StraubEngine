#include "InputSystem.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"

#include <algorithm>

void InputSystem::init(std::shared_ptr<Keyboard> keyboard, std::shared_ptr<Controller> controller, std::shared_ptr<Settings> settings) {
    _keyboard = keyboard;
    _controller = controller;
    _settings = settings;
}

void InputSystem::update(entt::registry& ecs) {
    auto entities = ecs.view<InputComponent, PhysicsComponent>();
    for(auto ent : entities) {
        auto& inputComponent = ecs.get<InputComponent>(ent);
        auto& physics = ecs.get<PhysicsComponent>(ent);
        auto allowedInputs = inputComponent.allowedInputs;

        // X inputs
        if(inputDown(InputEvent::LEFT) &&
           std::find(allowedInputs.begin(), allowedInputs.end(), InputEvent::LEFT) != allowedInputs.end()) {
            physics.velocity.x -= physics.acceleration.x;
        }
        else if(inputDown(InputEvent::RIGHT) &&
           std::find(allowedInputs.begin(), allowedInputs.end(), InputEvent::RIGHT) != allowedInputs.end()) {
            physics.velocity.x += physics.acceleration.x;
        }

        // Y inputs
        if(inputDown(InputEvent::UP) &&
           std::find(allowedInputs.begin(), allowedInputs.end(), InputEvent::UP) != allowedInputs.end()) {
            physics.velocity.y -= physics.acceleration.y;
        }
        else if(inputDown(InputEvent::DOWN) &&
           std::find(allowedInputs.begin(), allowedInputs.end(), InputEvent::DOWN) != allowedInputs.end()) {
            physics.velocity.y += physics.acceleration.y;
        }
    }
}

bool InputSystem::inputDown(InputEvent input) {
    if(input == InputEvent::LEFT) {
        return _controller->getAxisState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == -1 ||
            _controller->isButtonDown(SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_DPAD_LEFT) ||
            _keyboard->isKeyDown(_settings->getScancode(InputEvent::LEFT));
    }
    else if(input == InputEvent::RIGHT) {
        return _controller->getAxisState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == 1 ||
            _controller->isButtonDown(SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ||
            _keyboard->isKeyDown(_settings->getScancode(InputEvent::RIGHT));
    }
    else if(input == InputEvent::UP) {
        return _controller->getAxisState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == -1 ||
            _controller->isButtonDown(SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_DPAD_UP) ||
            _keyboard->isKeyDown(_settings->getScancode(InputEvent::UP));
    }
    else if(input == InputEvent::DOWN) {
        return _controller->getAxisState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == 1 ||
            _controller->isButtonDown(SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_DPAD_DOWN) ||
            _keyboard->isKeyDown(_settings->getScancode(InputEvent::DOWN));
    }
    else {
        return _controller->isButtonDown(_settings->getButton(input)) || _keyboard->isKeyDown(_settings->getScancode(input));
    }
}

bool InputSystem::inputUp(InputEvent input) {
    if(input == InputEvent::LEFT) {
        return !(_controller->getAxisState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == -1 ||
            _controller->isButtonUp(SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_DPAD_LEFT)) ||
            _keyboard->isKeyUp(_settings->getScancode(InputEvent::LEFT));
    }
    else if(input == InputEvent::RIGHT) {
        return !(_controller->getAxisState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == 1 ||
            _controller->isButtonUp(SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) ||
            _keyboard->isKeyUp(_settings->getScancode(InputEvent::RIGHT));
    }
    else if(input == InputEvent::UP) {
        return !(_controller->getAxisState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == -1 ||
            _controller->isButtonUp(SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_DPAD_UP)) ||
            _keyboard->isKeyUp(_settings->getScancode(InputEvent::UP));
    }
    else if(input == InputEvent::DOWN) {
        return !(_controller->getAxisState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == 1 ||
            _controller->isButtonUp(SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_DPAD_DOWN)) ||
            _keyboard->isKeyUp(_settings->getScancode(InputEvent::DOWN));
    }
    else {
        return _controller->isButtonUp(_settings->getButton(input)) || _keyboard->isKeyUp(_settings->getScancode(input));
    }
}

bool InputSystem::inputPressed(InputEvent input) {
    if(input == InputEvent::LEFT) {
        return (_controller->getAxisState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == -1 &&
            _controller->getAxisStateLastTick(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) != -1) ||
            _controller->isButtonPressed(SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_DPAD_LEFT) ||
            _keyboard->isKeyPressed(_settings->getScancode(InputEvent::LEFT));
    }
    else if(input == InputEvent::RIGHT) {
        return (_controller->getAxisState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == 1 &&
            _controller->getAxisStateLastTick(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) != 1) ||
            _controller->isButtonPressed(SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ||
            _keyboard->isKeyPressed(_settings->getScancode(InputEvent::RIGHT));
    }
    else if(input == InputEvent::UP) {
        return (_controller->getAxisState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == -1 &&
            _controller->getAxisStateLastTick(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) != -1) ||
            _controller->isButtonPressed(SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_DPAD_UP) ||
            _keyboard->isKeyPressed(_settings->getScancode(InputEvent::UP));
    }
    else if(input == InputEvent::DOWN) {
        return (_controller->getAxisState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == 1 &&
            _controller->getAxisStateLastTick(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) != 1) ||
            _controller->isButtonPressed(SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_DPAD_DOWN) ||
            _keyboard->isKeyPressed(_settings->getScancode(InputEvent::DOWN));
    }
    else {
        return _controller->isButtonPressed(_settings->getButton(input)) || _keyboard->isKeyPressed(_settings->getScancode(input));
    }
}

bool InputSystem::inputReleased(InputEvent input) {
    if(input == InputEvent::LEFT) {
        return (_controller->getAxisState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) != -1 &&
            _controller->getAxisStateLastTick(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == -1) ||
            _controller->isButtonReleased(SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_DPAD_LEFT) ||
            _keyboard->isKeyReleased(_settings->getScancode(InputEvent::LEFT));
    }
    else if(input == InputEvent::RIGHT) {
        return (_controller->getAxisState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) != 1 &&
            _controller->getAxisStateLastTick(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == 1) ||
            _controller->isButtonReleased(SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ||
            _keyboard->isKeyReleased(_settings->getScancode(InputEvent::RIGHT));
    }
    else if(input == InputEvent::UP) {
        return (_controller->getAxisState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) != -1 &&
            _controller->getAxisStateLastTick(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == -1) ||
            _controller->isButtonReleased(SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_DPAD_UP) ||
            _keyboard->isKeyReleased(_settings->getScancode(InputEvent::UP));
    }
    else if(input == InputEvent::DOWN) {
        return (_controller->getAxisState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) != 1 &&
            _controller->getAxisStateLastTick(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == 1) ||
            _controller->isButtonReleased(SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_DPAD_DOWN) ||
            _keyboard->isKeyReleased(_settings->getScancode(InputEvent::DOWN));
    }
    else {
        return _controller->isButtonReleased(_settings->getButton(input)) || _keyboard->isKeyReleased(_settings->getScancode(input));
    }
}