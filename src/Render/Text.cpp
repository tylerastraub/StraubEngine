#include "Text.h"
#include "rect2.h"

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

    if(font == nullptr) {
        printf("Failed to load font '%s'! SDL_ttf Error: %s\n", fontPath, TTF_GetError());
        return false;
    }

    SDL_Color white = {255, 255, 255};
    for(char c = '!'; c < '{'; ++c) {
        SDL_Surface* textSurface = TTF_RenderGlyph_Solid(font, c, white);
        SDL_Texture* texture = nullptr;
        if(textSurface == nullptr) {
            printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
            return false;
        }
        else {
            Bounds charBounds(textSurface->w, textSurface->h);

            // Create texture from surface pixels
            texture = SDL_CreateTextureFromSurface(_renderer, textSurface);
            if(texture == nullptr) {
                printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
                return false;
            }
            // Get rid of old surface
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

    int charCount = 0;
    for(auto word : _words) {
        if(x + word.w > maxTextWidth) {
            x = startX;
            y += std::ceil((float) word.h * _newLineSpacing);
        }
        for(size_t i = 0; i < word.text.size(); ++i) {
            ++charCount;
            if(_numOfRenderedChars != charCount) {
                _numOfRenderedChars = charCount;
            }
            if(charCount > _numOfChars * _percentOfTextDisplayed) return;
            char c = word.text[i];
            if(c == '\n') {
                _lastCharacter = ' ';
                x = startX;
                y += std::ceil((float) _characters['a'].second.h * _newLineSpacing);
                continue;
            }
            _lastCharacter = c;
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
        }
        if(x != startX) x += _characters['a'].second.w; // add space between words
    }
}

void Text::setString(std::string s) {
    _words.clear();
    _numOfChars = 0;
    _textString = s;
    _width = 0;
    _height = 0;
    if(s.empty()) return;
    Word currentWord;
    for(auto c : _textString) {
        if(c == ' ') {
            if(!currentWord.text.empty()) _words.push_back(currentWord);
            _width += currentWord.w;
            _width += _characters[' '].second.w;
            currentWord = Word();
            continue;
        }
        else if(c == '\n') {
            if(!currentWord.text.empty()) _words.push_back(currentWord);
            _width += currentWord.w;
            currentWord = Word();
            currentWord.text = "\n";
            _words.push_back(currentWord);
            currentWord = Word();
            ++_numOfChars;
            continue;
        }
        ++_numOfChars;
        currentWord.text.push_back(c);
        Bounds b = _characters[c].second;
        currentWord.w += _characters[c].second.w;
        if(_characters[c].second.h > currentWord.h) {
            currentWord.h = _characters[c].second.h;
            if(currentWord.h > _height) _height = currentWord.h;
        }
    }
    if(!currentWord.text.empty()) {
        _words.push_back(currentWord); // add that last word
        _width += currentWord.w;
    }
}

void Text::setPercentOfTextDisplayed(float percent) {
    _percentOfTextDisplayed = percent;
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

int Text::getNumOfChars() {
    return _numOfChars;
}

int Text::getNumOfRenderedChars() {
    return _numOfRenderedChars;
}

char Text::getLastCharacter() {
    return _lastCharacter;
}