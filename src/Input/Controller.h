#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Controls.h"

class Controller {
public:
    Controller() = default;
    ~Controller() = default;

    /**
     * Update methods should be called in the active state's handleControllerInput methods. They must be called
     * separately or else there will be some input fudging. 
     * 
     * However, updateInputs() should be called at the END(!!!) of the tick() method.
     */
    void updateInputs();
    void updateAxisInputs(SDL_Event e);
    void updateButtonInputs(SDL_Event e);

    bool isButtonDown(gamepad::SDL_GameControllerButton_Extended button);
    bool isButtonUp(gamepad::SDL_GameControllerButton_Extended button);
    bool isButtonPressed(gamepad::SDL_GameControllerButton_Extended button);
    bool isButtonReleased(gamepad::SDL_GameControllerButton_Extended button);

    int getAxisState(SDL_GameControllerAxis axis);
    int getAxisStateLastTick(SDL_GameControllerAxis axis);

private:
    const int ANALOG_DEAD_ZONE = 8000;
    const int TRIGGER_DEAD_ZONE = 4000;
    const int NUM_OF_BUTTON_STATES = 24;

    // Left analog stick
    // -1 for left, 1 for right
    int _leftAnalogXDir = 0;
    // -1 for up, 1 for down
    int _leftAnalogYDir = 0;
    // -1 for left, 1 for right
    int _lastLeftAnalogXDir = 0;
    // -1 for up, 1 for down
    int _lastLeftAnalogYDir = 0;

    // Right analog stick
    // -1 for left, 1 for right
    int _rightAnalogXDir = 0;
    // -1 for up, 1 for down
    int _rightAnalogYDir = 0;
    // -1 for left, 1 for right
    int _lastRightAnalogXDir = 0;
    // -1 for up, 1 for down
    int _lastRightAnalogYDir = 0;

    // List of current states of all buttons. Access array using SDL_GameControllerButton_Extended
    bool _currentButtonStates[24] = {0};
    // List of button states the previous tick
    bool _lastTickButtonStates[24] = {0};
};

#endif