#include "TextContainer.h"
#include "Hue.h"

TextContainer::TextContainer(std::shared_ptr<Text> text) : _text(text) {
    _type = ElementType::TEXT_CONTAINER;
}

void TextContainer::render(SDL_Renderer* renderer, strb::vec2f pos) {
    if(_text == nullptr) return;
    _text->setString(getProperty(ElementProperty::DISPLAY_STRING));
    int xOffset = 0;
    if(isCenterAligned()) {
        xOffset = getElementSize().x / 2 - _text->getWidth() / 2;
    }
    int yOffset = getElementSize().y / 2 - _text->getHeight() / 2;
    std::string maxWidthString = getProperty(ElementProperty::MAX_TEXT_WIDTH);
    int maxWidth = 99999;
    if(!maxWidthString.empty()) maxWidth = std::stoi(maxWidthString);
    Hue textColor = {0xFF, 0xFF, 0xFF};
    if(getProperty(ElementProperty::TEXT_COLOR).size() == 6) {
        textColor = convertStringToHue(getProperty(ElementProperty::TEXT_COLOR));
    }
    pos.x += xOffset;
    pos.y += yOffset;
    _text->render(pos, textColor.red, textColor.green, textColor.blue, 0xFF, maxWidth);

    // draw border
    // SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xAF);
    // SDL_FRect r = {pos.x - xOffset, pos.y - yOffset, getRenderSize().x, getRenderSize().y};
    // SDL_RenderDrawRectF(renderer, &r);
}