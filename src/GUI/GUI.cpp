#include "GUI.h"
#include "RectUtils.h"

#include <iostream>

void GUI::processMouseInput(std::shared_ptr<Mouse> mouse) {
    // find colliding gui elements with mouse
    std::vector<uint16_t> collidingElements;
    std::vector<uint16_t> nonCollidingElement;
    for(auto keyValuePair : _collisionRects) {
        if(RectUtils::isIntersecting(
           keyValuePair.second,
           strb::rect2f{static_cast<float>(mouse->getMouseX()), static_cast<float>(mouse->getMouseY()), 1.f, 1.f})) {
            collidingElements.push_back(keyValuePair.first);
        }
        else {
            nonCollidingElement.push_back(keyValuePair.first);
        }
    }
    // then process event
    if(mouse->isLeftButtonDown()) {
        for(auto id : collidingElements) {
            auto e = getElement(id);
            if(e != nullptr) {
                e->setElementState(ElementState::SELECTED);
            }
        }
    } 
    else if(!mouse->isLeftButtonDown()) {
        if(mouse->isLeftButtonReleased()) {
            // interaction happened
            for(auto id : collidingElements) {
                auto e = getElement(id);
                if(e != nullptr) {
                    e->setElementState(ElementState::HOVER);
                    e->onSelect();
                    if(e->getProperty(ElementProperty::ON_SELECTED_NAME).size() > 0) {
                        addEvent(
                            e->getProperty(ElementProperty::ON_SELECTED_NAME),
                            e->getProperty(ElementProperty::ON_SELECTED_VALUE)
                        );
                    }
                }
            }
        }
        else {
            for(auto id : collidingElements) {
                auto e = getElement(id);
                if(e != nullptr) {
                    e->setElementState(ElementState::HOVER);
                }
            }
        }
    }
    // if no intersection, element is in neutral state
    for(auto id : nonCollidingElement) {
        auto e = getElement(id);
        if(e != nullptr) {
            e->setElementState(ElementState::NOVAL);
        }
    }
}

void GUI::render(SDL_Renderer* renderer, strb::vec2f renderOffset) {
    if(_gridSize.x == 0 || _gridSize.y == 0) return;
    // render background first
    SDL_SetRenderDrawColor(renderer, _bgColor.red, _bgColor.green, _bgColor.blue, 0xFF);
    SDL_FRect r = {_pos.x + renderOffset.x, _pos.y + renderOffset.y, _guiRenderSize.x, _guiRenderSize.y};
    SDL_RenderFillRectF(renderer, &r);

    // then render gui elements row by row
    int runningH = 0;
    for(int y = 0; y < _gridSize.y; ++y) {
        int runningW = 0;
        Row row = _grid[y];
        SDL_SetRenderDrawColor(renderer, row.backgroundColor.red, row.backgroundColor.green, row.backgroundColor.blue, 0xFF);
        r = {_pos.x + renderOffset.x, _pos.y + renderOffset.y + runningH, static_cast<float>(row.width), static_cast<float>(row.height)};
        SDL_RenderFillRectF(renderer, &r);
        if(row.drawOutline) {
            SDL_SetRenderDrawColor(renderer, row.outlineColor.red, row.outlineColor.green, row.outlineColor.blue, 0xFF);
            SDL_RenderDrawRectF(renderer, &r);
        }
        for(int x = 0; x < _gridSize.x; ++x) {
            auto e = getElement(x, y);
            e->render(renderer, {_pos.x + renderOffset.x + runningW + e->getPadding().left, _pos.y + renderOffset.y + runningH + e->getPadding().top});
            runningW += e->getRenderSize().x;
        }
        runningH += row.height;
    }

    // SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x64);
    // for(auto pair : _collisionRects) {
    //     SDL_FRect r = RectUtils::strbRectToSdlFRect(pair.second);
    //     SDL_RenderFillRectF(renderer, &r);
    // }
}

void GUI::insertElement(std::shared_ptr<GUIElement> element, int x, int y) {
    if(x < 0 || x >= _gridSize.x || y < 0 || y >= _gridSize.y) {
        std::cout << "Error: Invalid position for GUI::insertElement()! Insert pos: (" << x << ", " << y << "), grid size: " << _gridSize << std::endl;
        return;
    }
    element->setId(_elementIdProvider);
    ++_elementIdProvider;
    _grid[y].elements[x] = element;
    // if element size is more than 1, overwrite other parts of grid
    for(int i = x + 1; i < x + element->getSizeInGrid().x; ++i) {
        for(int j = y + 1; j < y + element->getSizeInGrid().y; ++j) {
            _grid[j].elements[i] = std::make_shared<NullElement>();
        }   
    }
    // then re-define row size
    int runningW = 0;
    int maxH = 0;
    for(int i = 0; i < _gridSize.x; ++i) {
        auto e = getElement(i, y);
        runningW += e->getRenderSize().x;
        if(e->getRenderSize().y > maxH) maxH = e->getRenderSize().y;
    }
    _grid[y].width = runningW;
    _grid[y].height = maxH;

    updateGUISize();
}

void GUI::updateCollisionBoxes() {
    int runningH = 0;
    for(int y = 0; y < _gridSize.y; ++y) {
        int runningW = 0;
        for(int x = 0; x < _gridSize.x; ++x) {
            auto e = getElement(x, y);
            if(e->canBeSelected()) {
                _collisionRects[e->getId()] = {
                    _pos.x + e->getPadding().left + runningW,
                    _pos.y + e->getPadding().top + runningH,
                    static_cast<float>(e->getElementSize().x),
                    static_cast<float>(e->getElementSize().y)
                };
            }
            else {
                _collisionRects[e->getId()] = {0, 0, 0, 0};
            }
            runningW += e->getRenderSize().x;
        }
        runningH += _grid[y].height;
    }
}

void GUI::resetElementStates() {
    for(int x = 0; x < _gridSize.x; ++x) {
        for(int y = 0; y < _gridSize.y; ++y) {
            getElement(x, y)->setElementState(ElementState::NOVAL);
        }
    }
}

void GUI::clearEvents() {
    _events.clear();
}

void GUI::destroy() {
    _grid.clear();
    _collisionRects.clear();
    setGridSize(0, 0);
    updateGUISize();
}

void GUI::setPos(strb::vec2f pos) {
    _pos = pos;
    updateCollisionBoxes();
}

void GUI::setGridSize(int x, int y) {
    _gridSize = {x, y};
    while(_grid.size() < y) {
        _grid.push_back(Row());
    }
    _grid.shrink_to_fit();
    for(auto& row : _grid) {
        while(row.elements.size() < x) {
            row.elements.push_back(std::make_shared<NullElement>());
        }
        row.elements.shrink_to_fit();
    }
}

void GUI::setRowBackgroundColor(int rowY, Hue backgroundColor) {
    if(rowY >= 0 && rowY < _gridSize.y) {
        _grid[rowY].backgroundColor = backgroundColor;
    }
    else {
        std::cout << "GUI::setRowBackgroundColor(): row index out of bounds! Row index: " << rowY << ", number of rows: " << _gridSize.y << std::endl;
    }
}

void GUI::setRowDrawOutline(int rowY, bool drawOutline) {
    if(rowY >= 0 && rowY < _gridSize.y) {
        _grid[rowY].drawOutline = drawOutline;
    }
    else {
        std::cout << "GUI::setRowDrawOutline(): row index out of bounds! Row index: " << rowY << ", number of rows: " << _gridSize.y << std::endl;
    }
}

void GUI::setRowOutlineColor(int rowY, Hue outlineColor) {
    if(rowY >= 0 && rowY < _gridSize.y) {
        _grid[rowY].outlineColor = outlineColor;
    }
    else {
        std::cout << "GUI::setRowOutlineColor(): row index out of bounds! Row index: " << rowY << ", number of rows: " << _gridSize.y << std::endl;
    }
}

strb::vec2f GUI::getPos() {
    return _pos;
}

strb::vec2i GUI::getGridSize() {
    return _gridSize;
}

strb::vec2f GUI::getGUIRenderSize() {
    return _guiRenderSize;
}

std::shared_ptr<GUIElement> GUI::getElement(int x, int y) {
    if(x >= 0 && x < _gridSize.x && y >= 0 && y < _gridSize.y) {
        return _grid[y].elements[x];
    }
    return std::make_shared<NullElement>();
}

std::shared_ptr<GUIElement> GUI::getElement(uint16_t id) {
    for(auto row : _grid) {
        for(auto e : row.elements) {
            if(e->getId() == id) return e;
        }
    }
    return nullptr;
}

EventList GUI::getEvents() {
    return _events;
}

void GUI::updateGUISize() {
    int maxW = 0;
    int runningH = 0;
    for(int y = 0; y < _gridSize.y; ++y) {
        if(_grid[y].width > maxW) maxW = _grid[y].width;
        runningH += _grid[y].height;
    }
    _guiRenderSize = {static_cast<float>(maxW), static_cast<float>(runningH)};
}

void GUI::addEvent(std::string name, std::string value) {
    _events.push_back(std::make_pair(name, value));
}