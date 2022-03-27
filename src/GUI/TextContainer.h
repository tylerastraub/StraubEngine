#ifndef TEXT_CONTAINER_H
#define TEXT_CONTAINER_H

#include "GUIElement.h"
#include "Text.h"

class TextContainer : public GUIElement {
public:
    TextContainer(Text* text);
    ~TextContainer() = default;

    void render(int x, int y) override;

    void setValue(std::string) override;

    std::string getValue() override;

private:
    Text* _text = nullptr;

};

#endif