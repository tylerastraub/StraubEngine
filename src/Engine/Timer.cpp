#include "Timer.h"

void Timer::update(float timescale) {
    _timer -= timescale * 1000.f;
    if(_mostRecentSecond != _timer / 1000) {
        _mostRecentSecond = _timer / 1000;
    }
    if(_timer < 0) _timer = 0;
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

int Timer::getTimer() {
    return _timer;
}

int Timer::getMostRecentSecond() {
    return _mostRecentSecond;
}

std::string Timer::getTimerAsString() {
    int seconds = _timer / 1000;
    int ms = _timer % 100 / 10;
    return std::to_string(seconds) + "." + std::to_string(ms);
}

bool Timer::isZero() {
    return _timer <= 0;
}