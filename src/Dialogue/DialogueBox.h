#pragma once

#include "Text.h"
#include "Audio.h"
#include "ReadSpeed.h"
#include "Dialogue.h"

#include <vector>
#include <memory>

using Conversation = std::vector<Dialogue>;

class DialogueBox {
public:
    DialogueBox() = default;
    ~DialogueBox() = default;

    void tick(float timescale);
    void render(int x, int y);
    void advanceDialogue();
    void reset();

    void setText(Text* text);
    void setAudio(std::shared_ptr<Audio> audio);
    void setString(std::string s);
    void setConversation(Conversation conversation);
    void setDialogue(Dialogue dialogue);
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
    std::shared_ptr<Audio> _audio = nullptr;

    bool _isEnabled = false;
    float _timeActive = 0.f;

    int _readSpeed = 33; // num of milliseconds between display of each character
    bool _textIsFullyDisplayed = false;
    int _numOfCharactersRendered = 0;

    Conversation _conversation;
    Dialogue _currentDialogue;

    std::string _speakerName = "";
    SpritesheetID _portrait = SpritesheetID::NOVAL;
    std::string _currentString = "";
};