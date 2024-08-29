#include "GUIElement.h"

void GUIElement::setId(uint16_t id) {
    _id = id;
}

void GUIElement::setWidthInGrid(int width) {
    _sizeInGrid.x = width;
}

void GUIElement::setHeightInGrid(int height) {
    _sizeInGrid.y = height;
}

void GUIElement::setElementWidth(int width) {
    _elementSize.x = width;
}

void GUIElement::setElementHeight(int height) {
    _elementSize.y = height;
}

void GUIElement::setPadding(int top, int right, int bottom, int left) {
    _padding = {top, right, bottom, left};
}

void GUIElement::setPadding(Padding padding) {
    _padding = padding;
}

void GUIElement::setCanBeSelected(bool canBeSelected) {
    _canBeSelected = canBeSelected;
}

void GUIElement::setCenterAligned(bool centerAligned) {
    _isCenterAligned = centerAligned;
}

void GUIElement::setProperty(ElementProperty property, std::string value) {
    _properties[property] = value;
}

void GUIElement::setElementState(ElementState state) {
    _elementState = state;
}

uint16_t GUIElement::getId() {
    return _id;
}

ElementType GUIElement::getElementType() {
    return _type;
}

strb::vec2i GUIElement::getSizeInGrid() {
    return _sizeInGrid;
}

strb::vec2i GUIElement::getElementSize() {
    return _elementSize;
}

strb::vec2i GUIElement::getRenderSize() {
    return {
        _elementSize.x + _padding.left + _padding.right,
        _elementSize.y + _padding.top + _padding.bottom
    };
}

GUIElement::Padding GUIElement::getPadding() {
    return _padding;
}

bool GUIElement::canBeSelected() {
    return _canBeSelected;
}

bool GUIElement::isCenterAligned() {
    return _isCenterAligned;
}

std::string GUIElement::getProperty(ElementProperty property) {
    return _properties[property];
}

ElementState GUIElement::getElementState() {
    return _elementState;
}

Hue GUIElement::convertStringToHue(std::string rgbString) {
    return {
        static_cast<uint8_t>(std::strtol(rgbString.substr(0, 2).c_str(), NULL, 16)),
        static_cast<uint8_t>(std::strtol(rgbString.substr(2, 2).c_str(), NULL, 16)),
        static_cast<uint8_t>(std::strtol(rgbString.substr(4, 2).c_str(), NULL, 16))
    };
}