#include "ScreenShake.h"
#include "RandomGen.h"

void ScreenShake::tick(float timescale) {
    _shakeAmount -= _shakeDecrement * timescale;
    if(_shakeAmount < 0.f) _shakeAmount = 0.f;
}

void ScreenShake::setShakeAmount(float shakeAmount) {
    _shakeAmount = shakeAmount;
}

void ScreenShake::setMaxOffset(float maxOffset) {
    _maxOffset = maxOffset;
}

strb::vec2f ScreenShake::getScreenShake() {
    float xCoefficient = (float) RandomGen::getRandomInt(0, 1);
    if(xCoefficient == 0.f) xCoefficient = -1.f;
    float yCoefficient = (float) RandomGen::getRandomInt(0, 1);
    if(yCoefficient == 0.f) yCoefficient = -1.f;
    return {_maxOffset * _shakeAmount * xCoefficient, _maxOffset * _shakeAmount * yCoefficient};
}