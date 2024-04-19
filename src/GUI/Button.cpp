#include "Button.h"

Button::Button(Text* text) : _text(text) {
    setCanBeSelected(true);
}

void Button::onSelect() {}

void Button::render(strb::vec2f pos, bool centerAlign) {
    std::string s = getPropertyValue("displayString");
    if(isSelected()) {
        s.insert(0, "> ");
        s.append(" <");
    }
    _text->setString(s);
    int xOffset = 0;
    if(centerAlign) xOffset = getRenderWidth() / 2 - _text->getWidth() / 2;
    int yOffset = getRenderHeight() / 2 - _text->getHeight() / 2;
    pos.x += xOffset;
    pos.y += yOffset;
    if(getPropertyValue("dimTextDisplay") == "true") {
        _text->render(pos, 150, 150, 150);
    }
    else {
        _text->render(pos);
    }
}

void Button::setValue(std::string value) {
    setProperty("displayString", value);
}

std::string Button::getValue() {
    return _text->getString();
}