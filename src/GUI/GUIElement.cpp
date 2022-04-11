#include "GUIElement.h"

void GUIElement::setPos(int column, int row) {
    _row = row;
    _column = column;
}

void GUIElement::setSizeInGrid(int width, int height) {
    _width = width;
    _height = height;
}

void GUIElement::setWidthInGrid(int width) {
    _width = width;
}

void GUIElement::setHeightInGrid(int height) {
    _height = height;
}

void GUIElement::setRenderSize(int width, int height) {
    _renderWidth = width;
    _renderHeight = height;
}

void GUIElement::setRenderWidth(int width) {
    _renderWidth = width;
}

void GUIElement::setRenderHeight(int height) {
    _renderHeight = height;
}

void GUIElement::setId(std::string id) {
    _elementId = id;
}

void GUIElement::setValue(std::string value) {
    _value = value;
}

void GUIElement::setProperty(std::string property, std::string value) {
    _properties[property] = value;
}

void GUIElement::setIsSelected(bool isSelected) {
    _isSelected = isSelected;
}

void GUIElement::setCanBeSelected(bool canBeSelected) {
    _canBeSelected = canBeSelected;
}

void GUIElement::setCenterAligned(bool centerAligned) {
    _isCenterAligned = centerAligned;
}

int GUIElement::getRow() {
    return _row;
}

int GUIElement::getColumn() {
    return _column;
}

int GUIElement::getWidthInGrid() {
    return _width;
}

int GUIElement::getHeightInGrid() {
    return _height;
}

int GUIElement::getRenderWidth() {
    return _renderWidth;
}

int GUIElement::getRenderHeight() {
    return _renderHeight;
}

std::string GUIElement::getId() {
    return _elementId;
}

std::string GUIElement::getValue() {
    return _value;
}

std::string GUIElement::getPropertyValue(std::string property) {
    return _properties[property];
}

bool GUIElement::isSelected() {
    return _isSelected;
}

bool GUIElement::canBeSelected() {
    return _canBeSelected;
}

bool GUIElement::isCenterAligned() {
    return _isCenterAligned;
}