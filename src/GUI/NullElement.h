#pragma once

#include "GUIElement.h"

class NullElement : public GUIElement {
public:
    NullElement() = default;
    ~NullElement() = default;

    void render(SDL_Renderer* renderer, strb::vec2f pos) override {}

private:

};