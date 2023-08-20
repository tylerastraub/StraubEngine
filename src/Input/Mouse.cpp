#include "Mouse.h"

Mouse::Mouse(float xRenderScale, float yRenderScale) : _xRenderScale(xRenderScale), _yRenderScale(yRenderScale) {
    _mouseGrabBox.w = 8;
    _mouseGrabBox.h = 8;
}

void Mouse::updateInput(SDL_Event e, int xRenderOffset, int yRenderOffset) {
    if(e.type == SDL_MOUSEMOTION) {
        int x = 0;
        int y = 0;
        SDL_GetMouseState(&x, &y);
        setPos(x - xRenderOffset * _xRenderScale, y - yRenderOffset * _yRenderScale);
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

void Mouse::setPos(int x, int y) {
    _mousePos = {x / (int) _xRenderScale, y / (int) _yRenderScale};
    _mouseGrabBox.x = _mousePos.x - _mouseGrabBox.w / 2;
    _mouseGrabBox.y = _mousePos.y - _mouseGrabBox.h / 2;
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

strb::vec2i Mouse::getMousePos() {
    return _mousePos;
}

int Mouse::getMouseX() {
    return _mousePos.x;
}

int Mouse::getMouseY() {
    return _mousePos.y;
}

strb::rect2i Mouse::getMouseGrabBox() {
    return _mouseGrabBox;
}

bool Mouse::isLeftButtonDown() {
    return _leftButtonDown;
}

bool Mouse::isRightButtonDown() {
    return _rightButtonDown;
}

bool Mouse::mouseMoved() {
    return _mouseMoved;
}