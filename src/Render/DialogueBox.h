#ifndef DIALOGUE_BOX_H
#define DIALOGUE_BOX_H

#include "Text.h"
#include "Audio.h"

enum class ReadSpeed {
    VERY_SLOW = 150, // 6-7 characters per second
    SLOW = 67, // 15 characters per second
    MEDIUM = 33, // 30 characters per second. character blip starts to sound worse at this speed
    FAST = 17 // 60 characters per second
};

class DialogueBox {
public:
    DialogueBox() = default;
    ~DialogueBox() = default;

    void tick(float timescale);
    void render(int x, int y);

    void setText(Text* text);
    void setAudio(Audio* audio);
    void setString(std::string s);
    void setIsEnabled(bool isEnabled);
    void setTextFullyDisplayed(bool textFullyDisplayed);
    void setReadSpeed(ReadSpeed speed);

    bool isEnabled();
    float getTimeActive();
    bool isTextFullyDisplayed();

private:
    const int X_BORDER_BUFFER = 6;
    const int Y_BORDER_BUFFER = 3;

    Text* _text = nullptr;
    Audio* _audio = nullptr;

    bool _isEnabled = false;
    float _timeActive = 0.f;

    int _readSpeed = 33; // num of milliseconds between display of each character
    bool _textIsFullyDisplayed = false;
    int _numOfCharactersRendered = 0;
};

#endif