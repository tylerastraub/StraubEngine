#include "ScreenFade.h"

#include <cmath>
#include <iostream>

ScreenFade::ScreenFade(bool fadeIn, int duration) : _fadeIn(fadeIn), _duration(duration) {
    if(fadeIn) {
        _fadeDelta = -1.f;
        _currentFade = 255;
    }
    else {
        _fadeDelta = 1.f;
        _currentFade = 0;
    }
    _currentTime = 0;
}

void ScreenFade::updateFade(int ms) {
    _currentTime += ms;
    float fade = 255.f * _fadeDelta * (float) _currentTime / (float) _duration;
    _currentFade = (_fadeIn) ? 255.f + fade : fade;
}

float ScreenFade::getCurrentFade() {
    return _currentFade;
}

bool ScreenFade::isFadeComplete() {
    if(_fadeIn) {
        return _currentFade <= 0.f;
    }
    else {
        return _currentFade >= 255.f;
    }
}