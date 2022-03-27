#include "Controller.h"

void Controller::updateInputs() {
    for(size_t i = 0; i < NUM_OF_BUTTON_STATES; ++i) {
        _lastTickButtonStates[i] = _currentButtonStates[i];
    }
    _lastLeftAnalogXDir = _leftAnalogXDir;
    _lastLeftAnalogYDir = _leftAnalogYDir;
}

void Controller::updateAxisInputs(SDL_Event e) {
    SDL_Point startingDir = {_leftAnalogXDir, _leftAnalogYDir};
    // Left analog stick
    if(e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
        // X Axis
        if(e.caxis.value < ANALOG_DEAD_ZONE * -1) {
            _leftAnalogXDir = -1;
        }
        else if(e.caxis.value > ANALOG_DEAD_ZONE) {
            _leftAnalogXDir = 1;
        }
        else {
            _leftAnalogXDir = 0;
        }
    }
    else if(e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
        // Y Axis
        if(e.caxis.value < ANALOG_DEAD_ZONE * -1) {
            _leftAnalogYDir = -1;
        }
        else if(e.caxis.value > ANALOG_DEAD_ZONE) {
            _leftAnalogYDir = 1;
        }
        else {
            _leftAnalogYDir = 0;
        }
    }
    // Right analog stick
    else if(e.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX) {
        // X Axis
        if(e.caxis.value < ANALOG_DEAD_ZONE * -1) {
            _rightAnalogXDir = -1;
        }
        else if(e.caxis.value > ANALOG_DEAD_ZONE) {
            _rightAnalogXDir = 1;
        }
        else {
            _rightAnalogXDir = 0;
        }
    }
    else if(e.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY) {
        // Y Axis
        if(e.caxis.value < ANALOG_DEAD_ZONE * -1) {
            _rightAnalogYDir = -1;
        }
        else if(e.caxis.value > ANALOG_DEAD_ZONE) {
            _rightAnalogYDir = 1;
        }
        else {
            _rightAnalogYDir = 0;
        }
    }
    // Left trigger
    else if(e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT) {
        if(e.caxis.value > TRIGGER_DEAD_ZONE) {
            _currentButtonStates[gamepad::SDL_CONTROLLER_BUTTON_LEFTTRIGGER] = true;
        }
        else {
            _currentButtonStates[gamepad::SDL_CONTROLLER_BUTTON_LEFTTRIGGER] = false;
        }
    }
    // Right trigger
    else if(e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT) {
        if(e.caxis.value > TRIGGER_DEAD_ZONE) {
            _currentButtonStates[gamepad::SDL_CONTROLLER_BUTTON_RIGHTTRIGGER] = true;
        }
        else {
            _currentButtonStates[gamepad::SDL_CONTROLLER_BUTTON_RIGHTTRIGGER] = false;
        }
    }
}

void Controller::updateButtonInputs(SDL_Event e) {
    _currentButtonStates[(gamepad::SDL_GameControllerButton_Extended) e.cbutton.button] = e.cbutton.state;
}

bool Controller::isButtonDown(gamepad::SDL_GameControllerButton_Extended button) {
    return _currentButtonStates[button];
}

bool Controller::isButtonUp(gamepad::SDL_GameControllerButton_Extended button) {
    return !_currentButtonStates[button];
}

bool Controller::isButtonPressed(gamepad::SDL_GameControllerButton_Extended button) {
    return _currentButtonStates[button] && !_lastTickButtonStates[button];
}

bool Controller::isButtonReleased(gamepad::SDL_GameControllerButton_Extended button) {
    return !_currentButtonStates[button] && _lastTickButtonStates[button];
}

int Controller::getAxisState(SDL_GameControllerAxis axis) {
    switch(axis) {
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX:
            return _leftAnalogXDir;
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY:
            return _leftAnalogYDir;
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX:
            return _rightAnalogXDir;
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY:
            return _rightAnalogYDir;
        default:
            return 0;
    }
}

int Controller::getAxisStateLastTick(SDL_GameControllerAxis axis) {
    switch(axis) {
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX:
            return _lastLeftAnalogXDir;
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY:
            return _lastLeftAnalogYDir;
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX:
            return _lastRightAnalogXDir;
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY:
            return _lastRightAnalogYDir;
        default:
            return 0;
    }
}