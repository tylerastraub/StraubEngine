#include "DialogueBox.h"
#include "SpritesheetRegistry.h"

#include <iostream>

void DialogueBox::tick(float timescale) {
    if(!_textIsFullyDisplayed) _timeActive += timescale * 1000.f;
    if(_numOfCharactersRendered != _text->getNumOfRenderedChars() && _text->getLastCharacter() != ' ') {
        _numOfCharactersRendered = _text->getNumOfRenderedChars();
        _audio->playAudio(-1, AudioSound::CHARACTER_BLIP);
    }
}

void DialogueBox::render(int x, int y) {
    Spritesheet* dialogueBox = SpritesheetRegistry::getSpritesheet("DIALOGUE_BOX");
    dialogueBox->render(x, y, dialogueBox->getWidth(), dialogueBox->getHeight());

    if(_textIsFullyDisplayed) {
        _text->setPercentOfTextDisplayed(1.f);
    }
    else {
        float percent = _timeActive / ((float) _text->getNumOfChars() * (float) _readSpeed);
        _text->setPercentOfTextDisplayed(percent);
        if(percent >= 1.f) setTextFullyDisplayed(true);
    }
    _text->render(x + X_BORDER_BUFFER, y + Y_BORDER_BUFFER, 255, 255, 255, 255, dialogueBox->getWidth() - X_BORDER_BUFFER * 2);
}

void DialogueBox::setText(Text* text) {
    _text = text;
}

void DialogueBox::setAudio(Audio* audio) {
    _audio = audio;
}

void DialogueBox::setString(std::string s) {
    _text->setString(s);
}

void DialogueBox::setIsEnabled(bool isEnabled) {
    _isEnabled = isEnabled;
}

void DialogueBox::setTextFullyDisplayed(bool textFullyDisplayed) {
    _textIsFullyDisplayed = textFullyDisplayed;
}

void DialogueBox::setReadSpeed(ReadSpeed speed) {
    _readSpeed = (int) speed;
}

bool DialogueBox::isEnabled() {
    return _isEnabled;
}

float DialogueBox::getTimeActive() {
    return _timeActive;
}

bool DialogueBox::isTextFullyDisplayed() {
    return _textIsFullyDisplayed;
}