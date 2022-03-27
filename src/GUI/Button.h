#ifndef BUTTON_H
#define BUTTON_H

#include "GUIElement.h"
#include "Text.h"

class Button : public GUIElement {
public:
    Button(Text* text);
    ~Button() = default;

    void onSelect() override;
    void render(int x, int y) override;

    void setValue(std::string) override;

    std::string getValue() override;

private:
    Text* _text = nullptr;

};

#endif