#ifndef TILEMAP_H
#define TILEMAP_H

#include "Spritesheet.h"

#include <vector>
#include <string>
#include <SDL.h>

class Tilemap {
public:
    Tilemap() = default;
    ~Tilemap() = default;

    // Allocate tilemap using tile dimensions
    void allocate(int w, int h);

    void setTile(int x, int y, SDL_Rect spritesheetRect);
    void setTileset(Spritesheet* spritesheet);
    void setGameSize(int w, int h);

    int getTilemapWidth();
    int getTilemapHeight();
    SDL_Rect getTile(int x, int y);

private:
    std::vector<std::vector<SDL_Rect>> _tilemap;
    int _tilemapWidth = 0;
    int _tilemapHeight = 0;
    Spritesheet* _tileset = nullptr;

    // Game width and height used for rendering purposes
    int _gameWidth = 0;
    int _gameHeight = 0;

};

#endif