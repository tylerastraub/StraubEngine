#pragma once

#include "GUIElement.h"
#include "Text.h"

#include <memory>

class Button : public GUIElement {
public:
    Button(std::shared_ptr<Text> text);
    ~Button() = default;

    void onSelect() override;
    void render(SDL_Renderer* renderer, strb::vec2f pos) override;

private:
    std::shared_ptr<Text> _text = nullptr;

};