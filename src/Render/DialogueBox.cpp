#include "DialogueBox.h"
#include "SpritesheetRegistry.h"

// todo: add method for slowly rendering text, advancing text box, etc.

void DialogueBox::render(int x, int y) {
    Spritesheet* dialogueBox = SpritesheetRegistry::getSpritesheet("DIALOGUE_BOX");
    dialogueBox->render(x, y, dialogueBox->getWidth(), dialogueBox->getHeight());

    _text->render(x + BORDER_BUFFER, y + 2, 255, 255, 255, 255, dialogueBox->getWidth() - BORDER_BUFFER * 2);
}

void DialogueBox::setText(Text* text) {
    _text = text;
}

void DialogueBox::setString(std::string s) {
    _text->setString(s);
}