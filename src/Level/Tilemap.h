#ifndef TILEMAP_H
#define TILEMAP_H

#include "Spritesheet.h"
#include "Tile.h"

#include <vector>
#include <string>
#include <cstdint>
#include <list>

using Entity = std::uint16_t;

class Tilemap {
public:
    Tilemap() = default;
    ~Tilemap() = default;

    // Allocate tilemap using tile dimensions
    void allocate(int w, int h);
    void render(int xOffset, int yOffset);

    void setTileSize(int tileSize);
    void setTile(int x, int y, Tile tile);
    void setTileset(Spritesheet* spritesheet);
    void setGameSize(int w, int h);

    int getTilemapWidth();
    int getTilemapHeight();
    Tile getTile(int x, int y);

private:
    std::vector<std::vector<Tile>> _tilemap;
    int _tilemapWidth = 0;
    int _tilemapHeight = 0;
    Spritesheet* _tileset = nullptr;
    int _tileSize = 0;

    // Game width and height used for rendering purposes
    int _gameWidth = 0;
    int _gameHeight = 0;

};

#endif