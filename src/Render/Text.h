#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>
#include <unordered_map>

class Text {
public:
    Text(SDL_Renderer* renderer);
    ~Text();

    bool load(const  char * fontPath, int ptSize);
    void draw(int xOffset, int yOffset, int r = 255, int g = 255, int b = 255);

    void setString(std::string s);
    void setPos(int x, int y);

    int getWidth();
    int getHeight();
    SDL_Point getPos();

private:
    SDL_Renderer* _renderer = nullptr;
    TTF_Font* _font = nullptr;
    // 2nd half of pair is character bounds, i.e. width and height
    std::unordered_map<char, std::pair<SDL_Texture*, SDL_Point>> _characters;
    std::string _textString;

    int _width = 0;
    int _height = 0;
    SDL_Point _pos = {0, 0};

};

#endif