#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include <string>
#include <unordered_map>

// Parent class for all GUI elements. Allows elements to easily be added to a GUI grid
class GUIElement {
public:
    GUIElement() = default;
    ~GUIElement() = default;

    virtual void onSelect() {};
    virtual void render(int x, int y) = 0;

    void setPos(int row, int column);
    void setSizeInGrid(int width, int height);
    void setWidthInGrid(int width);
    void setHeightInGrid(int height);
    void setRenderSize(int width, int height);
    void setRenderWidth(int width);
    void setRenderHeight(int height);
    void setId(std::string id);
    virtual void setValue(std::string value);
    void setProperty(std::string property, std::string value);
    void setIsSelected(bool isSelected);
    void setCanBeSelected(bool canBeSelected);

    int getRow();
    int getColumn();
    int getWidthInGrid();
    int getHeightInGrid();
    int getRenderWidth();
    int getRenderHeight();
    std::string getId();
    virtual std::string getValue();
    std::string getPropertyValue(std::string property);
    bool isSelected();
    bool canBeSelected();

private:
    int _row = -1;
    int _column = -1;
    // How many columns the element spans
    int _width = 1;
    // How many rows the element spans
    int _height = 1;
    int _renderWidth = 0;
    int _renderHeight = 0;

    // Whether or not to check if the element can be selected (or clicked).
    bool _canBeSelected = false;
    // If the element is currently being considered for selection
    bool _isSelected = false;

    std::string _elementId;
    std::string _value;
    std::unordered_map<std::string, std::string> _properties;
};

#endif