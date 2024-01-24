#pragma once

#include "Tile.h"
#include "Spritesheet.h"
#include "FloatingPointLightMap.h"

#include <vector>
#include <cstdint>
#include <memory>
#include <entt/entity/registry.hpp>

class Level {
public:
    Level() = default;
    ~Level() = default;

    void allocateTilemap(int width, int height);
    void render(int xOffset, int yOffset);

    void setTilemap(std::vector<std::vector<Tile>> tilemap);
    void setLightMap(std::shared_ptr<FloatingPointLightMap> lightMap);
    void setTileSize(int tileSize);
    void setTileAt(int x, int y, Tile tile);
    void setTileset(Spritesheet* tileset);
    void setPlayerId(entt::entity player);

    Tile getTileAt(int x, int y);
    int getTileSize();
    int getTilemapWidth();
    int getTilemapHeight();
    entt::entity getPlayerId();
    std::shared_ptr<FloatingPointLightMap> getLightMap();

private:
    std::shared_ptr<FloatingPointLightMap> _lMap = nullptr;
    std::vector<std::vector<Tile>> _tilemap;
    int _tilemapWidth = 0;
    int _tilemapHeight = 0;
    int _tileSize = 16;
    Spritesheet* _tileset = nullptr;

    entt::entity _playerId;

};