#ifndef DIALOGUE_BOX_H
#define DIALOGUE_BOX_H

#include "Text.h"

class DialogueBox {
public:
    DialogueBox() = default;
    ~DialogueBox() = default;

    void render(int x, int y);

    void setText(Text* text);
    void setString(std::string s);

private:
    const int BORDER_BUFFER = 6;

    Text* _text = nullptr;

};

#endif