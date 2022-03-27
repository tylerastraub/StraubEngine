#include "TextContainer.h"

TextContainer::TextContainer(Text* text) : _text(text) {}

void TextContainer::render(int x, int y) {
    _text->setString(getPropertyValue("displayString"));
    int xOffset = getRenderWidth() / 2 - _text->getWidth() / 2;
    int yOffset = getRenderHeight() / 2 - _text->getHeight() / 2;
    _text->draw(x + xOffset, y + yOffset);
}

void TextContainer::setValue(std::string value) {
    setProperty("displayString", value);
}

std::string TextContainer::getValue() {
    return _text->getString();
}