#pragma once

#include "GUIElement.h"
#include "Text.h"

#include <memory>

class TextContainer : public GUIElement {
public:
    TextContainer(std::shared_ptr<Text> text);
    ~TextContainer() = default;

    void render(SDL_Renderer* renderer, strb::vec2f pos) override;

private:
    std::shared_ptr<Text> _text = nullptr;

};