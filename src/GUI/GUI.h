#pragma once

#include "Button.h"
#include "TextContainer.h"
#include "NullElement.h"
#include "vec2.h"
#include "Hue.h"
#include "Mouse.h"

#include <vector>
#include <memory>

using EventList = std::vector<std::pair<std::string, std::string>>;

class GUI {
public:
    struct Row {
        std::vector<std::shared_ptr<GUIElement>> elements;
        int width = 0; // render width
        int height = 0; // render height
        Hue backgroundColor = {0x26, 0x26, 0x26};
        bool drawOutline = false;
        Hue outlineColor = {0x54, 0x54, 0x54};
    };

    GUI() = default;
    ~GUI() = default;

    void processMouseInput(std::shared_ptr<Mouse> mouse);
    void render(SDL_Renderer* renderer, strb::vec2f renderOffset);
    void insertElement(std::shared_ptr<GUIElement> element, int x, int y);
    void updateCollisionBoxes();
    void resetElementStates();
    void clearEvents();

    // remove all GUI elements and collision rects from GUI.
    // should be mainly used to either kill a window or rebuild from scratch
    void destroy();

    void setPos(strb::vec2f pos);
    void setGridSize(int x, int y);
    void setRowBackgroundColor(int rowY, Hue backgroundColor);
    void setRowDrawOutline(int rowY, bool drawOutline);
    void setRowOutlineColor(int rowY, Hue outlineColor);

    // void setColumnPadding(int column, GUIElement::Padding padding);
    // void setRowPadding(int row, GUIElement::Padding padding);

    strb::vec2f getPos();
    strb::vec2i getGridSize();
    strb::vec2f getGUIRenderSize();
    std::shared_ptr<GUIElement> getElement(int x, int y);
    std::shared_ptr<GUIElement> getElement(uint16_t id);
    EventList getEvents();

private:
    void updateGUISize();
    void addEvent(std::string name, std::string value);

    uint16_t _elementIdProvider = 0;

    strb::vec2f _pos = {0.f, 0.f};
    std::vector<Row> _grid;
    strb::vec2i _gridSize = {0, 0};
    strb::vec2f _guiRenderSize = {0.f, 0.f};

    Hue _bgColor = {0x26, 0x26, 0x26}; // todo: getter/setters

    std::unordered_map<int, strb::rect2f> _collisionRects;

    EventList _events = {};

};