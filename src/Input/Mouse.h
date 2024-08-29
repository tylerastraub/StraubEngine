#pragma once

#include "rect2.h"
#include "vec2.h"

#include <SDL.h>

class Mouse {
public:
    /** 
     * Creates a wrapper class that contains mouse info from SDL_GetMouseState(). This should be
     * handled in the state that creates the mouse.
     * 
     * @param renderScale The ratio between the logical game size and the actual screen width. SDL_GetMouseState()
     * returns coordinates of the mouse relative to actual screen size, so to get anything useful
     * to the actual game, coordinates need to be scaled appropriately.
     **/
    Mouse(float xRenderScale, float yRenderScale);
    ~Mouse() = default;

    void handleEvent(SDL_Event e, int xRenderOffset, int yRenderOffset);
    void updateInputs();

    void setPos(float x, float y);
    void setLeftButtonDown(bool leftButtonDown);
    void setRightButtonDown(bool rightButtonDown);
    void setMouseMoved(bool moved);
    void setRenderScale(float xRenderScale, float yRenderScale);
    void setOffset(float xOffset, float yOffset);

    strb::vec2i getMousePos();
    int getMouseX();
    int getMouseY();
    int getMouseDX();
    int getMouseDY();
    strb::rect2f getMouseGrabBox();
    bool isLeftButtonDown();
    bool isRightButtonDown();
    bool isLeftButtonPressed();
    bool isRightButtonPressed();
    bool isLeftButtonReleased();
    bool isRightButtonReleased();
    bool mouseMoved();

private:
    strb::vec2f _mousePos = {0, 0};
    strb::vec2f _lastMousePos  {0, 0};
    strb::vec2f _mouseDelta = {0, 0};
    strb::rect2f _mouseGrabBox = {0, 0, 0, 0};
    bool _leftButtonDown = false;
    bool _leftButtonDownLastTick = false;
    bool _rightButtonDown = false;
    bool _rightButtonDownLastTick = false;
    bool _mouseMoved = false;

    float _xRenderScale = 0.f;
    float _yRenderScale = 0.f;
    float _xOffset = 0.f;
    float _yOffset = 0.f;
};