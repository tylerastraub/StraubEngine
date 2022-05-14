#include "Tilemap.h"

#include <iostream>

void Tilemap::allocate(int w, int h) {
    _tilemapWidth = w;
    _tilemapHeight = h;
    for(int y = 0; y < h; ++y) {
        std::vector<Tile> row;
        for(int x = 0; x < w; ++x) {
            row.push_back({TileType::NOVAL, {0, 0, 0, 0}});
        }
        _tilemap.push_back(row);
    }
}

void Tilemap::render(int xOffset, int yOffset) {
    _tileset->setTileWidth(_tileSize);
    _tileset->setTileHeight(_tileSize);
    _tileset->setIsAnimated(false);
    for(int x = 0; x < _tilemapWidth; ++x) {
        for(int y = 0; y < _tilemapHeight; ++y) {
            if(x * _tileSize + xOffset > _tileSize * -1 &&
               x * _tileSize + xOffset < _gameWidth &&
               y * _tileSize + yOffset > _tileSize * -1 &&
               y * _tileSize + yOffset < _gameHeight) {
                Tile t = getTile(x, y);
                _tileset->setTileIndex(t.spritesheetRect.x, t.spritesheetRect.y);
                _tileset->render(x * _tileSize + xOffset, y * _tileSize + yOffset, t.spritesheetRect.w, t.spritesheetRect.h);
            }
        }
    }
}

void Tilemap::setTileSize(int tileSize) {
    _tileSize = tileSize;
}

void Tilemap::setTile(int x, int y, Tile tile) {
    if(x >= 0 && x < _tilemapWidth && y >= 0 && y < _tilemapHeight) {
        _tilemap[y][x] = tile;
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

int Tilemap::getTileSize() {
    return _tileSize;
}

Tile Tilemap::getTile(int x, int y) {
    if(x >= 0 && x < _tilemapWidth && y >= 0 && y < _tilemapHeight) {
        return _tilemap[y][x];
    }
    return {TileType::NOVAL, {0, 0, 0, 0}};
}