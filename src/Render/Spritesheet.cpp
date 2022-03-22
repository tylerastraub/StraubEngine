#include "Spritesheet.h"

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

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(relativePath.c_str());
    if(loadedSurface == nullptr) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        return false;
    }
    else {
        _size.x = loadedSurface->w;
        _size.y = loadedSurface->h;
        //Create texture from surface pixels
        _texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(_texture == nullptr) {
            return false;
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return true;
}

void Spritesheet::render(int x, int y, SDL_RendererFlip flip, double angle, SDL_Point center) {
    SDL_Rect srcRect;
    srcRect.x = _tileIndex.x;
    srcRect.y = _tileIndex.y;
    srcRect.w = _tileSize.x;
    srcRect.h = _tileSize.y;
    SDL_Rect renderQuad = {x, y, _renderSize.x, _renderSize.y};
    if(center.x == -1 && center.y == -1) {
        SDL_RenderCopyEx(_renderer, _texture, &srcRect, &renderQuad, angle, NULL, flip);
    }
    else {
        SDL_RenderCopyEx(_renderer, _texture, &srcRect, &renderQuad, angle, &center, flip);
    }
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
    return _numOfFrames;
}

int Spritesheet::getMsBetweenFrames() {
    return _msBetweenFrames;
}

void Spritesheet::setTileIndex(int x, int y) {
    if(x >= 0 && x < _size.x / INDEX_SIZE &&
       y >= 0 && y < _size.y / INDEX_SIZE) {
        _tileIndex.x = x * INDEX_SIZE;
        _tileIndex.y = y * INDEX_SIZE;
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

void Spritesheet::setRenderWidth(int w) {
    _renderSize.x = w;
}

void Spritesheet::setRenderHeight(int h) {
    _renderSize.y = h;
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