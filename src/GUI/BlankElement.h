#pragma once

#include "GUIElement.h"

class BlankElement : public GUIElement {
public:
    BlankElement() = default;
    ~BlankElement() = default;

    void render(int x, int y, bool centerAlign = true) override {};

private:

};