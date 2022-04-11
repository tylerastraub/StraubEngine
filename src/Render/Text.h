#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include <string>

struct Bounds {
    int w;
    int h;

    Bounds() {}
    Bounds(int w, int h) : w(w), h(h) {}
};

class Text {
public:
    Text(SDL_Renderer* renderer);
    ~Text();
    
    bool load(const char * fontPath, int ptSize);
    void render(int x, int y, int r = 255, int g = 255, int b = 255, int a = 255, int maxTextWidth = 99999);

    void setString(std::string s);

    int getWidth();
    int getHeight();
    std::string getString();

private:
    SDL_Renderer* _renderer;
    TTF_Font* _gameFont = nullptr;
    std::unordered_map<char, std::pair<SDL_Texture*, Bounds>> _characters;
    std::string _textString;

    int _width = 0;
    int _height = 0;
};

#endif