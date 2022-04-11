#include "Text.h"

#include <iostream>
#include <cmath>

Text::Text(SDL_Renderer* renderer) : _renderer(renderer) {}

Text::~Text() {
    for(auto c : _characters) {
        SDL_DestroyTexture(c.second.first);
        c.second.first = nullptr;
    }
    TTF_CloseFont(_gameFont);
}

bool Text::load(const char * fontPath, int ptSize) {
    TTF_Font* font = TTF_OpenFont(fontPath, ptSize);

    if(font == NULL)
    {
        printf("Failed to load font '%s'! SDL_ttf Error: %s\n", fontPath, TTF_GetError());
        return false;
    }

    SDL_Color white = {255, 255, 255};
    SDL_Color black = {0, 0, 0};
    for(char c = '!'; c < '{'; ++c) {
        // Note that Blended is more expensive than Solid. If performance becomes an issue,
        // this could be a good place to look.
        SDL_Surface* textSurface = TTF_RenderGlyph_Solid(font, c, white);
        SDL_Texture* texture = nullptr;
        if( textSurface == NULL )
        {
            printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
            return false;
        }
        else
        {
            Bounds charBounds(textSurface->w, textSurface->h);

            //Create texture from surface pixels
            texture = SDL_CreateTextureFromSurface(_renderer, textSurface);
            if( texture == NULL )
            {
                printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
                return false;
            }
            //Get rid of old surface
            SDL_FreeSurface(textSurface);

            _characters[c] = std::make_pair(texture, charBounds);
        }
    }

    _characters[' '].second = _characters['a'].second;

    return true;
}

void Text::render(int x, int y, int r, int g, int b, int a, int maxTextWidth) {
    int startX = x;
    maxTextWidth += startX;
    if(_textString.empty()) {
        std::cout << "Empty string!" << std::endl;
        return;
    }

    for(size_t i = 0; i < _textString.size(); ++i) {
        char c = _textString[i];
        if(c == ' ') {
            if(x != startX) x += _characters['a'].second.w;
            continue;
        }
        else if(c == '\n') {
            x = startX;
            y += std::ceil((float) _characters['a'].second.h * 1.15);
            continue;
        }
        SDL_Texture* character;
        Bounds charBounds;
        try {
            character = _characters[c].first;
            charBounds = _characters[c].second;
        }
        catch(std::out_of_range) {
            std::cout << "Error: Invalid character in string! Character: " << c << std::endl;
            return;
        }
        SDL_SetTextureColorMod(character, r, g, b);
        SDL_SetTextureAlphaMod(character, a);
        SDL_Rect charRect;
        charRect.x = x;
        charRect.y = y;
        charRect.w = charBounds.w;
        charRect.h = charBounds.h;
        SDL_RenderCopy(_renderer, character, NULL, &charRect);
        x += charRect.w;
        if(x + charRect.w > maxTextWidth && i != _textString.size() - 1) {
            x = startX;
            if(_textString[i + 1] != '\n') y += std::ceil((float) charRect.h * 1.15);
        }
    }
}

void Text::setString(std::string s) {
    _textString = s;
    _width = 0;
    _height = 0;
    if(s.empty()) return;
    for(auto c : _textString) {
        if(c == '\n') continue;
        Bounds b = _characters[c].second;
        _width += _characters[c].second.w;
        if(_characters[c].second.h > _height) _height = _characters[c].second.h;
    }
}

int Text::getWidth() {
    return _width;
}

int Text::getHeight() {
    return _height;
}

std::string Text::getString() {
    return _textString;
}