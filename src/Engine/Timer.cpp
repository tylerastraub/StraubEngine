#include "Timer.h"

void Timer::update(float timescale) {
    _timer += timescale * 1000.f * _countingCoefficient;
    if(_mostRecentSecond != _timer / 1000) {
        _mostRecentSecond = _timer / 1000;
    }
    if(_timer < 0) {
        if(_autoTimerReset) {
            _timer = _timerResetDefault;
        }
        else {
            _timer = 0;
        }
    }
}

void Timer::reset() {
    _timer = _timerResetDefault;
    _mostRecentSecond = _timerResetDefault / 1000;
}

void Timer::setAudio(std::shared_ptr<Audio> audio) {
    _audio = audio;
}

void Timer::setTimer(int ms) {
    _timer = ms;
}

void Timer::setTimerResetDefault(int ms) {
    _timerResetDefault = ms;
}

void Timer::setTimerAutoReset(bool autoReset) {
    _autoTimerReset = autoReset;
}

void Timer::changeToTimer() {
    _countingCoefficient = -1;
}

void Timer::changeToStopwatch() {
    _countingCoefficient = 1;
}

int Timer::getTimer() {
    return _timer;
}

int Timer::getMostRecentSecond() {
    return _mostRecentSecond;
}

std::string Timer::getTimerAsString() {
    int min = _timer / 60000;
    int tempTimer = _timer % 60000;
    int seconds = tempTimer / 1000;
    if(seconds < 10) return std::to_string(min) + ":0" + std::to_string(seconds);
    else return std::to_string(min) + ":" + std::to_string(seconds);
}

bool Timer::isZero() {
    return _timer <= 0;
}