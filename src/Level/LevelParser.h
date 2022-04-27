#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H

#include "Level.h"
#include "tileson.hpp"
#include "Tile.h"

class LevelParser {
public:
    LevelParser() = default;
    ~LevelParser() = default;

    static Level parseLevel(tson::Map* map);

private:
    static Plane getLayerPlane(std::string layerName);
    static TileType getTileType(std::string type);

};

#endif