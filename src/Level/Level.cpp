#include "Level.h"

void Level::allocateTilemap(int width, int height) {
    if(width < 1 || height < 1) return;
    _tilemapWidth = width;
    _tilemapHeight = height;
    std::vector<std::vector<Tile>> tilemap;
    for(int y = 0; y < _tilemapHeight; ++y) {
        std::vector<Tile> row;
        for(int x = 0; x < _tilemapWidth; ++x) {
            row.push_back(Tile{});
        }
        tilemap.push_back(row);
    }
    _tilemap = tilemap;
}

void Level::render(int xOffset, int yOffset) {
    if(_tileset == nullptr) return;
    for(int x = 0; x < _tilemapWidth; ++x) {
        for(int y = 0; y < _tilemapHeight; ++y) {
            if((x + 1) * _tileSize + xOffset < 0 || x * _tileSize + xOffset > _tilemapWidth * _tileSize ||
               (y + 1) * _tileSize + yOffset < 0 || y * _tileSize + yOffset > _tilemapHeight * _tileSize) {
                continue;
               }
            Tile t = getTileAt(x, y);
            if(t.spritesheetRect.w == 0 && t.spritesheetRect.h == 0) continue;

            _tileset->setTileWidth(t.spritesheetRect.w);
            _tileset->setTileHeight(t.spritesheetRect.h);
            _tileset->setTileIndex(t.spritesheetRect.x, t.spritesheetRect.y);
            // in future, these properties could be added to tile struct
            _tileset->setIsAnimated(false);

            _tileset->render(x * _tileSize + xOffset, y * _tileSize + yOffset, t.spritesheetRect.w, t.spritesheetRect.h);
        }
    }
}

void Level::setTilemap(std::vector<std::vector<Tile>> tilemap) {
    _tilemap = tilemap;
    _tilemapHeight = _tilemap.size();
    if(_tilemap.size() > 0) {
        _tilemapWidth = _tilemap[0].size();
    }
}

void Level::setLightMap(std::shared_ptr<FloatingPointLightMap> lMap) {
    _lMap = lMap;
}

void Level::setTileSize(int tileSize) {
    _tileSize = tileSize;
}

void Level::setTileAt(int x, int y, Tile tile) {
    if(x >= 0 && x < _tilemapWidth && y >= 0 && y < _tilemapHeight) {
        _tilemap[y][x] = tile;
    }
}

void Level::setTileset(Spritesheet* tileset) {
    _tileset = tileset;
}

void Level::setPlayerId(entt::entity player) {
    _playerId = player;
}

Tile Level::getTileAt(int x, int y) {
    if(x >= 0 && x < _tilemapWidth && y >= 0 && y < _tilemapHeight) {
        return _tilemap[y][x];
    }
    return Tile{TileType::NOVAL, {0, 0, 0, 0}};
}

int Level::getTileSize() {
    return _tileSize;
}

int Level::getTilemapWidth() {
    return _tilemapWidth;
}

int Level::getTilemapHeight() {
    return _tilemapHeight;
}

entt::entity Level::getPlayerId() {
    return _playerId;
}

std::shared_ptr<FloatingPointLightMap> Level::getLightMap() {
    return _lMap;
}