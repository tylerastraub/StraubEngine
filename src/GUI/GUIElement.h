#pragma once

#include "vec2.h"
#include "rect2.h"
#include "Hue.h"

#include <string>
#include <unordered_map>
#include <SDL.h>

enum class ElementType {
    NOVAL = -1,
    BUTTON,
    TEXT_CONTAINER,
    ICON,
};

enum class ElementProperty {
    // Text
    DIM_TEXT_DISPLAY,
    DISPLAY_STRING,
    MAX_TEXT_WIDTH,
    TEXT_COLOR,
    // Style
    BACKGROUND_COLOR,
    DISABLED_COLOR,
    HOVER_COLOR,
    SELECTED_COLOR,
    SHADOW_COLOR,
    // Function
    ON_SELECTED_NAME,
    ON_SELECTED_VALUE, // quantity of ON_SELECTED_NAME (if relevant)
};

enum class ElementState {
    NOVAL = -1,
    HOVER,
    SELECTED,
};

class GUIElement {
public:
    struct Padding {
        Padding() = default;
        Padding(int top, int right, int bottom, int left) : top(top), right(right), bottom(bottom), left(left) {}

        int top = 0;
        int right = 0;
        int bottom = 0;
        int left = 0;
    };

    GUIElement() = default;
    ~GUIElement() = default;

    virtual void onSelect() {};
    virtual void render(SDL_Renderer* renderer, strb::vec2f pos) = 0;

    void setId(uint16_t id);
    void setWidthInGrid(int width);
    void setHeightInGrid(int height);
    void setElementWidth(int width);
    void setElementHeight(int height);
    void setPadding(int top, int right, int bottom, int left);
    void setPadding(Padding padding);
    void setCanBeSelected(bool canBeSelected);
    void setCenterAligned(bool centerAligned);
    void setProperty(ElementProperty property, std::string value);
    void setElementState(ElementState state);

    uint16_t getId();
    ElementType getElementType();
    strb::vec2i getSizeInGrid();
    strb::vec2i getElementSize();
    strb::vec2i getRenderSize();
    Padding getPadding();
    bool canBeSelected();
    bool isCenterAligned();
    std::string getProperty(ElementProperty property);
    ElementState getElementState();

protected:
    Hue convertStringToHue(std::string rgbString);

    ElementType _type = ElementType::NOVAL;

private:
    uint16_t _id = INT16_MAX;

    // How many columns and rows the element spans
    strb::vec2i _sizeInGrid = {1, 1};
    strb::vec2i _elementSize = {0, 0};
    Padding _padding = {0, 0, 0, 0};

    // Whether or not to check if the element can be selected (or clicked).
    bool _canBeSelected = false;
    // Whether or not to render the element center aligned
    bool _isCenterAligned = true;

    // Property map for fine tuning GUI elements
    std::unordered_map<ElementProperty, std::string> _properties;

    ElementState _elementState = ElementState::NOVAL;
};