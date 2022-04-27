#include "InputSystem.h"
#include "EntityRegistry.h"
#include "InputComponent.h"

#include <algorithm>

void InputSystem::init(Keyboard* keyboard, Controller* controller, Settings* settings) {
    _keyboard = keyboard;
    _controller = controller;
    _settings = settings;
}

void InputSystem::update() {
    auto ecs = EntityRegistry::getInstance();
    for(auto ent : _entities) {
        auto& inputComponent = ecs->getComponent<InputComponent>(ent);
        auto allowedInputs = inputComponent.allowedInputs;

        // X inputs
        if(inputPressed(InputEvent::LEFT) &&
           std::find(allowedInputs.begin(), allowedInputs.end(), InputEvent::LEFT) != allowedInputs.end()) {
            _inputRequested = true;
            std::cout << "left pressed" << std::endl;
        }
        else if(inputPressed(InputEvent::RIGHT) &&
           std::find(allowedInputs.begin(), allowedInputs.end(), InputEvent::RIGHT) != allowedInputs.end()) {
            _inputRequested = true;
            std::cout << "right pressed" << std::endl;
        }

        // Y inputs
        if(inputPressed(InputEvent::UP) &&
           std::find(allowedInputs.begin(), allowedInputs.end(), InputEvent::UP) != allowedInputs.end()) {
            _inputRequested = true;
            std::cout << "up pressed" << std::endl;
        }
        else if(inputPressed(InputEvent::DOWN) &&
           std::find(allowedInputs.begin(), allowedInputs.end(), InputEvent::DOWN) != allowedInputs.end()) {
            _inputRequested = true;
            std::cout << "down pressed" << std::endl;
        }
    }

    _keyboard->updateInputs();
    _controller->updateInputs();
}

void InputSystem::completeInputRequest() {
    _inputRequested = false;
}

bool InputSystem::requestsInput() {
    return _inputRequested;
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
        return _controller->isButtonDown(_settings->getButton(input));
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
        return _controller->isButtonUp(_settings->getButton(input));
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
        return _controller->isButtonPressed(_settings->getButton(input));
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
        return _controller->isButtonReleased(_settings->getButton(input));
    }
}