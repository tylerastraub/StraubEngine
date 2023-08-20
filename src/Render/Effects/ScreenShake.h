#pragma once

#include <SDL.h>

class ScreenShake {
public:
    ScreenShake() = default;
    ~ScreenShake() = default;

    void tick(float timescale);

    void setShakeAmount(float shakeAmount);
    void setMaxOffset(float maxOffset);

    SDL_FPoint getScreenShake();

private:
    float _shakeAmount = 0.f;
    float _maxOffset = 4.f;
    float _shakeDecrement = 0.8f;

};