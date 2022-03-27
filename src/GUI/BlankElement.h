#ifndef BLANK_ELEMENT_H
#define BLANK_ELEMENT_H

#include "GUIElement.h"

class BlankElement : public GUIElement {
public:
    BlankElement() = default;
    ~BlankElement() = default;

    void render(int x, int y) override {};

private:

};

#endif