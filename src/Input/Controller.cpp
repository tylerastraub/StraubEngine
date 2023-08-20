#include "Controller.h"

#include <iostream>

void Controller::updateInputs() {
    for(size_t i = 0; i < NUM_OF_BUTTON_STATES; ++i) {
        _lastTickButtonStates[i] = _currentButtonStates[i];
    }
    _lastLeftAnalogXValue = _leftAnalogXValue;
    _lastLeftAnalogYValue = _leftAnalogYValue;
    _lastRightAnalogXValue = _rightAnalogXValue;
    _lastRightAnalogYValue = _rightAnalogYValue;
}

void Controller::updateAxisInputs(SDL_Event e) {
    // Left analog stick
    if(e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
        // X Axis
        if(std::abs(e.caxis.value) > ANALOG_DEAD_ZONE) {
            _leftAnalogXValue = e.caxis.value;
        }
        else {
            _leftAnalogXValue = 0;
        }
    }
    else if(e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
        // Y Axis
        if(std::abs(e.caxis.value) > ANALOG_DEAD_ZONE) {
            _leftAnalogYValue = e.caxis.value;
        }
        else {
            _leftAnalogYValue = 0;
        }
    }
    // Right analog stick
    else if(e.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX) {
        // X Axis
        if(std::abs(e.caxis.value) > ANALOG_DEAD_ZONE) {
            _rightAnalogXValue = e.caxis.value;
        }
        else {
            _rightAnalogXValue = 0;
        }
    }
    else if(e.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY) {
        // Y Axis
        if(std::abs(e.caxis.value) > ANALOG_DEAD_ZONE) {
            _rightAnalogYValue = e.caxis.value;
        }
        else {
            _rightAnalogYValue = 0;
        }
    }
    // Left trigger
    else if(e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT) {
        if(e.caxis.value > TRIGGER_DEAD_ZONE) {
            _currentButtonStates[(int) SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_LEFTTRIGGER] = true;
        }
        else {
            _currentButtonStates[(int) SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_LEFTTRIGGER] = false;
        }
    }
    // Right trigger
    else if(e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT) {
        if(e.caxis.value > TRIGGER_DEAD_ZONE) {
            _currentButtonStates[(int) SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_RIGHTTRIGGER] = true;
        }
        else {
            _currentButtonStates[(int) SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_RIGHTTRIGGER] = false;
        }
    }
}

void Controller::updateButtonInputs(SDL_Event e) {
    _currentButtonStates[e.cbutton.button] = e.cbutton.state;
}

bool Controller::isButtonDown(SDL_GameControllerButton_Extended button) {
    return _currentButtonStates[(int) button];
}

bool Controller::isButtonUp(SDL_GameControllerButton_Extended button) {
    return !_currentButtonStates[(int) button];
}

bool Controller::isButtonPressed(SDL_GameControllerButton_Extended button) {
    return _currentButtonStates[(int) button] && !_lastTickButtonStates[(int) button];
}

bool Controller::isButtonReleased(SDL_GameControllerButton_Extended button) {
    return !_currentButtonStates[(int) button] && _lastTickButtonStates[(int) button];
}

int Controller::getAxisState(SDL_GameControllerAxis axis) {
    switch(axis) {
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX: {
            return calculateStickDirection(_leftAnalogXValue, _leftAnalogYValue).x;
        }
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY: {
            return calculateStickDirection(_leftAnalogXValue, _leftAnalogYValue).y;
        }
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX: {
            return calculateStickDirection(_rightAnalogXValue, _rightAnalogYValue).x;
        }
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY: {
            return calculateStickDirection(_rightAnalogXValue, _rightAnalogYValue).y;
        }
        default: {
            return 0;
        }
    }
}

int Controller::getAxisStateLastTick(SDL_GameControllerAxis axis) {
    switch(axis) {
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX: {
            return calculateStickDirection(_lastLeftAnalogXValue, _lastLeftAnalogYValue).x;
        }
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY: {
            return calculateStickDirection(_lastLeftAnalogXValue, _lastLeftAnalogYValue).y;
        }
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX: {
            return calculateStickDirection(_lastRightAnalogXValue, _lastRightAnalogYValue).x;
        }
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY: {
            return calculateStickDirection(_lastRightAnalogXValue, _lastRightAnalogYValue).y;
        }
        default: {
            return 0;
        }
    }
}

float Controller::getAxisPercent(SDL_GameControllerAxis axis) {
    switch(axis) {
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX: {
            return std::abs(_leftAnalogXValue / (float) MAX_ANALOG_VALUE);
        }
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY: {
            return std::abs(_leftAnalogYValue / (float) MAX_ANALOG_VALUE);
        }
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX: {
            return std::abs(_rightAnalogXValue / (float) MAX_ANALOG_VALUE);
        }
        case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY: {
            return std::abs(_rightAnalogYValue / (float) MAX_ANALOG_VALUE);
        }
        default: {
            return 0;
        }
    }
}

strb::vec2i Controller::calculateStickDirection(int xValue, int yValue) {
    if(xValue == 0 && yValue == 0) return {0, 0};
    if(std::abs(xValue) > std::abs(yValue)) {
        int dir = (xValue < 0) ? -1 : 1;
        return {dir, 0};
    }
    else {
        int dir = (yValue < 0) ? -1 : 1;
        return {0, dir};
    }
}