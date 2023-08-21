#pragma once

#include "Audio.h"

#include <string>
#include <memory>

class Timer {
public:
    Timer() = default;
    ~Timer() = default;

    void update(float timescale);
    void reset();

    void setAudio(std::shared_ptr<Audio> audio);
    void setTimer(int ms);
    void setTimerResetDefault(int ms);
    void setTimerAutoReset(bool autoReset);
    void changeToTimer();
    void changeToStopwatch();

    int getTimer();
    int getMostRecentSecond();
    std::string getTimerAsString();
    bool isZero();

private:
    std::shared_ptr<Audio> _audio = nullptr;

    int _timer = 0;
    int _timerResetDefault = 0;
    int _mostRecentSecond = 0;
    int _countingCoefficient = -1;
    bool _autoTimerReset = false;

};