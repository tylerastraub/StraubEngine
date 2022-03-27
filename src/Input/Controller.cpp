#include "Controller.h"

void Controller::updateInputs() {
    for(size_t i = 0; i < NUM_OF_BUTTON_STATES; ++i) {
        _lastTickButtonStates[i] = _currentButtonStates[i];
    }
    _lastXDir = _xDir;
    _lastYDir = _yDir;
}

void Controller::updateAxisInputs(SDL_Event e) {
    SDL_Point startingDir = {_xDir, _yDir};
    if(e.caxis.axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) {
        // X Axis
        if(e.caxis.value < ANALOG_DEAD_ZONE * -1) {
            _xDir = -1;
        }
        else if(e.caxis.value > ANALOG_DEAD_ZONE) {
            _xDir = 1;
        }
        else {
            _xDir = 0;
        }
    }
    else if(e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
        // Y Axis
        if(e.caxis.value < ANALOG_DEAD_ZONE * -1) {
            _yDir = -1;
        }
        else if(e.caxis.value > ANALOG_DEAD_ZONE) {
            _yDir = 1;
        }
        else {
            _yDir = 0;
        }
    }
    else if(e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT) {
        if(e.caxis.value > TRIGGER_DEAD_ZONE) {
            _currentButtonStates[gamepad::SDL_CONTROLLER_BUTTON_LEFTTRIGGER] = true;
        }
        else {
            _currentButtonStates[gamepad::SDL_CONTROLLER_BUTTON_LEFTTRIGGER] = false;
        }
    }
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
            return _xDir;
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY:
            return _yDir;
    }
    return 0;
}

int Controller::getAxisStateLastTick(SDL_GameControllerAxis axis) {
    switch(axis) {
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX:
            return _lastXDir;
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY:
            return _lastYDir;
    }
    return 0;
}