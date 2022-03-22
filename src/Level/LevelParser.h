#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H

#include "Level.h"
#include "tileson.hpp"

class LevelParser {
public:
    LevelParser() = default;
    ~LevelParser() = default;

    static Level parseLevel(tson::Map* map);

private:

};

#endif