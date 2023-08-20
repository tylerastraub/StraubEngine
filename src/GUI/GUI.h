#pragma once

#include "Button.h"
#include "TextContainer.h"
#include "BlankElement.h"

#include <vector>
#include <memory>

class GUI {
public:
    GUI(int gridWidth, int gridHeight);
    ~GUI() = default;

    void render(int x, int y);
    void changeSelection(int dx, int dy);

    void addGUIElement(std::shared_ptr<Button> button);
    void addGUIElement(std::shared_ptr<TextContainer> textContainer);
    void addGUIElement(std::shared_ptr<BlankElement> blankElement);

    void setRowHeightInGrid(int row, int height);
    void setAllRowsHeightInGrid(int height);
    void setColumnWidthInGrid(int column, int width);
    void setAllColumnsWidthInGrid(int width);

    void setRowRenderHeight(int row, int height);
    void setAllRowsRenderHeight(int height);
    void setColumnRenderWidth(int column, int width);
    void setAllColumnsRenderWidth(int width);

    void setWrapX(bool wrapX);
    void setWrapY(bool wrapY);

    void setCurrentSelection(int x, int y);

    GUIElement* getElement(int x, int y);
    GUIElement* getCurrentSelection();

private:
    void insertElement(std::shared_ptr<GUIElement> element, int x, int y);

    int _gridWidth = 0;
    int _gridHeight = 0;

    int _currentSelectionX = 0;
    int _currentSelectionY = 0;
    // Whether or not the selection should loop horizontally
    bool _wrapX = false;
    // Whether or not the selection should loop vertically
    bool _wrapY = false;

    std::vector<std::vector<std::shared_ptr<GUIElement>>> _grid;
};