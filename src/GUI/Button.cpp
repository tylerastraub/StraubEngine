#include "Button.h"
#include "Hue.h"

#include <sstream>

Button::Button(std::shared_ptr<Text> text) : _text(text) {
    setCanBeSelected(true);
    _type = ElementType::BUTTON;
    
    // default style
    setProperty(ElementProperty::BACKGROUND_COLOR, "AFAFAF");
    setProperty(ElementProperty::HOVER_COLOR, "8c8c8c");
    setProperty(ElementProperty::SELECTED_COLOR, "696969");
    setProperty(ElementProperty::DISABLED_COLOR, "696969");
    setProperty(ElementProperty::TEXT_COLOR, "FFFFFF");
}

void Button::onSelect() {}

void Button::render(SDL_Renderer* renderer, strb::vec2f pos) {
    // render button background
    std::string color;
    switch(getElementState()) {
        case ElementState::HOVER:
            color = getProperty(ElementProperty::HOVER_COLOR);
            break;
        case ElementState::SELECTED:
            color = getProperty(ElementProperty::SELECTED_COLOR);
            break;
        case ElementState::NOVAL:
        default:
            color = getProperty(ElementProperty::BACKGROUND_COLOR);
    }
    if(!canBeSelected()) color = getProperty(ElementProperty::DISABLED_COLOR);
    Hue bg = convertStringToHue(color);
    
    SDL_SetRenderDrawColor(renderer, bg.red, bg.green, bg.blue, 0xFF);
    SDL_FRect r = {pos.x, pos.y, static_cast<float>(getElementSize().x), static_cast<float>(getElementSize().y)};
    if(canBeSelected()) SDL_RenderFillRectF(renderer, &r);
    else SDL_RenderDrawRectF(renderer, &r);

    // render button text
    _text->setString(getProperty(ElementProperty::DISPLAY_STRING));
    int totalHeight = _text->getHeight();
    std::stringstream ss(getProperty(ElementProperty::DISPLAY_STRING));
    std::vector<std::string> result;
    while(ss.good()) {
        std::string substr;
        std::getline(ss, substr, '\n');
        result.push_back(substr);
    }
    for(int i = 0; i < result.size(); ++i) {
        std::string s = result[i];
        _text->setString(s);
        int xOffset = 0;
        int yOffset = 0;
        if(isCenterAligned()) {
            xOffset = getElementSize().x / 2 - _text->getWidth() / 2;
            yOffset = getElementSize().y / 2 - totalHeight / 2;
        }
        yOffset += totalHeight / result.size() * i;
        strb::vec2f tempPos = {pos.x + xOffset, pos.y + yOffset};
        color = getProperty(ElementProperty::TEXT_COLOR);
        Hue textColor = convertStringToHue(color);
        std::string maxWidthString = getProperty(ElementProperty::MAX_TEXT_WIDTH);
        int maxWidth = 99999;
        if(!maxWidthString.empty()) maxWidth = std::stoi(maxWidthString);
        if(!canBeSelected()) {
            _text->render(tempPos, textColor.red * 0.5, textColor.green * 0.5, textColor.blue * 0.5, 0xFF, maxWidth);
        }
        else {
            _text->render(tempPos, textColor.red, textColor.green, textColor.blue, 0xFF, maxWidth);
        }
    }
}