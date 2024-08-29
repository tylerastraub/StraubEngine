#include "Mouse.h"

#include <iostream>

Mouse::Mouse(float xRenderScale, float yRenderScale) : _xRenderScale(xRenderScale), _yRenderScale(yRenderScale) {
    _mouseGrabBox.w = 8;
    _mouseGrabBox.h = 8;
}

void Mouse::handleEvent(SDL_Event e, int xRenderOffset, int yRenderOffset) {
    if(e.type == SDL_MOUSEMOTION) {
        int x = 0;
        int y = 0;
        SDL_GetMouseState(&x, &y);
        setPos(x - xRenderOffset * _xRenderScale - _xOffset, y - yRenderOffset * _yRenderScale - _yOffset);
        setMouseMoved(true);
    }
    else if(e.type == SDL_MOUSEBUTTONDOWN) {
        setMouseMoved(false);
        if(e.button.button == SDL_BUTTON_LEFT) {
            setLeftButtonDown(true);
        }
        else if(e.button.button == SDL_BUTTON_RIGHT) {
            setRightButtonDown(true);
        } 
    }
    else if(e.type == SDL_MOUSEBUTTONUP) {
        setMouseMoved(false);
        if(e.button.button == SDL_BUTTON_LEFT) {
            setLeftButtonDown(false);
        }
        else if(e.button.button == SDL_BUTTON_RIGHT) {
            setRightButtonDown(false);
        } 
    }
    else {
        setMouseMoved(false);
    }
}

void Mouse::updateInputs() {
    _leftButtonDownLastTick = _leftButtonDown;
    _rightButtonDownLastTick = _rightButtonDown;
    _mouseDelta = _mousePos - _lastMousePos;
    _lastMousePos = _mousePos;
    _mouseMoved = false;
}

void Mouse::setPos(float x, float y) {
    _mousePos = {x / _xRenderScale, y / _yRenderScale};
    _mouseGrabBox.x = _mousePos.x - _mouseGrabBox.w / 2.f;
    _mouseGrabBox.y = _mousePos.y - _mouseGrabBox.h / 2.f;
}

void Mouse::setLeftButtonDown(bool leftButtonDown) {
    _leftButtonDown = leftButtonDown;
}

void Mouse::setRightButtonDown(bool rightButtonDown) {
    _rightButtonDown = rightButtonDown;
}

void Mouse::setMouseMoved(bool moved) {
    _mouseMoved = moved;
}

void Mouse::setRenderScale(float xRenderScale, float yRenderScale) {
    _xRenderScale = xRenderScale;
    _yRenderScale = yRenderScale;
}

void Mouse::setOffset(float xOffset, float yOffset) {
    _xOffset = xOffset;
    _yOffset = yOffset;
}

strb::vec2i Mouse::getMousePos() {
    return {static_cast<int>(_mousePos.x), static_cast<int>(_mousePos.y)};
}

int Mouse::getMouseX() {
    return _mousePos.x;
}

int Mouse::getMouseY() {
    return _mousePos.y;
}

int Mouse::getMouseDX() {
    return _mouseDelta.x;
}

int Mouse::getMouseDY() {
    return _mouseDelta.y;
}

strb::rect2f Mouse::getMouseGrabBox() {
    return _mouseGrabBox;
}

bool Mouse::isLeftButtonDown() {
    return _leftButtonDown;
}

bool Mouse::isRightButtonDown() {
    return _rightButtonDown;
}

bool Mouse::isLeftButtonPressed() {
    return _leftButtonDown && !_leftButtonDownLastTick;
}

bool Mouse::isRightButtonPressed() {
    return _rightButtonDown && !_rightButtonDownLastTick;
}

bool Mouse::isLeftButtonReleased() {
    return !_leftButtonDown && _leftButtonDownLastTick;
}

bool Mouse::isRightButtonReleased() {
    return !_rightButtonDown && _rightButtonDownLastTick;
}

bool Mouse::mouseMoved() {
    return _mouseMoved;
}