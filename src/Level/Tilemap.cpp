#include "Tilemap.h"

#include <iostream>

void Tilemap::allocate(int w, int h) {
    _tilemapWidth = w;
    _tilemapHeight = h;
    for(int y = 0; y < h; ++y) {
        std::vector<SDL_Rect> row;
        for(int x = 0; x < w; ++x) {
            row.push_back({0, 0, 0, 0});
        }
        _tilemap.push_back(row);
    }
}

void Tilemap::setTile(int x, int y, SDL_Rect spritesheetRect) {
    if(x >= 0 && x < _tilemapWidth && y >= 0 && y < _tilemapHeight) {
        _tilemap[y][x] = spritesheetRect;
    }
}

void Tilemap::setTileset(Spritesheet* spritesheet) {
    _tileset = spritesheet;
}

void Tilemap::setGameSize(int w, int h) {
    _gameWidth = w;
    _gameHeight = h;
}

int Tilemap::getTilemapWidth() {
    return _tilemapWidth;
}

int Tilemap::getTilemapHeight() {
    return _tilemapHeight;
}

SDL_Rect Tilemap::getTile(int x, int y) {
    if(x >= 0 && x < _tilemapWidth && y >= 0 && y < _tilemapHeight) {
        return _tilemap[y][x];
    }
    return {0, 0, 0, 0};
}