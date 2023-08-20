#pragma once

#include "Settings.h"
#include "vec2.h"

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

    bool isButtonDown(SDL_GameControllerButton_Extended button);
    bool isButtonUp(SDL_GameControllerButton_Extended button);
    bool isButtonPressed(SDL_GameControllerButton_Extended button);
    bool isButtonReleased(SDL_GameControllerButton_Extended button);

    int getAxisState(SDL_GameControllerAxis axis);
    int getAxisStateLastTick(SDL_GameControllerAxis axis);

    /**
     * @brief Get the percent the analog stick is along the given axis
     * 
     * @param axis Which axis to check
     * @return The percent on a scale from 0.f-1.f
     */
    float getAxisPercent(SDL_GameControllerAxis axis);

private:
    strb::vec2i calculateStickDirection(int xValue, int yValue);

    const int16_t MAX_ANALOG_VALUE = 32767;
    const int ANALOG_DEAD_ZONE = 8000;
    const int TRIGGER_DEAD_ZONE = 4000;
    const int NUM_OF_BUTTON_STATES = 24;

    // Left analog stick
    int _leftAnalogXValue = 0;
    int _leftAnalogYValue = 0;
    int _lastLeftAnalogXValue = 0;
    int _lastLeftAnalogYValue = 0;

    // Right analog stick
    int _rightAnalogXValue = 0;
    int _rightAnalogYValue = 0;
    int _lastRightAnalogXValue = 0;
    int _lastRightAnalogYValue = 0;

    // List of current states of all buttons. Access array using SDL_GameControllerButton_Extended
    bool _currentButtonStates[24] = {0};
    // List of button states the previous tick
    bool _lastTickButtonStates[24] = {0};
};