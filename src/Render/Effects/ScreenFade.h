#pragma once

class ScreenFade {
public:
    /**
     * @brief Construct a new Screen Fade object
     * 
     * @param fadeIn Whether or not the screen should fade in. If false, it will instead fade out.
     * @param duration How long it should take for the screen to full fade
     */
    ScreenFade(bool fadeIn, int duration);
    ~ScreenFade() = default;

    void updateFade(int ms);

    float getCurrentFade();
    bool isFadeComplete();

private:
    bool _fadeIn = false;
    int _duration = 0;
    int _currentTime = 0;
    float _currentFade = 0;
    float _fadeDelta = 0.f;

};