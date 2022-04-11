#include "GUI.h"

#include <iostream>

GUI::GUI(int gridWidth, int gridHeight) : _gridWidth(gridWidth), _gridHeight(gridHeight) {
    for(int y = 0; y < _gridHeight; ++y) {
        std::vector<std::shared_ptr<GUIElement>> row;
        for(int x = 0; x < _gridWidth; ++x) {
            row.push_back(nullptr);
        }
        _grid.push_back(row);
    }
}

void GUI::render(int x, int y) {
    int runningW = 0;
    for(size_t i = 0; i < _gridWidth; ++i) {
        int runningH = 0;
        GUIElement* e1 = nullptr;
        for(size_t j = 0; j < _gridHeight; ++j) {
            GUIElement* e = getElement(i, j);
            if(e) {
                e1 = e;
                e->render(x + runningW, y + runningH, e->isCenterAligned());
                runningH += e->getRenderHeight();
            }
        }
        if(e1) runningW += e1->getRenderWidth();
    }
}

void GUI::changeSelection(int dx, int dy) {
    getElement(_currentSelectionX, _currentSelectionY)->setIsSelected(false);
    for(int i = 0; i < _gridWidth; ++i) {
        _currentSelectionX += dx;
        if(_currentSelectionX < 0) {
            _currentSelectionX = (_wrapX) ? _gridWidth - 1 : 0;
        }
        else if(_currentSelectionX >= _gridWidth) {
            _currentSelectionX = (_wrapX) ? 0 : _gridWidth - 1;
        }

        if(getElement(_currentSelectionX, _currentSelectionY)) {
            if(getElement(_currentSelectionX, _currentSelectionY)->canBeSelected()) break;
        }
    }
    for(int i = 0; i < _gridHeight; ++i) {
        _currentSelectionY += dy;
        if(_currentSelectionY < 0) {
            _currentSelectionY = (_wrapY) ? _gridHeight - 1 : 0;
        }
        else if(_currentSelectionY >= _gridHeight) {
            _currentSelectionY = (_wrapY) ? 0 : _gridHeight - 1;
        }

        if(getElement(_currentSelectionX, _currentSelectionY)) {
            if(getElement(_currentSelectionX, _currentSelectionY)->canBeSelected()) break;
        }
    }
    getElement(_currentSelectionX, _currentSelectionY)->setIsSelected(true);
}

void GUI::addGUIElement(std::shared_ptr<Button> button) {
    if(button->getRow() < 0 &&
       button->getColumn() < 0 ||
       button->getColumn() + button->getWidthInGrid() > _gridWidth ||
       button->getRow() + button->getHeightInGrid() > _gridHeight) {
        std::cout << "Error: invalid GUI coordinates for GUIElement::Button " << button->getId() << std::endl;
        return;
    }
    insertElement(button, button->getColumn(), button->getRow());
}

void GUI::addGUIElement(std::shared_ptr<TextContainer> textContainer) {
    if(textContainer->getRow() < 0 ||
       textContainer->getColumn() < 0 ||
       textContainer->getColumn() + textContainer->getWidthInGrid() > _gridWidth ||
       textContainer->getRow() + textContainer->getHeightInGrid() > _gridHeight) {
        std::cout << "Error: invalid GUI coordinates for GUIElement::TextContainer " << textContainer->getId() << std::endl;
        return;
    }
    insertElement(textContainer, textContainer->getColumn(), textContainer->getRow());
}

void GUI::addGUIElement(std::shared_ptr<BlankElement> blankElement) {
    if(blankElement->getRow() < 0 ||
       blankElement->getColumn() < 0 ||
       blankElement->getColumn() + blankElement->getWidthInGrid() > _gridWidth ||
       blankElement->getRow() + blankElement->getHeightInGrid() > _gridHeight) {
        std::cout << "Error: invalid GUI coordinates for GUIElement::BlankElement " << blankElement->getId() << std::endl;
        return;
    }
    insertElement(blankElement, blankElement->getColumn(), blankElement->getRow());
}

void GUI::setRowHeightInGrid(int row, int height) {
    if(row >= 0 && row < _grid[0].size()) {
        for(size_t x = 0; x < _gridWidth; ++x) {
            if(getElement(x, row)) getElement(x, row)->setHeightInGrid(height);
        }
    }
}

void GUI::setAllRowsHeightInGrid(int height) {
    for(size_t x = 0; x < _gridWidth; ++x) {
        for(size_t y = 0; y < _gridHeight; ++y) {
            if(getElement(x, y)) getElement(x, y)->setHeightInGrid(height);
        }
    }
}

void GUI::setColumnWidthInGrid(int column, int width) {
    if(column >= 0 && column < _grid.size()) {
        for(size_t y = 0; y < _gridHeight; ++y) {
            if(getElement(column, y)) getElement(column, y)->setWidthInGrid(width);
        }
    }
}

void GUI::setAllColumnsWidthInGrid(int width) {
    for(size_t x = 0; x < _gridWidth; ++x) {
        for(size_t y = 0; y < _gridHeight; ++y) {
            if(getElement(x, y)) getElement(x, y)->setWidthInGrid(width);
        }
    }
}

void GUI::setRowRenderHeight(int row, int height) {
    if(row >= 0 && row < _grid.size()) {
        for(size_t x = 0; x < _gridWidth; ++x) {
            if(getElement(x, row)) getElement(x, row)->setRenderHeight(height);
        }
    }
}

void GUI::setAllRowsRenderHeight(int height) {
    for(size_t x = 0; x < _gridWidth; ++x) {
        for(size_t y = 0; y < _gridHeight; ++y) {
            if(getElement(x, y)) getElement(x, y)->setRenderHeight(height);
        }
    }
}

void GUI::setColumnRenderWidth(int column, int width) {
    if(column >= 0 && column < _grid[0].size()) {
        for(size_t y = 0; y < _gridHeight; ++y) {
            if(getElement(column, y)) getElement(column, y)->setRenderWidth(width);
        }
    }
}

void GUI::setAllColumnsRenderWidth(int width) {
    for(size_t x = 0; x < _gridWidth; ++x) {
        for(size_t y = 0; y < _gridHeight; ++y) {
            if(getElement(x, y)) getElement(x, y)->setRenderWidth(width);
        }
    }
}

void GUI::setWrapX(bool wrapX) {
    _wrapX = wrapX;
}

void GUI::setWrapY(bool wrapY) {
    _wrapY = wrapY;
}

void GUI::setCurrentSelection(int x, int y) {
    int oldX = x;
    int oldY = y;
    if(getElement(x, y)) {
        getElement(x, y)->setIsSelected(false);
    }
    _currentSelectionX = x;
    _currentSelectionY = y;
    GUIElement* e = getElement(x, y);
    if(e) {
        if(e->canBeSelected()) {
            e->setIsSelected(true);
        }
        else {
            setCurrentSelection(oldX, oldY);
        }
    }
    else {
        setCurrentSelection(oldX, oldY);
    }
}

GUIElement* GUI::getElement(int x, int y) {
    if(x >= 0 && x < _gridWidth && y >= 0 && y < _gridHeight) {
        return _grid[y][x].get();
    }
    return nullptr;
}

void GUI::insertElement(std::shared_ptr<GUIElement> element, int x, int y) {
    if(x >= 0 && x < _gridWidth && y >= 0 && y < _gridHeight) {
        _grid[y][x] = element;
    }
}

GUIElement* GUI::getCurrentSelection() {
    return getElement(_currentSelectionX, _currentSelectionY);
}