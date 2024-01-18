#include "Spritesheet.h"
#include "rect2.h"

#include <SDL_image.h>
#include <iostream>

Spritesheet::~Spritesheet() {
    free();
}

void Spritesheet::free() {
    if(_texture != nullptr) {
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
        _size.x = 0;
        _size.y = 0;
    }
}

bool Spritesheet::load(SDL_Renderer* renderer, std::string path) {
    _renderer = renderer;
    std::string relativePath = SDL_GetBasePath() + path;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(relativePath.c_str());
    if(loadedSurface == nullptr) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        return false;
    }
    else {
        _size.x = loadedSurface->w;
        _size.y = loadedSurface->h;
        // Create texture from surface pixels
        _texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(_texture == nullptr) {
            return false;
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return true;
}

void Spritesheet::render(float x, float y, float w, float h, SDL_RendererFlip flip, double angle, strb::vec2f center) {
    SDL_Rect srcRect;
    srcRect.x = _tileIndex.x;
    srcRect.y = _tileIndex.y;
    srcRect.w = _tileSize.x;
    srcRect.h = _tileSize.y;
    SDL_FRect renderQuad = {x, y, w, h};
    if(center.x == -1 && center.y == -1) {
        SDL_RenderCopyExF(_renderer, _texture, &srcRect, &renderQuad, angle, NULL, flip);
    }
    else {
        SDL_FPoint pointCenter = {center.x, center.y};
        SDL_RenderCopyExF(_renderer, _texture, &srcRect, &renderQuad, angle, &pointCenter, flip);
    }
}

SDL_Texture* Spritesheet::getTexture() {
    return _texture;
}

strb::vec2i Spritesheet::getTileIndex() {
    return {_tileIndex.x / _tileSize.x, _tileIndex.y / _tileSize.y};
}

int Spritesheet::getWidth() {
    return _size.x;
}

int Spritesheet::getHeight() {
    return _size.y;
}

int Spritesheet::getTileWidth() {
    return _tileSize.x;
}

int Spritesheet::getTileHeight() {
    return _tileSize.y;
}

bool Spritesheet::isAnimated() {
    return _isAnimated;
}

bool Spritesheet::isLooped() {
    return _isLooped;
}

int Spritesheet::getNumOfFrames() {
    if(_numOfFrames < 1) return 1;
    return _numOfFrames;
}

int Spritesheet::getMsBetweenFrames() {
    if(_msBetweenFrames < 1) return 1;
    return _msBetweenFrames;
}

void Spritesheet::setTileIndex(int x, int y) {
    if(x >= 0 && x < _size.x / _tileSize.x &&
       y >= 0 && y < _size.y / _tileSize.y) {
        _tileIndex.x = x * _tileSize.x;
        _tileIndex.y = y * _tileSize.y;
    }
    else {
        std::cout << "Error: Invalid tile index of (" << x << ", " << y << ")" << std::endl; 
        _tileIndex.x = 0;
        _tileIndex.y = 0;
    }
}

void Spritesheet::setTileWidth(int w) {
    _tileSize.x = w;
}

void Spritesheet::setTileHeight(int h) {
    _tileSize.y = h;
}

void Spritesheet::setIsAnimated(bool isAnimated) {
    _isAnimated = isAnimated;
}

void Spritesheet::setIsLooped(bool isLooped) {
    _isLooped = isLooped;
}

void Spritesheet::setNumOfFrames(int frames) {
    _numOfFrames = frames;
}

void Spritesheet::setMsBetweenFrames(int ms) {
    _msBetweenFrames = ms;
}