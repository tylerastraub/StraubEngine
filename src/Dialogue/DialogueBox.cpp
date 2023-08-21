#include "DialogueBox.h"
#include "SpritesheetRegistry.h"

#include <iostream>
#include <algorithm>

void DialogueBox::tick(float timescale) {
    if(!_textIsFullyDisplayed) _timeActive += timescale * 1000.f;
    if(_numOfCharactersRendered != _text->getNumOfRenderedChars() && _text->getLastCharacter() != ' ') {
        _numOfCharactersRendered = _text->getNumOfRenderedChars();
        _audio->playAudio(-1, AudioSound::CHARACTER_BLIP, 0.35f);
    }
}

void DialogueBox::render(int x, int y) {
    _text->setString(_currentString);
    Spritesheet* dialogueBox = SpritesheetRegistry::getSpritesheet(SpritesheetID::DIALOGUE_BOX);
    int yIndex = (isTextFullyDisplayed()) ? 1 : 0;
    dialogueBox->setTileIndex(0, yIndex);
    dialogueBox->render(x, y, dialogueBox->getWidth(), dialogueBox->getHeight() / 2);

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

void DialogueBox::advanceDialogue() {
    if(_currentDialogue.id == _currentDialogue.finalDialogueId) {
        setIsEnabled(false);
    }
    else {
        auto findDialogue = [&cd = _currentDialogue] (const Dialogue& d) -> bool { return cd.nextDialogueId == d.id; };
        setDialogue(*std::find_if(_conversation.begin(), _conversation.end(), findDialogue));
    }
    reset();
}

void DialogueBox::reset() {
    _timeActive = 0.f;
    setTextFullyDisplayed(false);
}

void DialogueBox::setText(Text* text) {
    _text = text;
}

void DialogueBox::setAudio(std::shared_ptr<Audio> audio) {
    _audio = audio;
}

void DialogueBox::setString(std::string s) {
    _currentString = s;
}

void DialogueBox::setConversation(Conversation conversation) {
    _conversation = conversation;
    auto findRoot = [](const Dialogue& d) -> bool { return d.isRoot; };
    auto it = std::find_if(_conversation.begin(), _conversation.end(), findRoot);
    if(it != _conversation.end()) {
        Dialogue d = *it;
        setDialogue(d);
    }
    else if(conversation.size() > 0) {
        setDialogue(*_conversation.begin());
    }
}

void DialogueBox::setDialogue(Dialogue dialogue) {
    _currentDialogue = dialogue;
    _speakerName = dialogue.speakerName;
    _portrait = dialogue.portrait;
    setReadSpeed(dialogue.readSpeed);
    _currentString = dialogue.text;
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