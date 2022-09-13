#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include <string>
#include <vector>

struct Bounds {
    int w = 0;
    int h = 0;

    Bounds() {}
    Bounds(int w, int h) : w(w), h(h) {}
};

struct Word {
    std::string text = "";
    int w = 0;
    int h = 0;
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
    SDL_Renderer* _renderer = nullptr;
    TTF_Font* _gameFont = nullptr;
    std::unordered_map<char, std::pair<SDL_Texture*, Bounds>> _characters;
    std::string _textString = "";
    std::vector<Word> _words;

    int _width = 0;
    int _height = 0;

    float _newLineSpacing = 1.05f; // line spacing between lines. standard should be something like 1.15f
};

#endif