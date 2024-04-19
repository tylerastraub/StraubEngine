#pragma once

#include "GUIElement.h"
#include "Text.h"

class TextContainer : public GUIElement {
public:
    TextContainer(Text* text);
    ~TextContainer() = default;

    void render(strb::vec2f pos, bool centerAlign = true) override;

    void setValue(std::string) override;

    std::string getValue() override;

private:
    Text* _text = nullptr;

};