#ifndef LEVEL_H
#define LEVEL_H

#include "Tile.h"
#include "Spritesheet.h"
#include "vec2.h"
#include "LightMap.h"

#include <vector>
#include <cstdint>
#include <memory>

using Entity = std::uint16_t;

class Level {
public:
    Level() = default;
    ~Level() = default;

    void allocateTilemap(int width, int height);
    void spawnPrefabs();
    void render(int xOffset, int yOffset);

    void setTilemap(std::vector<std::vector<Tile>> tilemap);
    void setLightMap(std::shared_ptr<LightMap> lightMap);
    void setTileSize(int tileSize);
    void setTileAt(int x, int y, Tile tile);
    void setTileset(Spritesheet* tileset);
    void setPlayerId(Entity player);
    void addPrefab(Entity entity);

    Tile getTileAt(int x, int y);
    int getTileSize();
    int getTilemapWidth();
    int getTilemapHeight();
    Entity getPlayerId();
    LightMap* getLightMap();

private:
    std::shared_ptr<LightMap> _lMap = nullptr;
    std::vector<std::vector<Tile>> _tilemap;
    int _tilemapWidth = 0;
    int _tilemapHeight = 0;
    int _tileSize = 16;
    Spritesheet* _tileset = nullptr;

    std::vector<Entity> _prefabs;
    Entity _playerId;

};

#endif