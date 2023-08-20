#pragma once

#include <SDL.h>

/**
 * @brief Keyboard wrapper class that adds helper methods such as isKeyPressed and isKeyReleased.
 * Note that updateInputs() must be called each tick for accurate inputs.
 * 
 */
class Keyboard {
public:
    Keyboard() = default;
    ~Keyboard() = default;

    void updateInputs();

    bool isKeyDown(SDL_Scancode keyCode);
    bool isKeyUp(SDL_Scancode keyCode);
    bool isKeyPressed(SDL_Scancode keyCode);
    bool isKeyReleased(SDL_Scancode keyCode);

private:
    Uint8 _currentKeyStates[SDL_NUM_SCANCODES] = {0};
    Uint8 _lastFrameKeyStates[SDL_NUM_SCANCODES] = {0};

};