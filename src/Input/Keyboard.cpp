#include "Keyboard.h"

void Keyboard::updateInputs() {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    for(size_t i = 0; i < SDL_NUM_SCANCODES; ++i) {
        _lastFrameKeyStates[i] = _currentKeyStates[i];
        _currentKeyStates[i] = currentKeyStates[i];
    }
}

bool Keyboard::isKeyDown(SDL_Scancode keyCode) {
    return _currentKeyStates[keyCode];
}

bool Keyboard::isKeyUp(SDL_Scancode keyCode) {
    return !_currentKeyStates[keyCode];
}

bool Keyboard::isKeyPressed(SDL_Scancode keyCode) {
    return _currentKeyStates[keyCode] && !_lastFrameKeyStates[keyCode];
}

bool Keyboard::isKeyReleased(SDL_Scancode keyCode) {
    return !_currentKeyStates[keyCode] && _lastFrameKeyStates[keyCode];
}