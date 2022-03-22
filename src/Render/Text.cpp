#include "Text.h"

#include <iostream>

Text::Text(SDL_Renderer* renderer) : _renderer(renderer) {}

Text::~Text() {
    for(auto c : _characters) {
        SDL_DestroyTexture(c.second.first);
    }
    TTF_CloseFont(_font);
}

bool Text::load(const  char * fontPath, int ptSize) {
    _font = TTF_OpenFont(fontPath, ptSize);

    if(_font == nullptr) {
        std::cout << "Error: failed to load font '" << fontPath << "'! SDL_ttf error: " << TTF_GetError() << std::endl;
        return false;
    }

    SDL_Color white = {255, 255, 255};
    // Kind of arbitrary char bounds but this covers most the important ones
    for(char c = '!'; c < '{'; ++c) {
        SDL_Surface* textSurface = TTF_RenderGlyph_Solid(_font, c, white);
        SDL_Texture* texture = nullptr;
        if(textSurface == nullptr) {
            std::cout << "Error: unable to render text surface! SDL_ttf error: " << TTF_GetError() << std::endl;
            return false;
        }
        SDL_Point charBounds = {textSurface->w, textSurface->h};
        texture = SDL_CreateTextureFromSurface(_renderer, textSurface);
        if(texture == nullptr) {
            std::cout << "Error: unable to create texture from loaded surface! SDL error: " << SDL_GetError() << std::endl;
            return false;
        }
        SDL_FreeSurface(textSurface);
        _characters[c] = std::make_pair(texture, charBounds);
    }

    return true;
}

void Text::draw(int xOffset, int yOffset, int r, int g, int b) {
    if(_textString.empty()) return;

    for(char c : _textString) {
        if(c == ' ') {
            xOffset += _characters['a'].second.x;
            continue;
        }
        SDL_Texture* character;
        SDL_Point charBounds;
        try {
            character = _characters[c].first;
            charBounds = _characters[c].second;
        }
        catch(std::out_of_range) {
            std::cout << "Error: character in string not found in font file! Character: '" << c << "'" << std::endl;
        }
        SDL_SetTextureColorMod(character, r, g, b);
        SDL_Rect charRect = {_pos.x + xOffset, _pos.y + yOffset, charBounds.x, charBounds.y};
        SDL_RenderCopy(_renderer, character, NULL, &charRect);
        xOffset += charBounds.x;
    }
}

void Text::setString(std::string s) {
    _textString = s;
    _width = 0;
    for(auto c : _textString) {
        _width += _characters[c].second.x;
    }
    
    if(s.empty()) {
        _height = 0;
        return;
    }
    _height = _characters[s[0]].second.y;
}

void Text::setPos(int x, int y) {
    _pos = {x, y};
}

int Text::getWidth() {
    return _width;
}

int Text::getHeight() {
    return _height;
}

SDL_Point Text::getPos() {
    return _pos;
}