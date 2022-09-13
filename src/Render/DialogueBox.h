#ifndef DIALOGUE_BOX_H
#define DIALOGUE_BOX_H

#include "Text.h"

enum class ReadSpeed {
    VERY_SLOW = 150,
    SLOW = 67,
    MEDIUM = 33,
    FAST = 17
};

class DialogueBox {
public:
    DialogueBox() = default;
    ~DialogueBox() = default;

    void tick(float timescale);
    void render(int x, int y);

    void setText(Text* text);
    void setString(std::string s);
    void setIsEnabled(bool isEnabled);
    void setTextFullyDisplayed(bool textFullyDisplayed);
    void setReadSpeed(ReadSpeed speed);

    bool isEnabled();
    float getTimeActive();
    bool isTextFullyDisplayed();

private:
    const int BORDER_BUFFER = 6;

    Text* _text = nullptr;

    bool _isEnabled = false;
    float _timeActive = 0.f;

    int _readSpeed = 33; // num of milliseconds between display of each character
    bool _textIsFullyDisplayed = false;
};

#endif