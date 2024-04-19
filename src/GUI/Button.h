#pragma once

#include "GUIElement.h"
#include "Text.h"

class Button : public GUIElement {
public:
    Button(Text* text);
    ~Button() = default;

    void onSelect() override;
    void render(strb::vec2f pos, bool centerAlign = true) override;

    void setValue(std::string) override;

    std::string getValue() override;

private:
    Text* _text = nullptr;

};