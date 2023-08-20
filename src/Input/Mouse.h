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
     * 
     **/
    Mouse(float xRenderScale, float yRenderScale);
    ~Mouse() = default;

    void updateInput(SDL_Event e, int xRenderOffset, int yRenderOffset);

    void setPos(int x, int y);
    void setLeftButtonDown(bool leftButtonDown);
    void setRightButtonDown(bool rightButtonDown);
    void setMouseMoved(bool moved);

    strb::vec2i getMousePos();
    int getMouseX();
    int getMouseY();
    int getMouseDX();
    int getMouseDY();
    strb::rect2i getMouseGrabBox();
    bool isLeftButtonDown();
    bool isRightButtonDown();
    bool mouseMoved();

private:
    strb::vec2i _mousePos = {0, 0};
    strb::vec2i _mouseDelta = {0, 0};
    strb::rect2i _mouseGrabBox = {0, 0, 0, 0};
    bool _leftButtonDown = false;
    bool _rightButtonDown = false;
    bool _mouseMoved = false;

    float _xRenderScale = 0.f;
    float _yRenderScale = 0.f;
};