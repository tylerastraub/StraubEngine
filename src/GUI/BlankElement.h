#pragma once

#include "GUIElement.h"

class BlankElement : public GUIElement {
public:
    BlankElement() = default;
    ~BlankElement() = default;

    void render(strb::vec2f pos, bool centerAlign = true) override {};

private:

};