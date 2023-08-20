#pragma once

#include "GUIElement.h"
#include "Text.h"

class TextContainer : public GUIElement {
public:
    TextContainer(Text* text);
    ~TextContainer() = default;

    void render(int x, int y, bool centerAlign = true) override;

    void setValue(std::string) override;

    std::string getValue() override;

private:
    Text* _text = nullptr;

};