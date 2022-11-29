#include "TextContainer.h"

TextContainer::TextContainer(Text* text) : _text(text) {}

void TextContainer::render(int x, int y, bool centerAlign) {
    _text->setString(getPropertyValue("displayString"));
    int xOffset = 0;
    if(centerAlign) {
        xOffset = getRenderWidth() / 2 - _text->getWidth() / 2;
    }
    int yOffset = getRenderHeight() / 2 - _text->getHeight() / 2;
    std::string maxWidthString = getPropertyValue("maxTextWidth");
    int maxWidth = 99999;
    if(!maxWidthString.empty()) maxWidth = std::stoi(maxWidthString);
    _text->render(x + xOffset, y + yOffset, 255, 255, 255, 255, maxWidth);
}

void TextContainer::setValue(std::string value) {
    setProperty("displayString", value);
}

std::string TextContainer::getValue() {
    return _text->getString();
}